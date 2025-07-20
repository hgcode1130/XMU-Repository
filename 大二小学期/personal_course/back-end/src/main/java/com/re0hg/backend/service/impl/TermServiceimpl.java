package com.re0hg.backend.service.impl;

import com.re0hg.backend.mapper.CourseMapper;
import com.re0hg.backend.mapper.ScheduleEntryMapper;
import com.re0hg.backend.mapper.TermMapper;
import com.re0hg.backend.pojo.PageBean;
import com.re0hg.backend.pojo.Term;
import com.re0hg.backend.pojo.User;
import com.re0hg.backend.service.TermService;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Service
public class TermServiceimpl implements TermService {
  @Autowired
  private TermMapper termMapper;

  @Autowired
  private CourseMapper courseMapper;

  @Autowired
    private ScheduleEntryMapper scheduleEntryMapper;

  @Override
  public Term createTerm(Term term, Long userId) {
    User user = new User();
    user.setId(userId);
    term.setUser(user);
    try {
      termMapper.createTerm(term);
    } catch (Exception e) {
      throw new RuntimeException("创建学期失败: " + e.getMessage());
    }
    return term;
  }

  @Override
  @Transactional
  public boolean deleteTerm(Long termId, Long userId) {
    // 1. 先查询学期是否存在
    Term existingTerm = termMapper.findById(termId);
    if (existingTerm == null) {
      throw new RuntimeException("学期不存在");
    }

    // 2. 验证学期是否属于当前用户
    boolean isOwner = termMapper.isTermOwnedByUser(termId, userId);
    if (!isOwner) {
      throw new RuntimeException("无权限删除此学期");
    }

    // 3. 获取该学期下的所有课程ID
    List<Long> courseIds = courseMapper.findCourseIdsByTermId(termId);

    // 4. 删除所有课程相关的排程
    for (Long courseId : courseIds) {
      scheduleEntryMapper.deleteScheduleEntriesByCourseId(courseId);
    }

    // 5. 删除该学期下的所有课程
    courseMapper.deleteCoursesByTermId(termId);

    // 6. 删除学期
    int rowsAffected = termMapper.delete(termId);
    return rowsAffected > 0;
  }

  @Override
  public PageBean<Term> getUserTermsWithPagination(Long userId, int page, int size) {
    // 计算偏移量
    int offset = page * size;

    // 查询当前页数据
    List<Term> terms = termMapper.findByUserIdWithPagination(userId, offset, size);

    // 查询总数
    long totalElements = termMapper.countByUserId(userId);

    // 构建分页结果
    return new PageBean<>(terms, page, size, totalElements);
  }

  @Override
  public Term getTermById(Long termId) {
    return termMapper.findById(termId);
  }

  @Override
  public Term updateTerm(Long termId, Term term, Long userId) {
    // 1. 先查询学期是否存在
    Term existingTerm = termMapper.findById(termId);
    if (existingTerm == null) {
      throw new RuntimeException("学期不存在");
    }

    // 2. 验证学期是否属于当前用户
    boolean isOwner = termMapper.isTermOwnedByUser(termId, userId);
    if (!isOwner) {
      throw new RuntimeException("无权限修改此学期");
    }

    // 3. 验证日期格式
    if (term.getStartDate() != null && term.getEndDate() != null) {
      if (term.getStartDate().isAfter(term.getEndDate())) {
        throw new RuntimeException("结束日期必须晚于开始日期");
      }
    }

    // 4. 只更新提供的字段
    if (term.getName() != null && !term.getName().isEmpty()) {
      existingTerm.setName(term.getName());
    }

    if (term.getStartDate() != null) {
      existingTerm.setStartDate(term.getStartDate());
    }

    if (term.getEndDate() != null) {
      existingTerm.setEndDate(term.getEndDate());
    }

    // 5. 设置更新时间（不需要手动设置，因为使用了@UpdateTimestamp注解）
    // existingTerm.setUpdatedAt(LocalDateTime.now()); // 有@UpdateTimestamp注解时可省略

    // 6. 执行更新
    termMapper.update(existingTerm);

    // 7. 返回更新后的学期信息
    return existingTerm;
  }
}
