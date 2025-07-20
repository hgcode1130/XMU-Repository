package com.re0hg.backend.controller;

import lombok.extern.slf4j.Slf4j;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
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

  // PUT /api/terms/{termId}
  @PutMapping("/terms/{termId}")
  public Result updateTerm(@PathVariable Long termId, @RequestBody Term term, HttpServletRequest request) {
    try {
      log.info("更新学期信息 - 学期ID: {}", termId);

      // 1. 从JWT token中获取用户ID
      Long userId = getCurrentUserId(request);

      if (userId == null) {
        return Result.error(401, "用户未认证");
      }

      // 2. 调用服务层更新学期
      try {
        Term updatedTerm = termService.updateTerm(termId, term, userId);
        log.info("成功更新学期信息 - 学期ID: {}, 名称: {}", termId, updatedTerm.getName());
        return Result.success(200, "学期更新成功", updatedTerm);
      } catch (RuntimeException e) {
        // 处理业务异常
        if (e.getMessage().equals("学期不存在")) {
          return Result.error(404, e.getMessage());
        } else if (e.getMessage().equals("无权限修改此学期")) {
          return Result.error(403, e.getMessage());
        } else if (e.getMessage().equals("结束日期必须晚于开始日期")) {
          return Result.error(400, e.getMessage());
        } else {
          throw e; // 重新抛出其他运行时异常
        }
      }
    } catch (Exception e) {
      log.error("更新学期信息失败: ", e);
      return Result.error(500, "系统内部错误");
    }
  }

  /// post api/terms
  @PostMapping("/terms")
  public Result createTerm(@RequestBody Term term, HttpServletRequest request) {
    try{
      log.info("创建学期 - 名称: {}", term.getName());

      //从JWT获取用户信息
      Long userId = getCurrentUserId(request);
      if(userId == null){
        return Result.error(401, "用户未认证");
      }

      // 调用服务层创建学期
      try {
        Term createdTerm = termService.createTerm(term, userId);
        log.info("成功创建学期 - 学期ID: {}, 名称: {}", createdTerm.getId(), createdTerm.getName());
        return Result.success(200, "学期创建成功", createdTerm);
      } catch (RuntimeException e) {
        // 处理业务异常
        if (e.getMessage().equals("学期已存在")) {
          return Result.error(400, e.getMessage());
        }
        return Result.error(500, "系统内部错误" + e.getMessage());
      }
    }catch(Exception e){
      return Result.error(500, "系统内部错误" + e.getMessage());
    }
  }

  @DeleteMapping("/terms/{termId}")
    public Result deleteTerm(@PathVariable Long termId, HttpServletRequest request) {
        try {
        log.info("删除学期 - 学期ID: {}", termId);

        // 从JWT token中获取用户ID
        Long userId = getCurrentUserId(request);
        if (userId == null) {
            return Result.error(401, "用户未认证");
        }

        // 调用服务层删除学期
        boolean deleted = termService.deleteTerm(termId, userId);
        if (deleted) {
            log.info("成功删除学期 - 学期ID: {}", termId);
            return Result.success(200, "学期删除成功");
        } else {
            return Result.error(404, "学期不存在或无权限删除");
        }
        } catch (Exception e) {
        log.error("删除学期失败: ", e);
        return Result.error(500, "系统内部错误");
        }
    }
}