<template>
  <router-view />
</template>

<script setup>
// 【新增】导入并初始化主题 store，使其能够监听并应用主题
import { useThemeStore } from "@/stores/theme";
const themeStore = useThemeStore();
</script>
