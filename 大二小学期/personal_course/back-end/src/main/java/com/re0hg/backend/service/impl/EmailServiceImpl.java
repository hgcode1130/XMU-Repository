package com.re0hg.backend.service.impl;

import com.re0hg.backend.service.EmailService;
import org.springframework.mail.SimpleMailMessage;
import org.springframework.mail.javamail.JavaMailSender;
import org.springframework.stereotype.Service;

@Service
public class EmailServiceImpl implements EmailService {

    private final JavaMailSender mailSender;

    public EmailServiceImpl(JavaMailSender mailSender) {
        this.mailSender = mailSender;
    }

    @Override
    public void sendReminderEmail(String to,
                                String username,
                                String courseName,
                                String classTime,
                                String location,
                                String reminderNote) {
        SimpleMailMessage message = new SimpleMailMessage();
        message.setTo(to);
        System.out.println(to);
        message.setSubject("[课程提醒] " + courseName);
        message.setText(String.format(
            "亲爱的 %s 同学：\n\n" +
            "您的课程《%s》%s\n" +
            "▌ 上课时间：%s\n" +
            "▌ 上课地点：%s\n\n" +
            "请提前做好准备！\n" +
            "（本邮件由系统自动发送，请勿直接回复）",
            username, courseName, reminderNote, classTime, location
        ));
        message.setFrom("1375803462@qq.com");
        mailSender.send(message);
    }
}
