<template>
  <div class="timetable-container">
    <div class="timetable-grid-daily" ref="gridRef">
      <!-- 左侧节次标题（加入时间显示） -->
      <div
        class="grid-header period-header"
        v-for="period in 12"
        :key="period"
        :style="{ gridRow: period }"
      >
        <div class="period-number">{{ period }}</div>
        <div class="period-time">{{ getPeriodTime(period) }}</div>
      </div>

      <!-- 网格背景（用于显示分界线） -->
      <div 
        v-for="periodIndex in 12" 
        :key="`bg-${periodIndex}`"
        class="grid-cell"
        :style="{ 
          gridColumn: 2, 
          gridRow: periodIndex 
        }"
      ></div>

      <!-- 课程块 -->
      <div
        v-for="(item, index) in processedCourses"
        :key="index"
        class="course-item"
        :style="item.style"
        :data-period-start="item.startPeriod"
        :data-period-end="item.endPeriod"
        :class="{ 'overlapping': item.isOverlapping }"
        @click="showCourseDetail(item)"
      >
        <div class="course-content">
          <strong class="course-name">{{ item.name }}</strong>
          <div class="course-location">@ {{ item.location }}</div>
          <div class="course-teacher">{{ item.teachers }}</div>
          <div class="course-weeks">({{ formatWeeks(item.weeks) }})</div>
          <el-tag
            v-if="item.tag !== null"
            :type="item.tag === 1 ? 'warning' : 'info'"
            size="small"
            style="margin-top: 5px"
            disable-transitions
          >
            {{ item.tag === 1 ? "必修" : "选修" }}
          </el-tag>
        </div>
      </div>
    </div>

    <!-- 课程详情面板 -->
    <div 
      v-if="selectedCourse" 
      class="course-detail-panel"
      :class="{ 'show': selectedCourse }"
    >
      <div class="panel-header">
        <h3>课程详情</h3>
        <el-button 
          type="text" 
          @click="closeCourseDetail"
          class="close-btn"
        >
          <el-icon><Close /></el-icon>
        </el-button>
      </div>
      
      <div class="panel-content">
        <div class="detail-item">
          <label>课程名称：</label>
          <span>{{ selectedCourse.name }}</span>
        </div>
        
        <div class="detail-item">
          <label>任课教师：</label>
          <span>{{ selectedCourse.teachers || '未设置' }}</span>
        </div>
        
        <div class="detail-item">
          <label>主讲教师邮箱：</label>
          <span>{{ selectedCourse.mainTeacherEmail || '未设置' }}</span>
        </div>
        
        <div class="detail-item">
          <label>课程群号：</label>
          <span>{{ selectedCourse.courseGroupChatId || '未设置' }}</span>
        </div>
        
        <div class="detail-item">
          <label>课程类型：</label>
          <el-tag 
            :type="selectedCourse.tag === 1 ? 'warning' : 'info'"
            size="small"
          >
            {{ selectedCourse.tag === 1 ? '必修' : selectedCourse.tag === 0 ? '选修' : '未设置' }}
          </el-tag>
        </div>
        
        <div class="detail-item">
          <label>上课地点：</label>
          <span>{{ selectedCourse.location || '未设置' }}</span>
        </div>
        
        <div class="detail-item">
          <label>上课时间：</label>
          <span>
            第{{ selectedCourse.startPeriod }}-{{ selectedCourse.endPeriod }}节
            ({{ getPeriodTime(selectedCourse.startPeriod) }}-{{ getPeriodTime(selectedCourse.endPeriod, true) }})
          </span>
        </div>
        
        <div class="detail-item">
          <label>上课周次：</label>
          <span>{{ formatWeeks(selectedCourse.weeks) }}</span>
        </div>
        
        <div class="detail-item" v-if="selectedCourse.note">
          <label>课程备注：</label>
          <div class="note-content">{{ selectedCourse.note }}</div>
        </div>
        
        <!-- 如果有多个上课安排，显示所有安排 -->
        <div v-if="selectedCourseAllSchedules && selectedCourseAllSchedules.length > 1" class="detail-item">
          <label>所有上课安排：</label>
          <div class="schedule-list">
            <div 
              v-for="(schedule, index) in selectedCourseAllSchedules" 
              :key="index"
              class="schedule-item"
            >
              <div>
                <strong>安排{{ index + 1 }}：</strong>
                星期{{ '一二三四五六日'[schedule.dayOfWeek - 1] }} 
                第{{ schedule.startPeriod }}-{{ schedule.endPeriod }}节
              </div>
              <div>地点：{{ schedule.location || '未设置' }}</div>
              <div>周次：{{ formatWeeks(schedule.weeks) }}</div>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- 遮罩层 -->
    <div 
      v-if="selectedCourse" 
      class="panel-overlay"
      @click="closeCourseDetail"
    ></div>
  </div>
</template>

<script setup>
import { computed, ref, onMounted, nextTick, watch } from 'vue'
import { Close } from '@element-plus/icons-vue'

const props = defineProps({
  courses: {
    type: Array,
    required: true,
  },
});

// 引用网格元素
const gridRef = ref(null)
const selectedCourse = ref(null)
const selectedCourseAllSchedules = ref(null)

// 时间段映射（与周视图保持一致）
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
}

// 获取节次对应的时间
const getPeriodTime = (period, isEnd = false) => {
  const time = periodTimes[period]
  if (!time) return ''
  return isEnd ? time.end : time.start
}

// 显示课程详情
const showCourseDetail = (courseItem) => {
  selectedCourse.value = courseItem
  
  // 找到该课程的所有上课安排
  const fullCourse = props.courses.find(c => c.id === courseItem.id)
  if (fullCourse) {
    selectedCourseAllSchedules.value = fullCourse.scheduleEntries
  }
}

// 关闭课程详情
const closeCourseDetail = () => {
  selectedCourse.value = null
  selectedCourseAllSchedules.value = null
}

// 预设的课程背景颜色池
const colorPalette = [
  "#fde2e2",
  "#fcece0",
  "#fff6e0",
  "#e3f3e6",
  "#e0f1f3",
  "#e4eaf9",
  "#f0e6f5",
  "#fae2ed",
  "#d9e7ff",
  "#ffe9d4",
];
const courseColorMap = new Map();
let colorIndex = 0;

// 检查两个时间段是否重叠
const isTimeOverlapping = (schedule1, schedule2) => {
  return schedule1.startPeriod <= schedule2.endPeriod &&
         schedule1.endPeriod >= schedule2.startPeriod
}

// 格式化周次显示
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

// 处理课程数据，计算每个课程块的CSS Grid位置和颜色
const processedCourses = computed(() => {
  const flatSchedules = [];
  courseColorMap.clear();
  colorIndex = 0;

  props.courses.forEach((course) => {
    if (!courseColorMap.has(course.name)) {
      courseColorMap.set(
        course.name,
        colorPalette[colorIndex % colorPalette.length]
      );
      colorIndex++;
    }
    const bgColor = courseColorMap.get(course.name);

    course.scheduleEntries.forEach((schedule) => {
      flatSchedules.push({
        ...course,
        ...schedule,
        originalBgColor: bgColor,
        courseId: course.id,
        scheduleId: schedule.id
      });
    });
  });

  // 检测时间冲突并处理布局（日视图版本）
  const processedSchedules = flatSchedules.map((schedule, index) => {
    // 找到与当前课程时间冲突的其他课程
    const overlappingSchedules = flatSchedules.filter((other, otherIndex) => 
      otherIndex !== index && isTimeOverlapping(schedule, other)
    )
    
    let columnOffset = 0
    let columnWidth = 1
    
    if (overlappingSchedules.length > 0) {
      // 计算当前课程在冲突组中的位置
      const allConflictingSchedules = [schedule, ...overlappingSchedules]
      allConflictingSchedules.sort((a, b) => {
        // 先按开始时间排序，再按课程ID排序确保稳定性
        if (a.startPeriod !== b.startPeriod) {
          return a.startPeriod - b.startPeriod
        }
        return (a.courseId || 0) - (b.courseId || 0)
      })
      
      const currentPosition = allConflictingSchedules.findIndex(s => 
        s.courseId === schedule.courseId && s.scheduleId === schedule.scheduleId
      )
      const totalConflicts = allConflictingSchedules.length
      
      columnOffset = currentPosition
      columnWidth = 1 / totalConflicts
    }

    return {
      ...schedule,
      isOverlapping: overlappingSchedules.length > 0,
      style: {
        gridRow: `${schedule.startPeriod} / span ${
          schedule.endPeriod - schedule.startPeriod + 1
        }`,
        gridColumn: 2, // 日视图只有一列课程
        backgroundColor: schedule.originalBgColor,
        // 处理重叠的情况
        ...(overlappingSchedules.length > 0 ? {
          width: `${columnWidth * 100}%`,
          marginLeft: `${columnOffset * columnWidth * 100}%`,
          zIndex: 10 + columnOffset,
          opacity: 0.9
        } : {})
      }
    }
  })

  return processedSchedules;
});

// 调整单元格高度的函数（改进版，根据内容动态调整）
const adjustCellHeights = () => {
  if (!gridRef.value) return
  
  nextTick(() => {
    const courseItems = gridRef.value.querySelectorAll('.course-item')
    if (!courseItems.length) {
      // 如果没有课程，使用默认高度
      const defaultRowHeights = Array(12).fill('80px')
      gridRef.value.style.gridTemplateRows = defaultRowHeights.join(' ')
      return
    }
    
    // 创建一个映射来存储每节课的最大高度
    const periodHeights = new Map()
    
    // 初始化所有节次的默认高度
    for (let period = 1; period <= 12; period++) {
      periodHeights.set(period, 80) // 默认最小高度80px
    }
    
    // 第一步：收集所有课程项的自然高度
    courseItems.forEach(item => {
      const startPeriod = parseInt(item.dataset.periodStart)
      const endPeriod = parseInt(item.dataset.periodEnd)
      
      // 测量课程内容的自然高度
      const content = item.querySelector('.course-content')
      
      // 临时移除任何限制高度的样式以获取真实高度
      const originalHeight = content.style.height
      content.style.height = 'auto'
      
      // 获取内容的自然高度，加上padding
      const naturalHeight = content.scrollHeight + 20 // 16px padding + 4px 余量
      
      // 恢复原始高度设置
      content.style.height = originalHeight
      
      // 计算跨越的节次数
      const spanPeriods = endPeriod - startPeriod + 1
      
      // 计算每节课应该分配的平均高度
      const avgHeightPerPeriod = naturalHeight / spanPeriods
      
      // 更新每个被跨越的节次的最大高度
      for (let period = startPeriod; period <= endPeriod; period++) {
        const currentMax = periodHeights.get(period) || 80
        periodHeights.set(period, Math.max(currentMax, avgHeightPerPeriod))
      }
    })
    
    // 第二步：生成每行的高度数组
    const rowHeights = []
    for (let period = 1; period <= 12; period++) {
      const height = Math.max(80, Math.ceil(periodHeights.get(period)))
      rowHeights.push(`${height}px`)
    }
    
    // 第三步：应用到网格
    gridRef.value.style.gridTemplateRows = rowHeights.join(' ')
    
    // 第四步：让所有课程项适应其容器高度
    courseItems.forEach(item => {
      const content = item.querySelector('.course-content')
      content.style.height = '100%'
    })
  })
}

// 监听课程数据变化，重新调整高度
watch(() => props.courses, adjustCellHeights, { deep: true })

// 组件挂载后调整高度
onMounted(() => {
  adjustCellHeights()
  
  // 监听窗口大小变化，重新调整
  window.addEventListener('resize', adjustCellHeights)
})
</script>

<style scoped>
.timetable-container {
  width: 100%;
  overflow-x: auto;
  position: relative;
}

.timetable-grid-daily {
  display: grid;
  /* 定义2列：第1列是节次，第2列是课程 */
  grid-template-columns: 80px 1fr;
  /* 初始12行，每行高度会被JS动态调整 */
  grid-template-rows: repeat(12, minmax(80px, auto));
  border: 1px solid #e0e0e0;
  border-radius: 8px;
  overflow: hidden;
  background-color: #fff;
  margin-top: 20px;
  min-width: 400px;
}

.grid-header {
  display: flex;
  align-items: center;
  justify-content: center;
  font-weight: bold;
  font-size: 14px;
  color: #333;
  background-color: #f7f8fa;
  border-bottom: 1px solid #e0e0e0;
  border-right: 1px solid #e0e0e0;
  z-index: 1;
}

.period-header {
  font-size: 14px;
  flex-direction: column;
  grid-column: 1; /* 固定在第一列 */
}

.period-number {
  font-weight: bold;
  font-size: 16px;
}

.period-time {
  font-size: 11px;
  color: #666;
  margin-top: 2px;
}

/* 网格背景单元格 - 用于显示分界线 */
.grid-cell {
  border-right: 1px solid #f0f0f0;
  border-bottom: 1px solid #f0f0f0;
  background-color: #fafafa;
  z-index: 0;
}

.course-item {
  position: relative;
  padding: 8px;
  border-bottom: 1px solid #e0e0e0;
  border-left: 1px solid #e0e0e0;
  box-sizing: border-box;
  overflow: hidden;
  transition: all 0.2s ease-in-out;
  cursor: pointer;
  z-index: 2; /* 确保课程块在网格背景之上 */
  height: 100%; /* 确保占满网格单元格 */
}

.course-item:hover {
  transform: scale(1.02);
  z-index: 20 !important;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15);
  border-radius: 4px;
}

/* 重叠课程的特殊样式 */
.course-item.overlapping {
  border: 2px solid #409eff;
  border-radius: 4px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
}

.course-item.overlapping:hover {
  border-color: #67c23a;
  box-shadow: 0 4px 16px rgba(0, 0, 0, 0.2);
}

.course-content {
  color: #4c4948;
  font-size: 14px;
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  text-align: center;
  word-break: break-word;
}

.course-name {
  font-weight: bold;
  font-size: 16px;
  margin-bottom: 4px;
  line-height: 1.4;
}

.course-location,
.course-teacher,
.course-weeks {
  line-height: 1.4;
  font-size: 12px;
  color: #666;
  margin-bottom: 2px;
}

/* 课程详情面板（与周视图相同的样式） */
.course-detail-panel {
  position: fixed;
  top: 0;
  right: -400px;
  width: 400px;
  height: 100vh;
  background-color: #fff;
  box-shadow: -2px 0 10px rgba(0, 0, 0, 0.1);
  z-index: 1000;
  transition: right 0.3s ease-in-out;
  overflow-y: auto;
}

.course-detail-panel.show {
  right: 0;
}

.panel-overlay {
  position: fixed;
  top: 0;
  left: 0;
  width: 100vw;
  height: 100vh;
  background-color: rgba(0, 0, 0, 0.3);
  z-index: 999;
}

.panel-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 20px;
  border-bottom: 1px solid #eee;
  background-color: #f8f9fa;
}

.panel-header h3 {
  margin: 0;
  color: #333;
}

.close-btn {
  padding: 5px;
  color: #666;
}

.close-btn:hover {
  color: #333;
}

.panel-content {
  padding: 20px;
}

.detail-item {
  margin-bottom: 16px;
  display: flex;
  flex-direction: column;
}

.detail-item label {
  font-weight: bold;
  color: #333;
  margin-bottom: 4px;
}

.detail-item span {
  color: #666;
  word-break: break-word;
}

.note-content {
  background-color: #f8f9fa;
  padding: 10px;
  border-radius: 4px;
  border-left: 3px solid #409eff;
  margin-top: 4px;
  color: #666;
  white-space: pre-wrap;
}

.schedule-list {
  margin-top: 8px;
}

.schedule-item {
  background-color: #f8f9fa;
  padding: 12px;
  border-radius: 4px;
  margin-bottom: 8px;
  border-left: 3px solid #67c23a;
}

.schedule-item > div {
  margin-bottom: 4px;
  color: #666;
}

.schedule-item > div:last-child {
  margin-bottom: 0;
}

/* 响应式调整 */
@media (max-width: 768px) {
  .timetable-grid-daily {
    grid-template-columns: 60px 1fr;
  }
  
  .course-content {
    font-size: 12px;
  }
  
  .course-name {
    font-size: 14px;
  }
  
  .grid-header {
    font-size: 12px;
  }
  
  .period-number {
    font-size: 14px;
  }
  
  .period-time {
    font-size: 10px;
  }
  
  /* 在小屏幕上简化重叠课程的显示 */
  .course-item.overlapping {
    opacity: 1;
    width: 100% !important;
    margin-left: 0 !important;
  }
  
  /* 在小屏幕上调整详情面板 */
  .course-detail-panel {
    width: 100vw;
    right: -100vw;
  }
}

@media (max-width: 1200px) {
  .course-detail-panel {
    width: 33.33vw;
    right: -33.33vw;
  }
}

@media (min-width: 1200px) {
  .course-detail-panel {
    width: 25vw;
    right: -25vw;
  }
}
</style>