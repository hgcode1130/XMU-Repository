package com.re0hg.backend.task;

import com.re0hg.backend.mapper.CourseMapper;
import com.re0hg.backend.mapper.ScheduleEntryMapper;
import com.re0hg.backend.mapper.UserMapper;
import com.re0hg.backend.pojo.ScheduleEntry;
import com.re0hg.backend.pojo.User;
import com.re0hg.backend.service.EmailService;
import com.re0hg.backend.service.UserService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import java.sql.Time;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Locale;

@Slf4j
@Component
public class CourseReminderTask {

    private final ScheduleEntryMapper scheduleEntryMapper;
    private final UserMapper userMapper;
    private final EmailService emailService;

    private static final DateTimeFormatter TIME_FORMATTER =
        DateTimeFormatter.ofPattern("HH:mm");

    public CourseReminderTask(ScheduleEntryMapper scheduleEntryMapper, UserMapper userMapper, CourseMapper courseMapper,
                              EmailService emailService, UserService userService) {
        this.scheduleEntryMapper = scheduleEntryMapper;
        this.userMapper = userMapper;
        this.emailService = emailService;
    }

    @Scheduled(cron = "0 * * * * ?")
    public void checkUpcomingCourses() {
        List<ScheduleEntry> entries = scheduleEntryMapper.findByStartTime(//////////////////////////////测试改时间
                toPeriod(LocalTime.now()),
                LocalDate.now().getDayOfWeek().getValue()
        );
        entries.forEach(entry -> {
            User user = userMapper.findByCourseId(entry.getCourse().getId());
            try {
                emailService.sendReminderEmail(
                    user.getEmail(),
                    user.getUsername(),
                    entry.getCourse().getName(),
                    LocalTime.now().plusMinutes(30).format(DateTimeFormatter.ofPattern("HH:mm")),
                    entry.getLocation(),
                    "课程将在30分钟后开始" // 新增的第六个参数
                );

                log.info("提醒邮件已发送 [课程: {}]", entry.getCourse().getName());
            } catch (Exception e) {
                log.error("发送失败 [课程ID: {}]: {}",
                    entry.getCourse().getId(), e.getMessage());
            }
        });
    }
    private static final LocalTime[] CLASS_START_TIMES = {
        LocalTime.of(8, 0),   // 1
        LocalTime.of(8, 50),  // 2
        LocalTime.of(9, 50),  // 3
        LocalTime.of(10, 40), // 4
        LocalTime.of(11, 30), // 5
        LocalTime.of(14, 0),  // 6
        LocalTime.of(14, 50), // 7
        LocalTime.of(15, 50), // 8
        LocalTime.of(16, 40), // 9
        LocalTime.of(17, 30), // 10
        LocalTime.of(19, 30), // 11
        LocalTime.of(20, 20)  // 12
    };
    private int toPeriod(LocalTime currentTime) {
        LocalTime targetTime = currentTime.plusMinutes(30);

        for (int i = 0; i < CLASS_START_TIMES.length; i++) {
            if (CLASS_START_TIMES[i].getHour() == targetTime.getHour() && CLASS_START_TIMES[i].getMinute() == targetTime.getMinute()) {
                return i + 1; // 找到精确匹配
            }
        }
        return 0; // 无匹配
    }

    private String convertDayOfWeek(int dayOfWeek) {
        String[] days = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
        return (dayOfWeek >= 1 && dayOfWeek <= 7) ? days[dayOfWeek - 1] : "未知";
    }
}
