package com.re0hg.backend.pojo;

import lombok.Data;

@Data
public class LoginRequest {
  private String username;
  private String password;
}