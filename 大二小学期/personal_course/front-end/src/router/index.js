import { createRouter, createWebHistory } from "vue-router";
import { useUserStore } from "@/stores/user";
import { getToken } from "@/utils/auth";
// ... (导入组件和 routes 数组的代码保持不变)
import Layout from "@/layout/index.vue";
import Login from "@/views/login/index.vue";
import TimetableView from "@/views/timetable/index.vue";
import TermsView from "@/views/terms/index.vue";
import Register from "@/views/register/index.vue";

const routes = [
  { path: "/login", name: "Login", component: Login },
  {
    path: "/",
    component: Layout,
    redirect: "/timetable",
    children: [
      {
        path: "timetable",
        name: "Timetable",
        component: TimetableView,
        meta: { title: "课表视图" },
      },
      {
        path: "terms",
        name: "Terms",
        component: TermsView,
        meta: { title: "学期管理" },
      },
    ],
  },
  {
    path: "/register",
    name: "Register",
    component: Register,
    meta: { title: "注册" },
  },
  {
    path: "/manage",
    component: Layout,
    redirect: "/manage/users",
    meta: { requiresAuth: true, roles: ["ADMIN"] },
    children: [
      {
        path: "users",
        name: "manage-users",
        component: () => import("@/views/manage/index.vue"),
        meta: { title: "用户管理", icon: "user" },
      },
    ],
  },
];

const router = createRouter({
  history: createWebHistory(),
  routes,
});

// 全局前置导航守卫
router.beforeEach((to, from, next) => {
  // 【关键修复】直接从localStorage获取token，不再依赖Pinia store
  const hasToken = getToken();

  if (hasToken) {
    // --- 用户已登录 ---
    if (to.path === "/login" || to.path === "/register") {
      return next({ path: "/" });
    }

    // 权限检查
    const userStore = useUserStore();
    const requiresAdmin = to.meta.roles?.includes("ADMIN");

    if (requiresAdmin && userStore.userInfo.role !== "ADMIN") {
      return next({ path: "/" });
    }

    return next();
  } else {
    // --- 用户未登录 ---
    const whiteList = ["/login", "/register"];
    if (whiteList.includes(to.path)) {
      return next();
    }
    return next({ path: "/login", query: { redirect: to.fullPath } });
  }
});


export default router;
