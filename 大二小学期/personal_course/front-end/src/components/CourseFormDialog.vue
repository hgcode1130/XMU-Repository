<template>
  <el-dialog
    :model-value="props.modelValue"
    :title="title"
    width="750px"
    :close-on-click-modal="false"
    @close="handleClose"
  >
    <el-form ref="formRef" :model="form" :rules="rules" label-width="100px">
      <!-- 基本信息区域 -->
      <el-divider content-position="left">
        <el-icon><Document /></el-icon>
        <span style="margin-left: 8px;">基本信息</span>
      </el-divider>
      
      <el-row :gutter="20">
        <el-col :span="12">
          <el-form-item label="课程名称" prop="name">
            <el-input 
              v-model="form.name" 
              placeholder="请输入课程名称"
              :prefix-icon="Document"
            />
          </el-form-item>
        </el-col>
        <el-col :span="12">
          <el-form-item label="课程类型" prop="tag">
            <el-select
              v-model="form.tag"
              placeholder="请选择课程类型"
              style="width: 100%"
            >
              <el-option label="必修" :value="1">
                <el-tag type="warning" size="small" disable-transitions>必修</el-tag>
              </el-option>
              <el-option label="选修" :value="0">
                <el-tag type="info" size="small" disable-transitions>选修</el-tag>
              </el-option>
            </el-select>
          </el-form-item>
        </el-col>
      </el-row>

      <el-row :gutter="20">
        <el-col :span="12">
          <el-form-item label="任课教师" prop="teachers">
            <el-input
              v-model="form.teachers"
              placeholder="多个教师用逗号隔开"
              :prefix-icon="User"
            />
          </el-form-item>
        </el-col>
        <el-col :span="12">
          <el-form-item label="主讲教师邮箱" prop="mainTeacherEmail">
            <el-input
              v-model="form.mainTeacherEmail"
              placeholder="请输入主讲教师邮箱"
              :prefix-icon="Message"
              type="email"
            />
          </el-form-item>
        </el-col>
      </el-row>

      <el-row :gutter="20">
        <el-col :span="12">
          <el-form-item label="课程群号" prop="courseGroupChatId">
            <el-input
              v-model="form.courseGroupChatId"
              placeholder="请输入课程群号"
              :prefix-icon="ChatDotRound"
            />
          </el-form-item>
        </el-col>
        <el-col :span="12">
          <!-- 占位列，保持布局平衡 -->
        </el-col>
      </el-row>

      <el-form-item label="课程备注" prop="note">
        <el-input
          v-model="form.note"
          type="textarea"
          placeholder="请输入备注信息（选填）"
          :rows="3"
          maxlength="500"
          show-word-limit
        />
      </el-form-item>

      <!-- 上课安排区域 -->
      <el-divider content-position="left">
        <el-icon><Calendar /></el-icon>
        <span style="margin-left: 8px;">上课安排</span>
      </el-divider>

      <div
        v-for="(schedule, index) in form.scheduleEntries"
        :key="index"
        class="schedule-item"
      >
        <div class="schedule-header">
          <span class="schedule-title">
            <el-icon><Timer /></el-icon>
            安排 {{ index + 1 }}
          </span>
          <el-button
            type="danger"
            :icon="Delete"
            circle
            size="small"
            @click="removeSchedule(index)"
            :disabled="form.scheduleEntries.length === 1"
          />
        </div>

        <el-row :gutter="16">
          <el-col :span="8">
            <el-form-item
              :prop="'scheduleEntries.' + index + '.location'"
              :rules="{
                required: true,
                message: '地点不能为空',
                trigger: 'blur',
              }"
              label="上课地点"
              label-width="80px"
            >
              <el-input 
                v-model="schedule.location" 
                placeholder="教学楼-教室号"
                :prefix-icon="Location"
              />
            </el-form-item>
          </el-col>
          <el-col :span="8">
            <el-form-item
              :prop="'scheduleEntries.' + index + '.dayOfWeek'"
              :rules="{
                required: true,
                message: '请选择星期',
                trigger: 'change',
              }"
              label="星期几"
              label-width="80px"
            >
              <el-select v-model="schedule.dayOfWeek" placeholder="选择星期" style="width: 100%">
                <el-option
                  v-for="day in 7"
                  :key="day"
                  :label="'星期' + '一二三四五六日'[day - 1]"
                  :value="day"
                />
              </el-select>
            </el-form-item>
          </el-col>
          <el-col :span="8">
            <el-form-item
              :prop="'scheduleEntries.' + index + '.weeks'"
              :rules="{
                required: true,
                message: '请填写周数',
                trigger: 'blur',
              }"
              label="上课周数"
              label-width="80px"
            >
              <el-input
                v-model="schedule.weeks"
                placeholder="1-16 或 1,3,5"
              />
            </el-form-item>
          </el-col>
        </el-row>

        <el-row :gutter="16">
          <el-col :span="12">
            <el-form-item
              label="上课节次"
              :prop="'scheduleEntries.' + index + '.periods'"
              :rules="{
                required: true,
                message: '请选择节次',
                trigger: 'change',
              }"
              label-width="80px"
            >
              <el-select
                v-model="schedule.periods"
                multiple
                placeholder="选择节次（可多选）"
                style="width: 100%"
              >
                <el-option
                  v-for="p in 12"
                  :key="p"
                  :label="`第${p}节 (${getPeriodTime(p)})`"
                  :value="p"
                />
              </el-select>
            </el-form-item>
          </el-col>
          <el-col :span="12">
            <!-- 显示选中节次的时间范围 -->
            <div class="period-info" v-if="schedule.periods && schedule.periods.length > 0">
              <el-text type="info" size="small">
                <el-icon><Clock /></el-icon>
                {{ getSelectedPeriodsTimeRange(schedule.periods) }}
              </el-text>
            </div>
          </el-col>
        </el-row>
      </div>

      <el-form-item>
        <el-button
          type="primary"
          @click="addSchedule"
          :icon="Plus"
          style="width: 100%; border-style: dashed;"
          size="default"
          plain
        >
          添加上课安排
        </el-button>
      </el-form-item>
    </el-form>
    
    <template #footer>
      <div class="dialog-footer">
        <!-- 新增：清空按钮区域 -->
        <div class="footer-left">
          <el-button 
            v-if="props.mode === 'edit'" 
            @click="handleClearForm"
            type="warning"
            :icon="RefreshLeft"
            plain
          >
            清空表单
          </el-button>
        </div>
        
        <!-- 主要操作按钮区域 -->
        <div class="footer-right">
          <el-button @click="handleClose" size="default">取 消</el-button>
          <el-button type="primary" @click="handleSubmit" size="default">
            {{ props.mode === 'edit' ? '更新课程' : '创建课程' }}
          </el-button>
        </div>
      </div>
    </template>
  </el-dialog>
</template>

<script setup>
import { ref, reactive, watch, computed, nextTick } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { 
  Plus, 
  Delete, 
  RefreshLeft, 
  Document, 
  User, 
  Message, 
  ChatDotRound, 
  Calendar, 
  Timer, 
  Location, 
  Clock 
} from "@element-plus/icons-vue";
import { cloneDeep } from "lodash-es";

// --- Props and Emits ---
const props = defineProps({
  modelValue: {
    type: Boolean,
    required: true,
  },
  mode: {
    type: String,
    default: "add",
  },
  courseData: {
    type: Object,
    default: () => ({}),
  },
  termId: {
    type: [Number, String],
    required: true,
  },
});

const emit = defineEmits(["update:modelValue", "submitSuccess"]);

// --- State and Data ---
const formRef = ref(null);

const title = computed(() =>
  props.mode === "add" ? "手动添加课程" : "编辑课程"
);

// 表单数据模型
const form = reactive({
  id: null,
  name: "",
  teachers: "",
  mainTeacherEmail: "",
  courseGroupChatId: "",
  note: "",
  tag: 1,
  termId: null,
  scheduleEntries: [],
});

// 保存原始数据用于重置
const originalCourseData = ref(null);

// 时间段映射
const periodTimes = {
  1: { start: '08:00', end: '08:45' },
  2: { start: '08:50', end: '09:35' },
  3: { start: '09:50', end: '10:35' },
  4: { start: '10:40', end: '11:25' },
  5: { start: '11:30', end: '12:15' },
  6: { start: '14:00', end: '14:45' },
  7: { start: '14:50', end: '15:35' },
  8: { start: '15:50', end: '16:35' },
  9: { start: '16:40', end: '17:25' },
  10: { start: '17:30', end: '18:15' },
  11: { start: '19:30', end: '20:15' },
  12: { start: '20:20', end: '21:05' }
};

// 获取节次对应的时间
const getPeriodTime = (period) => {
  const time = periodTimes[period];
  if (!time) return '';
  return `${time.start}-${time.end}`;
};

// 获取选中节次的时间范围
const getSelectedPeriodsTimeRange = (periods) => {
  if (!periods || periods.length === 0) return '';
  
  const sortedPeriods = [...periods].sort((a, b) => a - b);
  const startTime = periodTimes[sortedPeriods[0]]?.start;
  const endTime = periodTimes[sortedPeriods[sortedPeriods.length - 1]]?.end;
  
  if (startTime && endTime) {
    return `${startTime} - ${endTime}`;
  }
  return '';
};

// 表单校验规则
const rules = {
  name: [{ required: true, message: "请输入课程名称", trigger: "blur" }],
  tag: [{ required: true, message: '请选择课程类型', trigger: 'change' }],
  teachers: [{ required: true, message: "请输入任课教师", trigger: "blur" }],
  mainTeacherEmail: [
    { type: 'email', message: '请输入正确的邮箱格式', trigger: 'blur' }
  ],
};

// --- Dynamic Form Logic ---

// 新增一个空的 schedule entry
const addSchedule = () => {
  form.scheduleEntries.push({
    location: "",
    dayOfWeek: null,
    weeks: "",
    periods: [],
  });
};

// 移除指定索引的 schedule entry
const removeSchedule = (index) => {
  if (form.scheduleEntries.length > 1) {
    form.scheduleEntries.splice(index, 1);
  }
};

// 清空表单数据
const handleClearForm = () => {
  ElMessageBox.confirm(
    '确定要清空表单吗？当前填写的内容将会丢失。',
    '清空确认',
    {
      confirmButtonText: '确定清空',
      cancelButtonText: '取消',
      type: 'warning',
    }
  ).then(() => {
    // 重置为新建模式的空表单
    resetFormToEmpty();
    ElMessage.success('表单已清空');
  }).catch(() => {
    // 用户取消，不做任何操作
  });
};

// 重置表单到空状态
const resetFormToEmpty = () => {
  // 重置表单验证
  if (formRef.value) {
    formRef.value.resetFields();
  }
  
  // 清空表单数据
  Object.assign(form, {
    id: null,
    name: "",
    teachers: "",
    mainTeacherEmail: "",
    courseGroupChatId: "",
    note: "",
    tag: 1,
    termId: props.termId,
    scheduleEntries: [],
  });
  
  // 添加一个空的上课安排
  addSchedule();
};

// 加载表单数据（用于编辑模式）
const loadFormData = (courseData) => {
  console.log('🔧 [CourseFormDialog] 开始加载表单数据:', {
    courseData,
    mode: props.mode,
    hasScheduleEntries: courseData?.scheduleEntries?.length > 0,
    courseId: courseData?.id,
    courseName: courseData?.name
  });
  
  if (!courseData) {
    console.warn('⚠️ [CourseFormDialog] 课程数据为空，跳过加载');
    resetFormToEmpty();
    return;
  }
  
  if (!courseData.id) {
    console.warn('⚠️ [CourseFormDialog] 课程数据无ID，跳过加载');
    resetFormToEmpty();
    return;
  }
  
  // 保存原始数据
  originalCourseData.value = cloneDeep(courseData);
  
  // 深拷贝课程数据
  const initialData = cloneDeep(courseData);
  
  // 后端数据适配前端UI
  if (initialData.scheduleEntries && initialData.scheduleEntries.length > 0) {
    console.log('📅 [CourseFormDialog] 处理课程安排数据:', initialData.scheduleEntries);
    
    initialData.scheduleEntries.forEach((entry, index) => {
      console.log(`📍 [CourseFormDialog] 处理第${index + 1}个安排:`, entry);
      
      // 处理周数格式：将后端的 startWeek/endWeek 转换为前端的 weeks 字符串
      if (entry.startWeek !== undefined && entry.endWeek !== undefined) {
        entry.weeks = `${entry.startWeek}-${entry.endWeek}`;
        console.log(`✅ [CourseFormDialog] 周数转换: ${entry.startWeek}-${entry.endWeek} → ${entry.weeks}`);
      } else if (entry.weeks && Array.isArray(entry.weeks)) {
        // 如果后端返回的是周数数组，转换为字符串格式
        entry.weeks = entry.weeks.join(',');
        console.log(`✅ [CourseFormDialog] 周数数组转换: ${entry.weeks}`);
      } else {
        entry.weeks = "";
        console.log(`⚠️ [CourseFormDialog] 周数字段为空，设置默认值`);
      }
      
      // 处理节次格式：将后端的 startPeriod/endPeriod 转换为前端的 periods 数组
      if (entry.startPeriod !== undefined && entry.endPeriod !== undefined) {
        entry.periods = [];
        for (let i = entry.startPeriod; i <= entry.endPeriod; i++) {
          entry.periods.push(i);
        }
        console.log(`✅ [CourseFormDialog] 节次转换: ${entry.startPeriod}-${entry.endPeriod} → [${entry.periods.join(',')}]`);
      } else {
        entry.periods = [];
        console.log(`⚠️ [CourseFormDialog] 节次字段为空，设置默认值`);
      }
      
      // 确保必要字段存在
      entry.location = entry.location || "";
      entry.dayOfWeek = entry.dayOfWeek || null;
    });
  } else {
    console.log('📅 [CourseFormDialog] 无课程安排数据，将添加空安排');
    initialData.scheduleEntries = [];
  }
  
  // 填充表单（确保新字段的兼容性）
  const formData = {
    id: initialData.id || null,
    name: initialData.name || "",
    teachers: initialData.teachers || "",
    mainTeacherEmail: initialData.mainTeacherEmail || initialData.main_teacher_email || "",
    courseGroupChatId: initialData.courseGroupChatId || initialData.course_group_chat_id || "",
    note: initialData.note || "",
    tag: initialData.tag !== undefined ? initialData.tag : 1,
    termId: props.termId,
    scheduleEntries: initialData.scheduleEntries || [],
  };
  
  console.log('📝 [CourseFormDialog] 即将填充表单数据:', formData);
  
  // 直接赋值到reactive对象的每个属性，而不是使用Object.assign
  form.id = formData.id;
  form.name = formData.name;
  form.teachers = formData.teachers;
  form.mainTeacherEmail = formData.mainTeacherEmail;
  form.courseGroupChatId = formData.courseGroupChatId;
  form.note = formData.note;
  form.tag = formData.tag;
  form.termId = formData.termId;
  
  // 清空并重新填充scheduleEntries
  form.scheduleEntries.splice(0);
  formData.scheduleEntries.forEach(entry => {
    form.scheduleEntries.push({...entry});
  });
  
  // 如果没有课程安排，添加一个空的
  if (form.scheduleEntries.length === 0) {
    console.log('➕ [CourseFormDialog] 添加空的课程安排');
    addSchedule();
  }
  
  console.log('✅ [CourseFormDialog] 表单数据加载完成:', {
    originalData: courseData,
    processedFormData: form,
    scheduleCount: form.scheduleEntries.length,
    formName: form.name,
    formTeachers: form.teachers
  });
  
  // 强制触发 Vue 的响应式更新
  nextTick(() => {
    console.log('🔄 [CourseFormDialog] nextTick后的表单状态:', {
      formName: form.name,
      formTeachers: form.teachers,
      scheduleCount: form.scheduleEntries.length
    });
  });
};

// --- Dialog and Form Handling ---

// 监听多个数据源的变化
watch(
  [() => props.modelValue, () => props.mode, () => props.courseData],
  ([newVisible, newMode, newCourseData], [oldVisible, oldMode, oldCourseData]) => {
    console.log('👀 [CourseFormDialog] 监听器触发:', {
      visible: { old: oldVisible, new: newVisible },
      mode: { old: oldMode, new: newMode },
      courseData: { 
        old: oldCourseData?.id, 
        new: newCourseData?.id,
        hasData: !!newCourseData?.id,
        newCourseName: newCourseData?.name
      }
    });
    
    if (newVisible) {
      console.log('🚀 [CourseFormDialog] 对话框打开，开始初始化表单');
      
      // 使用 nextTick 确保 DOM 更新完成
      nextTick(() => {
        console.log('⏰ [CourseFormDialog] nextTick执行，DOM已更新');
        
        // 重置表单验证
        if (formRef.value) {
          formRef.value.resetFields();
          console.log('🔄 [CourseFormDialog] 表单验证已重置');
        }
        
        if (newMode === "edit" && newCourseData?.id) {
          console.log('📝 [CourseFormDialog] 编辑模式：加载现有数据');
          loadFormData(newCourseData);
        } else {
          console.log('➕ [CourseFormDialog] 新建模式：重置为空表单');
          resetFormToEmpty();
        }
      });
    }
  },
  { immediate: true, deep: true }
);

// 关闭对话框
const handleClose = () => {
  emit("update:modelValue", false);
};

// 提交表单
const handleSubmit = async () => {
  if (!formRef.value) return;
  
  await formRef.value.validate((valid) => {
    if (valid) {
      // 验证上课安排
      if (form.scheduleEntries.length === 0) {
        ElMessage.warning("请至少添加一个上课安排");
        return;
      }

      // 数据预处理，将前端UI数据转换为后端API需要的格式
      const submissionData = cloneDeep(form);
      
      try {
        submissionData.scheduleEntries.forEach((entry) => {
          // 处理节次数据：将 periods 数组转换为 startPeriod 和 endPeriod
          if (entry.periods && entry.periods.length > 0) {
            const periods = entry.periods.sort((a, b) => a - b);
            entry.startPeriod = periods[0];
            entry.endPeriod = periods[periods.length - 1];
          }
          
          // 处理周数数据：将 weeks 字符串转换为 startWeek 和 endWeek
          if (entry.weeks) {
            if (entry.weeks.includes('-')) {
              // 处理 "1-16" 格式
              const weekParts = entry.weeks.split("-");
              entry.startWeek = parseInt(weekParts[0], 10);
              entry.endWeek = parseInt(weekParts[1], 10);
            } else if (entry.weeks.includes(',')) {
              // 处理 "1,3,5" 格式 - 简化处理，取最小和最大值
              const weekList = entry.weeks.split(',').map(w => parseInt(w.trim(), 10));
              entry.startWeek = Math.min(...weekList);
              entry.endWeek = Math.max(...weekList);
            } else {
              // 单个周数
              const week = parseInt(entry.weeks, 10);
              entry.startWeek = week;
              entry.endWeek = week;
            }
          }

          // 删除前端UI专用的字段
          delete entry.periods;
          delete entry.weeks;
        });
      } catch (e) {
        console.error("数据格式处理失败:", e);
        ElMessage.error("数据格式处理失败，请检查周数或节次填写是否正确。");
        return;
      }

      console.log('📤 [CourseFormDialog] 提交数据:', submissionData);
      
      // 发射成功事件，由父组件处理API调用
      emit("submitSuccess", submissionData);
      handleClose();
    } else {
      ElMessage.error("请检查表单是否填写完整");
    }
  });
};
</script>

<style scoped>
/* 课程安排项样式 */
.schedule-item {
  padding: 20px;
  border: 1px solid #e4e7ed;
  border-radius: 8px;
  margin-bottom: 16px;
  background-color: #fafafa;
  position: relative;
}

.schedule-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 16px;
  padding-bottom: 8px;
  border-bottom: 1px solid #e4e7ed;
}

.schedule-title {
  display: flex;
  align-items: center;
  gap: 8px;
  font-weight: 600;
  color: #303133;
  font-size: 14px;
}

.period-info {
  display: flex;
  align-items: center;
  margin-top: 8px;
  padding: 8px 12px;
  background-color: #f0f9ff;
  border-radius: 4px;
  border-left: 3px solid #409eff;
}

/* 分隔线样式 */
.el-divider {
  margin: 24px 0 16px 0;
}

.el-divider .el-divider__text {
  background-color: #fff;
  color: #303133;
  font-weight: 600;
}

/* 表单项样式优化 */
.el-form-item {
  margin-bottom: 18px;
}

/* 底部按钮布局样式 */
.dialog-footer {
  display: flex;
  justify-content: space-between;
  align-items: center;
  width: 100%;
  padding-top: 16px;
  border-top: 1px solid #e4e7ed;
  margin-top: 16px;
}

.footer-left {
  flex: 1;
  display: flex;
  justify-content: flex-start;
}

.footer-right {
  display: flex;
  gap: 12px;
}

/* 响应式调整 */
@media (max-width: 768px) {
  .dialog-footer {
    flex-direction: column;
    gap: 12px;
  }
  
  .footer-left,
  .footer-right {
    width: 100%;
    justify-content: center;
  }
  
  .footer-left {
    order: 2;
  }
  
  .footer-right {
    order: 1;
  }
  
  .schedule-item {
    padding: 16px;
  }
  
  .schedule-header {
    flex-direction: column;
    gap: 8px;
    align-items: flex-start;
  }
}

/* 选择器选项样式 */
.el-select-dropdown__item {
  display: flex;
  align-items: center;
  justify-content: space-between;
}

/* 表单验证错误样式 */
.el-form-item.is-error .el-input__inner,
.el-form-item.is-error .el-select .el-input__inner,
.el-form-item.is-error .el-textarea__inner {
  border-color: #f56c6c;
}
</style>