package com.re0hg.backend.pojo;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */

import jakarta.persistence.*;
import lombok.Data;
import org.hibernate.annotations.CreationTimestamp;
import org.hibernate.annotations.UpdateTimestamp;

import java.time.LocalDateTime;
import java.util.List;

@Data
@Entity
@Table(name = "courses")
public class Course {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "name", nullable = false, length = 100)
    private String name;

    @Column(length = 255)
    private String teachers;

    @Column(name = "main_teacher_email", length = 100)
    private String mainTeacherEmail;

    @Column(name = "course_group_chat_id", length = 50)
    private String courseGroupChatId;

    private Integer tag; // 0代表选修，1代表必修

    @Lob // 对于 TEXT 类型，使用 @Lob (Large Object)
    private String note;

    @CreationTimestamp
    @Column(name = "created_at", nullable = false, updatable = false)
    private LocalDateTime createdAt;

    @UpdateTimestamp
    @Column(name = "updated_at", nullable = false)
    private LocalDateTime updatedAt;

    // --- 关系定义 ---
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "user_id", nullable = false)
    private User user;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "term_id", nullable = false)
    private Term term;

    // 一门课程有多个上课安排。删除课程时，其所有排程也应被删除
    // cascade = CascadeType.ALL: 级联所有操作（增、删、改）
    // orphanRemoval = true: 当从 courses 的 scheduleEntries 集合中移除一个排程时，该排程也会从数据库中删除
    @OneToMany(mappedBy = "course", cascade = CascadeType.ALL, orphanRemoval = true, fetch = FetchType.EAGER)
    private List<ScheduleEntry> scheduleEntries;
}