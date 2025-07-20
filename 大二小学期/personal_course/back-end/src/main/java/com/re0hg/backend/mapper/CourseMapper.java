package com.re0hg.backend.mapper;

import java.util.List;

import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Options;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import com.re0hg.backend.pojo.Course;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Mapper
public interface CourseMapper {
        /**
         * 创建课程
         * 
         * @param course 课程信息
         * @param userId 用户ID
         * @return 影响的行数
         */
        @Insert("INSERT INTO courses (name, teachers, main_teacher_email, course_group_chat_id, tag, note, term_id, user_id) "
                        +
                        "VALUES (#{course.name}, #{course.teachers}, #{course.mainTeacherEmail}, #{course.courseGroupChatId}, "
                        +
                        "#{course.tag}, #{course.note}, #{course.term.id}, #{userId})")
        @Options(useGeneratedKeys = true, keyProperty = "course.id")
        int createCourse(@Param("course") Course course, @Param("userId") Long userId);

        /**
         * 创建课程排程
         * 
         * @param scheduleEntry 排程信息
         * @return 影响的行数
         */
        // 已经移植到 ScheduleEntryMapper
        // @Insert("INSERT INTO schedule_entries (location, day_of_week, start_period,
        // end_period, start_week, end_week, course_id) "
        // +
        // "VALUES (#{location}, #{dayOfWeek}, #{startPeriod}, #{endPeriod},
        // #{startWeek}, #{endWeek}, #{course.id})")
        // @Options(useGeneratedKeys = true, keyProperty = "id")
        // int createScheduleEntry(ScheduleEntry scheduleEntry);

        /**
         * 根据ID查询课程
         * 
         * @param courseId 课程ID
         * @return 课程信息
         */
        @Select("SELECT id, name, teachers, main_teacher_email, course_group_chat_id, tag, note, created_at, updated_at, term_id "
                        +
                        "FROM courses WHERE id = #{courseId}")
        Course findById(@Param("courseId") Long courseId);

        // 过于复杂且有较大的交叉，不解耦
        // @Select("SELECT c.id, c.name, c.teachers, c.main_teacher_email,
        // c.course_group_chat_id, " +
        // "c.tag, c.note, c.created_at, c.updated_at, c.term_id, " +
        // "t.id as term_id, t.name as term_name, t.start_date, t.end_date " +
        // "FROM courses c " +
        // "JOIN terms t ON c.term_id = t.id " +
        // "WHERE c.id = #{courseId}")
        // @Results({
        // @Result(property = "id", column = "id"),
        // @Result(property = "name", column = "name"),
        // @Result(property = "teachers", column = "teachers"),
        // @Result(property = "mainTeacherEmail", column = "main_teacher_email"),
        // @Result(property = "courseGroupChatId", column = "course_group_chat_id"),
        // @Result(property = "tag", column = "tag"),
        // @Result(property = "note", column = "note"),
        // @Result(property = "createdAt", column = "created_at"),
        // @Result(property = "updatedAt", column = "updated_at"),
        // @Result(property = "term.id", column = "term_id"),
        // @Result(property = "term.name", column = "term_name"),
        // @Result(property = "term.startDate", column = "start_date"),
        // @Result(property = "term.endDate", column = "end_date")
        // })
        // Course findById(@Param("courseId") Long courseId);

        /**
         * 查询课程的排程列表
         * 
         * @param courseId 课程ID
         * @return 排程列表
         */
        // 已经移植到ScheduleEntryMapper中
        // @Select("SELECT id, location, day_of_week, start_period, end_period,
        // start_week, end_week " +
        // "FROM schedule_entries WHERE course_id = #{courseId}")
        // List<ScheduleEntry> findScheduleEntriesByCourseId(@Param("courseId") Long
        // courseId);

        /**
         * 检查学期是否属于用户
         * 
         * @param termId 学期ID
         * @param userId 用户ID
         * @return 是否属于用户
         */
        @Select("SELECT COUNT(*) > 0 FROM terms WHERE id = #{termId} AND user_id = #{userId}")
        boolean isTermOwnedByUser(@Param("termId") Long termId, @Param("userId") Long userId);

        /**
         * 分页查询指定学期的课程列表
         * 
         * @param termId   学期ID
         * @param offset   偏移量
         * @param pageSize 每页大小
         * @return 课程列表
         */
        @Select("SELECT id, name, teachers, main_teacher_email, course_group_chat_id, tag, note, term_id, user_id " +
                        "FROM courses WHERE term_id = #{termId} ORDER BY id DESC LIMIT #{offset}, #{pageSize}")
        List<Course> findByTermIdWithPagination(@Param("termId") Long termId, @Param("offset") int offset,
                        @Param("pageSize") int pageSize);

        /**
         * 统计指定学期的课程总数
         * 
         * @param termId 学期ID
         * @return 课程总数
         */
        @Select("SELECT COUNT(*) FROM courses WHERE term_id = #{termId}")
        long countByTermId(@Param("termId") Long termId);

        /**
         * 动态条件查询课程列表
         */
        List<Course> searchCourses(@Param("termId") Long termId,
                        @Param("name") String name,
                        @Param("teacher") String teacher,
                        @Param("tag") Integer tag,
                        @Param("dayOfWeek") Integer dayOfWeek,
                        @Param("offset") int offset,
                        @Param("pageSize") int pageSize);

        /**
         * 检查课程是否属于用户
         * 
         * @param courseId 课程ID
         * @param userId   用户ID
         * @return 是否属于用户
         */
        @Select("SELECT COUNT(*) > 0 FROM courses c " +
                        "JOIN terms t ON c.term_id = t.id " +
                        "WHERE c.id = #{courseId} AND t.user_id = #{userId}")
        boolean isCourseOwnedByUser(@Param("courseId") Long courseId, @Param("userId") Long userId);

        /**
         * 统计条件匹配的课程总数
         */
        long countSearchCourses(@Param("termId") Long termId,
                        @Param("name") String name,
                        @Param("teacher") String teacher,
                        @Param("tag") Integer tag,
                        @Param("dayOfWeek") Integer dayOfWeek);

        /**
         * 更新课程基本信息
         * 
         * @param course 课程信息
         * @return 影响的行数
         */
        @Update("UPDATE courses SET name = #{name}, teachers = #{teachers}, " +
                        "main_teacher_email = #{mainTeacherEmail}, course_group_chat_id = #{courseGroupChatId}, " +
                        "tag = #{tag}, note = #{note} WHERE id = #{id}")
        int updateCourse(Course course);

        /**
         * 删除课程的所有排程
         * 
         * @param courseId 课程ID
         * @return 影响的行数
         */
        // 已经移植到ScheduleEntryMapper中
        // @Delete("DELETE FROM schedule_entries WHERE course_id = #{courseId}")
        // int deleteScheduleEntriesByCourseId(@Param("courseId") Long courseId);

        /**
         * 删除课程
         *
         * @param courseId 课程ID
         * @return 影响的行数
         */
        @Delete("DELETE FROM courses WHERE id = #{courseId}")
        int deleteCourseById(Long courseId);

        /**
         * 根据学期ID获取课程ID
         *
         * @param termId 学期ID
         * @return 课程ID
         */
        @Select("SELECT id FROM courses WHERE term_id = #{termId}")
        List<Long> findCourseIdsByTermId(Long termId);

        /**
         * 根据学期ID删除所有课程
         *
         * @param termId 学期ID
         */
        @Delete("DELETE FROM courses WHERE term_id = #{termId}")
        void deleteCoursesByTermId(Long termId);
}
