package com.re0hg.backend.service;

import org.springframework.stereotype.Service;

import com.re0hg.backend.pojo.PageBean;
import com.re0hg.backend.pojo.Term;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/6/22
 */
@Service
public interface TermService {

  /*
     * 分页获取当前用户的所有学期
     * @param userId 用户ID
     * @param page 页码（从0开始）
     * @param size 每页大小
     * @return 分页结果
     */
    PageBean<Term> getUserTermsWithPagination(Long userId, int page, int size);
}
