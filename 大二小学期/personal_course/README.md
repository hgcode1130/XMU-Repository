# 📚 个人课表管理系统

> 基于 Vue 3 + Spring Boot 的现代化课表管理平台

[![Vue 3](https://img.shields.io/badge/Vue-3.x-4FC08D?style=flat-square&logo=vue.js)](https://vuejs.org/)
[![Spring Boot](https://img.shields.io/badge/Spring%20Boot-3.5.3-6DB33F?style=flat-square&logo=spring)](https://spring.io/projects/spring-boot)
[![MySQL](https://img.shields.io/badge/MySQL-8.0+-4479A1?style=flat-square&logo=mysql)](https://www.mysql.com/)

## 🎯 项目简介

个人课表管理系统是一个功能完整的现代化 Web 应用，专为学生和教师设计，提供直观的课程管理、多视图展示和便捷的数据导入功能。系统采用前后端分离架构，支持多用户管理和权限控制。

### ✨ 核心特性

- 🗓️ **多视图展示** - 周视图、日视图、学期视图满足不同需求
- 📊 **Excel 导入导出** - 支持批量导入课程数据，提供标准模板
- 🏷️ **课程标签管理** - 必修/选修课程分类标识
- 👥 **多用户支持** - 用户数据隔离，管理员权限控制
- 🎨 **主题切换** - 支持日间/夜间模式
- 📱 **响应式设计** - 适配桌面端、平板、移动设备
- 🔐 **安全认证** - JWT Token 认证，BCrypt 密码加密

## 🛠️ 技术栈

### 前端技术

- **框架**: Vue 3 + Composition API
- **构建工具**: Vite
- **UI 组件**: Element Plus
- **状态管理**: Pinia
- **路由**: Vue Router 4
- **HTTP 客户端**: Axios

### 后端技术

- **框架**: Spring Boot 3.5.3
- **数据访问**: MyBatis
- **数据库**: MySQL 8.0+
- **认证**: JWT + Spring Security
- **文档处理**: Apache POI
- **构建工具**: Maven

## 🚀 快速开始

### 环境要求

- **Node.js**: 16.0+
- **Java**: 17+
- **MySQL**: 8.0+
- **Maven**: 3.6+

### 1. 克隆项目

```bash
git clone https://github.com/hgcode1130/PersonalCoursesManagement.git
cd PersonalCoursesManagement
```

### 2. 数据库配置

```sql
CREATE DATABASE personal_courses_db CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
```

### 3. 环境变量配置

在系统环境变量中设置：

```bash
DB_URL=jdbc:mysql://localhost:3306/personal_courses_db
DB_USERNAME=root
DB_PASSWORD=your_password
SPRING_PROFILES_ACTIVE=dev
```

### 4. 启动后端服务

```bash
cd back-end
mvn clean install
mvn spring-boot:run
```

后端服务将在 `http://localhost:8080` 启动

### 5. 启动前端服务

```bash
cd front-end
npm install
npm run dev
```

前端应用将在 `http://localhost:5173` 启动

### 6. 验证部署

- 前端地址：http://localhost:5173
- 后端地址：http://localhost:8080
- 测试账户：
  - 管理员：用户名 `admin`，密码 `123456`
  - 普通用户：用户名 `testuser`，密码 `123456`

## 📋 主要功能

### 课程管理

- ✅ 课程增删改查
- ✅ 多排程支持（一门课程多个上课时间）
- ✅ 课程搜索与筛选
- ✅ 时间冲突检测

### 学期管理

- ✅ 学期创建与编辑
- ✅ 学期切换
- ✅ 级联删除保护

### 数据导入导出

- ✅ Excel 模板下载
- ✅ 批量课程导入
- ✅ 导入结果统计
- ✅ 错误信息反馈

### 用户系统

- ✅ 用户注册登录
- ✅ 权限角色管理（管理员/普通用户）
- ✅ 个人数据隔离
- ✅ 用户状态管理

### 界面体验

- ✅ 响应式布局
- ✅ 主题切换
- ✅ 流畅动画
- ✅ 友好的错误提示

## 📁 项目结构

```
PersonalCoursesManagement/
├── front-end/                 # Vue 3 前端应用
│   ├── src/
│   │   ├── api/               # API 接口层
│   │   ├── components/        # 可复用组件
│   │   ├── views/             # 页面组件
│   │   ├── stores/            # Pinia 状态管理
│   │   └── router/            # 路由配置
│   └── package.json
│
├── back-end/                  # Spring Boot 后端应用
│   ├── src/main/java/
│   │   └── com/re0hg/backend/
│   │       ├── controller/    # 控制器层
│   │       ├── service/       # 业务逻辑层
│   │       ├── mapper/        # 数据访问层
│   │       └── pojo/          # 实体类
│   └── pom.xml
│
└── docs/                      # 项目文档
    ├── 设计文档.md
    ├── api接口文档.md
    ├── front-end.md
    └── back-end/架构.md
```

## 🔧 开发说明

### API 接口

系统提供完整的 RESTful API，主要接口包括：

- **认证相关**: `/api/auth/login`, `/api/auth/register`
- **课程管理**: `/api/courses`, `/api/terms/{termId}/courses`
- **学期管理**: `/api/terms`
- **Excel 导入**: `/api/import/excel`, `/api/import/excel/template`
- **用户管理**: `/api/admin/users` (管理员功能)

详细的 API 文档请参考 [`api接口文档.md`](api接口文档.md)

### 数据库设计

系统采用关系型数据库设计，核心表结构：

- **users** - 用户表
- **terms** - 学期表
- **courses** - 课程表
- **schedule_entries** - 排程表

## 📖 文档资源

- 📋 [项目设计文档](设计文档.md) - 系统架构与需求分析
- 🔌 [API 接口文档](api接口文档.md) - 完整的后端接口说明
- 🎨 [前端架构文档](front-end.md) - Vue 3 前端实现详解
- ⚙️ [后端架构文档](back-end/架构.md) - Spring Boot 后端设计

## 🤝 贡献指南

欢迎提交 Issue 和 Pull Request！

1. Fork 本仓库
2. 创建您的特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交您的更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启一个 Pull Request

## 👨‍💻 作者

**re0hg** - [GitHub](https://github.com/hgcode1130)

---

⭐ 如果这个项目对您有帮助，请给个星标支持！
