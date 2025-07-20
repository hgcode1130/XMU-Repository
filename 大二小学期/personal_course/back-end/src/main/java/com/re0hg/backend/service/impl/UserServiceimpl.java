package com.re0hg.backend.service.impl;

import com.re0hg.backend.mapper.UserMapper;
import com.re0hg.backend.pojo.PageBean;
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
    private BCryptPasswordEncoder passwordEncoder; // 加密器
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

    /**
     * 获取所有用户列表，支持分页和条件查询
     *
     * @param username  用户名（模糊匹配）
     * @param email     邮箱（模糊匹配）
     * @param role      角色（ADMIN, USER, TRIAL）
     * @param isEnabled 账户状态（true/false）
     * @param page      页码（默认0）
     * @param pageSize  每页数量（默认20）
     * @return 分页用户列表
     */
    @Override
    public PageBean<User> getUserWithPagination(String username, String email, String role, Boolean isEnabled, int page,
            int pageSize) {
        // 处理分页参数
        int offset = page * pageSize;
        List<User> users;
        try {
            // 查询用户列表
            users = userMapper.getUserWithPagination(username, email, role, isEnabled, offset, pageSize);

        } catch (IllegalArgumentException e) {
            throw new RuntimeException("分页参数错误: " + e.getMessage());
        }
        Long total;
        try {
            // 查询总记录数
            total = userMapper.countUsers(username, email, role, isEnabled);
        } catch (Exception e) {
            throw new RuntimeException("查询用户总数失败: " + e.getMessage());
        }
        // 构建分页结果
        return new PageBean<>(users, page, pageSize, total);
    }

    // 判断用户是否是管理员

    @Override
    public boolean isAdmin(Long userId) {
        User user = userMapper.findByuserId(userId);
        if (user == null) {
            throw new RuntimeException("用户不存在");
        }
        return "ADMIN".equals(user.getRole());
    }

    //  更新用户状态
    @Override
    public void updateUserStatus(Long userId, Boolean isEnabled) {
        User user = userMapper.findByuserId(userId);
        if (user == null) {
            throw new RuntimeException("用户不存在");
        }
        if(user.getRole().equals("ADMIN")){
            throw new RuntimeException("管理员账户状态不能被更新");
        }
        try {
            userMapper.updateUserStatus(userId, isEnabled);
        } catch (Exception e) {
            throw new RuntimeException("更新用户状态失败: " + e.getMessage());
        }
    }
}