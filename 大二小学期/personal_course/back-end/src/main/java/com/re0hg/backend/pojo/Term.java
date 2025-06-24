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

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

@Data
@Entity
@Table(name = "terms")
public class Term {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "name", nullable = false, length = 100)
    private String name;

    @Column(name = "start_date")
    private LocalDate startDate;

    @Column(name = "end_date")
    private LocalDate endDate;

    @CreationTimestamp
    @Column(name = "created_at", nullable = false, updatable = false)
    private LocalDateTime createdAt;

    @UpdateTimestamp
    @Column(name = "updated_at", nullable = false)
    private LocalDateTime updatedAt;

    // --- 关系定义 ---
    // 多个学期可以属于一个用户
    @ManyToOne(fetch = FetchType.LAZY) // LAZY: 延迟加载，性能更优
    @JoinColumn(name = "user_id", nullable = false)
    private User user;

    // 一个学期可以包含多门课程。删除学期时，其下所有课程也应被删除
    @OneToMany(mappedBy = "term", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Course> courses;
}