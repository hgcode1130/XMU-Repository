package com.re0hg.backend.mapper;

import com.re0hg.backend.pojo.User;
import org.apache.ibatis.annotations.*;

import java.util.List;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Mapper
public interface UserMapper {
    @Select("SELECT * FROM users WHERE id = #{id}")
    User findById(Long id);

    @Select("SELECT u.* " +
            "FROM users u " +
            "WHERE u.id IN (SELECT user_id FROM courses c WHERE c.id = #{id})")
    User findByCourseId(Long id);

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

  /**
   * 获取分页用户列表
   *
   * @param username  用户名
   * @param email     邮箱
   * @param role      角色
   * @param isEnabled 是否启用
   * @param offset    偏移量
   * @param size      每页大小
   * @return 分页用户列表
   */
  List<User> getUserWithPagination(@Param("username") String username,
      @Param("email") String email,
      @Param("role") String role,
      @Param("isEnabled") Boolean isEnabled,
      @Param("offset") int offset,
      @Param("pageSize") int pageSize);

  /**
   * 统计用户数量
   *
   * @param username  用户名
   * @param email     邮箱
   * @param role      角色
   * @param isEnabled 是否启用
   * @return 用户数量
   */
  long countUsers(@Param("username") String username,
      @Param("email") String email,
      @Param("role") String role,
      @Param("isEnabled") Boolean isEnabled);

  /**
   * 根据用户ID查找用户
   *
   * @param userId 用户ID
   * @return 用户对象
   */
  @Select("SELECT * FROM users WHERE id = #{userId}")
  User findByuserId(Long userId);

  /**
   * 更新用户状态
   *
   * @param userId    用户ID
   * @param isEnabled 是否启用
   */
  @Update("UPDATE users SET is_enabled = #{isEnabled} WHERE id = #{userId}")
  void updateUserStatus(Long userId, Boolean isEnabled);
}
