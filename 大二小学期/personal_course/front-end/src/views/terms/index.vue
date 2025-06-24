<template>
  <div>
    <el-card>
      <template #header>
        <div class="card-header">
          <span>学期列表</span>
          <el-button type="primary" :icon="Plus" @click="handleAdd"
            >新建学期</el-button
          >
        </div>
      </template>

      <el-table :data="termStore.termList" v-loading="loading" stripe>
        <el-table-column prop="name" label="学期名称" width="250" />
        <el-table-column prop="startDate" label="开始日期" />
        <el-table-column prop="endDate" label="结束日期" />
        <el-table-column label="操作" width="200" fixed="right">
          <template #default="scope">
            <el-button
              type="primary"
              text
              :icon="Edit"
              @click="handleEdit(scope.row)"
              >编辑</el-button
            >
            <el-button
              type="danger"
              text
              :icon="Delete"
              @click="handleDelete(scope.row)"
              >删除</el-button
            >
          </template>
        </el-table-column>
      </el-table>
    </el-card>

    <el-dialog
      v-model="dialogVisible"
      :title="dialogTitle"
      width="500px"
      @close="handleCancel"
    >
      <el-form
        ref="formRef"
        :model="termForm"
        :rules="rules"
        label-width="80px"
      >
        <el-form-item label="学期名称" prop="name">
          <el-input
            v-model="termForm.name"
            placeholder="例如：2025-2026 第一学期"
          />
        </el-form-item>
        <el-form-item label="起止日期" prop="dateRange">
          <el-date-picker
            v-model="termForm.dateRange"
            type="daterange"
            range-separator="至"
            start-placeholder="开始日期"
            end-placeholder="结束日期"
            value-format="YYYY-MM-DD"
            style="width: 100%"
          />
        </el-form-item>
      </el-form>
      <template #footer>
        <span class="dialog-footer">
          <el-button @click="handleCancel">取 消</el-button>
          <el-button type="primary" @click="handleSubmit">确 定</el-button>
        </span>
      </template>
    </el-dialog>
  </div>
</template>

<script setup>
import { ref, reactive, onMounted, computed } from "vue";
import { useTermStore } from "@/stores/term";
import { createTermApi, updateTermApi, deleteTermApi } from "@/api/term";
import { ElMessage, ElMessageBox } from "element-plus";
import { Plus, Edit, Delete } from "@element-plus/icons-vue";

// --- 状态与数据 ---
const termStore = useTermStore();
const loading = ref(false);
const dialogVisible = ref(false);
const formRef = ref(null);

const dialogTitle = computed(() => (termForm.id ? "编辑学期" : "新建学期"));

const termForm = reactive({
  id: null,
  name: "",
  dateRange: [],
});

const rules = reactive({
  name: [{ required: true, message: "请输入学期名称", trigger: "blur" }],
  dateRange: [
    { required: true, message: "请选择学期起止日期", trigger: "change" },
  ],
});

// --- 核心方法 ---

const fetchTerms = async () => {
  loading.value = true;
  try {
    await termStore.fetchAllTerms();
  } catch (error) {
    console.error("获取学期列表失败", error);
  } finally {
    loading.value = false;
  }
};

onMounted(() => {
  fetchTerms();
});

const handleAdd = () => {
  Object.assign(termForm, { id: null, name: "", dateRange: [] });
  dialogVisible.value = true;
};

const handleEdit = (row) => {
  Object.assign(termForm, {
    id: row.id,
    name: row.name,
    dateRange: [row.startDate, row.endDate],
  });
  dialogVisible.value = true;
};

const handleDelete = (row) => {
  ElMessageBox.confirm(
    `确定要删除学期 “${row.name}” 吗？该学期下的所有课程也将被一并删除，此操作不可逆！`,
    "危险操作警告",
    {
      confirmButtonText: "确定删除",
      cancelButtonText: "取消",
      type: "warning",
    }
  )
    .then(async () => {
      try {
        await deleteTermApi(row.id);
        ElMessage.success("删除成功");
        fetchTerms(); // 重新加载数据
      } catch (error) {
        console.error("删除学期失败", error);
      }
    })
    .catch(() => {
      ElMessage.info("已取消删除");
    });
};

const handleSubmit = () => {
  formRef.value.validate(async (valid) => {
    if (valid) {
      const data = {
        name: termForm.name,
        startDate: termForm.dateRange[0],
        endDate: termForm.dateRange[1],
      };

      try {
        if (termForm.id) {
          await updateTermApi(termForm.id, data);
          ElMessage.success("更新成功");
        } else {
          await createTermApi(data);
          ElMessage.success("创建成功");
        }
        dialogVisible.value = false;
        fetchTerms(); // 重新加载数据
      } catch (error) {
        console.error("操作失败", error);
      }
    } else {
      ElMessage.error("请检查表单是否填写完整");
    }
  });
};

const handleCancel = () => {
  dialogVisible.value = false;
  formRef.value.resetFields();
};
</script>

<style scoped>
.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}
</style>
