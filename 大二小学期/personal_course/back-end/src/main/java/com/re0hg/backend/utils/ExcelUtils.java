package com.re0hg.backend.utils;

import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.springframework.web.multipart.MultipartFile;

import lombok.extern.slf4j.Slf4j;

import java.io.IOException;
import java.util.*;

@Slf4j
public class ExcelUtils {

  private static final Set<String> REQUIRED_HEADERS = Set.of(
      "课程名称", "星期", "开始节次", "结束节次", "开始周", "结束周");

  private static final Set<String> ALL_HEADERS = Set.of(
      "课程名称", "教师", "主讲老师邮箱", "课程群号", "标签",
      "上课地点", "星期", "开始节次", "结束节次", "开始周", "结束周", "备注");

  public static Workbook getWorkbook(MultipartFile file) throws IOException {
    String fileName = file.getOriginalFilename();
    if (fileName == null) {
      throw new IllegalArgumentException("文件名不能为空");
    }

    if (fileName.endsWith(".xlsx")) {
      return new XSSFWorkbook(file.getInputStream());
    } else if (fileName.endsWith(".xls")) {
      return new HSSFWorkbook(file.getInputStream());
    } else {
      throw new IllegalArgumentException("不支持的文件格式，请使用 .xlsx 或 .xls 文件");
    }
  }

  public static List<Map<String, Object>> parseExcelData(Workbook workbook) {
    Sheet sheet = workbook.getSheetAt(0);
    List<Map<String, Object>> dataList = new ArrayList<>();

    // 读取表头
    Row headerRow = sheet.getRow(0);
    if (headerRow == null) {
      throw new IllegalArgumentException("Excel文件表头不能为空");
    }

    List<String> headers = new ArrayList<>();
    for (Cell cell : headerRow) {
      headers.add(getCellStringValue(cell).trim());
    }

    // 验证必要表头
    validateHeaders(headers);

    // 读取数据行
    for (int i = 1; i <= sheet.getLastRowNum(); i++) {
      Row row = sheet.getRow(i);
      if (row == null || isEmptyRow(row)) {
        continue;
      }

      Map<String, Object> rowData = new HashMap<>();
      rowData.put("rowNumber", i + 1); // Excel行号（从1开始）

      for (int j = 0; j < headers.size() && j < row.getLastCellNum(); j++) {
        Cell cell = row.getCell(j);
        String header = headers.get(j);
        Object value = getCellValue(cell);
        rowData.put(header, value);
      }

      dataList.add(rowData);
    }

    return dataList;
  }

  private static void validateHeaders(List<String> headers) {
    Set<String> headerSet = new HashSet<>(headers);

    for (String required : REQUIRED_HEADERS) {
      if (!headerSet.contains(required)) {
        throw new IllegalArgumentException("缺少必要的表头字段: " + required);
      }
    }
  }

  private static boolean isEmptyRow(Row row) {
    for (Cell cell : row) {
      if (cell != null && cell.getCellType() != CellType.BLANK) {
        String value = getCellStringValue(cell).trim();
        if (!value.isEmpty()) {
          return false;
        }
      }
    }
    return true;
  }

  private static Object getCellValue(Cell cell) {
    if (cell == null) {
      return null;
    }

    return switch (cell.getCellType()) {
      case STRING -> cell.getStringCellValue().trim();
      case NUMERIC -> {
        if (DateUtil.isCellDateFormatted(cell)) {
          yield cell.getDateCellValue();
        } else {
          double numericValue = cell.getNumericCellValue();
          // 如果是整数，返回Long；否则返回Double
          if (numericValue == Math.floor(numericValue)) {
            yield (long) numericValue;
          } else {
            yield numericValue;
          }
        }
      }
      case BOOLEAN -> cell.getBooleanCellValue();
      case FORMULA -> cell.getStringCellValue().trim();
      default -> null;
    };
  }

  private static String getCellStringValue(Cell cell) {
    Object value = getCellValue(cell);
    return value != null ? value.toString() : "";
  }

  public static Workbook createTemplateWorkbook() {
    try {
      log.debug("开始创建Excel模板工作簿");

      Workbook workbook = new XSSFWorkbook();
      Sheet sheet = workbook.createSheet("课程数据");

      log.debug("工作表创建成功");

      // 创建表头
      Row headerRow = sheet.createRow(0);
      String[] headers = {
          "课程名称", "教师", "主讲老师邮箱", "课程群号", "标签",
          "上课地点", "星期", "开始节次", "结束节次", "开始周", "结束周", "备注"
      };

      for (int i = 0; i < headers.length; i++) {
        Cell cell = headerRow.createCell(i);
        cell.setCellValue(headers[i]);
      }

      log.debug("表头创建成功，共{}列", headers.length);

      // 创建示例数据
      Row exampleRow = sheet.createRow(1);
      Object[] exampleData = {
          "高等数学", "张三,李四", "zhangsan@xmu.edu.cn", "123456789", "必修",
          "教学楼A-101", 1, 1, 2, 1, 16, "重要基础课程"
      };

      for (int i = 0; i < exampleData.length; i++) {
        Cell cell = exampleRow.createCell(i);
        if (exampleData[i] instanceof Number) {
          cell.setCellValue(((Number) exampleData[i]).doubleValue());
        } else {
          cell.setCellValue(exampleData[i].toString());
        }
      }

      log.debug("示例数据创建成功");

      // 设置列宽
      try {
        for (int i = 0; i < headers.length; i++) {
          sheet.autoSizeColumn(i);
        }
        log.debug("列宽自动调整完成");
      } catch (Exception e) {
        log.warn("自动调整列宽失败，使用默认宽度: ", e);
      }

      log.debug("Excel模板工作簿创建完成");
      return workbook;

    } catch (Exception e) {
      log.error("创建Excel模板工作簿时发生异常: ", e);
      throw new RuntimeException("创建Excel模板失败", e);
    }
  }
}