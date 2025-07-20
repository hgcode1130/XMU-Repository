<template>
  <div class="timetable-page">
    <!-- 页面标题和操作栏 -->
    <div class="page-header">
      <div class="header-content">
        <div class="title-section">
          <h2 class="page-title">
            <el-icon size="20"><Calendar /></el-icon>
            课表管理
          </h2>
          <p class="page-subtitle" v-if="termStore.currentTerm">
            {{ termStore.currentTerm.name }}
            <span
              v-if="
                termStore.currentTerm.startDate && termStore.currentTerm.endDate
              "
            >
              ({{
                formatDateRange(
                  termStore.currentTerm.startDate,
                  termStore.currentTerm.endDate
                )
              }})
            </span>
          </p>
          <!-- 添加学期加载状态提示 -->
          <p class="page-subtitle" v-else-if="!isInitialized">
            正在加载学期信息...
          </p>
          <p class="page-subtitle" v-else>请选择学期</p>
        </div>

        <div class="action-buttons">
          <el-button
            type="primary"
            :icon="Plus"
            @click="handleAddCourse"
            size="default"
            :disabled="!termStore.currentTermId || !isInitialized"
          >
            添加课程
          </el-button>
          <!-- <el-button type="success" :icon="Upload" disabled size="default">
            Excel导入
          </el-button> -->
          <el-button
            type="success"
            :icon="Upload"
            @click="handleExcelImport"
            size="default"
            :disabled="!termStore.currentTermId || !isInitialized"
          >
            Excel导入
          </el-button>
        </div>
      </div>
    </div>

    <!-- 主要内容区 -->
    <el-card class="main-content-card" shadow="never">
      <!-- 初始化加载状态 -->
      <div v-if="!isInitialized" class="initialization-loading">
        <el-skeleton :rows="3" animated />
        <div style="text-align: center; margin-top: 20px">
          <el-text type="info">正在初始化课表数据...</el-text>
        </div>
      </div>

      <!-- 正常内容 -->
      <div v-else>
        <!-- 视图切换和控制器 -->
        <div class="view-controls">
          <el-tabs v-model="activeView" class="view-tabs">
            <el-tab-pane label="周视图" name="week">
              <template #label>
                <span class="tab-label">
                  <el-icon><Grid /></el-icon>
                  周视图
                </span>
              </template>
            </el-tab-pane>
            <el-tab-pane label="日视图" name="day">
              <template #label>
                <span class="tab-label">
                  <el-icon><Calendar /></el-icon>
                  日视图
                </span>
              </template>
            </el-tab-pane>
            <el-tab-pane label="学期视图" name="term">
              <template #label>
                <span class="tab-label">
                  <el-icon><List /></el-icon>
                  学期视图
                </span>
              </template>
            </el-tab-pane>
          </el-tabs>

          <!-- 统计信息 -->
          <div class="stats-info" v-if="!loading && courses.length > 0">
            <el-tag type="info" size="small">
              共 {{ totalCourses }} 门课程
            </el-tag>
            <el-tag type="warning" size="small" v-if="requiredCoursesCount > 0">
              必修 {{ requiredCoursesCount }}
            </el-tag>
            <el-tag type="success" size="small" v-if="electiveCoursesCount > 0">
              选修 {{ electiveCoursesCount }}
            </el-tag>
          </div>
        </div>

        <!-- 高级搜索筛选区域 (仅学期视图显示) -->
        <el-card
          v-if="activeView === 'term'"
          class="search-card"
          shadow="hover"
        >
          <template #header>
            <div class="search-header">
              <div class="search-title">
                <el-icon class="search-icon"><Search /></el-icon>
                <span>高级搜索</span>
              </div>
              <div class="search-actions">
                <el-button
                  @click="handleResetSearch"
                  :icon="RefreshLeft"
                  size="default"
                >
                  重置
                </el-button>
                <el-button
                  @click="handleSearch"
                  type="primary"
                  :icon="Search"
                  size="default"
                  :loading="searchLoading"
                >
                  搜索
                </el-button>
              </div>
            </div>
          </template>

          <el-form :model="searchQuery" class="search-form" :label-width="80">
            <el-row :gutter="24">
              <el-col :xl="6" :lg="8" :md="12" :sm="24">
                <el-form-item label="课程名称">
                  <el-input
                    v-model="searchQuery.name"
                    placeholder="模糊搜索课程名称"
                    :prefix-icon="Document"
                    clearable
                    @keyup.enter="handleSearch"
                  />
                </el-form-item>
              </el-col>
              <el-col :xl="6" :lg="8" :md="12" :sm="24">
                <el-form-item label="任课教师">
                  <el-input
                    v-model="searchQuery.teacher"
                    placeholder="模糊搜索教师姓名"
                    :prefix-icon="User"
                    clearable
                    @keyup.enter="handleSearch"
                  />
                </el-form-item>
              </el-col>
              <el-col :xl="6" :lg="8" :md="12" :sm="24">
                <el-form-item label="课程类型">
                  <el-select
                    v-model="searchQuery.tag"
                    placeholder="选择课程类型"
                    clearable
                    style="width: 100%"
                  >
                    <el-option
                      v-for="item in courseTagOptions"
                      :key="item.value"
                      :label="item.label"
                      :value="item.value"
                    >
                      <div class="tag-option">
                        <el-tag
                          :type="item.value === 1 ? 'warning' : 'info'"
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
                <el-form-item label="星期">
                  <el-select
                    v-model="searchQuery.dayOfWeek"
                    placeholder="选择星期几"
                    clearable
                    style="width: 100%"
                  >
                    <el-option
                      v-for="item in dayOptions"
                      :key="item.value"
                      :label="item.label"
                      :value="item.value"
                    />
                  </el-select>
                </el-form-item>
              </el-col>
            </el-row>
          </el-form>
        </el-card>

        <!-- 内容区域 -->
        <div class="content-area">
          <!-- 周视图 -->
          <div v-if="activeView === 'week'" class="view-container">
            <!-- 周次切换器 -->
            <div
              class="week-navigator"
              v-if="totalWeeks > 0 && termStore.currentTerm"
            >
              <el-button
                @click="changeWeek(-1)"
                :disabled="currentWeek <= 1"
                :icon="ArrowLeft"
                circle
              />
              <div class="week-info">
                <span class="week-display">第 {{ currentWeek }} 周</span>
                <span class="week-date" v-if="getCurrentWeekDateRange()">
                  {{ getCurrentWeekDateRange() }}
                </span>
              </div>
              <el-button
                @click="changeWeek(1)"
                :disabled="currentWeek >= totalWeeks"
                :icon="ArrowRight"
                circle
              />
            </div>

            <!-- 加载与空状态 -->
            <div v-if="loading" class="loading-container">
              <el-skeleton :rows="5" animated />
            </div>
            <div v-else-if="!termStore.currentTermId" class="empty-container">
              <el-empty description="请先选择一个学期">
                <el-button type="primary" @click="$router.push('/terms')">
                  前往学期管理
                </el-button>
              </el-empty>
            </div>
            <!-- 周视图网格 -->
            <div v-else-if="courses.length > 0" class="grid-container">
              <WeeklyGridView :courses="coursesForCurrentWeek" />
            </div>
            <div v-else class="empty-container">
              <el-empty description="当前学期暂无课程安排">
                <el-button type="primary" @click="handleAddCourse">
                  添加第一门课程
                </el-button>
              </el-empty>
            </div>
          </div>

          <!-- 日视图 -->
          <div v-if="activeView === 'day'" class="view-container">
            <!-- 控制器 -->
            <div class="day-controls">
              <!-- 周次切换器 -->
              <div class="week-navigator" v-if="totalWeeks > 0">
                <el-button
                  @click="changeWeek(-1)"
                  :disabled="currentWeek <= 1"
                  size="small"
                >
                  上一周
                </el-button>
                <span class="week-display">第 {{ currentWeek }} 周</span>
                <el-button
                  @click="changeWeek(1)"
                  :disabled="currentWeek >= totalWeeks"
                  size="small"
                >
                  下一周
                </el-button>
              </div>

              <!-- 日期切换器 -->
              <div class="day-navigator" v-if="totalWeeks > 0">
                <el-button
                  @click="changeDay(-1)"
                  :disabled="isFirstDayOfWeek"
                  :icon="ArrowLeft"
                  circle
                  size="small"
                />
                <div class="day-info">
                  <span class="day-display">{{ currentDayName }}</span>
                  <span class="day-date" v-if="getCurrentDayDate()">
                    {{ getCurrentDayDate() }}
                  </span>
                </div>
                <el-button
                  @click="changeDay(1)"
                  :disabled="isLastDayOfWeek"
                  :icon="ArrowRight"
                  circle
                  size="small"
                />
              </div>
            </div>

            <!-- 内容 -->
            <div v-if="loading" class="loading-container">
              <el-skeleton :rows="5" animated />
            </div>
            <div v-else-if="!termStore.currentTermId" class="empty-container">
              <el-empty description="请先选择一个学期">
                <el-button type="primary" @click="$router.push('/terms')">
                  前往学期管理
                </el-button>
              </el-empty>
            </div>
            <!-- 日视图网格 -->
            <div
              v-else-if="coursesForCurrentDay.length > 0"
              class="grid-container"
            >
              <DailyGridView :courses="coursesForCurrentDay" />
            </div>
            <div v-else class="empty-container">
              <el-empty description="今天没有课程安排">
                <el-button type="primary" @click="handleAddCourse">
                  添加课程
                </el-button>
              </el-empty>
            </div>
          </div>

          <!-- 学期视图 -->
          <div v-if="activeView === 'term'" class="view-container">
            <div class="table-container">
              <el-table
                :data="paginatedCourses"
                stripe
                v-loading="loading"
                :empty-text="getEmptyText()"
                class="courses-table"
              >
                <el-table-column type="expand">
                  <template #default="props">
                    <div class="expand-content">
                      <h4>上课安排详情</h4>
                      <div
                        v-if="
                          props.row.scheduleEntries &&
                          props.row.scheduleEntries.length > 0
                        "
                        class="schedule-grid"
                      >
                        <div
                          v-for="entry in props.row.scheduleEntries"
                          :key="entry.id"
                          class="schedule-card"
                        >
                          <div class="schedule-header">
                            <el-tag size="small" type="primary">
                              安排
                              {{ props.row.scheduleEntries.indexOf(entry) + 1 }}
                            </el-tag>
                          </div>
                          <div class="schedule-info">
                            <div class="info-item">
                              <el-icon><Location /></el-icon>
                              {{ entry.location || "未设置地点" }}
                            </div>
                            <div class="info-item">
                              <el-icon><Calendar /></el-icon>
                              星期{{ "一二三四五六日"[entry.dayOfWeek - 1] }}
                            </div>
                            <div class="info-item">
                              <el-icon><Timer /></el-icon>
                              第 {{ entry.startPeriod }}-{{ entry.endPeriod }}
                              节
                            </div>
                            <div class="info-item">
                              <el-icon><Document /></el-icon>
                              {{ formatWeeks(entry.weeks) }}
                            </div>
                          </div>
                        </div>
                      </div>
                      <div v-else class="no-schedule">
                        <el-empty description="暂无上课安排" :image-size="60" />
                      </div>
                    </div>
                  </template>
                </el-table-column>
                <el-table-column prop="name" label="课程名称" min-width="120">
                  <template #default="scope">
                    <div class="course-name-cell">
                      <span class="course-name">{{ scope.row.name }}</span>
                      <el-tag
                        v-if="scope.row.tag !== null"
                        :type="scope.row.tag === 1 ? 'warning' : 'info'"
                        size="small"
                        disable-transitions
                      >
                        {{ scope.row.tag === 1 ? "必修" : "选修" }}
                      </el-tag>
                    </div>
                  </template>
                </el-table-column>
                <el-table-column
                  prop="teachers"
                  label="任课教师"
                  min-width="100"
                />
                <el-table-column
                  prop="teachers"
                  label="任课教师"
                  min-width="100"
                />
                <el-table-column
                  prop="mainTeacherEmail"
                  label="主讲教师邮箱"
                  min-width="120"
                  show-overflow-tooltip
                >
                  <template #default="scope">
                    <span v-if="scope.row.mainTeacherEmail">
                      {{ scope.row.mainTeacherEmail }}
                    </span>
                    <el-text v-else type="info" size="small">未设置</el-text>
                  </template>
                </el-table-column>
                <el-table-column
                  prop="courseGroupChatId"
                  label="课程群号"
                  min-width="100"
                  show-overflow-tooltip
                >
                  <template #default="scope">
                    <span v-if="scope.row.courseGroupChatId">
                      {{ scope.row.courseGroupChatId }}
                    </span>
                    <el-text v-else type="info" size="small">未设置</el-text>
                  </template>
                </el-table-column>
                <!-- <el-table-column label="上课安排" min-width="150">
                  <template #default="scope">
                    <div class="schedule-summary">
                      <div
                        v-if="
                          scope.row.scheduleEntries &&
                          scope.row.scheduleEntries.length > 0
                        "
                      >
                        <div
                          v-for="entry in scope.row.scheduleEntries.slice(0, 2)"
                          :key="entry.id"
                          class="schedule-item-summary"
                        >
                          星期{{ "一二三四五六日"[entry.dayOfWeek - 1] }} 第{{
                            entry.startPeriod
                          }}-{{ entry.endPeriod }}节
                        </div>
                        <el-text
                          v-if="scope.row.scheduleEntries.length > 2"
                          type="info"
                          size="small"
                        >
                          等{{ scope.row.scheduleEntries.length }}个安排
                        </el-text>
                      </div>
                      <div v-else class="no-schedule-text">
                        <el-text type="info" size="small">暂无安排</el-text>
                      </div>
                    </div>
                  </template>
                </el-table-column> -->
                <el-table-column
                  prop="note"
                  label="备注"
                  show-overflow-tooltip
                  min-width="120"
                />
                <el-table-column label="操作" width="160" fixed="right">
                  <template #default="scope">
                    <div class="action-buttons-table">
                      <el-button
                        type="primary"
                        text
                        :icon="Edit"
                        @click="handleEditCourse(scope.row)"
                        size="small"
                      >
                        编辑
                      </el-button>
                      <el-button
                        type="danger"
                        text
                        :icon="Delete"
                        @click="handleDeleteCourse(scope.row)"
                        size="small"
                      >
                        删除
                      </el-button>
                    </div>
                  </template>
                </el-table-column>
              </el-table>

              <!-- 分页器 -->
              <div class="pagination-wrapper">
                <el-pagination
                  :current-page="currentPage"
                  :page-size="pageSize"
                  @size-change="handleSizeChange"
                  @current-change="handleCurrentChange"
                  layout="total, sizes, prev, pager, next, jumper"
                  :page-sizes="[5, 10, 15, 20, 50]"
                  :total="totalCourses"
                  background
                  class="pagination"
                />
              </div>
            </div>
          </div>
        </div>
      </div>
    </el-card>

    <!-- 课程表单对话框 -->
    <CourseFormDialog
      v-if="dialogVisible"
      v-model="dialogVisible"
      :mode="dialogMode"
      :course-data="currentCourseData"
      :term-id="termStore.currentTermId"
      @submitSuccess="handleSubmitSuccess"
    />

    <!-- Excel导入对话框 -->
    <ExcelImportDialog
      v-if="importDialogVisible"
      v-model="importDialogVisible"
      :term-id="termStore.currentTermId"
      @importSuccess="handleImportSuccess"
    />
  </div>
</template>

<script setup>
import { ref, watch, computed, onMounted, nextTick } from "vue";
import { useTermStore } from "@/stores/term";
import {
  getCoursesByTermApi,
  searchCoursesApi,
  createCourseApi,
  updateCourseApi,
  deleteCourseApi,
} from "@/api/course";
import CourseFormDialog from "@/components/CourseFormDialog.vue";
import WeeklyGridView from "@/components/WeeklyGridView.vue";
import DailyGridView from "@/components/DailyGridView.vue";
import ExcelImportDialog from "@/components/ExcelImportDialog.vue";
import { ElMessage, ElMessageBox } from "element-plus";
import {
  Plus,
  Upload,
  Edit,
  Delete,
  Location,
  Calendar,
  Timer,
  Grid,
  List,
  ArrowLeft,
  ArrowRight,
  Document,
  Search,
  RefreshLeft,
  User,
} from "@element-plus/icons-vue";
import { cloneDeep } from "lodash-es";

const termStore = useTermStore();
const activeView = ref("week");
const courses = ref([]);
const loading = ref(false);
const searchLoading = ref(false);
const isInitialized = ref(false);

// 分页相关状态
const currentPage = ref(1);
const pageSize = ref(10);
const totalCourses = ref(0);

// 搜索查询参数
const searchQuery = ref({
  name: null,
  teacher: null,
  tag: null,
  dayOfWeek: null,
});

// 搜索选项
const courseTagOptions = ref([
  { value: 1, label: "必修" },
  { value: 0, label: "选修" },
]);

const dayOptions = ref([
  { value: 1, label: "星期一" },
  { value: 2, label: "星期二" },
  { value: 3, label: "星期三" },
  { value: 4, label: "星期四" },
  { value: 5, label: "星期五" },
  { value: 6, label: "星期六" },
  { value: 7, label: "星期日" },
]);

// 对话框状态
const dialogVisible = ref(false);
const dialogMode = ref("add");
const currentCourseData = ref(null);
const importDialogVisible = ref(false);

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

// 学期视图的分页课程列表
const paginatedCourses = computed(() => {
  if (activeView.value !== "term") {
    return courses.value;
  }

  const start = (currentPage.value - 1) * pageSize.value;
  const end = start + pageSize.value;
  return courses.value.slice(start, end);
});

const coursesForCurrentWeek = computed(() => {
  if (!courses.value) return [];
  const result = [];
  courses.value.forEach((course) => {
    // 安全检查 scheduleEntries
    const scheduleEntries = course.scheduleEntries || [];
    const matchingSchedules = scheduleEntries.filter(
      (schedule) => schedule.weeks && schedule.weeks.includes(currentWeek.value)
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
    .filter(
      (course) =>
        course.scheduleEntries &&
        course.scheduleEntries.some(
          (schedule) => schedule.dayOfWeek === currentDay.value
        )
    )
    .map((course) => {
      // 只保留当天的排程，避免在日视图中显示其他天的信息
      return {
        ...course,
        scheduleEntries: (course.scheduleEntries || []).filter(
          (schedule) => schedule.dayOfWeek === currentDay.value
        ),
      };
    });
});

// 统计信息
const requiredCoursesCount = computed(
  () => courses.value.filter((course) => course.tag === 1).length
);

const electiveCoursesCount = computed(
  () => courses.value.filter((course) => course.tag === 0).length
);

const weekDayNames = [
  "星期一",
  "星期二",
  "星期三",
  "星期四",
  "星期五",
  "星期六",
  "星期日",
];
const currentDayName = computed(() => weekDayNames[currentDay.value - 1]);

const isFirstDayOfWeek = computed(() => currentDay.value <= 1);
const isLastDayOfWeek = computed(() => currentDay.value >= 7);

// 判断是否在使用搜索
const isSearching = computed(() => {
  return (
    searchQuery.value.name ||
    searchQuery.value.teacher ||
    searchQuery.value.tag !== null ||
    searchQuery.value.dayOfWeek !== null
  );
});

// 数据标准化函数
const normalizeCourseData = (course) => {
  return {
    ...course,
    scheduleEntries: course.scheduleEntries || [], // 确保 scheduleEntries 始终是数组
  };
};

// 日期格式化函数
const formatDateRange = (startDate, endDate) => {
  const start = new Date(startDate);
  const end = new Date(endDate);
  return `${start.getFullYear()}/${
    start.getMonth() + 1
  }/${start.getDate()} - ${end.getFullYear()}/${
    end.getMonth() + 1
  }/${end.getDate()}`;
};

const getCurrentWeekDateRange = () => {
  const term = termStore.currentTerm;
  if (!term?.startDate || !isInitialized.value) return "";

  const termStart = new Date(term.startDate);
  const weekStart = new Date(termStart);
  weekStart.setDate(termStart.getDate() + (currentWeek.value - 1) * 7);

  const weekEnd = new Date(weekStart);
  weekEnd.setDate(weekStart.getDate() + 6);

  return `${weekStart.getMonth() + 1}/${weekStart.getDate()} - ${
    weekEnd.getMonth() + 1
  }/${weekEnd.getDate()}`;
};

const getCurrentDayDate = () => {
  const term = termStore.currentTerm;
  if (!term?.startDate || !isInitialized.value) return "";

  const termStart = new Date(term.startDate);
  const currentDate = new Date(termStart);
  currentDate.setDate(
    termStart.getDate() + (currentWeek.value - 1) * 7 + (currentDay.value - 1)
  );

  return `${currentDate.getMonth() + 1}/${currentDate.getDate()}`;
};

// 获取空状态文本
const getEmptyText = () => {
  if (!termStore.currentTermId) {
    return "请先选择学期";
  }
  if (isSearching.value) {
    return "没有找到符合条件的课程";
  }
  return "暂无课程数据";
};

// 计算当前周和日的函数
const calculateCurrentWeekAndDay = () => {
  const term = termStore.currentTerm;
  if (!term?.startDate) {
    currentWeek.value = 1;
    currentDay.value = 1;
    return;
  }

  const today = new Date();
  const termStart = new Date(term.startDate);
  const termEnd = new Date(term.endDate);

  // 如果今天在学期开始之前，设置为第1周周一
  if (today < termStart) {
    currentWeek.value = 1;
    currentDay.value = 1;
    return;
  }

  // 如果今天在学期结束之后，设置为最后一周的最后一天
  if (today > termEnd) {
    currentWeek.value = totalWeeks.value || 1;
    currentDay.value = 7;
    return;
  }

  // 计算当前是第几周
  const diffTime = today - termStart;
  const diffDays = Math.floor(diffTime / (1000 * 60 * 60 * 24));
  const calculatedWeek = Math.floor(diffDays / 7) + 1;

  // 确保周数在有效范围内
  const maxWeeks = totalWeeks.value || 1;
  currentWeek.value = Math.min(Math.max(calculatedWeek, 1), maxWeeks);

  // 计算今天是星期几 (1-7, 1为周一)
  const todayOfWeek = today.getDay();
  currentDay.value = todayOfWeek === 0 ? 7 : todayOfWeek;

  console.log("计算当前位置:", {
    today: today.toLocaleDateString(),
    termStart: termStart.toLocaleDateString(),
    termEnd: termEnd.toLocaleDateString(),
    diffDays,
    calculatedWeek,
    currentWeek: currentWeek.value,
    currentDay: currentDay.value,
    totalWeeks: maxWeeks,
  });
};

// 初始化学期和日期
const initializeTermAndDate = async () => {
  try {
    // 确保学期数据已加载
    if (!termStore.currentTermId && termStore.termList.length === 0) {
      await termStore.fetchAllTerms();
    }

    // 如果没有选中的学期，自动选择最新的学期
    if (!termStore.currentTermId && termStore.termList.length > 0) {
      const sortedTerms = [...termStore.termList].sort(
        (a, b) =>
          new Date(b.createdAt || b.startDate) -
          new Date(a.createdAt || a.startDate)
      );
      await termStore.setTerm(sortedTerms[0].id);
    }

    // 等待学期数据完全设置后再计算日期
    await nextTick();

    if (termStore.currentTerm) {
      calculateCurrentWeekAndDay();
    }

    isInitialized.value = true;
  } catch (error) {
    console.error("初始化学期和日期失败:", error);
    // 设置默认值
    currentWeek.value = 1;
    currentDay.value = 1;
    isInitialized.value = true;
  }
};

// 方法
const fetchCourses = async (termId) => {
  if (!termId) {
    courses.value = [];
    totalCourses.value = 0;
    return;
  }
  loading.value = true;
  try {
    const res = await getCoursesByTermApi(termId);
    const rawCourses = res.data?.content || res.data || [];
    // 标准化课程数据
    courses.value = rawCourses.map(normalizeCourseData);
    totalCourses.value = courses.value.length;

    console.log("获取课程数据:", {
      termId,
      coursesCount: courses.value.length,
      courses: courses.value,
    });
  } catch (error) {
    console.error("获取课程失败", error);
    courses.value = [];
    totalCourses.value = 0;
  } finally {
    loading.value = false;
  }
};

// 搜索课程
const searchCourses = async (params) => {
  if (!termStore.currentTermId) {
    courses.value = [];
    totalCourses.value = 0;
    return;
  }

  loading.value = true;
  try {
    const searchParams = {
      termId: termStore.currentTermId,
      page: 0, // 重置为第一页
      size: 999, // 先获取所有数据，前端分页
      ...params,
    };

    // 清理空参数
    Object.keys(searchParams).forEach((key) => {
      if (
        searchParams[key] === null ||
        searchParams[key] === undefined ||
        searchParams[key] === ""
      ) {
        delete searchParams[key];
      }
    });

    console.log("搜索参数:", searchParams);

    const res = await searchCoursesApi(searchParams);
    const rawCourses = res.data?.content || res.data || [];
    const newTotal = res.data?.totalElements || rawCourses.length;

    // 标准化搜索结果数据
    const normalizedCourses = rawCourses.map(normalizeCourseData);

    // 强制更新数据
    courses.value = [...normalizedCourses];
    totalCourses.value = newTotal;

    // 重置到第一页
    currentPage.value = 1;

    console.log("搜索结果:", {
      searchParams,
      coursesCount: courses.value.length,
      totalCourses: totalCourses.value,
      courses: courses.value,
    });
  } catch (error) {
    console.error("搜索课程失败", error);
    courses.value = [];
    totalCourses.value = 0;
  } finally {
    loading.value = false;
  }
};

// 搜索处理函数
const handleSearch = () => {
  searchLoading.value = true;

  const params = {
    name: searchQuery.value.name || null,
    teacher: searchQuery.value.teacher || null,
    tag: searchQuery.value.tag,
    dayOfWeek: searchQuery.value.dayOfWeek,
  };

  console.log("执行搜索:", params);

  setTimeout(() => {
    searchCourses(params);
    searchLoading.value = false;
  }, 300);
};

// 重置搜索
const handleResetSearch = () => {
  console.log("重置搜索");

  searchQuery.value = {
    name: null,
    teacher: null,
    tag: null,
    dayOfWeek: null,
  };
  currentPage.value = 1;

  // 如果当前有学期，重新获取所有课程
  if (termStore.currentTermId) {
    fetchCourses(termStore.currentTermId);
  }

  ElMessage.success("搜索条件已重置");
};

// 处理Excel导入
const handleExcelImport = () => {
  if (!termStore.currentTermId) {
    ElMessage.warning("请先选择一个学期！");
    return;
  }
  importDialogVisible.value = true;
};

// 导入成功后的处理
const handleImportSuccess = (result) => {
  console.log("导入成功:", result);

  // 刷新课程列表
  if (isSearching.value) {
    handleSearch();
  } else {
    fetchCourses(termStore.currentTermId);
  }

  // 关闭导入对话框
  importDialogVisible.value = false;
};

// 分页处理函数
const handleSizeChange = (val) => {
  pageSize.value = val;
  currentPage.value = 1;
};

const handleCurrentChange = (val) => {
  currentPage.value = val;
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
  return `第 ${ranges.join(", ")} 周`;
};

// 监听器
watch(
  currentTermId,
  async (newId, oldId) => {
    console.log("学期变化:", { newId, oldId });

    if (newId && newId !== oldId) {
      // 重置搜索状态和分页
      searchQuery.value = {
        name: null,
        teacher: null,
        tag: null,
        dayOfWeek: null,
      };
      currentPage.value = 1;

      await fetchCourses(newId);
      // 只有在学期切换时才重新计算日期，避免初始化时的重复计算
      if (isInitialized.value && termStore.currentTerm) {
        calculateCurrentWeekAndDay();
      }
    } else if (!newId) {
      courses.value = [];
      totalCourses.value = 0;
    }
  },
  { immediate: false }
);

// 监听视图切换，重置分页
watch(activeView, () => {
  currentPage.value = 1;
});

// 组件挂载时初始化
onMounted(async () => {
  await initializeTermAndDate();

  // 初始化完成后获取课程数据
  if (termStore.currentTermId) {
    await fetchCourses(termStore.currentTermId);
  }
});

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

        // 根据当前状态重新获取数据
        if (isSearching.value) {
          handleSearch();
        } else {
          fetchCourses(currentTermId.value);
        }
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

    // 根据当前状态重新获取数据
    if (isSearching.value) {
      handleSearch();
    } else {
      fetchCourses(currentTermId.value);
    }
  } catch (error) {
    console.error("课程操作失败", error);
  }
};
</script>

<style scoped>
/* 新增：初始化加载样式 */
.initialization-loading {
  padding: 40px;
  text-align: center;
}

.page-subtitle {
  transition: opacity 0.3s ease;
}

/* 禁用状态的按钮样式优化 */
.action-buttons .el-button:disabled {
  opacity: 0.6;
}

.timetable-page {
  min-height: 100%;
  background-color: #f5f7fa;
}

.page-header {
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  border-radius: 12px;
  margin-bottom: 24px;
  overflow: hidden;
}

.header-content {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 24px 32px;
  color: white;
}

.title-section {
  flex: 1;
}

.page-title {
  margin: 0;
  font-size: 24px;
  font-weight: 600;
  display: flex;
  align-items: center;
  gap: 12px;
}

.page-subtitle {
  margin: 8px 0 0 0;
  font-size: 14px;
  opacity: 0.9;
  font-weight: normal;
}

.action-buttons {
  display: flex;
  gap: 12px;
}

.main-content-card {
  border-radius: 12px;
  box-shadow: 0 4px 24px rgba(0, 0, 0, 0.06);
  border: none;
}

.view-controls {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 24px;
  padding-bottom: 16px;
  border-bottom: 1px solid #f0f2f5;
}

.view-tabs {
  flex: 1;
}

.tab-label {
  display: flex;
  align-items: center;
  gap: 6px;
}

.stats-info {
  display: flex;
  gap: 8px;
  align-items: center;
}

/* 高级搜索卡片样式 */
.search-card {
  margin-bottom: 24px;
  border-radius: 12px;
  border: none;
  box-shadow: 0 2px 12px rgba(0, 0, 0, 0.04);
}

.search-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.search-title {
  display: flex;
  align-items: center;
  gap: 8px;
  font-weight: 600;
  color: #303133;
}

.search-icon {
  font-size: 18px;
  color: #409eff;
}

.search-actions {
  display: flex;
  gap: 12px;
}

.search-form {
  margin-top: 16px;
}

.tag-option {
  display: flex;
  align-items: center;
  gap: 8px;
}

.content-area {
  min-height: 600px;
}

.view-container {
  width: 100%;
}

.week-navigator {
  display: flex;
  justify-content: center;
  align-items: center;
  margin-bottom: 24px;
  gap: 16px;
}

.week-info,
.day-info {
  text-align: center;
  min-width: 120px;
}

.week-display,
.day-display {
  display: block;
  font-size: 16px;
  font-weight: 600;
  color: #303133;
}

.week-date,
.day-date {
  display: block;
  font-size: 12px;
  color: #909399;
  margin-top: 2px;
}

.day-controls {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 24px;
  padding: 16px;
  background-color: #f8f9fa;
  border-radius: 8px;
}

.day-navigator {
  display: flex;
  align-items: center;
  gap: 12px;
}

.loading-container,
.empty-container {
  padding: 40px;
  text-align: center;
}

.grid-container {
  background-color: #fff;
  border-radius: 8px;
  overflow: hidden;
}

.table-container {
  background-color: #fff;
  border-radius: 8px;
  overflow: hidden;
}

.courses-table {
  border-radius: 8px;
}

.expand-content {
  padding: 16px;
  background-color: #f8f9fa;
}

.expand-content h4 {
  margin: 0 0 16px 0;
  color: #303133;
  font-size: 16px;
}

.schedule-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(250px, 1fr));
  gap: 16px;
}

.schedule-card {
  background-color: #fff;
  border-radius: 8px;
  padding: 16px;
  border: 1px solid #e4e7ed;
}

.schedule-header {
  margin-bottom: 12px;
}

.schedule-info {
  display: flex;
  flex-direction: column;
  gap: 8px;
}

.info-item {
  display: flex;
  align-items: center;
  gap: 8px;
  font-size: 14px;
  color: #606266;
}

.course-name-cell {
  display: flex;
  flex-direction: column;
  gap: 6px;
}

.course-name {
  font-weight: 500;
  color: #303133;
}

.schedule-summary {
  display: flex;
  flex-direction: column;
  gap: 4px;
}

.schedule-item-summary {
  font-size: 13px;
  color: #606266;
}

.action-buttons-table {
  display: flex;
  gap: 8px;
}

/* 新增样式 */
.no-schedule {
  text-align: center;
  padding: 20px;
}

.no-schedule-text {
  text-align: center;
  padding: 8px 0;
}

/* 分页器样式 */
.pagination-wrapper {
  margin-top: 24px;
  padding-top: 24px;
  border-top: 1px solid #f0f0f0;
  display: flex;
  justify-content: center;
}

.pagination {
  background: none;
}

/* 响应式设计 */
@media (max-width: 768px) {
  .header-content {
    flex-direction: column;
    gap: 16px;
    text-align: center;
  }

  .view-controls {
    flex-direction: column;
    gap: 16px;
    align-items: stretch;
  }

  .stats-info {
    justify-content: center;
  }

  .search-header {
    flex-direction: column;
    gap: 16px;
    align-items: stretch;
  }

  .search-actions {
    justify-content: center;
  }

  .day-controls {
    flex-direction: column;
    gap: 16px;
  }

  .schedule-grid {
    grid-template-columns: 1fr;
  }

  .action-buttons {
    width: 100%;
    justify-content: center;
  }
}
</style>
