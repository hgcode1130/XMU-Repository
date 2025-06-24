package com.re0hg.backend.service.impl;

import com.re0hg.backend.mapper.TermMapper;
import com.re0hg.backend.pojo.PageBean;
import com.re0hg.backend.pojo.Term;
import com.re0hg.backend.service.TermService;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Service
public class TermServiceimpl implements TermService {
  @Autowired
  private TermMapper termMapper;

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
}
