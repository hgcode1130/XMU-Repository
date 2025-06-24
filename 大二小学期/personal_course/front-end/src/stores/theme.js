import { defineStore } from "pinia";
import { ref, watch } from "vue";

export const useThemeStore = defineStore("theme", () => {
  // 1. 从 localStorage 读取初始主题，默认为 'day'
  const currentTheme = ref(localStorage.getItem("app-theme") || "day");

  // 2. 切换主题的方法
  function toggleTheme() {
    currentTheme.value = currentTheme.value === "day" ? "night" : "day";
  }

  // 3. 监听主题变化，并更新 localStorage 和 <html> 的 data-theme 属性
  watch(
    currentTheme,
    (newTheme) => {
      localStorage.setItem("app-theme", newTheme);
      document.documentElement.setAttribute("data-theme", newTheme);
    },
    { immediate: true }
  ); // immediate: true 确保在初始化时就执行一次

  return { currentTheme, toggleTheme };
});
