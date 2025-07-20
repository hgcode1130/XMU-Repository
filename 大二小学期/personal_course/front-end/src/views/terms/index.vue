<template>
  <div class="terms-container">
    <!-- 学期选择器卡片 -->
    <el-card class="term-selector-card" shadow="hover">
      <template #header>
        <div class="selector-header">
          <el-icon class="header-icon"><Calendar /></el-icon>
          <span class="header-title">当前学期</span>
        </div>
      </template>
      <div class="selector-content">
        <el-select
          v-model="termStore.currentTermId"
          placeholder="请选择学期"
          size="large"
          class="term-select"
          @change="handleTermChange"
          clearable
        >
          <el-option
            v-for="term in sortedTerms"
            :key="term.id"
            :label="term.name"
            :value="term.id"
            :disabled="!term.startDate || !term.endDate"
          >
            <div class="option-content">
              <span class="option-name">{{ term.name }}</span>
              <span class="option-date" v-if="term.startDate && term.endDate">
                {{ formatDateRange(term.startDate, term.endDate) }}
              </span>
            </div>
          </el-option>
        </el-select>
        <div class="current-term-info" v-if="termStore.currentTerm">
          <el-tag :type="getTermStatus(termStore.currentTerm).type" size="large">
            {{ getTermStatus(termStore.currentTerm).text }}
          </el-tag>
          <div class="term-details">
            <p><el-icon><Calendar /></el-icon> {{ formatDateRange(termStore.currentTerm.startDate, termStore.currentTerm.endDate) }}</p>
            <p v-if="termStore.currentTerm.startDate && termStore.currentTerm.endDate">
              <el-icon><Timer /></el-icon> 共 {{ calculateWeeks(termStore.currentTerm.startDate, termStore.currentTerm.endDate) }} 周
            </p>
          </div>
        </div>
      </div>
    </el-card>

    <!-- 学期管理卡片 -->
    <el-card class="terms-management-card" shadow="hover">
      <template #header>
        <div class="card-header">
          <div class="header-left">
            <el-icon class="header-icon"><Management /></el-icon>
            <span class="header-title">学期管理</span>
            <el-tag v-if="termStore.termList.length" type="info" class="count-tag">
              共 {{ termStore.termList.length }} 个学期
            </el-tag>
          </div>
          <el-button 
            type="primary" 
            :icon="Plus" 
            @click="handleAdd"
            class="add-button"
            size="default"
          >
            新建学期
          </el-button>
        </div>
      </template>

      <!-- 空状态 -->
      <div v-if="!termStore.termList.length && !loading" class="empty-state">
        <el-empty 
          description="暂无学期数据，开始创建第一个学期吧！"
          :image-size="120"
        >
          <el-button type="primary" :icon="Plus" @click="handleAdd">
            创建学期
          </el-button>
        </el-empty>
      </div>

      <!-- 学期表格 -->
      <el-table 
        v-else
        :data="termStore.termList" 
        v-loading="loading" 
        stripe
        class="terms-table"
        :header-cell-style="{ backgroundColor: '#f8f9fa', color: '#606266' }"
      >
        <el-table-column prop="name" label="学期名称" min-width="200">
          <template #default="scope">
            <div class="term-name-cell">
              <el-icon v-if="scope.row.id == termStore.currentTermId" class="current-indicator">
                <Star />
              </el-icon>
              <span :class="{ 'current-term': scope.row.id == termStore.currentTermId }">
                {{ scope.row.name }}
              </span>
            </div>
          </template>
        </el-table-column>
        
        <el-table-column label="时间范围" min-width="180">
          <template #default="scope">
            <div class="date-cell">
              <el-icon><Calendar /></el-icon>
              <span v-if="scope.row.startDate && scope.row.endDate">
                {{ formatDateRange(scope.row.startDate, scope.row.endDate) }}
              </span>
              <span v-else class="no-date">未设置</span>
            </div>
          </template>
        </el-table-column>

        <el-table-column label="状态" width="120" align="center">
          <template #default="scope">
            <el-tag 
              :type="getTermStatus(scope.row).type"
              :effect="scope.row.id == termStore.currentTermId ? 'dark' : 'plain'"
            >
              {{ getTermStatus(scope.row).text }}
            </el-tag>
          </template>
        </el-table-column>

        <el-table-column label="周数" width="80" align="center">
          <template #default="scope">
            <span v-if="scope.row.startDate && scope.row.endDate" class="weeks-count">
              {{ calculateWeeks(scope.row.startDate, scope.row.endDate) }}周
            </span>
            <span v-else class="no-weeks">-</span>
          </template>
        </el-table-column>

        <el-table-column label="操作" width="200" fixed="right" align="center">
          <template #default="scope">
            <div class="action-buttons">
              <el-button
                type="success"
                text
                :icon="Check"
                @click="setCurrentTerm(scope.row)"
                v-if="scope.row.id != termStore.currentTermId"
                size="small"
              >
                设为当前
              </el-button>
              <el-button
                type="primary"
                text
                :icon="Edit"
                @click="handleEdit(scope.row)"
                size="small"
              >
                编辑
              </el-button>
              <el-button
                type="danger"
                text
                :icon="Delete"
                @click="handleDelete(scope.row)"
                size="small"
                :disabled="scope.row.id == termStore.currentTermId"
              >
                删除
              </el-button>
            </div>
          </template>
        </el-table-column>
      </el-table>
    </el-card>

    <!-- 编辑对话框 -->
    <el-dialog
      v-model="dialogVisible"
      :title="dialogTitle"
      width="520px"
      @close="handleCancel"
      :close-on-click-modal="false"
      class="term-dialog"
    >
      <el-form
        ref="formRef"
        :model="termForm"
        :rules="rules"
        label-width="100px"
        class="term-form"
      >
        <el-form-item label="学期名称" prop="name">
          <el-input
            v-model="termForm.name"
            placeholder="例如：2025-2026学年第一学期"
            size="large"
            :prefix-icon="Edit"
            clearable
          />
          <div class="form-tip">
            建议格式：学年+学期，如"2025-2026学年第一学期"
          </div>
        </el-form-item>
        
        <el-form-item label="起止日期" prop="dateRange">
          <el-date-picker
            v-model="termForm.dateRange"
            type="daterange"
            range-separator="至"
            start-placeholder="开始日期"
            end-placeholder="结束日期"
            value-format="YYYY-MM-DD"
            size="large"
            style="width: 100%"
            :prefix-icon="Calendar"
            :shortcuts="dateShortcuts"
          />
          <div class="form-tip">
            选择学期的起始和结束日期，系统将自动计算周数
          </div>
        </el-form-item>
      </el-form>
      
      <template #footer>
        <div class="dialog-footer">
          <el-button @click="handleCancel" size="large">取 消</el-button>
          <el-button 
            type="primary" 
            @click="handleSubmit" 
            size="large"
            :loading="submitting"
          >
            {{ termForm.id ? '更新学期' : '创建学期' }}
          </el-button>
        </div>
      </template>
    </el-dialog>
  </div>
</template>

<script setup>
import { ref, reactive, onMounted, computed } from "vue";
import { useTermStore } from "@/stores/term";
import { createTermApi, updateTermApi, deleteTermApi } from "@/api/term";
import { ElMessage, ElMessageBox } from "element-plus";
import { 
  Plus, 
  Edit, 
  Delete, 
  Calendar, 
  Management, 
  Timer, 
  Star, 
  Check 
} from "@element-plus/icons-vue";

// --- 状态与数据 ---
const termStore = useTermStore();
const loading = ref(false);
const submitting = ref(false);
const dialogVisible = ref(false);
const formRef = ref(null);

const dialogTitle = computed(() => (termForm.id ? "编辑学期" : "新建学期"));

// 按时间排序的学期列表
const sortedTerms = computed(() => {
  return [...termStore.termList].sort((a, b) => {
    // 首先按开始日期排序，如果没有开始日期则放到最后
    if (!a.startDate && !b.startDate) return 0;
    if (!a.startDate) return 1;
    if (!b.startDate) return -1;
    
    // 按开始日期倒序排列（最新的在前）
    return new Date(b.startDate) - new Date(a.startDate);
  });
});

const termForm = reactive({
  id: null,
  name: "",
  dateRange: [],
});

const rules = reactive({
  name: [
    { required: true, message: "请输入学期名称", trigger: "blur" },
    { min: 2, max: 50, message: "学期名称长度在 2 到 50 个字符", trigger: "blur" }
  ],
  dateRange: [
    { required: true, message: "请选择学期起止日期", trigger: "change" },
  ],
});

// 日期快捷选项
const dateShortcuts = [
  {
    text: '2024秋季学期',
    value: ['2024-09-01', '2025-01-20']
  },
  {
    text: '2025春季学期',
    value: ['2025-02-24', '2025-07-13']
  },
  {
    text: '2025秋季学期',
    value: ['2025-09-01', '2026-01-18']
  },
  {
    text: '2026春季学期',
    value: ['2026-02-23', '2026-07-12']
  }
];

// --- 工具函数 ---

// 格式化日期范围
const formatDateRange = (startDate, endDate) => {
  if (!startDate || !endDate) return "未设置";
  return `${startDate} ~ ${endDate}`;
};

// 计算周数
const calculateWeeks = (startDate, endDate) => {
  if (!startDate || !endDate) return 0;
  const start = new Date(startDate);
  const end = new Date(endDate);
  const diffTime = Math.abs(end - start);
  const diffDays = Math.ceil(diffTime / (1000 * 60 * 60 * 24));
  return Math.ceil(diffDays / 7);
};

// 获取学期状态
const getTermStatus = (term) => {
  if (!term.startDate || !term.endDate) {
    return { type: 'info', text: '未设置' };
  }
  
  const now = new Date();
  const start = new Date(term.startDate);
  const end = new Date(term.endDate);
  
  if (now < start) {
    return { type: 'warning', text: '未开始' };
  } else if (now > end) {
    return { type: '', text: '已结束' };
  } else {
    return { type: 'success', text: '进行中' };
  }
};

// --- 核心方法 ---

const fetchTerms = async () => {
  loading.value = true;
  try {
    await termStore.fetchAllTerms();
  } catch (error) {
    console.error("获取学期列表失败", error);
    ElMessage.error("获取学期列表失败");
  } finally {
    loading.value = false;
  }
};

const handleTermChange = (termId) => {
  if (termId) {
    termStore.setTerm(termId);
    ElMessage.success("已切换学期");
  }
};

const setCurrentTerm = (term) => {
  termStore.setTerm(term.id);
  ElMessage.success(`已设置"${term.name}"为当前学期`);
};

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
  if (row.id == termStore.currentTermId) {
    ElMessage.warning("无法删除当前正在使用的学期");
    return;
  }

  ElMessageBox.confirm(
    `确定要删除学期 "${row.name}" 吗？该学期下的所有课程也将被一并删除，此操作不可逆！`,
    "危险操作警告",
    {
      confirmButtonText: "确定删除",
      cancelButtonText: "取消",
      type: "warning",
      buttonSize: "default",
    }
  )
    .then(async () => {
      try {
        await deleteTermApi(row.id);
        ElMessage.success("删除成功");
        await fetchTerms();
      } catch (error) {
        console.error("删除学期失败", error);
        ElMessage.error("删除失败，请重试");
      }
    })
    .catch(() => {
      ElMessage.info("已取消删除");
    });
};

const handleSubmit = () => {
  formRef.value.validate(async (valid) => {
    if (!valid) {
      ElMessage.error("请检查表单是否填写完整");
      return;
    }

    submitting.value = true;
    const data = {
      name: termForm.name,
      startDate: termForm.dateRange[0],
      endDate: termForm.dateRange[1],
    };

    try {
      if (termForm.id) {
        await updateTermApi(termForm.id, data);
        ElMessage.success("学期更新成功");
      } else {
        await createTermApi(data);
        ElMessage.success("学期创建成功");
      }
      dialogVisible.value = false;
      await fetchTerms();
    } catch (error) {
      console.error("操作失败", error);
      ElMessage.error(termForm.id ? "更新失败，请重试" : "创建失败，请重试");
    } finally {
      submitting.value = false;
    }
  });
};

const handleCancel = () => {
  dialogVisible.value = false;
  formRef.value?.resetFields();
  submitting.value = false;
};

// --- 生命周期 ---
onMounted(() => {
  fetchTerms();
});
</script>

<style scoped>
.terms-container {
  padding: 20px;
  max-width: 1400px;
  margin: 0 auto;
}

/* 学期选择器卡片 */
.term-selector-card {
  margin-bottom: 24px;
  border-radius: 12px;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  border: none;
}

.term-selector-card :deep(.el-card__header) {
  background: transparent;
  border: none;
  padding: 20px 24px 0;
}

.term-selector-card :deep(.el-card__body) {
  padding: 0 24px 24px;
}

.selector-header {
  display: flex;
  align-items: center;
  color: white;
  font-weight: 600;
}

.header-icon {
  font-size: 20px;
  margin-right: 8px;
}

.header-title {
  font-size: 18px;
}

.selector-content {
  display: flex;
  flex-direction: column;
  gap: 16px;
}

.term-select {
  width: 100%;
}

.term-select :deep(.el-input__wrapper) {
  background-color: rgba(255, 255, 255, 0.95);
  border: 1px solid rgba(255, 255, 255, 0.3);
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
}

.option-content {
  display: flex;
  flex-direction: column;
  gap: 4px;
}

.option-name {
  font-weight: 500;
  color: #303133;
}

.option-date {
  font-size: 12px;
  color: #909399;
}

.current-term-info {
  display: flex;
  align-items: center;
  gap: 16px;
  padding: 16px;
  background: rgba(255, 255, 255, 0.1);
  border-radius: 8px;
  color: white;
}

.term-details {
  flex: 1;
  display: flex;
  flex-direction: column;
  gap: 4px;
}

.term-details p {
  margin: 0;
  display: flex;
  align-items: center;
  gap: 6px;
  font-size: 14px;
}

.term-details .el-icon {
  font-size: 16px;
}

/* 学期管理卡片 */
.terms-management-card {
  border-radius: 12px;
  border: 1px solid #e4e7ed;
  box-shadow: 0 2px 12px rgba(0, 0, 0, 0.04);
}

.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.header-left {
  display: flex;
  align-items: center;
  gap: 8px;
}

.header-title {
  font-size: 16px;
  font-weight: 600;
  color: #303133;
}

.count-tag {
  margin-left: 8px;
}

.add-button {
  border-radius: 8px;
  padding: 8px 16px;
}

/* 空状态 */
.empty-state {
  padding: 40px 20px;
  text-align: center;
}

/* 表格样式 */
.terms-table {
  border-radius: 8px;
  overflow: hidden;
}

.term-name-cell {
  display: flex;
  align-items: center;
  gap: 8px;
}

.current-indicator {
  color: #f39c12;
  font-size: 16px;
}

.current-term {
  font-weight: 600;
  color: #409eff;
}

.date-cell {
  display: flex;
  align-items: center;
  gap: 6px;
  font-size: 14px;
}

.date-cell .el-icon {
  color: #909399;
}

.no-date, .no-weeks {
  color: #c0c4cc;
  font-style: italic;
}

.weeks-count {
  font-weight: 500;
  color: #606266;
}

.action-buttons {
  display: flex;
  gap: 8px;
  justify-content: center;
}

/* 对话框样式 */
.term-dialog :deep(.el-dialog) {
  border-radius: 12px;
}

.term-dialog :deep(.el-dialog__header) {
  padding: 24px 24px 16px;
  border-bottom: 1px solid #f0f0f0;
}

.term-dialog :deep(.el-dialog__body) {
  padding: 24px;
}

.term-form {
  margin-top: 8px;
}

.form-tip {
  font-size: 12px;
  color: #909399;
  margin-top: 4px;
  line-height: 1.4;
}

.dialog-footer {
  display: flex;
  justify-content: flex-end;
  gap: 12px;
  padding: 16px 24px 24px;
  border-top: 1px solid #f0f0f0;
  margin: 0 -24px -24px;
}

/* 响应式设计 */
@media (max-width: 768px) {
  .terms-container {
    padding: 16px;
  }

  .card-header {
    flex-direction: column;
    gap: 16px;
    align-items: stretch;
  }

  .current-term-info {
    flex-direction: column;
    align-items: flex-start;
    gap: 12px;
  }

  .action-buttons {
    flex-direction: column;
    gap: 4px;
  }

  .term-dialog {
    width: 90vw;
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
  box-shadow: 0 4px 20px rgba(0, 0, 0, 0.08);
}

/* 深色模式适配 */
@media (prefers-color-scheme: dark) {
  .term-selector-card {
    background: linear-gradient(135deg, #4facfe 0%, #00f2fe 100%);
  }
}
</style>