import request from "./request"; // 引入封装好的 Axios 实例

/**
 * @description 获取用户列表 (分页与筛选)
 * @param {object} params - 查询参数
 * @param {number} params.page - 页码 (从0开始)
 * @param {number} params.size - 每页数量
 * @param {string} [params.username] - 用户名
 * @param {string} [params.email] - 邮箱
 * @param {string} [params.role] - 角色
 * @param {boolean} [params.isEnabled] - 账户状态
 */
export function fetchUsers(params) {
  return request({
    url: "/api/admin/users",
    method: "get",
    params, // GET 请求的参数会附加到 URL 后面
  });
}

/**
 * @description 更新用户状态 (启用/禁用)
 * @param {number} userId - 用户 ID
 * @param {object} data - 请求体
 * @param {boolean} data.isEnabled - 新的状态
 */
export function updateUserStatus(userId, data) {
  return request({
    url: `/api/admin/users/${userId}/status`,
    method: "put",
    data, // PUT 请求的请求体
  });
}
