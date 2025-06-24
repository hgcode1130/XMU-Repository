// src/api/auth.js

import request from './request' // 引入我们封装好的 Axios 实例

/**
 * @description 登录接口
 * @param {object} data - 包含用户名和密码的对象, e.g., { username: 'user', password: '123' }
 * @returns {Promise}
 */
export function loginApi(data) {
  return request({
    // 【重要】请将这里的 '/auth/login' 替换为您后端真实的登录接口路径
    url: '/auth/login',
    method: 'post',
    data,
  })
}

/**
 * @description 注册接口 (可选，如果您的项目有注册功能)
 * @param {object} data - 包含注册信息的对象
 * @returns {Promise}
 */
export function registerApi(data) {
  return request({
    // 【重要】请将这里的 '/auth/register' 替换为您后端真实的注册接口路径
    url: '/auth/register',
    method: 'post',
    data,
  })
}
