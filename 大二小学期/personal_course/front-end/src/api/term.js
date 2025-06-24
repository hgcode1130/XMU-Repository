// src/api/term.js

import request from './request'

// 获取所有学期列表
export function getTermsApi() {
  return request({
    url: '/terms',
    method: 'get',
  })
}

// 创建新学期
export function createTermApi(data) {
  return request({
    url: '/terms',
    method: 'post',
    data,
  })
}

// 根据 ID 更新学期信息
export function updateTermApi(termId, data) {
  return request({
    url: `/terms/${termId}`,
    method: 'put',
    data,
  })
}

// 根据 ID 删除学期
export function deleteTermApi(termId) {
  return request({
    url: `/terms/${termId}`,
    method: 'delete',
  })
}
