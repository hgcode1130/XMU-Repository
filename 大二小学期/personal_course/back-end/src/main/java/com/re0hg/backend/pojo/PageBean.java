package com.re0hg.backend.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/4/20
 */

@Data
// @NoArgsConstructor
// @AllArgsConstructor
public class PageBean<T> {

  private List<T> content; // 当前页内容
  private Pageable pageable; // 分页信息
  private int totalPages; // 总页数
  private long totalElements; // 总元素数
  private boolean last; // 是否最后一页
  private boolean first; // 是否第一页

  @Data
  @NoArgsConstructor
  @AllArgsConstructor
  public static class Pageable {
    private int pageNumber; // 页码
    private int pageSize; // 每页大小
  }

  /**
   * 构造方法，根据查询结果自动计算分页信息
   */
  public PageBean(List<T> content, int pageNumber, int pageSize, long totalElements) {
    this.content = content;
    this.totalElements = totalElements;
    this.totalPages = (int) Math.ceil((double) totalElements / pageSize);
    this.pageable = new Pageable(pageNumber, pageSize);
    this.first = pageNumber == 0;
    this.last = pageNumber >= totalPages - 1;
  }
}