package com.re0hg.backend.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import com.re0hg.backend.pojo.Result;
import com.re0hg.backend.pojo.User;
import com.re0hg.backend.service.UserService;

import lombok.extern.slf4j.Slf4j;

@Slf4j
@RestController
public class RegisterController {
  @Autowired
  private UserService userService;

  /**
   * 用户注册
   * 
   * @param user 包含用户名、密码、邮箱的用户对象
   * @return 注册结果
   */
  @PostMapping("/api/auth/register")
  public Result register(@RequestBody User user) { 
    log.info("用户注册: {}", user.getUsername());

    // 参数校验
    if (user.getUsername() == null || user.getPassword() == null || user.getEmail() == null) {
      // 对于错误的请求参数，返回 400 Bad Request
      return Result.error(400,"用户名、密码或邮箱不能为空");
    }

    // 设置默认角色和启用状态
    user.setRole("USER");
    user.setIsEnabled(true);

    try {
      // 调用服务层方法进行注册
      User registeredUser = userService.register(user);
      // 2. 注册成功，返回 201 Created 状态码
      return Result.success(201,"注册成功", registeredUser);
    } catch (RuntimeException e) { // 捕获业务异常
      log.error("注册失败: {}", e.getMessage());
      // 3. 用户已存在，返回 409 Conflict 状态码
      return Result.error(409,"注册失败：" + e.getMessage());
    }
  }
}
