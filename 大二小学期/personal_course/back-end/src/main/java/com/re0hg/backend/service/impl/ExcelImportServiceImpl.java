package com.re0hg.backend.service.impl;

import com.re0hg.backend.dto.ExcelImportResultDTO;
import com.re0hg.backend.mapper.CourseMapper;
import com.re0hg.backend.mapper.ScheduleEntryMapper;
import com.re0hg.backend.pojo.Course;
import com.re0hg.backend.pojo.ScheduleEntry;
import com.re0hg.backend.pojo.Term;
import com.re0hg.backend.service.ExcelImportService;
import com.re0hg.backend.utils.ExcelUtils;
import lombok.extern.slf4j.Slf4j;
import org.apache.poi.ss.usermodel.Workbook;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.multipart.MultipartFile;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

@Service
@Slf4j
public class ExcelImportServiceImpl implements ExcelImportService {

  @Autowired
  private CourseMapper courseMapper;

  @Autowired
  private ScheduleEntryMapper scheduleEntryMapper;

  @Override
  @Transactional
  public ExcelImportResultDTO importCoursesFromExcel(MultipartFile file, Long termId, Long userId) {
    long startTime = System.currentTimeMillis();

    ExcelImportResultDTO result = new ExcelImportResultDTO();
    result.setImportedCourses(new ArrayList<>());
    result.setErrors(new ArrayList<>());

    try {
      // 1. 验证学期权限
      if (!courseMapper.isTermOwnedByUser(termId, userId)) {
        throw new RuntimeException("无权限访问此学期或学期不存在");
      }

      // 2. 解析Excel文件
      Workbook workbook = ExcelUtils.getWorkbook(file);
      List<Map<String, Object>> dataList = ExcelUtils.parseExcelData(workbook);
      workbook.close();

      result.setTotalRows(dataList.size());

      // 3. 处理每一行数据
      for (Map<String, Object> rowData : dataList) {
        try {
          Course course = processRowData(rowData, termId, userId);

          // 添加成功记录
          ExcelImportResultDTO.ImportedCourseDTO importedCourse = new ExcelImportResultDTO.ImportedCourseDTO();
          importedCourse.setCourseId(course.getId());
          importedCourse.setCourseName(course.getName());
          importedCourse.setRowNumber((Integer) rowData.get("rowNumber"));
          result.getImportedCourses().add(importedCourse);

        } catch (Exception e) {
          log.warn("导入第{}行数据失败: {}", rowData.get("rowNumber"), e.getMessage());

          // 添加错误记录
          ExcelImportResultDTO.ImportErrorDTO error = new ExcelImportResultDTO.ImportErrorDTO();
          error.setRowNumber((Integer) rowData.get("rowNumber"));
          error.setCourseName((String) rowData.get("课程名称"));
          error.setError(e.getMessage());
          result.getErrors().add(error);
        }
      }

      // 4. 计算统计信息
      result.setSuccessfulImports(result.getImportedCourses().size());
      result.setFailedImports(result.getErrors().size());

      // 5. 生成处理时间
      long endTime = System.currentTimeMillis();
      ExcelImportResultDTO.SummaryDTO summary = new ExcelImportResultDTO.SummaryDTO();
      summary.setTotalProcessingTime((endTime - startTime) / 1000.0 + "秒");
      result.setSummary(summary);

      log.info("Excel导入完成 - 总计:{}行, 成功:{}行, 失败:{}行",
          result.getTotalRows(), result.getSuccessfulImports(), result.getFailedImports());

      return result;

    } catch (Exception e) {
      log.error("Excel导入失败: ", e);
      throw new RuntimeException("Excel导入失败: " + e.getMessage());
    }
  }

  private Course processRowData(Map<String, Object> rowData, Long termId, Long userId) {
    // 1. 验证必要字段
    String courseName = getStringValue(rowData, "课程名称");
    if (courseName == null || courseName.trim().isEmpty()) {
      throw new RuntimeException("课程名称不能为空");
    }

    // 2. 创建课程对象
    Course course = new Course();
    course.setName(courseName.trim());
    course.setTeachers(getStringValue(rowData, "教师"));
    course.setMainTeacherEmail(getStringValue(rowData, "主讲老师邮箱"));
    course.setCourseGroupChatId(getStringValue(rowData, "课程群号"));
    course.setNote(getStringValue(rowData, "备注"));

    // 处理标签
    String tagStr = getStringValue(rowData, "标签");
    if ("选修".equals(tagStr)) {
      course.setTag(0);
    } else if ("必修".equals(tagStr) || tagStr == null || tagStr.trim().isEmpty()) {
      course.setTag(1);
    } else {
      throw new RuntimeException("标签必须为'必修'或'选修'");
    }

    // 设置学期
    Term term = new Term();
    term.setId(termId);
    course.setTerm(term);

    // 3. 验证邮箱格式
    if (course.getMainTeacherEmail() != null && !course.getMainTeacherEmail().trim().isEmpty()) {
      if (!isValidEmail(course.getMainTeacherEmail())) {
        throw new RuntimeException("主讲老师邮箱格式不正确");
      }
    }

    // 4. 创建课程
    courseMapper.createCourse(course, userId);

    // 5. 创建排程
    ScheduleEntry scheduleEntry = new ScheduleEntry();
    scheduleEntry.setLocation(getStringValue(rowData, "上课地点"));

    // 验证和设置星期
    Integer dayOfWeek = getIntegerValue(rowData, "星期");
    if (dayOfWeek == null || dayOfWeek < 1 || dayOfWeek > 7) {
      throw new RuntimeException("星期必须为1-7的整数");
    }
    scheduleEntry.setDayOfWeek(dayOfWeek);

    // 验证和设置节次
    Integer startPeriod = getIntegerValue(rowData, "开始节次");
    Integer endPeriod = getIntegerValue(rowData, "结束节次");
    if (startPeriod == null || startPeriod < 1 || startPeriod > 12) {
      throw new RuntimeException("开始节次必须为1-12的整数");
    }
    if (endPeriod == null || endPeriod < startPeriod || endPeriod > 12) {
      throw new RuntimeException("结束节次必须大于等于开始节次且不超过12");
    }
    scheduleEntry.setStartPeriod(startPeriod);
    scheduleEntry.setEndPeriod(endPeriod);

    // 验证和设置周次
    Integer startWeek = getIntegerValue(rowData, "开始周");
    Integer endWeek = getIntegerValue(rowData, "结束周");
    if (startWeek == null || startWeek < 1 || startWeek > 20) {
      throw new RuntimeException("开始周必须为1-20的整数");
    }
    if (endWeek == null || endWeek < startWeek || endWeek > 20) {
      throw new RuntimeException("结束周必须大于等于开始周且不超过20");
    }
    scheduleEntry.setStartWeek(startWeek);
    scheduleEntry.setEndWeek(endWeek);

    scheduleEntry.setCourse(course);
    scheduleEntryMapper.createScheduleEntry(scheduleEntry);

    return course;
  }

  private String getStringValue(Map<String, Object> rowData, String key) {
    Object value = rowData.get(key);
    if (value == null) {
      return null;
    }
    String str = value.toString().trim();
    return str.isEmpty() ? null : str;
  }

  private Integer getIntegerValue(Map<String, Object> rowData, String key) {
    Object value = rowData.get(key);
    if (value == null) {
      return null;
    }

    if (value instanceof Number) {
      return ((Number) value).intValue();
    }

    try {
      return Integer.parseInt(value.toString().trim());
    } catch (NumberFormatException e) {
      throw new RuntimeException(key + "必须为数字");
    }
  }

  private boolean isValidEmail(String email) {
    return email.matches("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
  }
}