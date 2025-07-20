package com.re0hg.backend.dto;

import lombok.Data;

/**
 * 更新用户状态请求DTO
 * 
 * @author re0hg
 * @version 1.0
 * @date 2025/7/2
 */
@Data
public class UpdateUserStatusDTO {
  /**
   * 账户状态 - true: 启用, false: 禁用
   */
  private Boolean isEnabled;
}