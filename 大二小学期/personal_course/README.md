# 个人课表管理系统

> 一个功能完整的个人课表管理系统，支持多学期管理、课程标签分类、Excel 批量导入等功能

## 📋 项目概述

个人课表管理系统是一个基于 Spring Boot + Vue 3 的全栈 Web 应用，为用户提供私人的、灵活的、支持多学期的课表管理工具。

### ✨ 主要功能

- 🔐 **用户认证系统**：注册/登录、JWT 认证、角色权限管理
- 📅 **学期管理**：创建、编辑、删除学期，支持分页查询
- 📚 **课程管理**：手动添加课程、支持必修/选修标签、复杂排课时间
- 📊 **多视图展示**：周视图、学期视图、日视图
- 📝 **Excel 导入**：批量导入课程数据，支持标签识别
- 👨‍💼 **管理员功能**：用户管理、权限控制
- 🎨 **响应式设计**：基于 Element Plus 的现代化界面

### 🛠 技术栈

#### 后端技术栈

- **框架**：Spring Boot 3.5.3
- **数据库**：MySQL 8.0+
- **ORM**：JPA + MyBatis
- **认证**：JWT (JSON Web Token)
- **构建工具**：Maven
- **JDK 版本**：Java 21
- **其他依赖**：
  - Spring Security (密码加密)
  - PageHelper (分页)
  - Druid (数据库连接池)
  - 阿里云 OSS SDK (文件存储)
  - FastJSON2 (JSON 处理)

#### 前端技术栈

- **框架**：Vue 3 + Vite
- **UI 组件库**：Element Plus
- **状态管理**：Pinia
- **路由**：Vue Router 4
- **HTTP 客户端**：Axios
- **构建工具**：Vite

#### 数据库设计

- **用户表** (users)：支持角色权限管理
- **学期表** (terms)：多学期支持
- **课程表** (courses)：课程基本信息 + 标签
- **排课表** (schedule_entries)：复杂排课时间管理

## 🚀 快速开始

### 环境要求

- **JDK 21** 或更高版本
- **Node.js 16** 或更高版本
- **MySQL 8.0** 或更高版本
- **Maven 3.6** 或更高版本

### 1. 克隆项目

```bash
git clone https://github.com/hgcode1130/PersonalCoursesManagement.git
cd PersonalCoursesManagement
```

### 2. 数据库配置

#### 创建数据库

```sql
CREATE DATABASE personal_courses_db CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
```

#### 运行初始化脚本

```bash
# 使用项目提供的 Data.py 生成测试数据
python Data.py
# 将生成的SQL文件导入到MySQL数据库中
```

### 3. 环境变量配置

在 Windows 11 中设置以下环境变量：

#### 方法 1：系统环境变量

1. 按 `Win + R`，输入 `sysdm.cpl`
2. 点击"高级"选项卡 → "环境变量"
3. 在"用户变量"中添加以下变量：

```bash
# 数据库配置
DB_URL=jdbc:mysql://localhost:3306/personal_courses_db
DB_USERNAME=root
DB_PASSWORD=your_password

# 阿里云OSS配置 (可选，用于文件上传)
ALIYUN_OSS_ACCESS_KEY_ID=your_access_key_id
ALIYUN_OSS_ACCESS_KEY_SECRET=your_access_key_secret
ALIYUN_OSS_BUCKET_NAME=your_bucket_name
ALIYUN_OSS_ENDPOINT=https://oss-cn-hangzhou.aliyuncs.com

# Spring Profile
SPRING_PROFILES_ACTIVE=dev
```

#### 方法 2：临时设置 (PowerShell)

```powershell
$env:DB_URL="jdbc:mysql://localhost:3306/personal_courses_db"
$env:DB_USERNAME="root"
$env:DB_PASSWORD="your_password"
$env:SPRING_PROFILES_ACTIVE="dev"
```

### 4. 启动后端服务

```bash
cd back-end

# 安装依赖并启动
mvn clean install
mvn spring-boot:run

# 或者使用 Maven Wrapper
./mvnw spring-boot:run   # Linux/macOS
mvnw.cmd spring-boot:run # Windows
```

后端服务将在 `http://localhost:8080` 启动

### 5. 启动前端服务

```bash
cd front-end

# 安装依赖
npm install

# 启动开发服务器
npm run dev
```

前端应用将在 `http://localhost:5173` 启动

### 6. 验证部署

- 前端地址：http://localhost:5173
- 后端地址：http://localhost:8080
- 测试账户：
  - 管理员：用户名 `admin`，密码 `123456`
  - 普通用户：用户名 `testuser`，密码 `123456`

## 🔧 开发流程

### 后端开发流程

#### 1. API 设计与测试 (推荐使用 Apifox)

**重要：在前后端联调之前，必须先确保后端 API 正常工作**

1. **导入 API 文档**

   - 将项目根目录的 `api接口文档.md` 导入到 Apifox
   - 或者手动在 Apifox 中创建接口测试集合

2. **API 测试顺序**

   ```
   ① 用户认证测试
      - POST /api/auth/register (用户注册)
      - POST /api/auth/login (用户登录，获取token)

   ② 学期管理测试
      - POST /api/terms (创建学期)
      - GET /api/terms (获取学期列表)
      - PUT /api/terms/{id} (更新学期)
      - DELETE /api/terms/{id} (删除学期)

   ③ 课程管理测试
      - POST /api/courses (创建课程)
      - GET /api/terms/{termId}/courses (获取课程列表)
      - PUT /api/courses/{id} (更新课程)
      - DELETE /api/courses/{id} (删除课程)

   ④ 高级功能测试
      - GET /api/courses/search (课程搜索)
      - POST /api/import/excel (Excel导入)
      - GET /api/admin/users (管理员功能)
   ```

3. **测试要点**
   - 确保在请求头中正确设置 `token: <JWT_TOKEN>`
   - 验证响应格式符合文档规范
   - 测试各种边界情况和错误场景

#### 2. 新接口开发流程

1. **在 Controller 中添加接口**

   ```java
   @RestController
   @RequestMapping("/api")
   public class YourController {

       @GetMapping("/your-endpoint")
       public Result yourMethod(@RequestParam String param) {
           // 实现逻辑
           return Result.success(200, "操作成功", data);
       }
   }
   ```

2. **在 Service 层实现业务逻辑**

   ```java
   @Service
   public class YourServiceImpl implements YourService {
       // 业务逻辑实现
   }
   ```

3. **在 Mapper 中实现数据访问**

   ```java
   @Mapper
   public interface YourMapper {
       @Select("SELECT * FROM your_table WHERE id = #{id}")
       YourEntity findById(Long id);
   }
   ```

4. **在 Apifox 中测试新接口**
5. **确认测试通过后，通知前端同学进行联调**

### 前端开发流程

#### 1. 开发新页面

1. **在 `/src/views/` 下创建页面组件**
2. **在 `/src/router/index.js` 中添加路由**
3. **在 `/src/api/` 下添加相应的接口调用**
4. **在 `/src/stores/` 中管理页面状态**

#### 2. API 接口调用

```javascript
// /src/api/your-api.js
import request from "./request";

export const yourApiMethod = (params) => {
  return request({
    url: "/your-endpoint",
    method: "get",
    params,
  });
};
```

#### 3. 组件开发规范

- 使用 Element Plus 组件库
- 遵循 Vue 3 Composition API 规范
- 合理使用 Pinia 进行状态管理

### 前后端联调流程

1. **后端完成接口开发并在 Apifox 测试通过**
2. **前端根据 API 文档进行接口对接**
3. **联调测试，解决跨域、认证等问题**
4. **功能测试，确保业务流程正常**

## 📁 项目结构

```
personal_course/
├── back-end/                 # Spring Boot 后端
│   ├── src/main/java/com/re0hg/backend/
│   │   ├── controller/       # 控制器层
│   │   ├── service/         # 业务逻辑层
│   │   ├── mapper/          # 数据访问层
│   │   ├── pojo/            # 实体类和工具类
│   │   ├── config/          # 配置类
│   │   ├── interceptor/     # 拦截器
│   │   └── utils/           # 工具类
│   ├── src/main/resources/
│   │   └── application.yml  # 配置文件
│   └── pom.xml              # Maven依赖配置
│
├── front-end/               # Vue 3 前端
│   ├── src/
│   │   ├── api/            # API接口封装
│   │   ├── components/     # 公共组件
│   │   ├── views/          # 页面组件
│   │   ├── router/         # 路由配置
│   │   ├── stores/         # Pinia状态管理
│   │   └── utils/          # 工具函数
│   ├── package.json        # 前端依赖配置
│   └── vite.config.js      # Vite配置
│
├── api接口文档.md           # API接口文档
├── 设计文档.md             # 项目设计文档
├── front-end.md            # 前端设计文档
└── README.md               # 项目说明文档
```

## 🌟 核心功能说明

### 用户认证系统

- 基于 JWT 的无状态认证
- 支持用户注册、登录、权限验证
- 三种用户角色：ADMIN、USER、TRIAL

### 学期管理

- 支持创建多个学期
- 每个学期独立管理课程
- 支持学期的 CRUD 操作

### 课程管理

- 课程基本信息管理（名称、教师、备注等）
- 课程标签系统（必修/选修）
- 复杂的排课时间管理（支持多个时间段）
- 课程搜索和筛选功能

### 排课系统

- 支持每门课程多个上课时间
- 精确的时间管理（周次、星期、节次）
- 灵活的排课规则

### Excel 导入功能

- 支持批量导入课程数据
- 自动识别课程标签
- 错误处理和数据验证

## 🔍 接口文档

详细的 API 接口文档请参考：[api 接口文档.md](./api接口文档.md)

### 主要接口概览

| 功能模块 | 接口路径                      | 方法 | 说明         |
| -------- | ----------------------------- | ---- | ------------ |
| 用户认证 | `/api/auth/register`          | POST | 用户注册     |
| 用户认证 | `/api/auth/login`             | POST | 用户登录     |
| 学期管理 | `/api/terms`                  | GET  | 获取学期列表 |
| 学期管理 | `/api/terms`                  | POST | 创建学期     |
| 课程管理 | `/api/courses`                | POST | 创建课程     |
| 课程管理 | `/api/terms/{termId}/courses` | GET  | 获取课程列表 |
| 课程搜索 | `/api/courses/search`         | GET  | 搜索课程     |
| 文件导入 | `/api/import/excel`           | POST | Excel 导入   |

## 🛡️ 安全配置

### JWT 认证

- Token 有效期：12 小时
- 除登录/注册外，所有接口都需要携带 token
- 请求头格式：`token: <JWT_TOKEN>`

### 跨域配置

- 前端开发服务器：`http://localhost:5173`
- 后端已配置 CORS 允许前端访问

## 🚨 常见问题

### 1. 后端启动失败

- 检查环境变量是否正确设置
- 确认数据库连接信息
- 查看是否有端口冲突

### 2. 前端无法访问后端

- 确认后端服务正常启动
- 检查跨域配置
- 确认 API 接口路径是否正确

### 3. JWT 认证失败

- 检查 token 是否正确携带
- 确认 token 是否过期
- 验证请求头格式：`token: <JWT_TOKEN>`

### 4. 数据库连接问题

- 确认 MySQL 服务已启动
- 检查数据库用户权限
- 验证数据库 URL 格式

## 📝 开发规范

### 代码规范

- 后端：遵循 Spring Boot 最佳实践
- 前端：遵循 Vue 3 官方风格指南
- 数据库：使用下划线命名，字段注释完整

### Git 协作规范

- 功能分支：`feature/功能名称`
- 修复分支：`bugfix/问题描述`
- 提交信息：使用清晰的中英文描述

### 测试规范

- 新功能必须在 Apifox 中测试通过
- 前后端联调前确保接口稳定
- 关键功能需要编写单元测试

## 🤝 团队协作

### 分工建议

- **后端开发**：负责 API 接口、数据库设计、业务逻辑
- **前端开发**：负责用户界面、交互逻辑、数据展示
- **测试**：负责接口测试、功能测试、集成测试

### 沟通流程

1. 需求讨论和接口设计
2. 后端先完成接口开发和测试
3. 前端根据接口文档进行开发
4. 联调测试和问题修复
5. 功能验收和上线部署

## 📞 技术支持

如有技术问题，请：

1. 查看项目文档和接口文档
2. 检查控制台错误信息
3. 联系项目维护者

---

**项目维护者**：re0hg  
**最后更新时间**：2025 年 6 月 24 日  
**文档版本** v1.0
