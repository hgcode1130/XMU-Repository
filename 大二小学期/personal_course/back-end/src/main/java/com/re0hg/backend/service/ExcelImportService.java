package com.re0hg.backend.service;

import com.re0hg.backend.dto.ExcelImportResultDTO;
import org.springframework.web.multipart.MultipartFile;

public interface ExcelImportService {
  ExcelImportResultDTO importCoursesFromExcel(MultipartFile file, Long termId, Long userId);
}