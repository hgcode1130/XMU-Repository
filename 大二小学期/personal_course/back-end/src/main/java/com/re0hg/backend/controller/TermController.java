package com.re0hg.backend.controller;

import lombok.extern.slf4j.Slf4j;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.re0hg.backend.pojo.PageBean;
import com.re0hg.backend.pojo.Result;
import com.re0hg.backend.pojo.Term;
import com.re0hg.backend.service.TermService;
import com.re0hg.backend.utils.JwtUtils;

import io.jsonwebtoken.Claims;
import jakarta.servlet.http.HttpServletRequest;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@RestController
@RequestMapping("/api")
@Slf4j
public class TermController {

  @Autowired
  private TermService termService;

  /**
   * 获取所有学期 (分页)
   * GET /api/terms?page=0&size=10
   */
  @GetMapping("/terms")
  public Result getTermsWithPagination(
      @RequestParam(defaultValue = "0") int page,
      @RequestParam(defaultValue = "10") int size,
      HttpServletRequest request) {

    try {
      log.info("获取学期列表 - 页码: {}, 每页大小: {}", page, size);

      // 从JWT token中获取用户ID
      Long userId = getCurrentUserId(request);

      if (userId == null) {
        return Result.error(401, "用户未认证");
      }

      // 参数验证
      if (page < 0) {
        return Result.error(400, "页码不能小于0");
      }
      if (size <= 0 || size > 100) {
        return Result.error(400, "每页大小必须在1-100之间");
      }

      // 获取分页数据
      PageBean<Term> pageBean = termService.getUserTermsWithPagination(userId, page, size);

      log.info("成功获取学期列表 - 总数: {}, 当前页: {}", pageBean.getTotalElements(), page);
      return Result.success(200, "查询成功", pageBean);

    } catch (Exception e) {
      log.error("获取学期列表失败: ", e);
      return Result.error(500, "系统内部错误");
    }
  }

  /**
   * 从请求中获取当前用户ID
   * 通过解析JWT token获取用户信息
   * 注意：这里使用"token"请求头，与LoginCheckInterceptor保持一致
   */
  private Long getCurrentUserId(HttpServletRequest request) {
    try {
      // 1. 从请求头中获取token字段（与LoginCheckInterceptor保持一致）
      String token = request.getHeader("token");

      // 2. 检查token是否存在
      if (token == null || token.trim().isEmpty()) {
        log.warn("请求头中缺少token信息");
        return null;
      }

      // 3. 解析JWT token
      Claims claims = JwtUtils.parseJWT(token);

      // 4. 从claims中获取用户ID
      Object idObj = claims.get("id");
      if (idObj == null) {
        log.warn("JWT token中缺少用户ID信息");
        return null;
      }

      // 5. 转换为Long类型
      Long userId;
      if (idObj instanceof Integer) {
        userId = ((Integer) idObj).longValue();
      } else if (idObj instanceof Long) {
        userId = (Long) idObj;
      } else if (idObj instanceof String) {
        userId = Long.parseLong((String) idObj);
      } else {
        log.warn("JWT token中用户ID格式不正确: {}", idObj.getClass());
        return null;
      }

      log.debug("成功解析用户ID: {}", userId);
      return userId;

    } catch (Exception e) {
      log.error("解析JWT token失败: ", e);
      return null;
    }
  }
}