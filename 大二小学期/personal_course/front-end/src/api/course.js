// src/api/course.js

import request from './request'

// 根据学期 ID 获取课程列表
export function getCoursesByTermApi(termId) {
  return request({
    url: `/courses/term/${termId}`,
    method: 'get',
  })
}

// 创建新课程
export function createCourseApi(data) {
  return request({
    url: '/courses',
    method: 'post',
    data,
  })
}

// 根据 ID 更新课程信息
export function updateCourseApi(courseId, data) {
  return request({
    url: `/courses/${courseId}`,
    method: 'put',
    data,
  })
}

// 根据 ID 删除课程
export function deleteCourseApi(courseId) {
  return request({
    url: `/courses/${courseId}`,
    method: 'delete',
  })
}
