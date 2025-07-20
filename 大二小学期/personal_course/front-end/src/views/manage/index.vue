<template>
  <div class="manage-container">
    <!-- 页面头部 -->
    <div class="page-header">
      <div class="header-content">
        <div class="header-left">
          <el-icon class="header-icon"><User /></el-icon>
          <div class="header-text">
            <h1 class="page-title">用户管理</h1>
            <p class="page-subtitle">管理系统用户信息、权限和状态</p>
          </div>
        </div>
        <div class="header-stats">
          <div class="stat-card">
            <div class="stat-number">{{ total }}</div>
            <div class="stat-label">总用户数</div>
          </div>
          <div class="stat-card">
            <div class="stat-number">{{ enabledCount }}</div>
            <div class="stat-label">活跃用户</div>
          </div>
          <div class="stat-card">
            <div class="stat-number">{{ adminCount }}</div>
            <div class="stat-label">管理员</div>
          </div>
        </div>
      </div>
    </div>

    <!-- 筛选搜索区域 -->
    <el-card class="filter-card" shadow="hover">
      <template #header>
        <div class="filter-header">
          <div class="filter-title">
            <el-icon class="filter-icon"><Search /></el-icon>
            <span>筛选搜索</span>
          </div>
          <div class="filter-actions">
            <el-button
              @click="handleResetSearch()"
              :icon="RefreshLeft"
              size="default"
            >
              重置
            </el-button>
            <el-button
              @click="handleSearchList()"
              type="primary"
              :icon="Search"
              size="default"
              :loading="searchLoading"
            >
              查询
            </el-button>
          </div>
        </div>
      </template>

      <el-form :model="listQuery" class="filter-form" :label-width="80">
        <el-row :gutter="24">
          <el-col :xl="6" :lg="8" :md="12" :sm="24">
            <el-form-item label="用户名">
              <el-input
                v-model="listQuery.username"
                placeholder="按用户名模糊查询"
                :prefix-icon="User"
                clearable
                @keyup.enter="handleSearchList"
              />
            </el-form-item>
          </el-col>
          <el-col :xl="6" :lg="8" :md="12" :sm="24">
            <el-form-item label="邮箱">
              <el-input
                v-model="listQuery.email"
                placeholder="按邮箱模糊查询"
                :prefix-icon="Message"
                clearable
                @keyup.enter="handleSearchList"
              />
            </el-form-item>
          </el-col>
          <el-col :xl="6" :lg="8" :md="12" :sm="24">
            <el-form-item label="角色">
              <el-select
                v-model="listQuery.role"
                placeholder="请选择用户角色"
                clearable
                style="width: 100%"
              >
                <el-option
                  v-for="item in roleOptions"
                  :key="item.value"
                  :label="item.label"
                  :value="item.value"
                >
                  <div class="role-option">
                    <el-tag
                      :type="getRoleTagType(item.value)"
                      size="small"
                      disable-transitions
                    >
                      {{ item.label }}
                    </el-tag>
                  </div>
                </el-option>
              </el-select>
            </el-form-item>
          </el-col>
          <el-col :xl="6" :lg="8" :md="12" :sm="24">
            <el-form-item label="状态">
              <el-select
                v-model="listQuery.isEnabled"
                placeholder="请选择启用状态"
                clearable
                style="width: 100%"
              >
                <el-option :value="true" label="已启用">
                  <div class="status-option">
                    <el-icon color="#67c23a"><CircleCheck /></el-icon>
                    <span>已启用</span>
                  </div>
                </el-option>
                <el-option :value="false" label="已禁用">
                  <div class="status-option">
                    <el-icon color="#f56c6c"><CircleClose /></el-icon>
                    <span>已禁用</span>
                  </div>
                </el-option>
              </el-select>
            </el-form-item>
          </el-col>
        </el-row>
      </el-form>
    </el-card>

    <!-- 用户列表 -->
    <el-card class="table-card" shadow="hover">
      <template #header>
        <div class="table-header">
          <div class="table-title">
            <el-icon class="table-icon"><List /></el-icon>
            <span>用户列表</span>
            <el-tag v-if="total" type="info" class="count-tag">
              共 {{ total }} 条记录
            </el-tag>
          </div>
          <div class="table-actions">
            <el-tooltip content="刷新数据" placement="top">
              <el-button
                :icon="Refresh"
                circle
                @click="getList"
                :loading="listLoading"
              />
            </el-tooltip>
          </div>
        </div>
      </template>

      <!-- 表格 -->
      <el-table
        ref="userTable"
        :data="list"
        style="width: 100%"
        v-loading="listLoading"
        class="user-table"
        :header-cell-style="{ backgroundColor: '#f8f9fa', color: '#606266' }"
        empty-text="暂无用户数据"
      >
        <el-table-column label="ID" prop="id" width="80" align="center" />

        <el-table-column label="用户信息" min-width="200">
          <template #default="scope">
            <div class="user-info">
              <div class="user-avatar">
                <el-avatar :size="40" :src="scope.row.avatar">
                  {{ scope.row.username.charAt(0).toUpperCase() }}
                </el-avatar>
              </div>
              <div class="user-details">
                <div class="username">{{ scope.row.username }}</div>
                <div class="user-email">{{ scope.row.email }}</div>
              </div>
            </div>
          </template>
        </el-table-column>

        <el-table-column label="角色" width="120" align="center">
          <template #default="scope">
            <el-tag
              :type="getRoleTagType(scope.row.role)"
              :effect="scope.row.role === 'ADMIN' ? 'dark' : 'plain'"
              disable-transitions
            >
              <el-icon style="margin-right: 4px">
                <component :is="getRoleIcon(scope.row.role)" />
              </el-icon>
              {{ getRoleLabel(scope.row.role) }}
            </el-tag>
          </template>
        </el-table-column>

        <el-table-column label="状态" width="100" align="center">
          <template #default="scope">
            <el-switch
              v-model="scope.row.isEnabled"
              @change="handleStatusChange(scope.row)"
              :loading="scope.row.loading"
              active-color="#67c23a"
              inactive-color="#f56c6c"
              :active-icon="Check"
              :inactive-icon="Close"
            />
          </template>
        </el-table-column>

        <el-table-column label="注册时间" width="180" align="center">
          <template #default="scope">
            <div class="date-info">
              <el-icon class="date-icon"><Calendar /></el-icon>
              <span>{{ formatDate(scope.row.createdAt) }}</span>
            </div>
          </template>
        </el-table-column>

        <!-- <el-table-column label="最后登录" width="180" align="center">
          <template #default="scope">
            <div class="date-info">
              <el-icon class="date-icon"><Clock /></el-icon>
              <span v-if="scope.row.lastLoginAt">
                {{ formatDate(scope.row.lastLoginAt) }}
              </span>
              <span v-else class="no-data">从未登录</span>
            </div>
          </template>
        </el-table-column> -->

        <el-table-column label="操作" width="120" align="center" fixed="right">
          <template #default="scope">
            <div class="action-buttons">
              <el-tooltip
                :content="scope.row.isEnabled ? '禁用用户' : '启用用户'"
                placement="top"
              >
                <el-button
                  :type="scope.row.isEnabled ? 'danger' : 'success'"
                  text
                  :icon="scope.row.isEnabled ? CircleClose : CircleCheck"
                  @click="
                    handleStatusChange({
                      ...scope.row,
                      isEnabled: !scope.row.isEnabled,
                    })
                  "
                  :loading="scope.row.loading"
                  size="small"
                />
              </el-tooltip>
            </div>
          </template>
        </el-table-column>
      </el-table>

      <!-- 分页 -->
      <div class="pagination-wrapper">
        <el-pagination
          :current-page="currentPage"
          :page-size="listQuery.size"
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
          layout="total, sizes, prev, pager, next, jumper"
          :page-sizes="[5, 10, 15, 20, 50]"
          :total="total"
          background
          class="pagination"
        />
      </div>
    </el-card>
  </div>
</template>

<script setup>
import { ref, reactive, onMounted, computed } from "vue";
import { fetchUsers, updateUserStatus } from "@/api/admin";
import { ElMessage, ElMessageBox } from "element-plus";
import {
  User,
  Search,
  RefreshLeft,
  Refresh,
  List,
  Message,
  Calendar,
  Clock,
  Check,
  Close,
  CircleCheck,
  CircleClose,
  Star,
  UserFilled,
  Timer,
} from "@element-plus/icons-vue";

const listQuery = reactive({
  page: 0,
  size: 10,
  username: null,
  email: null,
  role: null,
  isEnabled: null,
});

const list = ref([]);
const total = ref(0);
const listLoading = ref(false);
const searchLoading = ref(false);
const currentPage = ref(1);

const roleOptions = ref([
  { value: "ADMIN", label: "管理员" },
  { value: "USER", label: "普通用户" },
  { value: "TRIAL", label: "试用用户" },
]);

// 统计数据计算
const enabledCount = computed(
  () => list.value.filter((user) => user.isEnabled).length
);

const adminCount = computed(
  () => list.value.filter((user) => user.role === "ADMIN").length
);

// 工具函数
const getRoleTagType = (role) => {
  const types = {
    ADMIN: "danger",
    USER: "success",
    TRIAL: "warning",
  };
  return types[role] || "info";
};

const getRoleIcon = (role) => {
  const icons = {
    ADMIN: Star,
    USER: UserFilled,
    TRIAL: Timer,
  };
  return icons[role] || UserFilled;
};

const getRoleLabel = (role) => {
  const labels = {
    ADMIN: "管理员",
    USER: "普通用户",
    TRIAL: "试用用户",
  };
  return labels[role] || role;
};

const formatDate = (dateString) => {
  if (!dateString) return "-";
  const date = new Date(dateString);
  return date.toLocaleString("zh-CN", {
    year: "numeric",
    month: "2-digit",
    day: "2-digit",
    hour: "2-digit",
    minute: "2-digit",
  });
};

// 核心方法
onMounted(() => {
  getList();
});

function getList() {
  listLoading.value = true;
  // 清理空的查询参数
  const params = Object.entries(listQuery).reduce((acc, [key, value]) => {
    if (value !== null && value !== "") {
      acc[key] = value;
    }
    return acc;
  }, {});

  fetchUsers(params)
    .then((response) => {
      list.value = response.data.content.map((user) => ({
        ...user,
        loading: false,
      }));
      total.value = response.data.totalElements;
      listLoading.value = false;
    })
    .catch((error) => {
      console.error("获取用户列表失败:", error);
      ElMessage.error("获取用户列表失败");
      listLoading.value = false;
    });
}

function handleSearchList() {
  searchLoading.value = true;
  listQuery.page = 0;
  currentPage.value = 1;

  setTimeout(() => {
    getList();
    searchLoading.value = false;
  }, 300);
}

function handleResetSearch() {
  listQuery.page = 0;
  listQuery.size = 10;
  listQuery.username = null;
  listQuery.email = null;
  listQuery.role = null;
  listQuery.isEnabled = null;
  currentPage.value = 1;
  getList();
  ElMessage.success("筛选条件已重置");
}

function handleSizeChange(val) {
  listQuery.page = 0;
  listQuery.size = val;
  currentPage.value = 1;
  getList();
}

function handleCurrentChange(val) {
  listQuery.page = val - 1;
  currentPage.value = val;
  getList();
}

function handleStatusChange(user) {
  const action = user.isEnabled ? "启用" : "禁用";
  const message = `确定要${action}用户 "${user.username}" 吗？`;

  ElMessageBox.confirm(message, "状态变更确认", {
    confirmButtonText: "确定",
    cancelButtonText: "取消",
    type: "warning",
  })
    .then(() => {
      // 找到原始用户对象并设置加载状态
      const originalUser = list.value.find((u) => u.id === user.id);
      if (originalUser) {
        originalUser.loading = true;

        updateUserStatus(user.id, { isEnabled: user.isEnabled })
          .then(() => {
            originalUser.isEnabled = user.isEnabled;
            originalUser.loading = false;
            ElMessage.success(`用户状态${action}成功`);
          })
          .catch((error) => {
            console.error("状态更新失败:", error);
            ElMessage.error(`用户状态${action}失败`);
            originalUser.loading = false;
          });
      }
    })
    .catch(() => {
      ElMessage.info("已取消操作");
    });
}
</script>

<style scoped>
.manage-container {
  padding: 24px;
  max-width: 1400px;
  margin: 0 auto;
  background-color: #f5f7fa;
  min-height: calc(100vh - 120px);
}

/* 页面头部 */
.page-header {
  margin-bottom: 24px;
}

.header-content {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 24px;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  border-radius: 16px;
  color: white;
  box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
}

.header-left {
  display: flex;
  align-items: center;
  gap: 16px;
}

.header-icon {
  font-size: 32px;
  color: white;
}

.page-title {
  margin: 0;
  font-size: 28px;
  font-weight: 600;
}

.page-subtitle {
  margin: 4px 0 0;
  font-size: 14px;
  opacity: 0.9;
}

.header-stats {
  display: flex;
  gap: 24px;
}

.stat-card {
  text-align: center;
  padding: 16px;
  background: rgba(255, 255, 255, 0.1);
  border-radius: 12px;
  min-width: 80px;
  backdrop-filter: blur(10px);
}

.stat-number {
  font-size: 24px;
  font-weight: 700;
  margin-bottom: 4px;
}

.stat-label {
  font-size: 12px;
  opacity: 0.8;
}

/* 筛选卡片 */
.filter-card {
  margin-bottom: 24px;
  border-radius: 12px;
  border: none;
  box-shadow: 0 2px 12px rgba(0, 0, 0, 0.04);
}

.filter-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.filter-title {
  display: flex;
  align-items: center;
  gap: 8px;
  font-weight: 600;
  color: #303133;
}

.filter-icon {
  font-size: 18px;
  color: #409eff;
}

.filter-actions {
  display: flex;
  gap: 12px;
}

.filter-form {
  margin-top: 16px;
}

.role-option,
.status-option {
  display: flex;
  align-items: center;
  gap: 8px;
}

/* 表格卡片 */
.table-card {
  border-radius: 12px;
  border: none;
  box-shadow: 0 2px 12px rgba(0, 0, 0, 0.04);
}

.table-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.table-title {
  display: flex;
  align-items: center;
  gap: 8px;
  font-weight: 600;
  color: #303133;
}

.table-icon {
  font-size: 18px;
  color: #409eff;
}

.count-tag {
  margin-left: 8px;
}

/* 用户表格 */
.user-table {
  border-radius: 8px;
  overflow: hidden;
}

.user-info {
  display: flex;
  align-items: center;
  gap: 12px;
  padding: 8px 0;
}

.user-details {
  flex: 1;
}

.username {
  font-weight: 600;
  color: #303133;
  margin-bottom: 4px;
}

.user-email {
  font-size: 12px;
  color: #909399;
}

.date-info {
  display: flex;
  align-items: center;
  gap: 6px;
  font-size: 14px;
}

.date-icon {
  color: #909399;
  font-size: 14px;
}

.no-data {
  color: #c0c4cc;
  font-style: italic;
}

.action-buttons {
  display: flex;
  gap: 8px;
  justify-content: center;
}

/* 分页 */
.pagination-wrapper {
  display: flex;
  justify-content: center;
  margin-top: 24px;
  padding-top: 24px;
  border-top: 1px solid #f0f0f0;
}

.pagination {
  background: none;
}

/* 响应式设计 */
@media (max-width: 1200px) {
  .header-content {
    flex-direction: column;
    gap: 20px;
    text-align: center;
  }

  .header-stats {
    flex-wrap: wrap;
    justify-content: center;
  }
}

@media (max-width: 768px) {
  .manage-container {
    padding: 16px;
  }

  .filter-header {
    flex-direction: column;
    gap: 16px;
    align-items: stretch;
  }

  .filter-actions {
    justify-content: center;
  }

  .table-header {
    flex-direction: column;
    gap: 16px;
    align-items: stretch;
  }

  .stat-card {
    min-width: 60px;
    padding: 12px;
  }

  .stat-number {
    font-size: 20px;
  }

  .user-info {
    flex-direction: column;
    text-align: center;
    gap: 8px;
  }
}

/* 过渡动画 */
.el-table {
  transition: all 0.3s ease;
}

.el-card {
  transition: all 0.3s ease;
}

.el-card:hover {
  transform: translateY(-2px);
  box-shadow: 0 8px 30px rgba(0, 0, 0, 0.08);
}

/* 深色模式适配 */
@media (prefers-color-scheme: dark) {
  .manage-container {
    background-color: #141414;
  }

  .header-content {
    background: linear-gradient(135deg, #4facfe 0%, #00f2fe 100%);
  }
}
</style>
