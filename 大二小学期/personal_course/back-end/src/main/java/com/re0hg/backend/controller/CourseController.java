package com.re0hg.backend.controller;

import lombok.extern.slf4j.Slf4j;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.poi.ss.usermodel.Workbook;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import com.re0hg.backend.dto.CourseDTO;
import com.re0hg.backend.dto.ExcelImportResultDTO;
import com.re0hg.backend.pojo.Course;
import com.re0hg.backend.pojo.PageBean;
import com.re0hg.backend.pojo.Result;
import com.re0hg.backend.pojo.ScheduleEntry;
import com.re0hg.backend.pojo.Term;
import com.re0hg.backend.service.CourseService;
import com.re0hg.backend.service.ExcelImportService;
import com.re0hg.backend.utils.ExcelUtils;
import com.re0hg.backend.utils.JwtUtils;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Slf4j
@RestController
@RequestMapping("/api")
public class CourseController {
  @Autowired
  private CourseService courseService;

  @Autowired
  private ExcelImportService excelImportService;

  /**
   * Excel 导入课程
   * POST /api/import/excel
   */
  @PostMapping("/import/excel")
  public Result importExcelCourses(
      @RequestParam("file") MultipartFile file,
      @RequestParam("termId") Long termId,
      HttpServletRequest request) {

    try {
      log.info("Excel导入课程 - 学期ID: {}, 文件名: {}", termId, file.getOriginalFilename());

      // 验证文件
      if (file.isEmpty()) {
        return Result.error(400, "上传的文件不能为空");
      }

      // 验证文件大小（10MB）
      if (file.getSize() > 10 * 1024 * 1024) {
        return Result.error(400, "文件大小不能超过10MB");
      }

      // 验证文件类型
      String fileName = file.getOriginalFilename();
      if (fileName == null || (!fileName.endsWith(".xlsx") && !fileName.endsWith(".xls"))) {
        return Result.error(400, "只支持.xlsx和.xls格式的Excel文件");
      }

      // 获取用户信息
      Long userId = JwtUtils.getCurrentUserId(request);
      if (userId == null) {
        return Result.error(401, "用户未认证");
      }

      // 执行导入
      ExcelImportResultDTO result = excelImportService.importCoursesFromExcel(file, termId, userId);

      // 根据结果返回不同的状态码
      if (result.getFailedImports() == 0) {
        return Result.success(200, "Excel导入成功", result);
      } else if (result.getSuccessfulImports() > 0) {
        return Result.success(207, "Excel导入部分成功，存在错误数据", result);
      } else {
        return Result.error(400, "Excel导入失败，所有数据都存在错误", result);
      }

    } catch (Exception e) {
      log.error("Excel导入失败: ", e);
      return Result.error(500, "Excel导入失败: " + e.getMessage());
    }
  }

  /**
   * 下载Excel模板
   * GET /api/import/excel/template
   */
  @GetMapping("/import/excel/template")
  public void downloadTemplate(HttpServletResponse response) {
    try {
      log.info("开始下载Excel模板");

      // 调试信息：打印是否成功进入方法
      log.debug("创建 Excel 模板工作簿...");

      Workbook workbook = null;
      try {
        workbook = ExcelUtils.createTemplateWorkbook();
        log.debug("工作簿创建成功，工作表数量: {}", workbook.getNumberOfSheets());
      } catch (Exception e) {
        log.error("创建工作簿时发生异常: ", e);
        response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        return;
      }

      // 设置响应头
      try {
        response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
        response.setHeader("Content-Disposition", "attachment; filename=\"course_template.xlsx\"");
        response.setHeader("Cache-Control", "no-cache");
        response.setHeader("Pragma", "no-cache");
        response.setDateHeader("Expires", 0);
        log.debug("响应头设置完毕");
      } catch (Exception e) {
        log.error("设置响应头时发生异常: ", e);
        workbook.close();
        response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        return;
      }

      // 调试信息：输出响应头设置
      log.debug("响应头设置完毕，准备写入文件...");

      try {
        // 调试信息：检查输出流是否正常
        log.debug("准备写入响应流...");
        workbook.write(response.getOutputStream());
        response.getOutputStream().flush();
        log.debug("写入响应流成功");
      } catch (IOException e) {
        log.error("写入响应流失败: ", e);
        response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        return;
      } finally {
        // 调试信息：关闭工作簿
        try {
          workbook.close();
          log.debug("工作簿关闭成功");
        } catch (IOException e) {
          log.warn("关闭工作簿时发生异常: ", e);
        }
      }

      log.info("Excel模板下载完成");

    } catch (Exception e) {
      // 捕获任何异常并输出详细日志
      log.error("下载模板失败: ", e);
      response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
    }
  }

  /**
   * 创建课程
   * POST /api/courses
   */
  @PostMapping("/courses")
  public Result createCourse(@RequestBody CourseDTO courseDTO, HttpServletRequest request) {
    try {
      log.info("创建课程 - 名称: {}, 学期ID: {}", courseDTO.getName(), courseDTO.getTermId());

      // 从JWT获取用户信息
      Long userId = JwtUtils.getCurrentUserId(request);
      if (userId == null) {
        return Result.error(401, "用户未认证");
      }

      // 将DTO转换为实体
      Course course = new Course();
      course.setName(courseDTO.getName());
      course.setTeachers(courseDTO.getTeachers());
      course.setMainTeacherEmail(courseDTO.getMainTeacherEmail());
      course.setCourseGroupChatId(courseDTO.getCourseGroupChatId());
      course.setTag(courseDTO.getTag());
      course.setNote(courseDTO.getNote());

      // 设置Term
      Term term = new Term();
      term.setId(courseDTO.getTermId());
      course.setTerm(term);

      // 转换排程
      if (courseDTO.getScheduleEntries() != null) {
        List<ScheduleEntry> entries = new ArrayList<>();
        for (CourseDTO.ScheduleEntryDTO entryDTO : courseDTO.getScheduleEntries()) {
          ScheduleEntry entry = new ScheduleEntry();
          entry.setLocation(entryDTO.getLocation());
          entry.setDayOfWeek(entryDTO.getDayOfWeek());
          entry.setStartPeriod(entryDTO.getStartPeriod());
          entry.setEndPeriod(entryDTO.getEndPeriod());
          entry.setStartWeek(entryDTO.getStartWeek());
          entry.setEndWeek(entryDTO.getEndWeek());
          entries.add(entry);
        }
        course.setScheduleEntries(entries);
      }

      // 调用服务层创建课程
      try {
        Course createdCourse = courseService.createCourse(course, userId);
        log.info("成功创建课程 - 课程ID: {}, 名称: {}", createdCourse.getId(), createdCourse.getName());
        return Result.success(201, "课程创建成功", createdCourse);
      } catch (RuntimeException e) {
        // 处理业务异常
        if (e.getMessage().contains("无权限")) {
          return Result.error(403, e.getMessage());
        } else {
          return Result.error(400, e.getMessage());
        }
      }
    } catch (Exception e) {
      log.error("创建课程失败: ", e);
      return Result.error(500, "系统内部错误");
    }
  }

  // /**
  // * 从请求中获取当前用户ID
  // * 通过解析JWT token获取用户信息
  // */
  // private Long getCurrentUserId(HttpServletRequest request) {
  // try {
  // // 1. 获取请求头中的token
  // String token = request.getHeader("token");
  //
  // if (token == null || token.trim().isEmpty()) {
  // log.warn("请求头中缺少token信息");
  // return null;
  // }
  //
  // // 2. 解析JWT token
  // Claims claims = JwtUtils.parseJWT(token);
  //
  // // 3. 从claims中获取用户ID
  // Object idObj = claims.get("id");
  // if (idObj == null) {
  // log.warn("JWT token中缺少用户ID信息");
  // return null;
  // }
  //
  // // 4. 转换为Long类型
  // Long userId;
  // if (idObj instanceof Integer) {
  // userId = ((Integer) idObj).longValue();
  // } else if (idObj instanceof Long) {
  // userId = (Long) idObj;
  // } else if (idObj instanceof String) {
  // userId = Long.parseLong((String) idObj);
  // } else {
  // log.warn("JWT token中用户ID格式不正确: {}", idObj.getClass());
  // return null;
  // }
  //
  // log.debug("成功解析用户ID: {}", userId);
  // return userId;
  // } catch (Exception e) {
  // log.error("解析JWT token失败: ", e);
  // return null;
  // }
  // }

  /**
   * 获取指定学期的所有课程 (分页)
   * GET /api/terms/{termId}/courses
   */
  @GetMapping("/terms/{termId}/courses")
  public Result getCoursesForTerm(
      @PathVariable Long termId,
      @RequestParam(defaultValue = "0") int page,
      @RequestParam(defaultValue = "20") int size,
      HttpServletRequest request) {

    try {
      log.info("获取学期课程 - 学期ID: {}, 页码: {}, 每页大小: {}", termId, page, size);

      // 从JWT获取用户信息
      Long userId = JwtUtils.getCurrentUserId(request);
      if (userId == null) {
        return Result.error(401, "用户未认证");
      }

      // 调用服务层获取课程
      try {
        PageBean<Course> pageBean = courseService.getCoursesForTermWithPagination(
            termId, userId, page, size);

        return Result.success(200, "查询成功", pageBean);
      } catch (RuntimeException e) {
        // 处理业务异常
        if (e.getMessage().contains("无权限")) {
          return Result.error(403, e.getMessage());
        } else {
          return Result.error(400, e.getMessage());
        }
      }
    } catch (Exception e) {
      log.error("获取学期课程失败: ", e);
      return Result.error(500, "系统内部错误");
    }
  }

  /**
   * 高级课程搜索 (多条件筛选与分页)
   * GET /api/courses/search
   */
  @GetMapping("/courses/search")
  public Result searchCourses(
      @RequestParam(required = false) Long termId,
      @RequestParam(required = false) String name,
      @RequestParam(required = false) String teacher,
      @RequestParam(required = false) Integer tag,
      @RequestParam(required = false) Integer dayOfWeek,
      @RequestParam(defaultValue = "0") int page,
      @RequestParam(defaultValue = "10") int size,
      HttpServletRequest request) {

    try {
      log.info("高级课程搜索 - termId: {}, name: {}, teacher: {}, tag: {}, dayOfWeek: {}, page: {}, size: {}",
          termId, name, teacher, tag, dayOfWeek, page, size);

      // 从JWT获取用户信息
      Long userId = JwtUtils.getCurrentUserId(request);
      if (userId == null) {
        return Result.error(401, "用户未认证");
      }

      // 调用服务层搜索课程
      try {
        PageBean<Course> pageBean = courseService.searchCoursesWithPagination(
            termId, name, teacher, tag, dayOfWeek, userId, page, size);

        return Result.success(200, "查询成功", pageBean);
      } catch (RuntimeException e) {
        return Result.error(400, e.getMessage());
      }
    } catch (Exception e) {
      log.error("课程搜索失败: ", e);
      return Result.error(500, "系统内部错误");
    }
  }

  // PUT /api/courses/{courseId}
  @PutMapping("/courses/{courseId}")
  public Result updateCourse(@PathVariable Long courseId, @RequestBody CourseDTO courseDTO,
      HttpServletRequest request) {
    try {
      log.info("更新课程 - 课程ID: {}, 名称: {}", courseId, courseDTO.getName());

      // 从JWT获取用户信息
      Long userId = JwtUtils.getCurrentUserId(request);
      if (userId == null) {
        return Result.error(401, "用户未认证");
      }

      // 将DTO转换为实体
      Course course = new Course();
      course.setId(courseId);
      course.setName(courseDTO.getName());
      course.setTeachers(courseDTO.getTeachers());
      course.setMainTeacherEmail(courseDTO.getMainTeacherEmail());
      course.setCourseGroupChatId(courseDTO.getCourseGroupChatId());
      course.setTag(courseDTO.getTag());
      course.setNote(courseDTO.getNote());

      // 设置Term
      Term term = new Term();
      term.setId(courseDTO.getTermId());
      course.setTerm(term);

      // 转换排程
      if (courseDTO.getScheduleEntries() != null) {
        List<ScheduleEntry> entries = new ArrayList<>();
        for (CourseDTO.ScheduleEntryDTO entryDTO : courseDTO.getScheduleEntries()) {
          ScheduleEntry entry = new ScheduleEntry();
          entry.setLocation(entryDTO.getLocation());
          entry.setDayOfWeek(entryDTO.getDayOfWeek());
          entry.setStartPeriod(entryDTO.getStartPeriod());
          entry.setEndPeriod(entryDTO.getEndPeriod());
          entry.setStartWeek(entryDTO.getStartWeek());
          entry.setEndWeek(entryDTO.getEndWeek());
          entries.add(entry);
        }
        course.setScheduleEntries(entries);
      }

      // 调用服务层更新课程
      try {
        Course updatedCourse = courseService.updateCourse(courseId, course, userId);
        log.info("成功更新课程 - 课程ID: {}, 名称: {}", updatedCourse.getId(), updatedCourse.getName());
        return Result.success(200, "课程更新成功", updatedCourse);
      } catch (RuntimeException e) {
        // 处理业务异常
        if (e.getMessage().contains("无权限")) {
          return Result.error(403, e.getMessage());
        } else {
          return Result.error(400, e.getMessage());
        }
      }
    } catch (Exception e) {
      log.error("更新课程失败: ", e);
      return Result.error(500, "系统内部错误");
    }
  }

  // delete /api/courses/{courseId}
  @DeleteMapping("/courses/{courseId}")
  public Result deleteCourse(@PathVariable Long courseId, HttpServletRequest request) {
    try {
      log.info("删除课程 - 课程ID: {}", courseId);

      // 从JWT获取用户信息
      Long userId = JwtUtils.getCurrentUserId(request);
      if (userId == null) {
        return Result.error(401, "用户未认证");
      }

      // 调用服务层删除课程
      boolean deleted = courseService.deleteCourse(courseId, userId);
      if (deleted) {
        log.info("成功删除课程 - 课程ID: {}", courseId);
        return Result.success(200, "课程删除成功");
      } else {
        return Result.error(404, "课程不存在或无权限删除");
      }
    } catch (Exception e) {
      log.error("删除课程失败: ", e);
      return Result.error(500, "系统内部错误");
    }
  }
}
