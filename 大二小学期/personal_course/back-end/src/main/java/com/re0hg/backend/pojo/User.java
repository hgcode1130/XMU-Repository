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

@Data // Lombok 注解，自动生成 Getter, Setter, toString, equals, hashCode 等方法
@Entity
@Table(name = "users")
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false, unique = true, length = 50)
    private String username;

    @Column(nullable = false)
    private String password;

    @Column(unique = true, length = 100)
    private String email;

    @Column(nullable = false, length = 20)
    private String role; // 建议使用枚举类型(Enum)来约束角色值

    @Column(name = "is_enabled", nullable = false)
    private Boolean isEnabled;

    @CreationTimestamp
    @Column(name = "created_at", nullable = false, updatable = false)
    private LocalDateTime createdAt;

    @UpdateTimestamp
    @Column(name = "updated_at", nullable = false)
    private LocalDateTime updatedAt;

    // --- 关系定义 ---
    // 一个用户可以有多个学期。当删除用户时，其所有学期也应被删除 (CascadeType.ALL)
    @OneToMany(mappedBy = "user", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Term> terms;
}