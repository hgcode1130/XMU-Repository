// 使用一个简单直接的键名存储token
const TOKEN_KEY = "personal-course-token";
const USER_INFO_KEY = "personal-course-user";

/**
 * 获取本地存储的token
 */
export function getToken() {
  return localStorage.getItem(TOKEN_KEY);
}

/**
 * 设置token到本地存储
 */
export function setToken(token) {
  return localStorage.setItem(TOKEN_KEY, token);
}

/**
 * 从本地存储中移除token
 */
export function removeToken() {
  return localStorage.removeItem(TOKEN_KEY);
}

/**
 * 获取用户信息
 */
export function getUserInfo() {
  const info = localStorage.getItem(USER_INFO_KEY);
  return info ? JSON.parse(info) : null;
}

/**
 * 设置用户信息
 */
export function setUserInfo(userInfo) {
  return localStorage.setItem(USER_INFO_KEY, JSON.stringify(userInfo));
}

/**
 * 移除用户信息
 */
export function removeUserInfo() {
  return localStorage.removeItem(USER_INFO_KEY);
}
