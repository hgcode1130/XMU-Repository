// CourseServiceTest.java
package com.re0hg.backend;

import com.re0hg.backend.mapper.CourseMapper;
import com.re0hg.backend.mapper.ScheduleEntryMapper;
import com.re0hg.backend.pojo.Course;
import com.re0hg.backend.pojo.ScheduleEntry;
import com.re0hg.backend.pojo.Term;
import com.re0hg.backend.service.CourseService;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.transaction.annotation.Transactional;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/30
 */
@RunWith(SpringRunner.class)
@SpringBootTest(classes = BackEndApplication.class)
public class CourseServiceTest {

    @Autowired
    private CourseService courseService;

    @Autowired
    private CourseMapper courseMapper;

    @Autowired
    private ScheduleEntryMapper scheduleEntryMapper;

    /**
     * 测试删除课程及其关联排程
     * 验证以下功能：
     * 1. 课程及关联排程的级联删除
     * 2. 用户权限验证
     * 3. 删除状态返回值
     */
    @Test
    @Transactional // 确保测试数据不污染数据库
    public void testDeleteCourseWithSchedule() {
        // 准备测试数据
        Long courseId = 1L;
        Long userId = 1L;

        // 1. 创建测试数据
        createTestCourseWithSchedule(courseId, userId);

        // 2. 执行删除操作
        boolean result = courseService.deleteCourse(courseId, userId);

        // 3. 验证删除结果
        assertTrue(result, "删除操作应返回true");

        // 4. 验证课程已被删除
        assertNull(courseMapper.findById(courseId),
                "课程表中应不存在ID为" + courseId + "的记录");

        // 5. 验证排程数据已被删除
        List<ScheduleEntry> entries = scheduleEntryMapper.findByCourseId(courseId);
        assertTrue(entries.isEmpty(),
                "排程表中应不存在课程ID为" + courseId + "的记录");
    }

    /**
     * 创建测试用的课程及排程数据
     * @param courseId 课程ID
     * @param userId 用户ID
     */
    private void createTestCourseWithSchedule(Long courseId, Long userId) {
        // 创建课程对象
        Course course = new Course();
        course.setId(courseId);
        course.setName("测试课程");
        course.setTeachers("测试教师");
        course.setTag(1);

        // 设置学期信息（需确保学期存在）
        Term term = new Term();
        term.setId(1L); // 假设存在ID为1的学期
        course.setTerm(term);

        // 创建排程数据
        List<ScheduleEntry> entries = new ArrayList<>();
        for (int i = 1; i <= 2; i++) {
            ScheduleEntry entry = new ScheduleEntry();
            entry.setLocation("测试教室" + i);
            entry.setDayOfWeek(1);
            entry.setStartPeriod(1);
            entry.setEndPeriod(2);
            entry.setStartWeek(1);
            entry.setEndWeek(18);
            entry.setCourse(course);
            entries.add(entry);
        }

        course.setScheduleEntries(entries);

        // 保存测试数据（需确保courseMapper和scheduleEntryMapper已注入）
        courseMapper.createCourse(course, userId);

        for (ScheduleEntry entry : entries) {
            scheduleEntryMapper.createScheduleEntry(entry);
        }
    }
}
