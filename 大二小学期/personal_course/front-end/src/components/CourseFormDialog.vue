<template>
  <el-dialog
    :model-value="props.modelValue"
    :title="title"
    width="650px"
    :close-on-click-modal="false"
    @close="handleClose"
  >
    <el-form ref="formRef" :model="form" :rules="rules" label-width="80px">
      <el-row :gutter="20">
        <el-col :span="12">
          <el-form-item label="课程名称" prop="name">
            <el-input v-model="form.name" placeholder="请输入课程名称" />
          </el-form-item>
        </el-col>
        <el-col :span="12">
          <el-form-item label="任课教师" prop="teachers">
            <el-input
              v-model="form.teachers"
              placeholder="多个教师用逗号隔开"
            />
          </el-form-item>
        </el-col>
      </el-row>
      <el-form-item label="课程备注" prop="note">
        <el-input
          v-model="form.note"
          type="textarea"
          placeholder="请输入备注信息"
        />
      </el-form-item>

      <el-divider content-position="left">上课安排</el-divider>

      <div
        v-for="(schedule, index) in form.scheduleEntries"
        :key="index"
        class="schedule-item"
      >
        <el-row :gutter="10" align="middle">
          <el-col :span="10">
            <el-form-item
              :prop="'scheduleEntries.' + index + '.location'"
              :rules="{
                required: true,
                message: '地点不能为空',
                trigger: 'blur',
              }"
              label="上课地点"
            >
              <el-input v-model="schedule.location" placeholder="上课地点" />
            </el-form-item>
          </el-col>
          <el-col :span="6">
            <el-form-item
              :prop="'scheduleEntries.' + index + '.dayOfWeek'"
              :rules="{
                required: true,
                message: '请选择星期',
                trigger: 'change',
              }"
              label="星期"
            >
              <el-select v-model="schedule.dayOfWeek" placeholder="星期">
                <el-option
                  v-for="day in 7"
                  :key="day"
                  :label="'星期' + '一二三四五六日'[day - 1]"
                  :value="day"
                />
              </el-select>
            </el-form-item>
          </el-col>
          <el-col :span="6">
            <el-form-item
              label-width="0"
              :prop="'scheduleEntries.' + index + '.weeks'"
              :rules="{
                required: true,
                message: '请填写周数',
                trigger: 'blur',
              }"
            >
              <el-input
                v-model="schedule.weeks"
                placeholder="1-16周 或 1,3,5周"
              />
            </el-form-item>
          </el-col>
          <el-col :span="1">
            <el-button
              type="danger"
              :icon="Delete"
              circle
              @click="removeSchedule(index)"
            />
          </el-col>
        </el-row>
        <el-row :gutter="10">
          <el-col :span="10">
            <el-form-item
              label="上课节次"
              :prop="'scheduleEntries.' + index + '.periods'"
              :rules="{
                required: true,
                message: '请选择节次',
                trigger: 'change',
              }"
            >
              <el-select
                v-model="schedule.periods"
                multiple
                placeholder="选择节次"
                style="width: 100%"
              >
                <el-option
                  v-for="p in 12"
                  :key="p"
                  :label="`第${p}节`"
                  :value="p"
                />
              </el-select>
            </el-form-item>
          </el-col>
          <el-col :span="12">
            <el-form-item label="课程标签" prop="tag">
              <el-select
                v-model="form.tag"
                placeholder="请选择课程标签"
                style="width: 100%"
              >
                <!-- 将 value 修改为数字 -->
                <el-option label="必修" :value="1" />
                <el-option label="选修" :value="0" />
              </el-select>
            </el-form-item>
          </el-col>
        </el-row>
      </div>

      <el-form-item>
        <el-button
          type="dashed"
          @click="addSchedule"
          :icon="Plus"
          style="width: 100%"
        >
          添加上课安排
        </el-button>
      </el-form-item>
    </el-form>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="handleClose">取 消</el-button>
        <el-button type="primary" @click="handleSubmit">确 定</el-button>
      </span>
    </template>
  </el-dialog>
</template>

<script setup>
import { ref, reactive, watch, computed } from "vue";
import { ElMessage } from "element-plus";
import { Plus, Delete } from "@element-plus/icons-vue";
import { cloneDeep } from "lodash-es"; // 使用 lodash 的深拷贝，防止数据污染

// --- Props and Emits ---
const props = defineProps({
  modelValue: {
    // 对话框是否可见
    type: Boolean,
    required: true,
  },
  mode: {
    // 模式: 'add' 或 'edit'
    type: String,
    default: "add",
  },
  courseData: {
    // 编辑模式下的初始课程数据
    type: Object,
    default: () => ({}),
  },
  termId: {
    // 当前学期ID
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
  note: "",
  tag: 1,
  termId: null,
  scheduleEntries: [],
});

// 表单校验规则
const rules = {
  name: [{ required: true, message: "请输入课程名称", trigger: "blur" }],
  tag: [{ required: true, message: '请选择课程标签', trigger: 'change' }],
};

// --- Dynamic Form Logic ---

// 新增一个空的 schedule entry
const addSchedule = () => {
  form.scheduleEntries.push({
    location: "",
    dayOfWeek: null,
    weeks: "", // 改为字符串以支持 "1-8" 或 "1,3,5" 格式
    periods: [], // 改为数组接收多选节次
  });
};

// 移除指定索引的 schedule entry
const removeSchedule = (index) => {
  form.scheduleEntries.splice(index, 1);
};

// --- Dialog and Form Handling ---

// 监听 props.modelValue 变化，打开对话框时填充数据
watch(
  () => props.modelValue,
  (newVal) => {
    if (newVal) {
      // 重置表单
      formRef.value?.resetFields();
      let initialData;

      if (props.mode === "edit" && props.courseData) {
        initialData = cloneDeep(props.courseData);
        // 后端数据适配前端UI
        initialData.scheduleEntries.forEach((entry) => {
          // 假设后端存储 startWeek/endWeek 和 startPeriod/endPeriod
          // 这里需要根据您的后端数据结构进行调整
          // 示例：将 start/end 转换为 weeks 和 periods 数组
          entry.weeks = `${entry.startWeek}-${entry.endWeek}`;
          entry.periods = [];
          for (let i = entry.startPeriod; i <= entry.endPeriod; i++) {
            entry.periods.push(i);
          }
        });
      } else {
        initialData = {
          id: null,
          name: "",
          teachers: "",
          note: "",
          scheduleEntries: [],
        };
      }

      Object.assign(form, initialData);
      form.termId = props.termId;
      // 如果是新建模式，默认添加一个空的排程项
      if (props.mode === "add" && form.scheduleEntries.length === 0) {
        addSchedule();
      }
    }
  }
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
      if (form.scheduleEntries.length === 0) {
        ElMessage.warning("请至少添加一个上课安排");
        return;
      }

      // 数据预处理，将前端UI数据转换为后端API需要的格式
      const submissionData = cloneDeep(form);
      try {
        submissionData.scheduleEntries.forEach((entry) => {
          // 这里是数据转换的关键，需要您根据后端API来定义
          // 示例：将 "1-8" 或 "1,3,5" 格式的 weeks 拆分
          // 示例：将 periods 数组转换为 startPeriod 和 endPeriod
          const periods = entry.periods.sort((a, b) => a - b);
          entry.startPeriod = periods[0];
          entry.endPeriod = periods[periods.length - 1];
          // ... weeks 的解析逻辑会更复杂，这里仅作示意
          // 为了简化，我们暂时假设用户只输入 "开始周-结束周" 格式
          const weekParts = entry.weeks.split("-");
          entry.startWeek = parseInt(weekParts[0], 10);
          entry.endWeek = parseInt(weekParts[1], 10);

          // 删除前端UI专用的字段
          delete entry.periods;
          delete entry.weeks;
        });
      } catch (e) {
        ElMessage.error("数据格式处理失败，请检查周数或节次填写是否正确。");
        return;
      }

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
.schedule-item {
  padding: 10px;
  border: 1px dashed #dcdfe6;
  border-radius: 4px;
  margin-bottom: 15px;
  position: relative;
}

.el-button.is-dashed {
  border-style: dashed;
}

/* 动态表单的label在小屏幕下可能需要调整，这里保持默认 */
/* 如果需要更复杂的布局，可以给 el-form-item 增加 class 并单独设置样式 */
</style>
