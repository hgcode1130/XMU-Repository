package com.re0hg.backend.dto;

import lombok.Data;
import java.util.List;

@Data
public class ExcelImportResultDTO {
  private int totalRows;
  private int successfulImports;
  private int failedImports;
  private List<ImportedCourseDTO> importedCourses;
  private List<ImportErrorDTO> errors;
  private SummaryDTO summary;

  @Data
  public static class ImportedCourseDTO {
    private Long courseId;
    private String courseName;
    private int rowNumber;
  }

  @Data
  public static class ImportErrorDTO {
    private int rowNumber;
    private String courseName;
    private String error;
  }

  @Data
  public static class SummaryDTO {
    private String totalProcessingTime;
  }
}