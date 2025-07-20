package com.re0hg.backend.service;

import com.re0hg.backend.pojo.PageBean;
import com.re0hg.backend.pojo.User;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Service
public interface UserService {

   /**
    * 获取所有用户
    * 
    * @return 所有用户列表
    */
   List<User> list();

   /**
    * 用户注册
    * 
    * @param user 用户对象
    * @return 注册成功的用户
    */
   User register(User user);

   /**
    * 根据用户名查找用户
    * 
    * @param username 用户名
    * @return 用户对象，如果不存在则返回null
    */
   User findByUsername(String username);

   /**
    * h
    * 获取所有用户列表
    *
    * @return 用户列表
    */
   PageBean<User> getUserWithPagination(String username, String email, String role, Boolean isEnabled, int page,
         int size);

   boolean isAdmin(Long userId);

   void updateUserStatus(Long userId, Boolean isEnabled);
}
