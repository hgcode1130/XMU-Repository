package com.re0hg.backend.mapper;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.springframework.data.repository.query.Param;

import com.re0hg.backend.pojo.Term;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Mapper
public interface TermMapper {
  /**
   * 分页查询指定用户的学期列表
   * 
   * @param userId   用户ID
   * @param offset   偏移量
   * @param pageSize 每页大小
   * @return 学期列表
   */
  @Select("SELECT id, name, start_date, end_date, created_at, updated_at " +
      "FROM terms WHERE user_id = #{userId} " +
      "ORDER BY created_at DESC " +
      "LIMIT #{pageSize} OFFSET #{offset}")
  List<Term> findByUserIdWithPagination(@Param("userId") Long userId,
      @Param("offset") int offset,
      @Param("pageSize") int pageSize);

  /**
   * 统计指定用户的学期总数
   * 
   * @param userId 用户ID
   * @return 学期总数
   */
  @Select("SELECT COUNT(*) FROM terms WHERE user_id = #{userId}")
  long countByUserId(@Param("userId") Long userId);
}
