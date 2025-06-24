// src/api/request.js

import axios from "axios";
import { ElMessage, ElMessageBox } from "element-plus";
import { useUserStore } from "@/stores/user";

// 1. 创建并配置新的 Axios 实例
const service = axios.create({
  // 根据环境变量设置基础路径，Vite 中通过 import.meta.env.VITE_APP_BASE_API 获取
  // 我们在 vite.config.js 中配置了 '/api' 代理，所以这里写 '/api'
  baseURL: "/api",
  // 请求超时时间
  timeout: 10000,
});

// 2. 添加请求拦截器
// 2. 添加请求拦截器
service.interceptors.request.use(
  (config) => {
    const userStore = useUserStore();
    // 如果 store 中有 token，则为每个请求都带上
    if (userStore.token) {
      // 后端拦截器 LoginCheckInterceptor/Filter 需要的是 'token' 请求头
      config.headers["token"] = userStore.token;
    }
    return config;
  },
  (error) => {
    // 对请求错误做些什么
    console.error("Request Error:", error);
    return Promise.reject(error);
  }
);

// 3. 添加响应拦截器
service.interceptors.response.use(
  /**
   * 成功响应处理 (HTTP 状态码为 2xx)
   * 此函数会进一步检查响应体中的业务状态码 `code`
   */
  (response) => {
    const res = response.data;

    // 根据新后端逻辑，业务成功码为 200, 201 等 (2xx 范围)
    const isSuccess = res.code >= 200 && res.code < 300;

    if (isSuccess) {
      // 业务成功，直接返回整个响应体，让业务代码的 .then() 处理
      return res;
    } else {
      // 业务失败 (例如，登录时密码错误，后端返回 code: 401 但 HTTP status: 200)
      // 弹出后端返回的错误信息
      ElMessage({
        message: res.msg || "业务处理失败",
        type: "error",
        duration: 5 * 1000,
      });
      // 将其作为错误拒绝，让业务代码的 .catch() 捕获
      return Promise.reject(new Error(res.msg || "Error"));
    }
  },

  /**
   * 失败响应处理 (HTTP 状态码超出 2xx)
   * 例如 401 (未授权), 409 (冲突), 500 (服务器内部错误)
   */
  (error) => {
    console.error("Response HTTP Error:", error); // 方便调试

    let message = "请求失败，请检查网络或联系管理员";

    // 优先使用后端在响应体中提供的错误信息
    if (error.response && error.response.data && error.response.data.msg) {
      message = error.response.data.msg;
    } else if (error.message) {
      message = error.message;
    }

    ElMessage({
      message: message,
      type: "error",
      duration: 5 * 1000,
    });

    // 【关键】专门处理 401 未授权错误
    if (error.response && error.response.status === 401) {
      ElMessageBox.confirm("您的登录已过期或无效，请重新登录", "确认登出", {
        confirmButtonText: "重新登录",
        cancelButtonText: "取消",
        type: "warning",
      }).then(() => {
        // 调用 user store 的登出方法，清空 token 并跳转到登录页
        useUserStore().logout();
      });
    }

    // 返回一个被拒绝的 Promise，这样调用处的 .catch() 才能捕获到错误
    return Promise.reject(error);
  }
);


export default service;
