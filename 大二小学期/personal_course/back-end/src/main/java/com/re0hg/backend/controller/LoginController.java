package com.re0hg.backend.controller;

import com.re0hg.backend.pojo.LoginRequest;
import com.re0hg.backend.pojo.Result;
import com.re0hg.backend.pojo.User;
import com.re0hg.backend.service.UserService;
import com.re0hg.backend.utils.JwtUtils;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/4/22
 */
@Slf4j
@RestController
public class LoginController {

    @Autowired
    private UserService userService;

    @Autowired
    private BCryptPasswordEncoder passwordEncoder;

    /**
     * 用户登录
     * 
     * @param loginRequest 登录请求参数
     * @return 登录结果
     */
    @PostMapping("/api/auth/login")
    public Result login(@RequestBody LoginRequest loginRequest) {
        log.info("用户登录: {}", loginRequest.getUsername());

        // 1. 参数校验
        if (loginRequest.getUsername() == null || loginRequest.getPassword() == null) {
            return Result.error(400,"用户名或密码不能为空");
        }

        // 2. 根据用户名查询用户
        User user = userService.findByUsername(loginRequest.getUsername());
        if (user == null) {
            log.info("用户名不存在: {}", loginRequest.getUsername());
            return Result.error(401,"用户名或密码错误，或账户已被禁用");
        }

        // 3. 检查账户状态
        if (!user.getIsEnabled()) {
            log.info("账户已被禁用: {}", loginRequest.getUsername());
            return Result.error(401,"用户名或密码错误，或账户已被禁用");
        }

        // 4. 校验密码
        if (!passwordEncoder.matches(loginRequest.getPassword(), user.getPassword())) {
            log.info("密码错误: {}", loginRequest.getUsername());
            return Result.error(401,"用户名或密码错误，或账户已被禁用");
        }

        // 5. 生成JWT令牌
        Map<String, Object> claims = new HashMap<>();
        claims.put("id", user.getId());
        claims.put("username", user.getUsername());
        claims.put("role", user.getRole());

        String token = JwtUtils.generateJwt(claims);

        // 6. 构建返回数据
        HashMap<String, Object> data = new HashMap<>();
        data.put("token", token);
        data.put("expiresIn", 7200); // 令牌有效期，单位为秒
        data.put("role", user.getRole());

        return Result.success(200,"登录成功", data);
    }
}