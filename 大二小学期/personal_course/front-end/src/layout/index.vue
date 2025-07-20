<template>
  <el-container class="layout-container">
    <el-aside width="220px" class="layout-aside">
      <div class="logo-container">
        <el-icon :size="24" style="margin-right: 8px"><Calendar /></el-icon>
        <span>个人课表系统</span>
      </div>
      
      <!-- 学期选择器 -->
      <div class="term-selector-container">
        <div class="term-selector-label">当前学期</div>
        <el-select
          v-model="termStore.currentTermId"
          @change="handleTermChange"
          placeholder="请选择学期"
          class="term-selector"
          filterable
          :loading="termLoading"
        >
          <el-option
            v-for="term in termStore.termList"
            :key="term.id"
            :label="term.name"
            :value="term.id"
          >
            <div class="term-option">
              <div class="term-name">{{ term.name }}</div>
              <div class="term-date" v-if="term.startDate && term.endDate">
                {{ formatDate(term.startDate) }} ~ {{ formatDate(term.endDate) }}
              </div>
            </div>
          </el-option>
        </el-select>
        
        <!-- 如果没有学期，显示提示 -->
        <div v-if="termStore.termList.length === 0 && !termLoading" class="no-terms-hint">
          <el-text type="info" size="small">暂无学期，请前往</el-text>
          <el-button text type="primary" size="small" @click="$router.push('/terms')">
            学期管理
          </el-button>
          <el-text type="info" size="small">创建</el-text>
        </div>
      </div>

      <el-menu :default-active="$route.path" router class="layout-menu">
        <el-menu-item index="/timetable">
          <el-icon><Calendar /></el-icon>
          <span>课表视图</span>
        </el-menu-item>
        <el-menu-item index="/terms">
          <el-icon><Management /></el-icon>
          <span>学期管理</span>
        </el-menu-item>
        <el-menu-item v-if="isAdmin" index="/manage/users">
          <el-icon><User /></el-icon>
          <span>用户管理</span>
        </el-menu-item>
      </el-menu>
    </el-aside>

    <el-container>
      <el-header class="layout-header">
        <div class="header-left">
          <!-- 面包屑导航 -->
          <el-breadcrumb separator="/" class="breadcrumb">
            <el-breadcrumb-item>
              <el-icon><House /></el-icon>
              个人课表系统
            </el-breadcrumb-item>
            <el-breadcrumb-item v-if="$route.meta.title">
              {{ $route.meta.title }}
            </el-breadcrumb-item>
          </el-breadcrumb>
        </div>
        <div class="header-right">
          <!-- 当前学期显示 -->
          <div class="current-term-display" v-if="termStore.currentTerm">
            <el-icon><Calendar /></el-icon>
            <span>{{ termStore.currentTerm.name }}</span>
          </div>
          
          <el-divider direction="vertical" />
          
          <!-- 主题切换 -->
          <el-switch
            v-model="isNightMode"
            @change="themeStore.toggleTheme"
            inline-prompt
            :active-icon="Moon"
            :inactive-icon="Sunny"
            style="margin-right: 20px"
          />
          
          <!-- 用户菜单 -->
          <el-dropdown>
            <span class="el-dropdown-link">
              <el-avatar :size="32" style="margin-right: 8px">
                {{ userStore.userInfo.username?.[0]?.toUpperCase() || "U" }}
              </el-avatar>
              {{ userStore.userInfo.username || "用户名" }}
              <el-icon class="el-icon--right"><arrow-down /></el-icon>
            </span>
            <template #dropdown>
              <el-dropdown-menu>
                <el-dropdown-item disabled>
                  <el-tag :type="getRoleTagType()" size="small">
                    {{ getRoleDisplayName() }}
                  </el-tag>
                </el-dropdown-item>
                <el-dropdown-item divided @click="handleLogout">
                  <el-icon><SwitchButton /></el-icon>
                  退出登录
                </el-dropdown-item>
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
import { computed, ref, onMounted } from "vue";
import { useUserStore } from "@/stores/user";
import { useTermStore } from "@/stores/term";
import { useThemeStore } from "@/stores/theme";
import { useRouter } from "vue-router";
import { ElMessage } from "element-plus";
import {
  Calendar,
  Management,
  User,
  House,
  ArrowDown,
  Sunny,
  Moon,
  SwitchButton,
} from "@element-plus/icons-vue";

const userStore = useUserStore();
const termStore = useTermStore();
const themeStore = useThemeStore();
const router = useRouter();
const termLoading = ref(false);

const isAdmin = computed(
  () => userStore.userInfo && userStore.userInfo.role === "ADMIN"
);
const isNightMode = computed(() => themeStore.currentTheme === "night");

// 格式化日期显示
const formatDate = (dateStr) => {
  if (!dateStr) return '';
  const date = new Date(dateStr);
  return `${date.getMonth() + 1}/${date.getDate()}`;
};

// 获取角色显示名称
const getRoleDisplayName = () => {
  const role = userStore.userInfo?.role;
  switch (role) {
    case 'ADMIN': return '管理员';
    case 'USER': return '普通用户';
    case 'TRIAL': return '试用用户';
    default: return '未知角色';
  }
};

// 获取角色标签类型
const getRoleTagType = () => {
  const role = userStore.userInfo?.role;
  switch (role) {
    case 'ADMIN': return 'danger';
    case 'USER': return 'success';
    case 'TRIAL': return 'warning';
    default: return 'info';
  }
};

// 处理学期切换
const handleTermChange = (termId) => {
  termStore.setTerm(termId);
  ElMessage.success(`已切换到：${termStore.currentTerm?.name}`);
};

// 初始化学期数据
const initTerms = async () => {
  termLoading.value = true;
  try {
    await termStore.fetchAllTerms();
    
    // 如果没有当前选中的学期，自动选择最近的学期
    if (!termStore.currentTermId && termStore.termList.length > 0) {
      // 按创建时间降序排序，选择最新的学期
      const sortedTerms = [...termStore.termList].sort((a, b) => 
        new Date(b.createdAt || b.startDate) - new Date(a.createdAt || a.startDate)
      );
      termStore.setTerm(sortedTerms[0].id);
    }
  } catch (error) {
    console.error("初始化学期数据失败", error);
  } finally {
    termLoading.value = false;
  }
};

const handleLogout = () => {
  userStore.logout();
  ElMessage.success("已成功退出登录");
  router.push('/login');
};

onMounted(() => {
  initTerms();
});
</script>

<style scoped>
/* 使用 CSS 变量来定义样式 */
.layout-container {
  height: 100vh;
  background-color: var(--layout-bg-color);
}

.layout-aside {
  background-color: var(--sidebar-bg-color);
  color: var(--sidebar-text-color);
  display: flex;
  flex-direction: column;
  border-right: 1px solid var(--header-border-color);
}

.logo-container {
  display: flex;
  align-items: center;
  justify-content: center;
  height: 60px;
  background-color: var(--sidebar-logo-bg-color);
  color: #fff;
  font-size: 16px;
  font-weight: bold;
  border-bottom: 1px solid rgba(255, 255, 255, 0.1);
}

/* 学期选择器样式 */
.term-selector-container {
  padding: 20px 16px;
  border-bottom: 1px solid rgba(255, 255, 255, 0.1);
}

.term-selector-label {
  font-size: 12px;
  color: var(--sidebar-text-color);
  margin-bottom: 8px;
  opacity: 0.8;
}

.term-selector {
  width: 100%;
}

.term-selector :deep(.el-input__inner) {
  background-color: rgba(255, 255, 255, 0.1);
  border-color: rgba(255, 255, 255, 0.2);
  color: #fff;
}

.term-selector :deep(.el-input__inner):focus {
  border-color: var(--sidebar-active-text-color);
}

.term-selector :deep(.el-input__inner::placeholder) {
  color: rgba(255, 255, 255, 0.6);
}

.term-option {
  padding: 4px 0;
}

.term-name {
  font-size: 14px;
  font-weight: 500;
  color: #303133;
}

.term-date {
  font-size: 12px;
  color: #909399;
  margin-top: 2px;
}

.no-terms-hint {
  text-align: center;
  padding: 12px;
  background-color: rgba(255, 255, 255, 0.05);
  border-radius: 4px;
  font-size: 12px;
}

.layout-menu {
  flex: 1;
  border: none;
  background-color: transparent;
  --el-menu-text-color: var(--sidebar-text-color);
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
  padding: 0 24px;
  box-shadow: 0 1px 4px rgba(0, 0, 0, 0.08);
}

.header-left {
  display: flex;
  align-items: center;
}

.breadcrumb {
  font-size: 14px;
}

.breadcrumb :deep(.el-breadcrumb__item) {
  color: var(--header-text-color);
}

.header-right {
  display: flex;
  align-items: center;
  gap: 16px;
}

.current-term-display {
  display: flex;
  align-items: center;
  gap: 6px;
  font-size: 14px;
  color: var(--header-text-color);
  background-color: var(--el-color-primary-light-9);
  padding: 6px 12px;
  border-radius: 16px;
  border: 1px solid var(--el-color-primary-light-7);
}

.el-dropdown-link {
  cursor: pointer;
  display: flex;
  align-items: center;
  color: var(--header-text-color);
  font-size: 14px;
  transition: color 0.3s ease;
}

.el-dropdown-link:hover {
  color: var(--el-color-primary);
}

.layout-main {
  padding: 24px;
  background-color: var(--main-bg-color);
  background-image: var(--main-bg-image);
  background-size: var(--main-bg-size);
  transition: background-color 0.3s ease;
  overflow-y: auto;
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

/* 响应式设计 */
@media (max-width: 768px) {
  .layout-aside {
    width: 60px !important;
  }
  
  .logo-container span {
    display: none;
  }
  
  .term-selector-container {
    display: none;
  }
  
  .layout-menu :deep(.el-menu-item span) {
    display: none;
  }
  
  .header-left .breadcrumb {
    display: none;
  }
  
  .current-term-display span {
    display: none;
  }
  
  .el-dropdown-link span {
    display: none;
  }
}

/* 优化滚动条样式 */
.layout-main::-webkit-scrollbar {
  width: 6px;
}

.layout-main::-webkit-scrollbar-track {
  background: transparent;
}

.layout-main::-webkit-scrollbar-thumb {
  background-color: rgba(0, 0, 0, 0.2);
  border-radius: 3px;
}

.layout-main::-webkit-scrollbar-thumb:hover {
  background-color: rgba(0, 0, 0, 0.3);
}
</style>