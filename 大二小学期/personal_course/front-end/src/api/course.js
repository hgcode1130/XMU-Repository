// src/api/course.js

import request from "./request";

// 根据学期 ID 获取课程列表
export function getCoursesByTermApi(termId) {
  return request({
    url: `/terms/${termId}/courses`,
    method: "get",
  });
}

// 创建新课程
export function createCourseApi(data) {
  return request({
    url: "/courses",
    method: "post",
    data,
  });
}

// 根据 ID 更新课程信息
export function updateCourseApi(courseId, data) {
  return request({
    url: `/courses/${courseId}`,
    method: "put",
    data,
  });
}

// 根据 ID 删除课程
export function deleteCourseApi(courseId) {
  return request({
    url: `/courses/${courseId}`,
    method: "delete",
  });
}

// 高级课程搜索功能
export function searchCoursesApi(params) {
  return request({
    url: "/courses/search",
    method: "get",
    params, // 查询参数：termId, name, teacher, tag, dayOfWeek, page, size
  });
}

// Excel导入课程
export function importExcelApi(termId, file) {
  const formData = new FormData();
  formData.append("file", file);

  return request({
    url: `/import/excel?termId=${termId}`,
    method: "post",
    data: formData,
    headers: {
      "Content-Type": "multipart/form-data",
    },
    timeout: 60000, // 增加超时时间到60秒，因为Excel导入可能需要较长时间
  });
}

// 下载Excel模板
export function downloadTemplateApi() {
  return request({
    url: "/import/excel/template",
    method: "get",
    responseType: "blob", // 重要：指定响应类型为blob以处理文件下载
    // 添加一个标识，让响应拦截器知道这是文件下载请求
    skipResponseIntercept: true,
  });
}
