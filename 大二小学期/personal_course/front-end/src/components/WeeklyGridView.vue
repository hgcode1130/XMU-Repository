<template>
  <div class="timetable-grid">
    <div class="grid-header day-header" v-for="day in weekDays" :key="day.name" :style="{ gridColumn: day.index + 1 }">
      {{ day.name }}
    </div>

    <div class="grid-header period-header" v-for="period in 12" :key="period" :style="{ gridRow: period + 1 }">
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
        <div class="course-weeks">({{ item.startWeek }}-{{ item.endWeek }}周)</div>
      </div>
    </div>
  </div>
</template>

<script setup>
import { computed } from 'vue'

const props = defineProps({
  courses: {
    type: Array,
    required: true,
  },
})

const weekDays = [
  { name: '星期一', index: 2 },
  { name: '星期二', index: 3 },
  { name: '星期三', index: 4 },
  { name: '星期四', index: 5 },
  { name: '星期五', index: 6 },
  { name: '星期六', index: 7 },
  { name: '星期日', index: 8 },
]

// 预设的课程背景颜色池
const colorPalette = [
  '#fde2e2', '#fcece0', '#fff6e0', '#e3f3e6', '#e0f1f3',
  '#e4eaf9', '#f0e6f5', '#fae2ed', '#d9e7ff', '#ffe9d4'
]
const courseColorMap = new Map()
let colorIndex = 0

// 【核心逻辑】处理课程数据，计算每个课程块的CSS Grid位置和颜色
const processedCourses = computed(() => {
  const flatSchedules = []
  courseColorMap.clear() // 每次重新计算时清空颜色映射

  props.courses.forEach(course => {
    // 为每个唯一的课程名称分配一个颜色
    if (!courseColorMap.has(course.name)) {
      courseColorMap.set(course.name, colorPalette[colorIndex % colorPalette.length])
      colorIndex++
    }
    const bgColor = courseColorMap.get(course.name);

    course.scheduleEntries.forEach(schedule => {
      flatSchedules.push({
        ...course, // 继承课程的 name, teachers 等信息
        ...schedule, // 继承 schedule 的 location, dayOfWeek 等信息
        style: {
          // CSS Grid 的强大之处: 直接指定行和列的起始位置和跨度
          // grid-column: 列起始线 (星期一在第2列)
          gridColumn: schedule.dayOfWeek + 1,
          // grid-row: 行起始线 / span 跨度 (一节课在第2行开始)
          gridRow: `${schedule.startPeriod + 1} / span ${schedule.endPeriod - schedule.startPeriod + 1}`,
          backgroundColor: bgColor,
        }
      })
    })
  })
  return flatSchedules
})
</script>

<style scoped>
.timetable-grid {
  display: grid;
  /* 定义8列：第1列是节次，后7列是星期 */
  grid-template-columns: 50px repeat(7, 1fr);
  /* 定义13行：第1行是星期，后12行是课程节次 */
  grid-template-rows: 40px repeat(12, 60px);
  border: 1px solid #e0e0e0;
  border-radius: 8px;
  overflow: hidden;
  background-color: #fff;
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
}

.period-number {
  font-weight: bold;
}

.course-item {
  position: relative;
  padding: 6px;
  border-right: 1px solid #e0e0e0;
  border-bottom: 1px solid #e0e0e0;
  box-sizing: border-box;
  overflow: hidden;
  transition: all 0.2s ease-in-out;
}

.course-item:hover {
  transform: scale(1.02);
  z-index: 10;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
  border-radius: 4px;
}

.course-content {
  color: #4c4948;
  font-size: 13px;
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  text-align: center;
  word-break: break-all;
}

.course-name {
  font-weight: bold;
  margin-bottom: 4px;
}

.course-location,
.course-teacher,
.course-weeks {
  line-height: 1.3;
}
</style>