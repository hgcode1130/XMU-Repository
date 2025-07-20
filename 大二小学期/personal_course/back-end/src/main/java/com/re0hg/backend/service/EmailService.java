package com.re0hg.backend.service;

public interface EmailService {
    void sendReminderEmail(String to,
                         String username,
                         String courseName,
                         String classTime,
                         String location,
                         String reminderNote); // 添加reminderNote参数
}
