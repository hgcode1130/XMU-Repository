# **个人课表系统 - 前端设计文档 (v3.0)**

> **文档版本**: v3.0  
> **更新日期**: 2025 年 7 月 1 日  
> **项目状态**: 生产就绪

---

## **1. 前端技术栈与架构概览**

### **1.1 核心技术栈**

- **框架**: `Vue 3` + `Composition API` (基于 `Vite` 构建工具)
- **UI 组件库**: `Element Plus` (企业级组件库)
- **状态管理**: `Pinia` (Vue 3 官方推荐)
- **HTTP 请求**: `Axios` (统一请求/响应拦截器)
- **路由管理**: `Vue Router` (支持权限守卫)
- **样式方案**: 响应式设计 + 主题切换支持

### **1.2 项目架构特色**

- **🎨 双主题模式**: 支持日间/夜间主题切换
- **🔐 三级权限体系**: ADMIN / USER / TRIAL 用户分级管理
- **📱 响应式设计**: 适配桌面端、平板、移动设备
- **🚀 组件化开发**: 高度复用的业务组件
- **⚡ 性能优化**: 懒加载路由、虚拟滚动

### **1.3 设计理念**

- **现代化界面**: 扁平化设计，毛玻璃效果，柔和阴影
- **用户体验至上**: 直观的操作流程，友好的错误提示
- **数据可视化**: 统计图表、标签分类、状态指示器
- **无障碍支持**: 键盘导航、高对比度模式

---

## **2. 项目结构与组件架构**

### **2.1 目录结构**

```
front-end/
├── public/                     # 静态资源
│   ├── favicon.ico
├── src/
│   ├── api/                    # API 接口层
│   │   ├── request.js          # Axios 封装
│   │   ├── auth.js             # 认证相关接口
│   │   ├── course.js           # 课程管理接口
│   │   ├── term.js             # 学期管理接口
│   │   └── admin.js            # 管理员功能接口
│   │
│   ├── assets/                 # 资源文件
│   │   ├── css/
│   │   │   ├── main.css        # 全局样式
│   │   │   └── theme.css       # 主题样式变量
│   │   └── images/
│   │       ├── logo.svg
│   │       └── xmu-campus-1.jpg
│   │
│   ├── components/             # 业务组件
│   │   ├── CourseFormDialog.vue    # 课程添加/编辑对话框
│   │   ├── ExcelImportDialog.vue   # Excel导入对话框
│   │   ├── WeeklyGridView.vue      # 周视图网格组件
│   │   └── DailyGridView.vue       # 日视图网格组件
│   │
│   ├── layout/                 # 布局组件
│   │   └── index.vue           # 主布局框架
│   │
│   ├── router/                 # 路由配置
│   │   └── index.js            # 路由规则与权限守卫
│   │
│   ├── stores/                 # Pinia 状态管理
│   │   ├── index.js            # Pinia 实例
│   │   ├── user.js             # 用户状态管理
│   │   ├── term.js             # 学期数据管理
│   │   └── theme.js            # 主题状态管理
│   │
│   ├── utils/                  # 工具函数
│   │   ├── index.js            # 通用工具
│   │   └── auth.js             # 认证工具
│   │
│   ├── views/                  # 页面组件
│   │   ├── login/index.vue     # 登录页
│   │   ├── register/index.vue  # 注册页
│   │   ├── timetable/index.vue # 课表管理页
│   │   ├── terms/index.vue     # 学期管理页
│   │   └── manage/index.vue    # 用户管理页(管理员)
│   │
│   ├── App.vue                 # 根组件
│   └── main.js                 # 应用入口
```

### **2.2 核心组件设计**

#### **布局组件 (Layout)**

- **主框架**: 侧边栏 + 顶部栏 + 内容区的经典布局
- **侧边栏**: 学期选择器 + 导航菜单 + 权限控制
- **顶部栏**: 面包屑导航 + 学期显示 + 主题切换 + 用户菜单

#### **业务组件**

- **[`CourseFormDialog.vue`](front-end/src/components/CourseFormDialog.vue)**: 复用性课程表单对话框
- **[`ExcelImportDialog.vue`](front-end/src/components/ExcelImportDialog.vue)**: Excel 批量导入组件
- **[`WeeklyGridView.vue`](front-end/src/components/WeeklyGridView.vue)**: 周视图网格布局
- **[`DailyGridView.vue`](front-end/src/components/DailyGridView.vue)**: 日视图网格布局

---

## **3. 页面功能详细设计**

### **3.1 认证页面**

#### **3.1.1 登录页面 (`/login`)**

**设计特色**:

- 渐变背景 + 浮动装饰元素
- 左右分栏布局：信息面板 + 登录表单
- 毛玻璃效果卡片设计

**功能实现**:

```vue
// 核心功能 const handleLogin = async () => { loginFormRef.value.validate(async
(valid) => { if (valid) { await userStore.login(loginForm);
ElMessage.success('登录成功！'); router.push('/'); } }); };
```

**组件使用**:

- `el-card`: 登录卡片容器
- `el-form`: 表单验证与提交
- `el-input`: 用户名/密码输入框
- `el-button`: 登录按钮(支持加载状态)

**API 集成**: `POST /api/auth/login`

#### **3.1.2 注册页面 (`/register`)**

**设计亮点**:

- 优雅的左侧产品介绍面板
- 多步骤表单验证
- 服务条款确认机制

**表单字段**:

- 用户名(3-20 字符)
- 邮箱地址(格式验证)
- 密码(6-20 字符)
- 确认密码(一致性校验)

**API 集成**: `POST /api/auth/register`

### **3.2 课表管理页面 (`/timetable`)**

这是系统的核心页面，支持多种视图模式和丰富的交互功能。

#### **3.2.1 页面整体布局**

**顶部区域**:

- 页面标题 + 学期信息显示
- 操作按钮：添加课程、Excel 导入
- 视图切换选项卡：周视图 | 日视图 | 学期视图

**主要功能**:

- 课程的增删改查操作
- 多种视图模式展示
- Excel 批量导入/模板下载
- 高级搜索与筛选

#### **3.2.2 周视图 (WeeklyGridView)**

**设计特色**:

- CSS Grid 实现的 8×13 网格布局
- 智能处理课程时间冲突
- 颜色自动分配与视觉区分
- 课程详情侧边面板

**核心实现**:

```vue
// 时间冲突检测 const isTimeOverlapping = (schedule1, schedule2) => { return
schedule1.dayOfWeek === schedule2.dayOfWeek && schedule1.startPeriod <=
schedule2.endPeriod && schedule1.endPeriod >= schedule2.startPeriod } //
动态网格布局计算 const processedCourses = computed(() => { //
处理课程数据，计算CSS Grid位置 // 自动分配颜色，处理重叠显示 });
```

**交互功能**:

- 点击课程卡片查看详情
- 悬浮显示课程信息
- 侧边详情面板展示
- 必修/选修标签区分

#### **3.2.3 日视图 (DailyGridView)**

**设计理念**:

- 专注单日课程详细展示
- 垂直时间轴布局
- 优化移动端体验

**导航控制**:

```vue
const changeDay = (delta) => { const newDay = currentDay.value + delta; if
(newDay >= 1 && newDay <= 7) { currentDay.value = newDay; } };
```

#### **3.2.4 学期视图 (表格模式)**

**功能特色**:

- `el-table` 表格展示所有课程
- 可展开行显示详细排程信息
- 分页展示与性能优化
- 高级搜索筛选功能

**搜索功能**:

```vue
const searchQuery = ref({ name: null, // 课程名称 teacher: null, // 任课教师
tag: null, // 课程类型(必修/选修) dayOfWeek: null, // 上课星期 });
```

**表格列设计**:

- 展开行：显示所有排程详情
- 课程名称：带标签的课程信息
- 任课教师：教师信息展示
- 操作列：编辑/删除按钮

### **3.3 学期管理页面 (`/terms`)**

**功能清单**:

- 学期列表展示与管理
- 新建学期(名称+日期范围)
- 编辑学期信息
- 删除学期(级联删除保护)

**API 集成**:

- `GET /api/terms` - 获取学期列表
- `POST /api/terms` - 创建新学期
- `PUT /api/terms/{id}` - 更新学期
- `DELETE /api/terms/{id}` - 删除学期

### **3.4 管理员用户管理页面 (`/manage/users`)**

**权限控制**: 仅 ADMIN 角色可访问

**页面特色**:

- 渐变色页面头部设计
- 统计卡片展示用户概览
- 高级搜索筛选功能
- 用户状态实时切换

**核心功能**:

```vue
// 用户状态切换 const handleStatusChange = (user) => {
ElMessageBox.confirm(`确定要${action}用户 "${user.username}" 吗？`) .then(() =>
{ updateUserStatus(user.id, { isEnabled: user.isEnabled }); }); };
```

**搜索筛选**:

- 用户名模糊搜索
- 邮箱模糊搜索
- 角色类型筛选
- 账户状态筛选

**表格功能**:

- 用户头像 + 基本信息展示
- 角色标签化显示
- 状态开关实时切换
- 注册时间展示

---

## **4. 核心组件详细说明**

### **4.1 课程表单对话框 (CourseFormDialog)**

**组件特色**:

- 添加/编辑模式复用
- 动态排程条目管理
- 完整的表单验证

**表单字段**:

```vue
const form = reactive({ name: '', // 课程名称 teachers: '', // 任课教师
mainTeacherEmail: '', // 主讲教师邮箱 courseGroupChatId: '', // 课程群号 tag:
null, // 课程标签(必修/选修) note: '', // 课程备注 scheduleEntries: [ //
排程列表 { location: '', // 上课地点 dayOfWeek: null, // 星期 startWeek: null,
// 开始周 endWeek: null, // 结束周 startPeriod: null, // 开始节次 endPeriod:
null, // 结束节次 } ] });
```

**API 集成**:

- 添加: `POST /api/courses`
- 编辑: `PUT /api/courses/{id}`

### **4.2 Excel 导入对话框 (ExcelImportDialog)**

**功能亮点**:

- 模板下载功能
- 文件上传与验证
- 导入进度反馈
- 错误信息详细展示

**核心功能**:

```vue
// 模板下载 const handleDownloadTemplate = async () => { const response = await
downloadTemplateApi(props.termId); // 处理文件下载 }; // 文件导入 const
handleFileImport = async (file) => { const formData = new FormData();
formData.append('file', file); const result = await importExcelApi(props.termId,
formData); // 处理导入结果 };
```

**错误处理**:

- 文件格式验证
- 数据格式检查
- 导入结果统计
- 详细错误报告

### **4.3 主题切换系统**

**主题状态管理**:

```javascript
// stores/theme.js
export const useThemeStore = defineStore("theme", () => {
  const currentTheme = ref("light");

  const toggleTheme = () => {
    currentTheme.value = currentTheme.value === "light" ? "night" : "light";
    applyTheme();
  };

  const applyTheme = () => {
    document.documentElement.setAttribute("data-theme", currentTheme.value);
  };

  return { currentTheme, toggleTheme };
});
```

**CSS 变量系统**:

```css
/* assets/css/theme.css */
:root {
  --main-bg-color: #f5f7fa;
  --sidebar-bg-color: #ffffff;
  --text-primary: #303133;
}

[data-theme="night"] {
  --main-bg-color: #1a1a1a;
  --sidebar-bg-color: #2d2d2d;
  --text-primary: #e4e7ed;
}
```

---

## **5. 状态管理架构 (Pinia)**

### **5.1 用户状态管理 (user.js)**

```javascript
export const useUserStore = defineStore(
  "user",
  () => {
    const token = ref(null);
    const userInfo = ref({});

    const login = async (loginData) => {
      const res = await loginApi(loginData);
      token.value = res.data.token;
      userInfo.value = {
        username: loginData.username,
        role: res.data.role || "USER",
      };
    };

    const logout = () => {
      token.value = null;
      userInfo.value = {};
      router.push("/login");
    };

    return { token, userInfo, login, logout };
  },
  {
    persist: {
      paths: ["token", "userInfo"],
    },
  }
);
```

### **5.2 学期状态管理 (term.js)**

```javascript
export const useTermStore = defineStore("term", () => {
  const terms = ref([]);
  const currentTermId = ref(null);
  const currentTerm = computed(() =>
    terms.value.find((term) => term.id === currentTermId.value)
  );

  const fetchTerms = async () => {
    const response = await getTermsApi();
    terms.value = response.data;
  };

  return { terms, currentTermId, currentTerm, fetchTerms };
});
```

### **5.3 主题状态管理 (theme.js)**

支持持久化的主题切换，自动应用 CSS 变量。

---

## **6. 路由系统与权限控制**

### **6.1 路由配置**

```javascript
const routes = [
  { path: "/login", component: Login },
  {
    path: "/",
    component: Layout,
    redirect: "/timetable",
    children: [
      { path: "timetable", component: TimetableView },
      { path: "terms", component: TermsView },
    ],
  },
  {
    path: "/manage",
    component: Layout,
    meta: { requiresAuth: true, roles: ["ADMIN"] },
    children: [{ path: "users", component: ManageUsersView }],
  },
];
```

### **6.2 权限守卫**

```javascript
router.beforeEach((to, from, next) => {
  const hasToken = getToken();

  if (hasToken) {
    // 权限检查
    const requiresAdmin = to.meta.roles?.includes("ADMIN");
    if (requiresAdmin && userStore.userInfo.role !== "ADMIN") {
      return next({ path: "/" });
    }
    return next();
  } else {
    // 白名单检查
    const whiteList = ["/login", "/register"];
    if (whiteList.includes(to.path)) {
      return next();
    }
    return next({ path: "/login", query: { redirect: to.fullPath } });
  }
});
```

---

## **7. API 集成与请求封装**

### **7.1 Axios 统一封装**

```javascript
// api/request.js
const service = axios.create({
  baseURL: "/api",
  timeout: 10000,
});

// 请求拦截器
service.interceptors.request.use((config) => {
  const userStore = useUserStore();
  if (userStore.token) {
    config.headers["token"] = userStore.token;
  }
  return config;
});

// 响应拦截器
service.interceptors.response.use(
  (response) => response,
  (error) => {
    if (error.response?.status === 401) {
      userStore.logout();
    }
    return Promise.reject(error);
  }
);
```

### **7.2 API 模块化管理**

- **[`auth.js`](front-end/src/api/auth.js)**: 登录、注册、权限验证
- **[`course.js`](front-end/src/api/course.js)**: 课程 CRUD、搜索、Excel 导入
- **[`term.js`](front-end/src/api/term.js)**: 学期管理相关接口
- **[`admin.js`](front-end/src/api/admin.js)**: 管理员功能接口

---

## **8. 响应式设计与兼容性**

### **8.1 断点设计**

```css
/* 响应式断点 */
@media (max-width: 768px) {
  .timetable-grid {
    grid-template-columns: 60px repeat(7, minmax(80px, 1fr));
  }
}

@media (max-width: 1024px) {
  .layout-aside {
    width: 60px !important;
  }

  .course-detail-panel {
    width: 100vw;
  }
}
```

### **8.2 移动端优化**

- 侧边栏自动收缩
- 触摸友好的操作区域
- 简化的课程卡片显示
- 优化的详情面板

### **8.3 浏览器兼容性**

- **现代浏览器**: Chrome 90+, Firefox 88+, Safari 14+
- **CSS 特性**: Grid Layout, Flexbox, CSS Variables
- **JavaScript**: ES2020+ 语法支持

---

## **9. 性能优化策略**

### **9.1 代码层面优化**

- **路由懒加载**: 动态 import() 语法
- **组件按需加载**: Tree-shaking 优化
- **计算属性缓存**: Vue 3 响应式系统
- **防抖节流**: 搜索输入优化

### **9.2 渲染性能优化**

```vue
<!-- 虚拟滚动 -->
<el-table :data="paginatedCourses" v-loading="loading" virtual-scroll />

<!-- 条件渲染优化 -->
<template v-if="activeView === 'week'">
  <WeeklyGridView :courses="coursesForCurrentWeek" />
</template>
```

### **9.3 网络请求优化**

- 请求去重与缓存
- 分页加载策略
- 错误重试机制
- 接口响应时间监控

---

## **10. 开发规范与最佳实践**

### **10.1 代码规范**

- **Vue 3 Composition API**: 统一使用组合式 API
- **ESLint + Prettier**: 代码格式化与规范检查
- **命名规范**: 驼峰命名、语义化变量名
- **注释规范**: JSDoc 文档注释

### **10.2 组件设计原则**

- **单一职责**: 每个组件职责明确
- **可复用性**: 通过 props 和 slots 提高复用
- **可测试性**: 逻辑与视图分离
- **可维护性**: 清晰的组件接口设计

### **10.3 状态管理最佳实践**

```javascript
// 推荐的 Pinia Store 结构
export const useExampleStore = defineStore('example', () => {
  // State
  const data = ref([]);

  // Getters
  const filteredData = computed(() => /* ... */);

  // Actions
  const fetchData = async () => { /* ... */ };

  return { data, filteredData, fetchData };
});
```

---

## **11. 部署与构建配置**

### **11.1 Vite 构建配置**

```javascript
// vite.config.js
export default defineConfig({
  plugins: [vue()],
  build: {
    rollupOptions: {
      output: {
        manualChunks: {
          vendor: ["vue", "vue-router", "pinia"],
          element: ["element-plus"],
        },
      },
    },
  },
  server: {
    proxy: {
      "/api": {
        target: "http://localhost:8080",
        changeOrigin: true,
      },
    },
  },
});
```

### **11.2 环境配置**

- **开发环境**: Hot Module Replacement
- **生产环境**: 代码压缩、资源优化
- **测试环境**: Mock 数据支持

---

## **12. 总结与展望**

### **12.1 项目成果**

✅ **完整的前端架构**: 基于 Vue 3 + Element Plus 的现代化前端应用  
✅ **丰富的功能模块**: 课表管理、用户系统、权限控制  
✅ **优秀的用户体验**: 响应式设计、主题切换、流畅交互  
✅ **高质量代码**: 组件化开发、状态管理、错误处理

### **12.2 技术亮点**

1. **智能课表网格**: CSS Grid + 算法实现的课程时间冲突处理
2. **Excel 批量导入**: 文件上传、模板下载、错误处理一体化
3. **权限管理体系**: 基于角色的访问控制(RBAC)
4. **主题切换系统**: CSS 变量 + Pinia 状态管理
5. **响应式设计**: 适配多种设备的优秀用户体验

### **12.3 未来扩展方向**

🚀 **功能扩展**: 课程提醒、数据导出、课表分享  
🎨 **UI 增强**: 更多主题选项、动画效果、微交互  
📱 **移动端**: PWA 支持、原生应用开发  
🔍 **数据分析**: 学习统计、时间分析、个性化推荐

---

**文档维护**: 本文档将随项目发展持续更新，确保与实际实现保持同步。
