<template>
  <div class="timetable-grid-daily">
    <div
      class="grid-header period-header"
      v-for="period in 12"
      :key="period"
      :style="{ gridRow: period }"
    >
      <div class="period-number">{{ period }}</div>
    </div>

    <div
      v-for="(item, index) in processedCourses"
      :key="index"
      class="course-item"
      :style="item.style"
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
</template>

<script setup>
import { computed } from "vue";

const props = defineProps({
  courses: {
    type: Array,
    required: true,
  },
});

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
        style: {
          gridRow: `${schedule.startPeriod} / span ${
            schedule.endPeriod - schedule.startPeriod + 1
          }`,
          backgroundColor: bgColor,
        },
      });
    });
  });
  return flatSchedules;
});
</script>

<style scoped>
.timetable-grid-daily {
  display: grid;
  /* 定义2列：第1列是节次，后1列是课程 */
  grid-template-columns: 60px 1fr;
  /* 定义12行，每行是课程节次 */
  grid-template-rows: repeat(12, 80px);
  border: 1px solid #e0e0e0;
  border-radius: 8px;
  overflow: hidden;
  background-color: #fff;
  margin-top: 20px;
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
}

.period-header {
  font-size: 16px;
  flex-direction: column;
  grid-column: 1; /* 固定在第一列 */
}

.period-number {
  font-weight: bold;
}

.course-item {
  position: relative;
  padding: 8px;
  border-bottom: 1px solid #e0e0e0;
  box-sizing: border-box;
  overflow: hidden;
  transition: all 0.2s ease-in-out;
  grid-column: 2; /* 固定在第二列 */
  border-left: 1px solid #e0e0e0;
}

.course-item:hover {
  transform: scale(1.01);
  z-index: 10;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
  border-radius: 4px;
}

.course-content {
  color: #4c4948;
  font-size: 14px;
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  text-align: center;
  word-break: break-all;
}

.course-name {
  font-weight: bold;
  font-size: 16px;
  margin-bottom: 4px;
}

.course-location,
.course-teacher,
.course-weeks {
  line-height: 1.4;
  font-size: 12px;
  color: #666;
}
</style>
