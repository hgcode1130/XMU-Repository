<template>
  <div class="app-container">
    <!-- 筛选区域 -->
    <el-card class="filter-container" shadow="never">
      <div>
        <i class="el-icon-search"></i>
        <span>筛选搜索</span>
        <el-button
          style="float: right"
          @click="handleResetSearch()"
          size="small"
        >
          重置
        </el-button>
        <el-button
          style="float: right; margin-right: 15px"
          @click="handleSearchList()"
          type="primary"
          size="small"
        >
          查询结果
        </el-button>
      </div>
      <div style="margin-top: 15px">
        <el-form
          :inline="true"
          :model="listQuery"
          size="small"
          label-width="140px"
        >
          <el-form-item label="用户名:">
            <el-input
              style="width: 203px"
              v-model="listQuery.username"
              placeholder="按用户名模糊查询"
            ></el-input>
          </el-form-item>
          <el-form-item label="邮箱:">
            <el-input
              style="width: 203px"
              v-model="listQuery.email"
              placeholder="按邮箱模糊查询"
            ></el-input>
          </el-form-item>
          <el-form-item label="角色:">
            <el-select v-model="listQuery.role" placeholder="请选择" clearable>
              <el-option
                v-for="item in roleOptions"
                :key="item.value"
                :label="item.label"
                :value="item.value"
              >
              </el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="是否启用:">
            <el-select
              v-model="listQuery.isEnabled"
              placeholder="请选择"
              clearable
            >
              <el-option :value="true" label="是"></el-option>
              <el-option :value="false" label="否"></el-option>
            </el-select>
          </el-form-item>
        </el-form>
      </div>
    </el-card>

    <!-- 用户列表 -->
    <el-card class="operate-container" shadow="never">
      <i class="el-icon-tickets"></i>
      <span>数据列表</span>
    </el-card>
    <div class="table-container">
      <el-table
        ref="userTable"
        :data="list"
        style="width: 100%"
        v-loading="listLoading"
        border
      >
        <el-table-column
          label="ID"
          prop="id"
          width="100"
          align="center"
        ></el-table-column>
        <el-table-column
          label="用户名"
          prop="username"
          align="center"
        ></el-table-column>
        <el-table-column
          label="邮箱"
          prop="email"
          align="center"
        ></el-table-column>
        <el-table-column label="角色" prop="role" width="120" align="center">
          <template #default="scope">
            <el-tag
              :type="scope.row.role === 'ADMIN' ? 'danger' : 'success'"
              disable-transitions
              >{{ scope.row.role }}</el-tag
            >
          </template>
        </el-table-column>
        <el-table-column label="是否启用" width="120" align="center">
          <template #default="scope">
            <el-switch
              v-model="scope.row.isEnabled"
              @change="handleStatusChange(scope.row)"
              :loading="scope.row.loading"
            >
            </el-switch>
          </template>
        </el-table-column>
        <el-table-column
          label="注册时间"
          prop="createdAt"
          width="180"
          align="center"
        ></el-table-column>
      </el-table>
    </div>

    <!-- 分页 -->
    <div class="pagination-container">
      <el-pagination
        background
        @size-change="handleSizeChange"
        @current-change="handleCurrentChange"
        layout="total, sizes,prev, pager, next,jumper"
        :page-size="listQuery.size"
        :page-sizes="[5, 10, 15]"
        :current-page.sync="listQuery.page"
        :total="total"
      >
      </el-pagination>
    </div>
  </div>
</template>

<script setup>
import { ref, reactive, onMounted } from "vue";
import { fetchUsers, updateUserStatus } from "@/api/admin";
import { ElMessage } from "element-plus";

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
const listLoading = ref(true);

const roleOptions = ref([
  { value: "ADMIN", label: "管理员" },
  { value: "USER", label: "普通用户" },
  { value: "TRIAL", label: "试用用户" },
]);

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
      ElMessage.error("获取用户列表失败");
      listLoading.value = false;
    });
}

function handleSearchList() {
  listQuery.page = 0;
  getList();
}

function handleResetSearch() {
  listQuery.page = 0;
  listQuery.size = 10;
  listQuery.username = null;
  listQuery.email = null;
  listQuery.role = null;
  listQuery.isEnabled = null;
  getList();
}

function handleSizeChange(val) {
  listQuery.page = 0;
  listQuery.size = val;
  getList();
}

function handleCurrentChange(val) {
  listQuery.page = val - 1; // el-pagination 页码从1开始，API从0开始
  getList();
}

function handleStatusChange(user) {
  user.loading = true;
  updateUserStatus(user.id, { isEnabled: user.isEnabled })
    .then(() => {
      ElMessage.success("状态更新成功");
      user.loading = false;
    })
    .catch(() => {
      ElMessage.error("状态更新失败");
      // 恢复原来的状态
      user.isEnabled = !user.isEnabled;
      user.loading = false;
    });
}
</script>

<style scoped>
.app-container {
  padding: 20px;
}
.filter-container {
  margin-bottom: 20px;
}
.operate-container {
  margin-bottom: 20px;
}
.pagination-container {
  margin-top: 20px;
  display: flex;
  justify-content: center;
}
</style>
