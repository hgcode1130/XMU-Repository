package com.re0hg.backend.service.impl;

import com.re0hg.backend.mapper.UserMapper;
import com.re0hg.backend.pojo.User;
import com.re0hg.backend.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Service
public class UserServiceimpl implements UserService {

    @Autowired
    private UserMapper userMapper;

    @Autowired
    private BCryptPasswordEncoder passwordEncoder;  // 加密器
    /*
     * 获取所有用户
     */
    public List<User> list() {
        return userMapper.list();
    }

    /*
     * 注册用户
     */
    @Override
    public User register(User user) {
        // 检查用户名是否已存在
        User existingUserByUsername = userMapper.findByUsername(user.getUsername());
        if (existingUserByUsername != null) {
            throw new RuntimeException("用户名已存在");
        }

        // 检查邮箱是否已存在
        User existingUserByEmail = userMapper.findByEmail(user.getEmail());
        if (existingUserByEmail != null) {
            throw new RuntimeException("邮箱已被使用");
        }

        // 加密密码（需添加Spring Security依赖以使用BCryptPasswordEncoder）
        String encodedPassword = passwordEncoder.encode(user.getPassword());
        user.setPassword(encodedPassword);

        // 保存用户
        userMapper.save(user);

        // 返回注册成功的用户（密码置空）
        User resultUser = new User();
        resultUser.setId(user.getId());
        resultUser.setUsername(user.getUsername());
        resultUser.setEmail(user.getEmail());
        resultUser.setRole(user.getRole());
        resultUser.setIsEnabled(user.getIsEnabled());
        // 不返回密码
        return resultUser;
    }
    
    /**
     * 根据用户名查找用户
     */
    @Override
    public User findByUsername(String username) {
        return userMapper.findByUsername(username);
    }
}