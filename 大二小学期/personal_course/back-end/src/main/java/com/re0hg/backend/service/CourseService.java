package com.re0hg.backend.service;

import org.springframework.stereotype.Service;

import com.re0hg.backend.pojo.Course;
import com.re0hg.backend.pojo.PageBean;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Service
public interface CourseService {

  /**
   * 创建课程
   * 
   * @param course 课程信息
   * @param userId 用户ID
   * @return 创建后的课程
   */
  Course createCourse(Course course, Long userId);

  /**
   * 根据课程ID获取学期ID
   * @param courseId 课程ID
   */
   Long getTermIdByCourseId(Long courseId);

  /**
   * 分页获取指定学期的所有课程
   * 
   * @param termId 学期ID
   * @param userId 用户ID
   * @param page   页码（从0开始）
   * @param size   每页大小
   * @return 分页结果
   */
  PageBean<Course> getCoursesForTermWithPagination(Long termId, Long userId, int page, int size);

  /**
   * 高级课程搜索 (多条件筛选与分页)
   *
   * @param termId    学期ID (可选)
   * @param name      课程名 (模糊匹配，可选)
   * @param teacher   教师名 (模糊匹配，可选)
   * @param tag       课程标签 (0=选修，1=必修，可选)
   * @param dayOfWeek 星期几 (1-7，可选)
   * @param userId    用户ID
   * @param page      页码（从0开始）
   * @param size      每页大小
   * @return 分页结果
   */
  PageBean<Course> searchCoursesWithPagination(Long termId, String name, String teacher,
      Integer tag, Integer dayOfWeek, Long userId,
      int page, int size);

  /**
   * 更新课程信息
   *
   * @param courseId 课程ID
   * @param course   新的课程信息
   * @param userId   用户ID（用于权限验证）
   * @return 更新后的课程
   */
  Course updateCourse(Long courseId, Course course, Long userId);

    /**
     * 删除课程
     *
     * @param courseId 课程ID
     * @param userId   用户ID（用于权限验证）
     * @return 是否删除成功
     */
  boolean deleteCourse(Long courseId, Long userId);
}
