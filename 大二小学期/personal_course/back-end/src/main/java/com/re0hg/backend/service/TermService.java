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

    /**
     * 分页获取当前用户的所有学期
     * @param userId 用户ID
     * @param page 页码（从0开始）
     * @param size 每页大小
     * @return 分页结果
     */
  PageBean<Term> getUserTermsWithPagination(Long userId, int page, int size);
    
  /**
   * 更新学期信息
   * 
   * @param termId 学期ID
   * @param term   更新的学期信息
   * @param userId 当前用户ID
   * @return 更新后的学期
   */
  Term updateTerm(Long termId, Term term, Long userId);

  /**
   * 根据ID查询学期
   * 
   * @param termId 学期ID
   * @return 学期信息
   */
  Term getTermById(Long termId);


  /**
   * 创建学期
   * 
   * @param term   要创建的学期信息
   * @param userId 当前用户ID
   * @return 创建成功的学期
   */
  Term createTerm(Term term, Long userId);

    boolean deleteTerm(Long termId, Long userId);
}
