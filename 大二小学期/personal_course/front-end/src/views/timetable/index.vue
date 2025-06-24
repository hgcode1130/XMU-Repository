<template>
  <div>
    <el-card>
      <template #header>
        <div class="card-header">
          <span>{{ currentTermName }}</span>
          <div>
            <el-button type="primary" :icon="Plus" @click="handleAddCourse"
              >手动添加课程</el-button
            >
            <el-button type="success" :icon="Upload" disabled
              >Excel导入课程</el-button
            >
          </div>
        </div>
      </template>

      <el-tabs v-model="activeView">
        <el-tab-pane label="周视图" name="week">
          <!-- 周次切换器 -->
          <div class="week-navigator" v-if="totalWeeks > 0">
            <el-button @click="changeWeek(-1)" :disabled="currentWeek <= 1"
              >上一周</el-button
            >
            <span class="week-display">第 {{ currentWeek }} 周</span>
            <el-button
              @click="changeWeek(1)"
              :disabled="currentWeek >= totalWeeks"
              >下一周</el-button
            >
          </div>

          <!-- 加载与空状态 -->
          <div v-if="loading"><el-skeleton :rows="5" animated /></div>
          <div v-else-if="!termStore.currentTermId">
            <el-empty
              description="请先在页面顶部或学期管理中选择或创建一个学期"
            />
          </div>
          <!-- 周视图网格 -->
          <WeeklyGridView
            v-else-if="courses.length > 0"
            :courses="coursesForCurrentWeek"
          />
          <div v-else>
            <el-empty description="当前学期暂无课程安排，快去添加吧！" />
          </div>
        </el-tab-pane>

        <el-tab-pane label="日视图" name="day">
          <!-- 周次切换器 -->
          <div class="week-navigator" v-if="totalWeeks > 0">
            <el-button @click="changeWeek(-1)" :disabled="currentWeek <= 1"
              >上一周</el-button
            >
            <span class="week-display">第 {{ currentWeek }} 周</span>
            <el-button
              @click="changeWeek(1)"
              :disabled="currentWeek >= totalWeeks"
              >下一周</el-button
            >
          </div>
          <!-- 日期切换器 -->
          <div class="day-navigator" v-if="totalWeeks > 0">
            <el-button @click="changeDay(-1)" :disabled="isFirstDayOfWeek"
              >前一天</el-button
            >
            <span class="day-display">{{ currentDayName }}</span>
            <el-button @click="changeDay(1)" :disabled="isLastDayOfWeek"
              >后一天</el-button
            >
          </div>

          <!-- 加载与空状态 -->
          <div v-if="loading"><el-skeleton :rows="5" animated /></div>
          <div v-else-if="!termStore.currentTermId">
            <el-empty
              description="请先在页面顶部或学期管理中选择或创建一个学期"
            />
          </div>
          <!-- 日视图网格 -->
          <DailyGridView
            v-else-if="coursesForCurrentDay.length > 0"
            :courses="coursesForCurrentDay"
          />
          <div v-else>
            <el-empty description="今天没有课程安排，好好休息吧！" />
          </div>
        </el-tab-pane>

        <el-tab-pane label="学期视图" name="term">
          <el-table :data="courses" stripe v-loading="loading">
            <el-table-column type="expand">
              <template #default="props">
                <div style="padding: 10px 20px">
                  <h4>上课安排详情</h4>
                  <ul style="list-style-type: none; padding-left: 0">
                    <li
                      v-for="entry in props.row.scheduleEntries"
                      :key="entry.id"
                    >
                      <el-icon><Location /></el-icon> 地点:
                      {{ entry.location }} |
                      <el-icon><Calendar /></el-icon> 周次:
                      {{ formatWeeks(entry.weeks) }} |
                      <el-icon><Timer /></el-icon> 星期{{
                        "一二三四五六日"[entry.dayOfWeek - 1]
                      }}
                      | 第 {{ entry.startPeriod }}-{{ entry.endPeriod }} 节
                    </li>
                  </ul>
                </div>
              </template>
            </el-table-column>
            <el-table-column prop="name" label="课程名称" />
            <el-table-column prop="teachers" label="任课教师" />
            <el-table-column prop="tag" label="标签" width="100" align="center">
              <template #default="scope">
                <el-tag
                  v-if="scope.row.tag !== null"
                  :type="scope.row.tag === 1 ? 'warning' : 'info'"
                  disable-transitions
                >
                  {{ scope.row.tag === 1 ? "必修" : "选修" }}
                </el-tag>
              </template>
            </el-table-column>
            <el-table-column prop="note" label="备注" show-overflow-tooltip />
            <el-table-column label="操作" width="200" fixed="right">
              <template #default="scope">
                <el-button
                  type="primary"
                  text
                  :icon="Edit"
                  @click="handleEditCourse(scope.row)"
                  >编辑</el-button
                >
                <el-button
                  type="danger"
                  text
                  :icon="Delete"
                  @click="handleDeleteCourse(scope.row)"
                  >删除</el-button
                >
              </template>
            </el-table-column>
          </el-table>
        </el-tab-pane>
      </el-tabs>
    </el-card>

    <CourseFormDialog
      v-if="dialogVisible"
      v-model="dialogVisible"
      :mode="dialogMode"
      :course-data="currentCourseData"
      :term-id="termStore.currentTermId"
      @submitSuccess="handleSubmitSuccess"
    />
  </div>
</template>

<script setup>
import { ref, watch, computed } from "vue";
import { useTermStore } from "@/stores/term";
import {
  getCoursesByTermApi,
  createCourseApi,
  updateCourseApi,
  deleteCourseApi,
} from "@/api/course";
import CourseFormDialog from "@/components/CourseFormDialog.vue";
import WeeklyGridView from "@/components/WeeklyGridView.vue";
import DailyGridView from "@/components/DailyGridView.vue";
import { ElMessage, ElMessageBox } from "element-plus";
import {
  Plus,
  Upload,
  Edit,
  Delete,
  Location,
  Calendar,
  Timer,
} from "@element-plus/icons-vue";
import { cloneDeep } from "lodash-es";

const termStore = useTermStore();
const activeView = ref("week");
const courses = ref([]);
const loading = ref(false);

// 对话框状态
const dialogVisible = ref(false);
const dialogMode = ref("add");
const currentCourseData = ref(null);

// 周视图状态
const currentWeek = ref(1);
const currentDay = ref(1); // 1 for Monday, 7 for Sunday

// 计算属性
const currentTermId = computed(() => termStore.currentTermId);
const currentTermName = computed(
  () => termStore.currentTerm?.name || "请选择学期"
);

const totalWeeks = computed(() => {
  const term = termStore.currentTerm;
  if (!term || !term.startDate || !term.endDate) return 0;
  const start = new Date(term.startDate);
  const end = new Date(term.endDate);
  const diffTime = Math.abs(end - start) + 1000 * 60 * 60 * 24;
  const diffDays = Math.ceil(diffTime / (1000 * 60 * 60 * 24));
  return Math.ceil(diffDays / 7);
});

const coursesForCurrentWeek = computed(() => {
  if (!courses.value) return [];
  const result = [];
  courses.value.forEach((course) => {
    const matchingSchedules = course.scheduleEntries.filter((schedule) =>
      schedule.weeks.includes(currentWeek.value)
    );
    if (matchingSchedules.length > 0) {
      result.push({
        ...course,
        scheduleEntries: matchingSchedules,
      });
    }
  });
  return result;
});

const coursesForCurrentDay = computed(() => {
  // 先过滤出本周的课程
  const weekCourses = coursesForCurrentWeek.value;
  // 再从本周课程中过滤出当天的课程
  return weekCourses
    .filter((course) =>
      course.scheduleEntries.some(
        (schedule) => schedule.dayOfWeek === currentDay.value
      )
    )
    .map((course) => {
      // 只保留当天的排程，避免在日视图中显示其他天的信息
      return {
        ...course,
        scheduleEntries: course.scheduleEntries.filter(
          (schedule) => schedule.dayOfWeek === currentDay.value
        ),
      };
    });
});

const weekDayNames = ["星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"];
const currentDayName = computed(() => weekDayNames[currentDay.value - 1]);

const isFirstDayOfWeek = computed(() => currentDay.value <= 1);
const isLastDayOfWeek = computed(() => currentDay.value >= 7);

// 方法
const fetchCourses = async (termId) => {
  if (!termId) {
    courses.value = [];
    return;
  }
  loading.value = true;
  try {
    const res = await getCoursesByTermApi(termId);
    courses.value = res.data?.content || res.data || [];
  } catch (error) {
    console.error("获取课程失败", error);
    courses.value = [];
  } finally {
    loading.value = false;
  }
};

const changeWeek = (delta) => {
  const newWeek = currentWeek.value + delta;
  if (newWeek > 0 && newWeek <= totalWeeks.value) {
    currentWeek.value = newWeek;
  }
};

const changeDay = (delta) => {
  const newDay = currentDay.value + delta;
  if (newDay >= 1 && newDay <= 7) {
    currentDay.value = newDay;
  }
};

const formatWeeks = (weeks) => {
  if (!weeks || weeks.length === 0) return "";
  weeks.sort((a, b) => a - b);
  const ranges = [];
  let start = weeks[0];
  let end = weeks[0];
  for (let i = 1; i < weeks.length; i++) {
    if (weeks[i] === end + 1) {
      end = weeks[i];
    } else {
      ranges.push(start === end ? `${start}` : `${start}-${end}`);
      start = end = weeks[i];
    }
  }
  ranges.push(start === end ? `${start}` : `${start}-${end}`);
  return ranges.join(", ");
};

// 监听器
watch(
  currentTermId,
  (newId) => {
    if (newId) {
      fetchCourses(newId);
      // 尝试将周和日设置为今天
      const today = new Date();
      const termStart = termStore.currentTerm?.startDate ? new Date(termStore.currentTerm.startDate) : null;
      if(termStart){
        const diffTime = today - termStart;
        const diffDays = Math.floor(diffTime / (1000 * 60 * 60 * 24));
        if(diffDays >= 0){
          currentWeek.value = Math.floor(diffDays / 7) + 1;
        } else {
          currentWeek.value = 1;
        }
      } else {
         currentWeek.value = 1;
      }
      currentDay.value = today.getDay() === 0 ? 7 : today.getDay();
    } else {
      courses.value = [];
    }
  },
  { immediate: true }
);

// CRUD 操作
const handleAddCourse = () => {
  if (!termStore.currentTermId) {
    ElMessage.warning("请先选择一个学期！");
    return;
  }
  dialogMode.value = "add";
  currentCourseData.value = null;
  dialogVisible.value = true;
};

const handleEditCourse = (row) => {
  dialogMode.value = "edit";
  currentCourseData.value = cloneDeep(row);
  dialogVisible.value = true;
};

const handleDeleteCourse = (row) => {
  ElMessageBox.confirm(`确定要删除课程 "${row.name}" 吗？`, "删除确认", {
    confirmButtonText: "确定",
    cancelButtonText: "取消",
    type: "warning",
  })
    .then(async () => {
      try {
        await deleteCourseApi(row.id);
        ElMessage.success("删除成功");
        fetchCourses(currentTermId.value);
      } catch (error) {
        console.error("删除课程失败", error);
      }
    })
    .catch(() => {
      ElMessage.info("已取消删除");
    });
};

const handleSubmitSuccess = async (submissionData) => {
  try {
    if (dialogMode.value === "add") {
      await createCourseApi(submissionData);
      ElMessage.success("课程添加成功");
    } else {
      await updateCourseApi(submissionData.id, submissionData);
      ElMessage.success("课程更新成功");
    }
    fetchCourses(currentTermId.value);
  } catch (error) {
    console.error("课程操作失败", error);
  }
};
</script>

<style scoped>
.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}
.week-navigator {
  display: flex;
  justify-content: center;
  align-items: center;
  margin-bottom: 20px;
}
.week-display {
  margin: 0 20px;
  font-size: 16px;
  font-weight: bold;
  user-select: none;
}
.day-navigator {
  display: flex;
  justify-content: center;
  align-items: center;
  margin-bottom: 20px;
}
.day-display {
  margin: 0 20px;
  font-size: 16px;
  font-weight: bold;
  user-select: none;
}
</style>