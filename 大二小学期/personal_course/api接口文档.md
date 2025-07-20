# **个人课表系统 - API 接口文档 (v3.0)**

## 环境配置

### 必需的环境变量

在运行项目前，请设置以下环境变量：

#### 数据库配置

```bash
DB_URL=jdbc:mysql://localhost:3306/personal_courses_db
DB_USERNAME=root
DB_PASSWORD=your_password
```

#### 阿里云 OSS 配置

```bash
ALIYUN_OSS_ACCESS_KEY_ID=your_access_key_id
ALIYUN_OSS_ACCESS_KEY_SECRET=your_access_key_secret
ALIYUN_OSS_BUCKET_NAME=your_bucket_name
ALIYUN_OSS_ENDPOINT=https://oss-cn-hangzhou.aliyuncs.com
```

#### Spring Profile

```bash
SPRING_PROFILES_ACTIVE=dev
```

### Windows 环境变量设置

1. 按 Win+R，输入`sysdm.cpl`
2. 高级 → 环境变量
3. 在用户变量中添加上述变量

### 开发环境快速启动

1. 设置环境变量
2. 运行后端：`mvn spring-boot:run`
3. 运行前端：`npm run dev`

## **一、概述**

本文档详细描述了个人课表管理系统的后端 API 接口，涵盖用户认证、学期管理、课程管理、管理员功能和导入功能。所有接口均基于 RESTful 风格设计，数据传输格式为 JSON。

**项目最新特性**：

- ✅ 课程标签功能（必修/选修）
- ✅ 用户权限管理（ADMIN/USER/TRIAL）
- ✅ JWT 认证与状态持久化
- ✅ 前端多视图支持（周视图/日视图/学期视图）
- ✅ Excel 批量导入与模板下载

### **技术规范**

- **根路径**: `/api`
- **认证**: 除用户注册和登录接口外，所有接口均需在请求头中携带 `token: <JWT_TOKEN>` 进行认证
- **时间格式**: 所有时间字段均为 ISO 8601 格式，如 `"2025-06-23T11:30:00"`
- **命名约定**: JSON 字段采用小驼峰命名法 (camelCase)

### **通用响应结构**

```json
{
  "code": 200,         // 响应码，200 代表成功，其他代表失败
  "message": "具体消息", // 提示信息
  "data": { ... }      // 返回的数据，成功时为具体数据，失败时为 null
}
```

### **开发测试建议**

为了确保 API 开发的循序渐进，建议按以下顺序进行测试：

1. **基础认证** → 用户注册/登录 → JWT 验证
2. **学期管理** → 创建学期 → 获取学期列表
3. **课程管理** → 添加课程（含标签） → 获取课程列表
4. **高级功能** → 课程搜索 → Excel 导入
5. **管理功能** → 用户管理 → 权限控制

---

## **二、用户认证接口 (Auth)**

### **2.1 用户注册**

#### **基本信息**

- **请求路径**：`POST /api/auth/register`
- **接口描述**：创建新用户，默认为 `USER` 角色
- **前置条件**：无

#### **请求参数**

参数格式：`application/json`

| 参数名   | 类型   | 是否必须 | 验证规则            | 备注     |
| -------- | ------ | -------- | ------------------- | -------- |
| username | string | 必须     | 长度 3-50，字母数字 | 用户名   |
| password | string | 必须     | 长度 6-255          | 密码     |
| email    | string | 必须     | 邮箱格式            | 电子邮箱 |

**请求示例**：

```json
{
  "username": "newuser",
  "password": "Password123!",
  "email": "newuser@example.com"
}
```

#### **响应数据**

**成功响应 (201 Created)**：

```json
{
  "code": 201,
  "message": "用户注册成功",
  "data": {
    "userId": 1,
    "username": "newuser"
  }
}
```

**失败响应 (400 Bad Request)**：

```json
{
  "code": 400,
  "message": "用户名或邮箱已存在",
  "data": null
}
```

#### **测试步骤**

1. 使用 Postman 发送注册请求
2. 验证用户名/邮箱唯一性
3. 检查密码加密存储
4. 确认默认角色为 USER

---

### **2.2 用户登录**

#### **基本信息**

- **请求路径**：`POST /api/auth/login`
- **接口描述**：用户登录，返回 JWT token 及用户信息
- **前置条件**：用户已注册

#### **请求参数**

参数格式：`application/json`

| 参数名   | 类型   | 是否必须 | 备注   |
| -------- | ------ | -------- | ------ |
| username | string | 必须     | 用户名 |
| password | string | 必须     | 密码   |

**请求示例**：

```json
{
  "username": "testuser",
  "password": "Password123!"
}
```

#### **响应数据**

**成功响应 (200 OK)**：

```json
{
  "code": 200,
  "message": "登录成功",
  "data": {
    "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
    "expiresIn": 7200,
    "userInfo": {
      "id": 1,
      "username": "testuser",
      "email": "testuser@example.com",
      "role": "USER",
      "isEnabled": true
    }
  }
}
```

**失败响应 (401 Unauthorized)**：

```json
{
  "code": 401,
  "message": "用户名或密码错误，或账户已被禁用",
  "data": null
}
```

#### **测试步骤**

1. 使用注册的用户名密码登录
2. 验证返回的 JWT token 格式
3. 测试错误用户名/密码
4. 测试被禁用账户登录

---

## **三、学期管理接口 (Terms)**

### **3.1 创建新学期**

#### **基本信息**

- **请求路径**：`POST /api/terms`
- **接口描述**：为当前用户创建一个新学期
- **前置条件**：用户已登录，获得有效 token

#### **请求参数**

参数格式：`application/json`

| 参数名    | 类型   | 是否必须 | 验证规则        | 备注                     |
| --------- | ------ | -------- | --------------- | ------------------------ |
| name      | string | 必须     | 长度 1-100      | 学期名称                 |
| startDate | string | 非必须   | YYYY-MM-DD 格式 | 开始日期                 |
| endDate   | string | 非必须   | YYYY-MM-DD 格式 | 结束日期，需晚于开始日期 |

**请求示例**：

```json
{
  "name": "2025-2026 第二学期",
  "startDate": "2026-02-16",
  "endDate": "2026-07-05"
}
```

#### **响应数据**

**成功响应 (201 Created)**：

```json
{
  "code": 201,
  "message": "学期创建成功",
  "data": {
    "id": 3,
    "name": "2025-2026 第二学期",
    "startDate": "2026-02-16",
    "endDate": "2026-07-05",
    "createdAt": "2025-06-23T11:30:00",
    "updatedAt": "2025-06-23T11:30:00"
  }
}
```

#### **测试步骤**

1. 先完成用户注册登录获取 token
2. 使用 token 创建学期
3. 验证学期名称唯一性（同一用户下）
4. 测试日期格式验证

---

### **3.2 获取所有学期 (分页)**

#### **基本信息**

- **请求路径**：`GET /api/terms?page=0&size=10`
- **接口描述**：获取当前用户的所有学期列表
- **前置条件**：用户已登录

#### **请求参数**

查询参数：

| 参数名 | 类型   | 是否必须 | 默认值 | 备注     |
| ------ | ------ | -------- | ------ | -------- |
| page   | number | 非必须   | 0      | 页码     |
| size   | number | 非必须   | 10     | 每页数量 |

#### **响应数据**

**成功响应 (200 OK)**：

```json
{
  "code": 200,
  "message": "查询成功",
  "data": {
    "content": [
      {
        "id": 2,
        "name": "2025-2026 第一学期",
        "startDate": "2025-09-01",
        "endDate": "2026-01-18",
        "createdAt": "2025-01-01T00:00:00",
        "updatedAt": "2025-01-01T00:00:00"
      }
    ],
    "pageable": {
      "pageNumber": 0,
      "pageSize": 10
    },
    "totalPages": 1,
    "totalElements": 2,
    "last": true,
    "first": true
  }
}
```

#### **测试步骤**

1. 创建多个学期后测试获取
2. 验证分页功能
3. 确认只返回当前用户的学期

---

### **3.3 更新学期信息**

#### **基本信息**

- **请求路径**：`PUT /api/terms/{termId}`
- **接口描述**：更新指定学期的信息
- **前置条件**：学期属于当前用户

#### **请求参数**

路径参数：`termId` (学期 ID)

请求体参数同创建学期，所有字段均为可选。

#### **响应数据**

响应格式同创建学期响应。

#### **测试步骤**

1. 更新已创建的学期信息
2. 测试权限验证（不能更新他人学期）
3. 验证部分字段更新

---

### **3.4 删除学期**

#### **基本信息**

- **请求路径**：`DELETE /api/terms/{termId}`
- **接口描述**：删除指定学期及其下的所有课程
- **前置条件**：学期属于当前用户

#### **响应数据**

**成功响应 (200 OK)**：

```json
{
  "code": 200,
  "message": "学期删除成功",
  "data": null
}
```

#### **测试步骤**

1. 创建学期并添加课程
2. 删除学期，验证课程是否级联删除
3. 测试权限验证

---

## **四、课程管理接口 (Courses)**

### **4.1 手动添加新课程**

#### **基本信息**

- **请求路径**：`POST /api/courses`
- **接口描述**：为指定学期添加新课程及其排程
- **前置条件**：学期存在且属于当前用户

#### **请求参数**

参数格式：`application/json`

| 参数名            | 类型     | 是否必须 | 验证规则      | 备注                         |
| ----------------- | -------- | -------- | ------------- | ---------------------------- |
| termId            | number   | 必须     | 存在的学期 ID | 学期 ID                      |
| name              | string   | 必须     | 长度 1-100    | 课程名称                     |
| teachers          | string   | 非必须   | 长度 0-255    | 教师姓名（逗号分隔）         |
| mainTeacherEmail  | string   | 非必须   | 邮箱格式      | 主讲教师邮箱                 |
| courseGroupChatId | string   | 非必须   | 长度 0-50     | 课程群号                     |
| tag               | number   | 非必须   | 0 或 1        | **课程标签**：0=选修，1=必修 |
| note              | string   | 非必须   | 长度 0-1000   | 备注                         |
| scheduleEntries   | object[] | 非必须   | -             | 排程列表                     |
| ├─ location       | string   | 非必须   | 长度 0-255    | 上课地点                     |
| ├─ dayOfWeek      | number   | 必须     | 1-7           | 星期几 (1=周一)              |
| ├─ startPeriod    | number   | 必须     | 1-12          | 开始节次                     |
| ├─ endPeriod      | number   | 必须     | ≥startPeriod  | 结束节次                     |
| ├─ startWeek      | number   | 必须     | 1-20          | 开始周                       |
| └─ endWeek        | number   | 必须     | ≥startWeek    | 结束周                       |

**请求示例**：

```json
{
  "termId": 1,
  "name": "高等数学",
  "teachers": "张三,李四",
  "mainTeacherEmail": "zhangsan@example.com",
  "courseGroupChatId": "123456789",
  "tag": 1,
  "note": "期末考试占比70%",
  "scheduleEntries": [
    {
      "location": "教学楼A-101",
      "dayOfWeek": 1,
      "startPeriod": 1,
      "endPeriod": 2,
      "startWeek": 1,
      "endWeek": 16
    },
    {
      "location": "教学楼B-203",
      "dayOfWeek": 3,
      "startPeriod": 3,
      "endPeriod": 4,
      "startWeek": 1,
      "endWeek": 8
    }
  ]
}
```

#### **响应数据**

**成功响应 (201 Created)**：

```json
{
  "code": 201,
  "message": "课程创建成功",
  "data": {
    "id": 1,
    "name": "高等数学",
    "teachers": "张三,李四",
    "mainTeacherEmail": "zhangsan@example.com",
    "courseGroupChatId": "123456789",
    "tag": 1,
    "note": "期末考试占比70%",
    "scheduleEntries": [
      {
        "id": 1,
        "location": "教学楼A-101",
        "dayOfWeek": 1,
        "startPeriod": 1,
        "endPeriod": 2,
        "weeks": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
      },
      {
        "id": 2,
        "location": "教学楼B-203",
        "dayOfWeek": 3,
        "startPeriod": 3,
        "endPeriod": 4,
        "weeks": [1, 2, 3, 4, 5, 6, 7, 8]
      }
    ],
    "createdAt": "2025-06-23T11:40:00",
    "updatedAt": "2025-06-23T11:40:00"
  }
}
```

#### **测试步骤**

1. 先创建学期
2. 为学期添加课程（包含 tag 字段）
3. 验证排程时间冲突检测
4. 测试必修/选修标签功能

---

### **4.2 获取指定学期的所有课程 (分页)**

#### **基本信息**

- **请求路径**：`GET /api/terms/{termId}/courses?page=0&size=20`
- **接口描述**：获取指定学期下的所有课程
- **前置条件**：学期属于当前用户

#### **请求参数**

路径参数：`termId` (学期 ID)

| 参数名 | 类型   | 是否必须 | 默认值 | 备注     |
| ------ | ------ | -------- | ------ | -------- |
| page   | number | 非必须   | 0      | 页码     |
| size   | number | 非必须   | 20     | 每页数量 |

#### **响应数据**

响应格式同创建课程，但为分页结构。课程列表中每个课程都包含`tag`字段。

#### **测试步骤**

1. 创建多门课程（包含必修和选修）
2. 获取课程列表，验证 tag 字段正确返回
3. 测试分页功能

---

### **4.3 高级课程搜索 (筛选与分页)**

#### **基本信息**

- **请求路径**：`GET /api/courses/search`
- **接口描述**：多条件课程搜索功能

#### **请求参数**

查询参数：

| 参数名    | 类型   | 是否必须 | 备注                             |
| --------- | ------ | -------- | -------------------------------- |
| termId    | number | 非必须   | 学期 ID                          |
| name      | string | 非必须   | 课程名 (模糊匹配)                |
| teacher   | string | 非必须   | 教师名 (模糊匹配)                |
| tag       | number | 非必须   | **课程标签筛选**：0=选修，1=必修 |
| dayOfWeek | number | 非必须   | 星期几 (1-7)                     |
| page      | number | 非必须   | 页码 (默认 0)                    |
| size      | number | 非必须   | 每页数量 (默认 10)               |

**请求示例**：

```
GET /api/courses/search?termId=1&tag=1&teacher=张三&page=0&size=10
```

#### **测试步骤**

1. 创建多样化的课程数据
2. 测试各种筛选条件组合
3. 重点测试 tag 字段筛选功能

---

### **4.4 更新课程信息**

#### **基本信息**

- **请求路径**：`PUT /api/courses/{courseId}`
- **接口描述**：完全替换课程信息及其所有排程

#### **请求参数**

请求体格式同创建课程，但不包含`termId`，且所有字段均为可选。

**特别注意**：更新时`tag`字段可以在必修和选修之间切换。

#### **测试步骤**

1. 更新课程基本信息
2. 重点测试 tag 字段的修改
3. 测试排程信息更新

---

### **4.5 删除课程**

#### **基本信息**

- **请求路径**：`DELETE /api/courses/{courseId}`
- **接口描述**：删除指定课程及其所有排程

#### **响应数据**

**成功响应 (200 OK)**：

```json
{
  "code": 200,
  "message": "课程删除成功",
  "data": null
}
```

#### **测试步骤**

1. 删除课程，验证排程级联删除
2. 测试权限验证

---

## **五、管理员接口 (Admin)**

**访问控制**：以下接口仅限 `ADMIN` 角色的用户访问。

### **5.1 获取用户列表 (分页与筛选)**

#### **基本信息**

- **请求路径**：`GET /api/admin/users`
- **接口描述**：获取用户列表，支持分页和多条件筛选
- **前置条件**：当前用户角色为 ADMIN

#### **请求参数**

查询参数：

| 参数名    | 类型    | 是否必须 | 备注                      |
| --------- | ------- | -------- | ------------------------- |
| username  | string  | 非必须   | 用户名 (模糊匹配)         |
| email     | string  | 非必须   | 邮箱 (模糊匹配)           |
| role      | string  | 非必须   | 角色 (ADMIN, USER, TRIAL) |
| isEnabled | boolean | 非必须   | 账户状态 (true/false)     |
| page      | number  | 非必须   | 页码 (默认 0)             |
| size      | number  | 非必须   | 每页数量 (默认 20)        |

#### **响应数据**

**成功响应 (200 OK)**：

```json
{
  "code": 200,
  "message": "查询成功",
  "data": {
    "content": [
      {
        "id": 2,
        "username": "user_one",
        "email": "user_one@example.com",
        "role": "USER",
        "isEnabled": true,
        "createdAt": "2025-01-01T00:00:00",
        "updatedAt": "2025-01-01T00:00:00"
      }
    ],
    "pageable": {
      "pageNumber": 0,
      "pageSize": 20
    },
    "totalPages": 5,
    "totalElements": 48
  }
}
```

#### **测试步骤**

1. 使用 ADMIN 角色用户登录
2. 测试各种筛选条件
3. 验证非 ADMIN 用户无法访问（403 错误）

---

### **5.2 更新用户状态 (启用/禁用)**

#### **基本信息**

- **请求路径**：`PUT /api/admin/users/{userId}/status`
- **接口描述**：更新指定用户的启用状态
- **前置条件**：当前用户角色为 ADMIN

#### **请求参数**

路径参数：`userId` (用户 ID)

请求体参数：

| 参数名    | 类型    | 是否必须 | 备注     |
| --------- | ------- | -------- | -------- |
| isEnabled | boolean | 必须     | 账户状态 |

#### **响应数据**

**成功响应 (200 OK)**：

```json
{
  "code": 200,
  "message": "用户状态更新成功",
  "data": null
}
```

#### **测试步骤**

1. 禁用用户账户
2. 验证被禁用用户无法登录
3. 重新启用用户

---

## **六、导入接口 (Import)**

### **6.1 下载 Excel 导入模板**

#### **基本信息**

- **请求路径**：`GET /api/import/excel/template`
- **接口描述**：下载标准的 Excel 导入模板文件
- **前置条件**：用户已登录
- **响应类型**：文件流 (application/vnd.openxmlformats-officedocument.spreadsheetml.sheet)

#### **请求参数**

无需参数

#### **请求示例**

```bash
curl -X GET "http://localhost:8080/api/import/excel/template" \
  -H "token: <your-jwt-token>" \
  -o "course_template.xlsx"
```

#### **响应数据**

**成功响应 (200 OK)**：

- **Content-Type**: `application/vnd.openxmlformats-officedocument.spreadsheetml.sheet`
- **Content-Disposition**: `attachment; filename="course_template.xlsx"`
- **响应体**: Excel 文件二进制流

**模板文件结构**：

| 列名         | 示例数据            | 说明                     |
| ------------ | ------------------- | ------------------------ |
| 课程名称     | 高等数学            | 必填，课程名称           |
| 教师         | 张三,李四           | 选填，多个教师用逗号分隔 |
| 主讲老师邮箱 | zhangsan@xmu.edu.cn | 选填，邮箱格式           |
| 课程群号     | 123456789           | 选填，课程群号           |
| 标签         | 必修                | 选填，必修/选修          |
| 上课地点     | 教学楼 A-101        | 选填，上课地点           |
| 星期         | 1                   | 必填，1-7 (1=周一)       |
| 开始节次     | 1                   | 必填，1-12               |
| 结束节次     | 2                   | 必填，≥ 开始节次         |
| 开始周       | 1                   | 必填，1-20               |
| 结束周       | 16                  | 必填，≥ 开始周           |
| 备注         | 重要基础课程        | 选填，课程备注           |

#### **前端调用示例**

```javascript
// 下载Excel模板
export function downloadTemplateApi() {
  return request({
    url: "/import/excel/template",
    method: "get",
    responseType: "blob", // 重要：指定响应类型为blob
    skipResponseIntercept: true,
  });
}

// 使用示例
const handleDownloadTemplate = async () => {
  try {
    const response = await downloadTemplateApi();

    // 创建下载链接
    const url = window.URL.createObjectURL(response.data);
    const link = document.createElement("a");
    link.href = url;
    link.download = "课程导入模板.xlsx";

    // 触发下载
    document.body.appendChild(link);
    link.click();

    // 清理
    document.body.removeChild(link);
    window.URL.revokeObjectURL(url);

    ElMessage.success("模板下载成功");
  } catch (error) {
    ElMessage.error("下载模板失败，请重试");
  }
};
```

#### **测试步骤**

1. 使用有效 token 请求下载接口
2. 验证响应头 Content-Type 和 Content-Disposition
3. 检查下载的文件是否为有效的 Excel 文件
4. 验证模板文件包含正确的表头和示例数据

---

### **6.2 通过 Excel 导入课程**

#### **基本信息**

- **请求路径**：`POST /api/import/excel?termId=1`
- **接口描述**：将 Excel 文件中的课程数据导入到指定学期
- **前置条件**：学期存在且属于当前用户

#### **请求参数**

**请求头**：`Content-Type: multipart/form-data`

**查询参数**：

| 参数名 | 类型   | 是否必须 | 备注    |
| ------ | ------ | -------- | ------- |
| termId | number | 必须     | 学期 ID |

**表单参数**：

| 参数名 | 类型 | 是否必须 | 备注                                  |
| ------ | ---- | -------- | ------------------------------------- |
| file   | file | 必须     | Excel 文件(.xlsx 或 .xls 格式，≤10MB) |

#### **Excel 格式约定**

Excel 文件第一行必须包含以下表头（严格按照表头名称）：

| 字段名称     | 是否必须 | 数据类型 | 备注                          |
| ------------ | -------- | -------- | ----------------------------- |
| 课程名称     | 必须     | 文本     | 长度 1-100 字符               |
| 教师         | 非必须   | 文本     | 多个教师用逗号分隔，≤255 字符 |
| 主讲老师邮箱 | 非必须   | 文本     | 有效邮箱格式，≤100 字符       |
| 课程群号     | 非必须   | 文本     | ≤50 字符                      |
| 标签         | 非必须   | 文本     | **必修/选修**，默认为必修     |
| 上课地点     | 非必须   | 文本     | ≤255 字符                     |
| 星期         | 必须     | 数字     | 1-7 的整数 (1=周一)           |
| 开始节次     | 必须     | 数字     | 1-12 的整数                   |
| 结束节次     | 必须     | 数字     | ≥ 开始节次的整数，≤12         |
| 开始周       | 必须     | 数字     | 1-20 的整数                   |
| 结束周       | 必须     | 数字     | ≥ 开始周的整数，≤20           |
| 备注         | 非必须   | 文本     | ≤1000 字符                    |

#### **Excel 示例数据**

```
课程名称    | 教师      | 主讲老师邮箱        | 课程群号   | 标签 | 上课地点     | 星期 | 开始节次 | 结束节次 | 开始周 | 结束周 | 备注
高等数学    | 张三,李四 | zhangsan@xmu.edu.cn | 123456789  | 必修 | 教学楼A-101  | 1    | 1        | 2        | 1      | 16     | 重要基础课程
大学英语    | 王老师    | wang@xmu.edu.cn     | 987654321  | 选修 | 外语楼B-201  | 3    | 3        | 4        | 1      | 8      |
计算机基础  | 李教授    |                     |            | 必修 | 实验楼C-301  | 5    | 1        | 3        | 1      | 16     | 包含实验课
```

#### **请求示例**

```bash
curl -X POST "http://localhost:8080/api/import/excel?termId=1" \
  -H "token: <your-jwt-token>" \
  -H "Content-Type: multipart/form-data" \
  -F "file=@courses.xlsx"
```

#### **响应数据**

**成功响应 (200 OK)**：

```json
{
  "code": 200,
  "message": "Excel导入完成",
  "data": {
    "totalRows": 10,
    "successfulImports": 8,
    "failedImports": 2,
    "importedCourses": [
      {
        "rowNumber": 2,
        "courseName": "高等数学",
        "courseId": 15,
        "status": "成功"
      },
      {
        "rowNumber": 3,
        "courseName": "大学英语",
        "courseId": 16,
        "status": "成功"
      }
    ],
    "errors": [
      {
        "rowNumber": 5,
        "courseName": "数据结构",
        "error": "星期字段必须为1-7的数字，当前值：8"
      },
      {
        "rowNumber": 7,
        "courseName": "操作系统",
        "error": "标签字段只能是'必修'或'选修'，当前值：核心"
      }
    ],
    "summary": {
      "totalProcessingTime": "2.3秒",
      "importStartTime": "2025-06-30T14:30:00",
      "importEndTime": "2025-06-30T14:30:02"
    }
  }
}
```

**部分失败响应 (207 Multi-Status)**：

```json
{
  "code": 207,
  "message": "Excel导入部分成功，存在错误数据",
  "data": {
    "totalRows": 5,
    "successfulImports": 3,
    "failedImports": 2,
    "importedCourses": [
      {
        "rowNumber": 2,
        "courseName": "高等数学",
        "courseId": 15,
        "status": "成功"
      }
    ],
    "errors": [
      {
        "rowNumber": 3,
        "courseName": "",
        "error": "课程名称不能为空"
      },
      {
        "rowNumber": 4,
        "courseName": "数据结构",
        "error": "开始节次必须为1-12的整数，当前值：15"
      }
    ]
  }
}
```

**完全失败响应 (400 Bad Request)**：

```json
{
  "code": 400,
  "message": "Excel文件格式错误或无有效数据",
  "data": {
    "errors": [
      "Excel文件缺少必要的表头：课程名称",
      "Excel文件缺少必要的表头：星期",
      "文件格式不正确，请使用.xlsx或.xls格式"
    ],
    "totalRows": 0,
    "successfulImports": 0,
    "failedImports": 0
  }
}
```

**权限错误响应 (403 Forbidden)**：

```json
{
  "code": 403,
  "message": "无权限访问此学期或学期不存在",
  "data": null
}
```

#### **错误类型说明**

| 错误类型     | 说明                                  |
| ------------ | ------------------------------------- |
| 文件格式错误 | 非 Excel 格式、文件损坏、超出大小限制 |
| 表头格式错误 | 缺少必要表头、表头名称不匹配          |
| 数据验证错误 | 字段值不符合格式要求、超出长度限制    |
| 业务逻辑错误 | 课程时间冲突、学期不存在              |
| 权限错误     | 学期不属于当前用户                    |
| 系统错误     | 数据库连接失败、服务器内部错误        |

#### **数据验证规则**

1. **必填字段验证**：

   - 课程名称：不能为空，长度 1-100 字符
   - 星期：必须为 1-7 的整数
   - 开始节次、结束节次：必须为 1-12 的整数
   - 开始周、结束周：必须为 1-20 的整数

2. **逻辑验证**：

   - 结束节次 ≥ 开始节次
   - 结束周 ≥ 开始周
   - 邮箱格式验证（如果填写）
   - 标签只能是"必修"或"选修"

3. **业务验证**：
   - 学期必须存在且属于当前用户
   - 课程时间不能与同学期其他课程冲突

#### **工作流程推荐**

1. **下载模板**：调用 `GET /api/import/excel/template` 获取标准模板
2. **填写数据**：按照模板格式填写课程数据
3. **上传导入**：调用 `POST /api/import/excel` 上传填写好的 Excel 文件
4. **查看结果**：根据响应查看导入结果和错误信息

#### **测试步骤**

1. **准备测试文件**：

   ```bash
   # 使用 GenerateExcel.py 生成测试文件
   python GenerateExcel.py -n 50              # 生成50条正常数据
   python GenerateExcel.py -t error           # 生成包含错误的文件
   python GenerateExcel.py -t invalid         # 生成格式错误的文件
   python GenerateExcel.py -t all             # 生成所有类型的测试文件
   ```

2. **功能测试**：

   ```bash
   # 测试正常导入
   POST /api/import/excel?termId=1 (标准格式文件)

   # 测试标签功能
   上传包含"必修"和"选修"标签的文件

   # 测试错误处理
   上传格式错误的文件

   # 测试权限验证
   使用其他用户token访问不属于自己的学期
   ```

3. **边界测试**：
   ```bash
   # 测试大文件导入 (接近10MB)
   # 测试大量数据导入 (1000+行)
   # 测试特殊字符处理
   # 测试空行处理
   ```

#### **性能说明**

- **文件大小限制**：最大 10MB
- **处理行数建议**：单次导入建议不超过 1000 行课程数据
- **处理时间**：平均每 100 行数据处理时间约 1 秒
- **并发限制**：同一用户同时只能进行一个导入操作

#### **注意事项**

1. **Excel 文件要求**：

   - 支持.xlsx 和.xls 格式
   - 文件编码建议使用 UTF-8
   - 第一行必须是表头，从第二行开始是数据

2. **标签字段处理**：

   - 支持"必修"、"选修"两种值
   - 不区分大小写
   - 空值默认为"必修"
   - 其他值将报错

3. **课程时间冲突**：

   - 系统会检查同一学期内的课程时间冲突
   - 如有冲突，该行数据导入失败，其他数据继续处理

4. **事务处理**：
   - 每行数据独立事务，单行失败不影响其他行
   - 导入过程中断不会影响已成功导入的数据

---

## **七、错误码说明**

| 错误码 | 说明             | 常见场景                   |
| ------ | ---------------- | -------------------------- |
| 200    | 请求成功         | 正常操作                   |
| 201    | 资源创建成功     | 用户注册、学期/课程创建    |
| 207    | 部分成功         | Excel 导入部分成功         |
| 400    | 请求参数错误     | 缺少必要参数、格式错误     |
| 401    | 未认证或认证失败 | token 过期、用户名密码错误 |
| 403    | 权限不足         | 非管理员访问管理接口       |
| 404    | 资源不存在       | 学期/课程不存在            |
| 409    | 资源冲突         | 用户名重复、课程时间冲突   |
| 413    | 文件过大         | 上传文件超过 10MB          |
| 415    | 文件格式不支持   | 上传非 Excel 格式文件      |
| 500    | 服务器内部错误   | 数据库连接失败、未知异常   |

---

## **八、新功能特色说明**

### **8.1 课程标签功能**

**功能描述**：为每门课程添加标签属性，支持必修/选修分类。

**技术实现**：

- 数据库：`courses.tag` 字段，类型 `TINYINT(1)`，1=必修，0=选修
- 前端：支持筛选、展示、编辑标签
- Excel 导入：支持"标签"列导入

**使用场景**：

- 学生区分必修选修课程
- 按课程类型统计学分
- 课程表视觉化区分

### **8.2 Excel 导入增强**

**功能亮点**：

- **模板下载**：提供标准格式模板，确保导入成功率
- **智能验证**：多层次数据验证，精确定位错误位置
- **批量处理**：支持 1000+ 行数据的高效导入
- **错误报告**：详细的错误信息和成功统计

**技术特性**：

- 支持 .xlsx 和 .xls 格式
- 自动识别课程标签（必修/选修）
- 独立事务处理，单行失败不影响整体
- 实时处理进度反馈

### **8.3 多视图支持**

**周视图**：传统课程表格网格视图
**日视图**：单日课程详细展示  
**学期视图**：课程列表形式，支持展开详情

### **8.4 权限管理体系**

**角色类型**：

- `ADMIN`：系统管理员，可管理所有用户
- `USER`：普通用户，管理个人课表
- `TRIAL`：试用用户，功能受限

---

## **九、开发与测试建议**

### **9.1 开发环境搭建**

1. **数据库初始化**

   ```sql
   -- 运行Data.py生成的SQL脚本
   -- 包含admin用户（用户名：admin，密码：123456）
   ```

2. **测试数据**
   - 使用 Data.py 生成的示例数据
   - 包含多种标签的课程样例

### **9.2 测试流程**

#### **阶段一：基础功能**

1. 用户注册/登录 ✅
2. JWT 认证验证 ✅
3. 学期 CRUD 操作 ✅

#### **阶段二：核心功能**

1. 课程 CRUD 操作（含标签） ✅
2. 课程搜索筛选 ✅
3. 前端多视图展示 ✅

#### **阶段三：高级功能**

1. Excel 模板下载 ✅
2. Excel 导入（含标签） ✅
3. 管理员用户管理 ✅
4. 权限控制验证 ✅

### **9.3 重点测试用例**

1. **课程标签功能**

   - 创建必修课程（tag=1）
   - 创建选修课程（tag=0）
   - 必修选修之间切换
   - 标签筛选功能

2. **Excel 导入功能**

   - 模板下载测试
   - 标准格式文件导入
   - 标签列识别
   - 错误格式处理
   - 大文件导入性能测试

3. **权限验证**
   - 普通用户访问管理接口
   - 禁用用户登录
   - 跨用户数据访问

### **9.4 测试工具推荐**

#### **API 测试**

- **Postman**: 接口测试
- **Apifox**: API 文档管理和测试
- **curl**: 命令行测试

#### **Excel 测试文件生成**

```bash
# 使用项目提供的 GenerateExcel.py 工具
python GenerateExcel.py -h              # 查看帮助信息
python GenerateExcel.py -n 100          # 生成100条正常数据
python GenerateExcel.py -t all          # 生成所有类型的测试文件
```

---

## **十、附录**

### **10.1 快速开始**

```bash
# 1. 管理员登录
POST /api/auth/login
{
  "username": "admin",
  "password": "123456"
}

# 2. 下载Excel模板
GET /api/import/excel/template
Headers: token: <your-jwt-token>

# 3. 创建学期
POST /api/terms
Headers: token: <your-jwt-token>
{
  "name": "2025年春季学期",
  "startDate": "2025-02-17",
  "endDate": "2025-06-20"
}

# 4. 添加课程（含标签）
POST /api/courses
{
  "termId": 1,
  "name": "数据结构",
  "teachers": "王教授",
  "tag": 1,
  "scheduleEntries": [...]
}

# 5. Excel批量导入
POST /api/import/excel?termId=1
Headers: token: <your-jwt-token>
Content-Type: multipart/form-data
Form: file=@courses.xlsx
```

### **10.2 常用测试账户**

| 用户名 | 密码   | 角色  | 状态 | 备注     |
| ------ | ------ | ----- | ---- | -------- |
| admin  | 123456 | ADMIN | 启用 | 管理员   |
| user1  | 123456 | USER  | 启用 | 普通用户 |
| trial  | 123456 | TRIAL | 启用 | 试用用户 |
| user2  | 123456 | USER  | 禁用 | 测试禁用 |

### **10.3 前端配置建议**

- API Base URL: `http://localhost:8080/api`
- Token 存储: localStorage
- 请求拦截器: 自动添加 token 头
- 响应拦截器: 统一错误处理
- 文件下载: 使用 blob 响应类型

### **10.4 Excel 相关接口总结**

| 接口                         | 方法 | 用途         | 响应类型 |
| ---------------------------- | ---- | ------------ | -------- |
| `/api/import/excel/template` | GET  | 下载导入模板 | 文件流   |
| `/api/import/excel`          | POST | 上传导入数据 | JSON     |

### **10.5 开发工具**

- **数据库初始化**: [Data.py](./Data.py)
- **Excel 测试文件生成**: [GenerateExcel.py](./GenerateExcel.py)
- **测试文件目录**: [excel_test_files/](./excel_test_files/)

---

**文档版本**: v3.0  
**更新时间**: 2025 年 7 月 1 日  
**主要更新**: 新增 Excel 模板下载接口、完善导入流程、更新认证方式说明
