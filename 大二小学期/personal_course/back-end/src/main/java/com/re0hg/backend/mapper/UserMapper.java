package com.re0hg.backend.mapper;

import com.re0hg.backend.pojo.User;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Options;
import org.apache.ibatis.annotations.Select;

import java.util.List;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Mapper
public interface UserMapper {

    /**
     * 查询所有用户
     * 
     * @return 用户列表
     */
    @Select("SELECT * FROM users")
    List<User> list();

    /**
     * 通过用户名查找用户
     * 
     * @param username 用户名
     * @return 用户对象
     */
    @Select("SELECT * FROM users WHERE username = #{username}")
    User findByUsername(String username);

    /**
     * 通过邮箱查找用户
     * 
     * @param email 邮箱
     * @return 用户对象
     */
    @Select("SELECT * FROM users WHERE email = #{email}")
    User findByEmail(String email);

    /**
     * 保存用户
     * 
     * @param user 用户对象
     */
    @Insert("""
            INSERT INTO users
              (username, password, email, role, is_enabled, created_at, updated_at)
            VALUES
              (#{username}, #{password}, #{email}, #{role}, #{isEnabled},
               CURRENT_TIMESTAMP, CURRENT_TIMESTAMP)
            """)
    @Options(useGeneratedKeys = true, keyProperty = "id")
    void save(User user);

}
