<template>
  <el-dialog
    :model-value="props.modelValue"
    title="Excel批量导入课程"
    width="650px"
    :close-on-click-modal="false"
    @close="handleClose"
  >
    <!-- 导入说明 -->
    <div class="import-info">
      <el-alert type="info" :closable="false" show-icon>
        <template #title>
          <span style="font-weight: 600">导入说明</span>
        </template>
        <template #default>
          <ul class="info-list">
            <li>支持 .xlsx 和 .xls 格式的Excel文件</li>
            <li>文件大小不超过 10MB，建议单次导入不超过 1000 行课程数据</li>
            <li>请严格按照模板格式填写，确保表头名称完全匹配</li>
            <li>标签字段只能填写"必修"或"选修"，空值默认为"必修"</li>
          </ul>
        </template>
      </el-alert>
    </div>

    <!-- 模板下载区域 -->
    <div class="template-section">
      <el-card shadow="hover" class="template-card">
        <template #header>
          <div class="template-header">
            <el-icon><Document /></el-icon>
            <span>Excel模板</span>
          </div>
        </template>

        <div class="template-content">
          <p>为确保导入成功，请先下载并使用标准模板填写课程数据：</p>
          <el-button
            type="primary"
            :icon="Download"
            @click="handleDownloadTemplate"
            :loading="downloadLoading"
            size="default"
          >
            {{ downloadLoading ? "下载中..." : "下载Excel模板" }}
          </el-button>
        </div>
      </el-card>
    </div>

    <!-- 文件上传区域 -->
    <div class="upload-section">
      <el-card shadow="hover" class="upload-card">
        <template #header>
          <div class="upload-header">
            <el-icon><Upload /></el-icon>
            <span>文件上传</span>
          </div>
        </template>

        <el-upload
          ref="uploadRef"
          class="excel-upload"
          drag
          :auto-upload="false"
          :show-file-list="true"
          :limit="1"
          accept=".xlsx,.xls"
          :on-change="handleFileChange"
          :on-remove="handleFileRemove"
          :before-upload="beforeUpload"
        >
          <el-icon class="el-icon--upload"><UploadFilled /></el-icon>
          <div class="el-upload__text">
            将Excel文件拖到此处，或<em>点击上传</em>
          </div>
          <template #tip>
            <div class="el-upload__tip">
              只能上传 .xlsx/.xls 文件，且不超过 10MB
            </div>
          </template>
        </el-upload>
      </el-card>
    </div>

    <!-- 导入结果显示 -->
    <div v-if="importResult" class="result-section">
      <el-card shadow="hover" class="result-card">
        <template #header>
          <div class="result-header">
            <el-icon><TrendCharts /></el-icon>
            <span>导入结果</span>
          </div>
        </template>

        <!-- 统计信息 -->
        <div class="result-summary">
          <el-row :gutter="16">
            <el-col :span="6">
              <el-statistic title="总行数" :value="importResult.totalRows" />
            </el-col>
            <el-col :span="6">
              <el-statistic
                title="成功导入"
                :value="importResult.successfulImports"
              >
                <template #suffix>
                  <el-icon style="color: #67c23a"><CircleCheck /></el-icon>
                </template>
              </el-statistic>
            </el-col>
            <el-col :span="6">
              <el-statistic
                title="导入失败"
                :value="importResult.failedImports"
              >
                <template #suffix>
                  <el-icon style="color: #f56c6c"><CircleClose /></el-icon>
                </template>
              </el-statistic>
            </el-col>
            <el-col :span="6">
              <el-statistic
                title="处理时间"
                :value="importResult.summary?.totalProcessingTime || '0秒'"
              />
            </el-col>
          </el-row>
        </div>

        <!-- 成功导入的课程 -->
        <div
          v-if="importResult.importedCourses?.length > 0"
          class="success-courses"
        >
          <el-divider content-position="left">
            <el-icon><CircleCheck /></el-icon>
            <span style="margin-left: 8px">成功导入的课程</span>
          </el-divider>
          <div class="course-list">
            <el-tag
              v-for="course in importResult.importedCourses.slice(0, 10)"
              :key="course.courseId"
              type="success"
              class="course-tag"
            >
              第{{ course.rowNumber }}行: {{ course.courseName }}
            </el-tag>
            <el-text
              v-if="importResult.importedCourses.length > 10"
              type="info"
              size="small"
            >
              ... 还有 {{ importResult.importedCourses.length - 10 }} 门课程
            </el-text>
          </div>
        </div>

        <!-- 错误信息 -->
        <div v-if="importResult.errors?.length > 0" class="error-section">
          <el-divider content-position="left">
            <el-icon><CircleClose /></el-icon>
            <span style="margin-left: 8px">导入错误</span>
          </el-divider>
          <div class="error-list">
            <el-alert
              v-for="error in importResult.errors"
              :key="error.rowNumber"
              type="error"
              :closable="false"
              class="error-item"
            >
              <template #title>
                第{{ error.rowNumber }}行
                <span v-if="error.courseName">: {{ error.courseName }}</span>
              </template>
              <template #default>{{ error.error }}</template>
            </el-alert>
          </div>
        </div>
      </el-card>
    </div>

    <template #footer>
      <div class="dialog-footer">
        <el-button @click="handleClose" size="default">
          {{ importResult ? "关闭" : "取消" }}
        </el-button>
        <el-button
          type="primary"
          @click="handleImport"
          :loading="importing"
          :disabled="!selectedFile"
          size="default"
        >
          {{ importing ? "导入中..." : "开始导入" }}
        </el-button>
      </div>
    </template>
  </el-dialog>
</template>

<script setup>
import { ref, reactive } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import {
  Document,
  Download,
  Upload,
  UploadFilled,
  TrendCharts,
  CircleCheck,
  CircleClose,
} from "@element-plus/icons-vue";
import { importExcelApi, downloadTemplateApi } from "@/api/course";

// --- Props and Emits ---
const props = defineProps({
  modelValue: {
    type: Boolean,
    required: true,
  },
  termId: {
    type: [Number, String],
    required: true,
  },
});

const emit = defineEmits(["update:modelValue", "importSuccess"]);

// --- State ---
const uploadRef = ref(null);
const selectedFile = ref(null);
const importing = ref(false);
const downloadLoading = ref(false);
const importResult = ref(null);

// --- Methods ---

// 下载Excel模板
const handleDownloadTemplate = async () => {
  downloadLoading.value = true;
  try {
    console.log("开始下载Excel模板...");

    const response = await downloadTemplateApi();

    console.log("API响应:", {
      status: response.status,
      headers: response.headers,
      dataType: typeof response.data,
      dataSize: response.data?.size || "unknown",
    });

    // 确保响应是 Blob 类型
    if (!(response.data instanceof Blob)) {
      console.error("响应数据类型错误:", typeof response.data, response.data);
      throw new Error("响应数据不是有效的 Blob 类型");
    }

    // 检查Blob大小
    if (response.data.size === 0) {
      console.error("响应的Blob大小为0");
      throw new Error("下载的文件为空");
    }

    console.log("Blob验证通过，大小:", response.data.size);

    // 创建下载链接
    const url = window.URL.createObjectURL(response.data);
    const link = document.createElement("a");
    link.href = url;
    link.download = "课程导入模板.xlsx";

    console.log("下载链接创建:", url);

    // 触发下载
    document.body.appendChild(link);
    link.click();

    console.log("下载已触发");

    // 清理
    document.body.removeChild(link);
    window.URL.revokeObjectURL(url);

    ElMessage.success("模板下载成功");
  } catch (error) {
    console.error("下载模板失败详细信息:", {
      message: error.message,
      response: error.response,
      status: error.response?.status,
      data: error.response?.data,
    });

    if (error.response?.status === 500) {
      ElMessage.error("服务器内部错误，请联系管理员");
    } else if (error.response?.status === 404) {
      ElMessage.error("下载接口未找到，请检查服务器配置");
    } else {
      ElMessage.error("下载模板失败，请重试");
    }
  } finally {
    downloadLoading.value = false;
  }
};


// 文件选择变化
const handleFileChange = (file, fileList) => {
  console.log("文件选择:", file);
  selectedFile.value = file.raw;
  importResult.value = null; // 清空之前的导入结果
};

// 文件移除
const handleFileRemove = () => {
  selectedFile.value = null;
  importResult.value = null;
};

// 上传前验证
const beforeUpload = (file) => {
  // 检查文件类型
  const isExcel =
    file.type ===
      "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet" ||
    file.type === "application/vnd.ms-excel";
  if (!isExcel) {
    ElMessage.error("只能上传Excel文件（.xlsx或.xls格式）！");
    return false;
  }

  // 检查文件大小（10MB）
  const isLt10M = file.size / 1024 / 1024 < 10;
  if (!isLt10M) {
    ElMessage.error("文件大小不能超过10MB！");
    return false;
  }

  return true;
};

// 执行导入
const handleImport = async () => {
  if (!selectedFile.value) {
    ElMessage.warning("请先选择要导入的Excel文件");
    return;
  }

  if (!props.termId) {
    ElMessage.warning("学期信息异常，请刷新页面后重试");
    return;
  }

  // 确认导入
  try {
    await ElMessageBox.confirm(
      "确定要导入该Excel文件吗？导入过程可能需要一些时间，请耐心等待。",
      "确认导入",
      {
        confirmButtonText: "确定导入",
        cancelButtonText: "取消",
        type: "warning",
      }
    );
  } catch {
    return; // 用户取消
  }

  importing.value = true;
  try {
    console.log("开始导入Excel文件:", {
      fileName: selectedFile.value.name,
      fileSize: selectedFile.value.size,
      termId: props.termId,
    });

    const response = await importExcelApi(props.termId, selectedFile.value);
    importResult.value = response.data;

    console.log("导入结果:", importResult.value);

    // 根据导入结果显示相应消息
    const { successfulImports, failedImports, totalRows } = importResult.value;

    if (failedImports === 0) {
      ElMessage.success(`导入成功！共导入 ${successfulImports} 门课程`);
    } else if (successfulImports > 0) {
      ElMessage.warning(
        `部分导入成功：成功 ${successfulImports} 门，失败 ${failedImports} 门`
      );
    } else {
      ElMessage.error(`导入失败：${failedImports} 门课程导入失败`);
    }

    // 如果有成功导入的课程，通知父组件刷新数据
    if (successfulImports > 0) {
      emit("importSuccess", importResult.value);
    }
  } catch (error) {
    console.error("Excel导入失败:", error);

    // 处理不同类型的错误
    if (error.response?.data?.message) {
      ElMessage.error(`导入失败：${error.response.data.message}`);
    } else if (error.response?.status === 413) {
      ElMessage.error("文件过大，请减少数据量或分批导入");
    } else if (error.response?.status === 415) {
      ElMessage.error("文件格式不支持，请使用标准Excel格式");
    } else {
      ElMessage.error("导入失败，请检查文件格式和网络连接");
    }

    // 如果后端返回了错误详情，也显示在结果中
    if (error.response?.data?.data) {
      importResult.value = error.response.data.data;
    }
  } finally {
    importing.value = false;
  }
};

// 关闭对话框
const handleClose = () => {
  // 清理状态
  selectedFile.value = null;
  importResult.value = null;
  if (uploadRef.value) {
    uploadRef.value.clearFiles();
  }

  emit("update:modelValue", false);
};
</script>

<style scoped>
/* 导入说明样式 */
.import-info {
  margin-bottom: 20px;
}

.info-list {
  margin: 0;
  padding-left: 20px;
  color: #606266;
}

.info-list li {
  margin-bottom: 6px;
  line-height: 1.5;
}

/* 模板下载区域 */
.template-section {
  margin-bottom: 20px;
}

.template-card {
  border-radius: 8px;
  border: 1px solid #e4e7ed;
}

.template-header {
  display: flex;
  align-items: center;
  gap: 8px;
  font-weight: 600;
  color: #303133;
}

.template-content {
  text-align: center;
  padding: 16px 0;
}

.template-content p {
  margin-bottom: 16px;
  color: #606266;
  line-height: 1.5;
}

/* 文件上传区域 */
.upload-section {
  margin-bottom: 20px;
}

.upload-card {
  border-radius: 8px;
  border: 1px solid #e4e7ed;
}

.upload-header {
  display: flex;
  align-items: center;
  gap: 8px;
  font-weight: 600;
  color: #303133;
}

.excel-upload {
  width: 100%;
}

.excel-upload :deep(.el-upload-dragger) {
  width: 100%;
  height: 180px;
  border-radius: 8px;
  border: 2px dashed #d9d9d9;
  background-color: #fafafa;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  transition: all 0.3s ease;
}

.excel-upload :deep(.el-upload-dragger:hover) {
  border-color: #409eff;
  background-color: #f0f9ff;
}

.excel-upload :deep(.el-icon--upload) {
  font-size: 48px;
  color: #c0c4cc;
  margin-bottom: 16px;
}

.excel-upload :deep(.el-upload__text) {
  color: #606266;
  font-size: 14px;
}

.excel-upload :deep(.el-upload__text em) {
  color: #409eff;
  font-style: normal;
}

.excel-upload :deep(.el-upload__tip) {
  color: #909399;
  font-size: 12px;
  margin-top: 12px;
}

/* 导入结果区域 */
.result-section {
  margin-bottom: 20px;
}

.result-card {
  border-radius: 8px;
  border: 1px solid #e4e7ed;
}

.result-header {
  display: flex;
  align-items: center;
  gap: 8px;
  font-weight: 600;
  color: #303133;
}

.result-summary {
  margin-bottom: 20px;
}

.result-summary :deep(.el-statistic__head) {
  font-size: 14px;
  color: #909399;
}

.result-summary :deep(.el-statistic__content) {
  font-size: 24px;
  font-weight: 600;
}

/* 成功课程列表 */
.success-courses {
  margin-bottom: 20px;
}

.course-list {
  display: flex;
  flex-wrap: wrap;
  gap: 8px;
  margin-top: 12px;
}

.course-tag {
  margin: 0;
}

/* 错误列表 */
.error-section {
  margin-bottom: 20px;
}

.error-list {
  margin-top: 12px;
  max-height: 300px;
  overflow-y: auto;
}

.error-item {
  margin-bottom: 8px;
}

.error-item:last-child {
  margin-bottom: 0;
}

/* 分隔线样式 */
.el-divider {
  margin: 16px 0;
}

.el-divider .el-divider__text {
  background-color: #fff;
  color: #303133;
  font-weight: 600;
}

/* 底部按钮样式 */
.dialog-footer {
  display: flex;
  justify-content: flex-end;
  gap: 12px;
  padding-top: 16px;
  border-top: 1px solid #e4e7ed;
  margin-top: 16px;
}

/* 响应式调整 */
@media (max-width: 768px) {
  .result-summary :deep(.el-col) {
    margin-bottom: 16px;
  }

  .course-list {
    justify-content: center;
  }

  .error-list {
    max-height: 200px;
  }
}
</style>
