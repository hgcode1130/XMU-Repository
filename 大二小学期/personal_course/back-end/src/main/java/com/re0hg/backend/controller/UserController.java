package com.re0hg.backend.controller;

import com.re0hg.backend.dto.UpdateUserStatusDTO;
import com.re0hg.backend.pojo.PageBean;
import com.re0hg.backend.pojo.Result;
import com.re0hg.backend.pojo.User;
import com.re0hg.backend.service.UserService;
import com.re0hg.backend.utils.JwtUtils;
import jakarta.servlet.http.HttpServletRequest;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@RestController
@Slf4j
@RequestMapping("/api/")
public class UserController {

    @Autowired
    private UserService userService;

    // GET /api/admin/users
    @GetMapping("admin/users")
    public Result getAllUsers(@RequestParam(required = false) String username,
            @RequestParam(required = false) String email,
            @RequestParam(required = false) String role,
            @RequestParam(required = false) Boolean isEnabled,
            @RequestParam(defaultValue = "0") int page,
            @RequestParam(defaultValue = "20") int size,
            HttpServletRequest requestBody) {
        Long userId = JwtUtils.getCurrentUserId(requestBody); // 假设从请求体中获取用户ID
        log.info("获取所有用户列表");
        log.info("查询条件 - 用户名: {}, 邮箱: {}, 角色: {}, 是否启用: {}, 页码: {}, 每页大小: {}",
                username, email, role, isEnabled, page, size);
        if (userId == null) {
            log.error("用户未认证");
            return Result.error(401, "用户未认证");
        }
        // 权限验证
        try {
            // 检查用户是否有权限访问此接口
            if (!userService.isAdmin(userId)) {
                return Result.error(403, "无权限访问此接口");
            }
        } catch (Exception e) {
            log.error("权限验证失败", e);
            return Result.error(500, "权限验证失败");
        }
        try {
            log.info("获取所有用户列表");
            PageBean<User> userPage = userService.getUserWithPagination(username, email, role, isEnabled, page, size);
            return Result.success(200, "查询成功", userPage);
        } catch (Exception e) {
            log.error("获取用户列表失败", e);
            return Result.error(500, "获取用户列表失败");
        }
    }

    @PutMapping("admin/users/{userId}/status")
    public Result updateUserStatus(@PathVariable Long userId,
            @RequestBody UpdateUserStatusDTO updateUserStatusDTO,
            HttpServletRequest request) {
        Long userID = JwtUtils.getCurrentUserId(request);
        log.info("更新用户状态 - 用户ID: {}, 是否启用: {}", userId, updateUserStatusDTO.getIsEnabled());

        if (userID == null) {
            log.error("用户未认证");
            return Result.error(401, "用户未认证");
        }

        // 验证请求参数
        if (updateUserStatusDTO.getIsEnabled() == null) {
            log.error("请求参数无效: isEnabled 不能为空");
            return Result.error(400, "请求参数无效: isEnabled 不能为空");
        }

        // 权限验证
        try {
            if (!userService.isAdmin(userID)) {
                return Result.error(403, "无权限执行此操作");
            }
        } catch (Exception e) {
            log.error("权限验证失败", e);
            return Result.error(500, "权限验证失败");
        }

        try {
            userService.updateUserStatus(userId, updateUserStatusDTO.getIsEnabled());
            return Result.success(200, "用户状态更新成功");
        } catch (Exception e) {
            log.error("更新用户状态失败", e);
            return Result.error(500, "更新用户状态失败: " + e.getMessage());
        }
    }
}
