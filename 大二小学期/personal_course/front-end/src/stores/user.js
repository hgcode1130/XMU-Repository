// import { defineStore } from "pinia";
// import { ref } from "vue";
// import { useRouter } from "vue-router";
// import { loginApi } from "@/api/auth";

// export const useUserStore = defineStore(
//   "user",
//   () => {
//     const router = useRouter();

//     const token = ref(null);
//     const role = ref("");
//     // 一个 ref 来存储用户信息
//     const userInfo = ref({});

//     const login = async (loginData) => {
//       try {
//         const res = await loginApi(loginData);
//         if (res.data && res.data.token) {
//           token.value = res.data.token;
//           role.value = res.data.role || "USER";
//           userInfo.value = {
//             username: loginData.username,
//             role: res.data.role || "USER",
//           };
//         } else {
//           throw new Error("登录成功，但响应数据格式不正确。");
//         }
//       } catch (error) {
//         console.error("Pinia store 在登录时捕获到错误:", error);
//         token.value = null;
//         role.value = "";
//         userInfo.value = {}; // 失败时也清空
//         throw error;
//       }
//     };

//     const logout = () => {
//       token.value = null;
//       role.value = "";
//       userInfo.value = {}; // 登出时清空用户信息
//       router.push("/login");
//     };

//     return {
//       token,
//       role,
//       userInfo, // 导出 userInfo
//       login,
//       logout,
//     };
//   },
//   {
//     persist: {
//       // 将 userInfo 也加入持久化
//       paths: ["token", "role", "userInfo"],
//     },
//   }
// );
import { defineStore } from "pinia";
import { ref } from "vue";
import { useRouter } from "vue-router";
import { loginApi } from "@/api/auth";
// 【关键修复】导入我们的auth工具函数
import {
  getToken,
  setToken,
  removeToken,
  getUserInfo,
  setUserInfo,
  removeUserInfo,
} from "@/utils/auth";

export const useUserStore = defineStore(
  "user",
  () => {
    const router = useRouter();

    // 初始化时从localStorage读取值（同步操作，不依赖插件）
    const token = ref(getToken() || null);
    const userInfo = ref(getUserInfo() || {});

    const login = async (loginData) => {
      try {
        const res = await loginApi(loginData);
        if (res.data && res.data.token) {
          // 更新store状态
          token.value = res.data.token;
          userInfo.value = {
            username: loginData.username,
            role: res.data.role || "USER",
          };

          // 【关键修复】直接更新localStorage
          setToken(res.data.token);
          setUserInfo(userInfo.value);

          console.log("Pinia store: 登录成功，token和userInfo已更新");
        } else {
          throw new Error("登录成功，但响应数据格式不正确");
        }
      } catch (error) {
        console.error("Pinia store在登录时捕获到错误:", error);
        // 清空状态
        token.value = null;
        userInfo.value = {};
        // 清空localStorage
        removeToken();
        removeUserInfo();
        throw error;
      }
    };

    const logout = () => {
      // 清空状态
      token.value = null;
      userInfo.value = {};
      // 【关键修复】清空localStorage
      removeToken();
      removeUserInfo();
      // 跳转到登录页
      router.push("/login");
    };

    return {
      token,
      userInfo,
      login,
      logout,
    };
  }
  // 【关键修复】不再使用pinia的持久化插件
  // {
  //   persist: {
  //     paths: ["token", "role", "userInfo"],
  //   },
  // }
);