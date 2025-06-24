<template>
  <el-container class="layout-container">
    <el-aside width="220px" class="layout-aside">
      <div class="logo-container">
        <el-icon :size="24" style="margin-right: 8px"><Calendar /></el-icon>
        <span>个人课表系统</span>
      </div>
      <el-menu :default-active="$route.path" router class="layout-menu">
        <el-menu-item index="/timetable">
          <el-icon><Calendar /></el-icon>
          <i class="el-icon-setting"></i>
          <span>课表视图</span>
        </el-menu-item>
        <el-menu-item index="/terms">
          <el-icon><Management /></el-icon>
          <i class="el-icon-setting"></i>
          <span>学期管理</span>
        </el-menu-item>
        <el-menu-item v-if="isAdmin" index="/manage/users">
          <el-icon><User /></el-icon>
          <i class="el-icon-setting"></i>
          <span>用户管理</span>
        </el-menu-item>
      </el-menu>
    </el-aside>

    <el-container>
      <el-header class="layout-header">
        <div class="header-left">
          <!-- 可以放置面包屑导航等 -->
        </div>
        <div class="header-right">
          <el-switch
            v-model="isNightMode"
            @change="themeStore.toggleTheme"
            inline-prompt
            :active-icon="Moon"
            :inactive-icon="Sunny"
            style="margin-right: 20px"
          />
          <el-dropdown>
            <span class="el-dropdown-link">
              {{ userStore.userInfo.username || "用户名" }}
              <el-icon class="el-icon--right"><arrow-down /></el-icon>
            </span>
            <template #dropdown>
              <el-dropdown-menu>
                <el-dropdown-item @click="handleLogout"
                  >退出登录</el-dropdown-item
                >
              </el-dropdown-menu>
            </template>
          </el-dropdown>
        </div>
      </el-header>

      <el-main class="layout-main">
        <router-view v-slot="{ Component }">
          <transition name="fade-transform" mode="out-in">
            <component :is="Component" />
          </transition>
        </router-view>
      </el-main>
    </el-container>
  </el-container>
</template>

<script setup>
import { computed } from "vue";
import { useUserStore } from "@/stores/user";
import { useThemeStore } from "@/stores/theme";
import { useRouter } from "vue-router";
import {
  Calendar,
  Management,
  ArrowDown,
  Sunny,
  Moon,
} from "@element-plus/icons-vue";

const userStore = useUserStore();
const themeStore = useThemeStore();
const router = useRouter();
const isAdmin = computed(
  () => userStore.userInfo && userStore.userInfo.role === "ADMIN"
);
const isNightMode = computed(() => themeStore.currentTheme === "night");

const handleLogout = () => {
  userStore.logout();
  ElMessage.success("已成功退出登录");
};
</script>

<style scoped>
/* 使用 CSS 变量来定义样式 */
.layout-container {
  height: 100%;
  background-color: var(--layout-bg-color);
  transition: background-color 0.3s ease;
}

.layout-aside {
  background-color: var(--sidebar-bg-color);
  color: var(--sidebar-text-color);
  transition: background-color 0.3s ease;
  box-shadow: 2px 0 6px rgba(0, 21, 41, 0.15);
  z-index: 10;
}

.logo-container {
  display: flex;
  align-items: center;
  justify-content: center;
  height: 60px;
  font-size: 20px;
  font-weight: bold;
  color: #fff;
  background-color: var(--sidebar-logo-bg-color);
  transition: background-color 0.3s ease;
}

.layout-menu {
  border-right: none;
  background-color: var(--sidebar-bg-color);
  --el-menu-text-color: var(--sidebar-text-color);
  --el-menu-hover-bg-color: rgba(255, 255, 255, 0.1);
  --el-menu-active-color: var(--sidebar-active-text-color);
  transition: background-color 0.3s ease;
}

.layout-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  background-color: var(--header-bg-color);
  border-bottom: 1px solid var(--header-border-color);
  color: var(--header-text-color);
  transition: background-color 0.3s ease, border-color 0.3s ease;
}

.header-right {
  display: flex;
  align-items: center;
}

.el-dropdown-link {
  cursor: pointer;
  display: flex;
  align-items: center;
  color: var(--header-text-color);
}

.layout-main {
  padding: 20px;
  background-color: var(--main-bg-color);
  background-image: var(--main-bg-image);
  background-size: var(--main-bg-size);
  transition: background-color 0.3s ease;
}

/* 路由切换动画 */
.fade-transform-leave-active,
.fade-transform-enter-active {
  transition: all 0.3s;
}

.fade-transform-enter-from {
  opacity: 0;
  transform: translateX(-30px);
}

.fade-transform-leave-to {
  opacity: 0;
  transform: translateX(30px);
}
</style>
