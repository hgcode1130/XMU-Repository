package com.re0hg.backend.mapper;

import java.util.List;

import org.apache.ibatis.annotations.*;
import org.springframework.data.repository.query.Param;

import com.re0hg.backend.pojo.Term;
import java.time.*;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Mapper
public interface TermMapper {
  /**
     * 查询用户当前活跃的学期
     * @param userId 用户ID
     * @param date 查询日期
     * @return 学期信息
     */
    @Select("SELECT * FROM terms " +
           "WHERE user_id = #{userId} " +
           "AND #{date} BETWEEN start_date AND end_date " +
           "ORDER BY start_date DESC LIMIT 1")
    Term findCurrentTerm(@Param("userId") Long userId,
                        @Param("date") LocalDate date);


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

  /**
   * 根据ID查询学期（包含用户信息）
   * 
   * @param termId 学期ID
   * @return 学期信息
   */
  @Select("SELECT id, name, start_date, end_date, created_at, updated_at, user_id " +
      "FROM terms WHERE id = #{termId}")
  Term findById(@Param("termId") Long termId);

  /**
   * 更新学期信息
   * 
   * @param term 学期信息
   * @return 影响的行数
   */
  @Update("UPDATE terms SET name = #{name}, start_date = #{startDate}, end_date = #{endDate} " +
      "WHERE id = #{id}")
  int update(Term term);

  /**
   * 验证学期是否属于指定用户
   */
  @Select("SELECT COUNT(*) > 0 FROM terms WHERE id = #{termId} AND user_id = #{userId}")
  boolean isTermOwnedByUser(@Param("termId") Long termId, @Param("userId") Long userId);


  /**
   * 创建学期
   * @param term 学期信息
   * @return 影响的行
   */
  @Insert("INSERT INTO terms (name, start_date, end_date, user_id) VALUES (#{name}, #{startDate}, #{endDate}, #{user.id})")
  @Options(useGeneratedKeys = true, keyProperty = "id")
  int createTerm(Term term);

    /**
     * 删除学期
     *
     * @param termId 学期ID
     * @return 影响的行数
     */
    @Delete("DELETE FROM terms WHERE id = #{termId}")
  int delete(Long termId);

    /**
     * 根据课程ID获取学期ID
     *
     * @param courseId 课程ID
     * @return 学期ID
     */
    @Select("SELECT term_id FROM courses WHERE id = #{courseId}")
    Long getTermIdByCourseId(Long courseId);
}
