package com.re0hg.backend.dto;

import java.util.List;
import lombok.Data;

@Data
public class CourseDTO {
  private Long termId;
  private String name;
  private String teachers;
  private String mainTeacherEmail;
  private String courseGroupChatId;
  private Integer tag;
  private String note;
  private List<ScheduleEntryDTO> scheduleEntries;

  @Data
  public static class ScheduleEntryDTO {
    private String location;
    private Integer dayOfWeek;
    private Integer startPeriod;
    private Integer endPeriod;
    private Integer startWeek;
    private Integer endWeek;
  }
}