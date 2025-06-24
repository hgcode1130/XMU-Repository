// src/stores/term.js

import { defineStore } from "pinia";
import { ref, computed } from "vue";
import { getTermsApi } from "@/api/term"; // 引入获取学期列表的 API

export const useTermStore = defineStore("term", () => {
  // --- State ---

  // 1. 完整的学期列表
  const termList = ref([]);

  // 2. 当前选中的学期 ID
  // 尝试从 localStorage 读取上次选中的ID，以提供持久化体验
  const currentTermId = ref(localStorage.getItem("current-term-id") || null);

  // --- Getters ---

  // 3. 根据 currentTermId 计算出当前选中的完整学期对象
  const currentTerm = computed(() => {
    // 如果ID存在，就在列表中查找对应的对象
    if (currentTermId.value) {
      return termList.value.find((term) => term.id == currentTermId.value);
    }
    // 如果ID不存在，可以返回 null 或一个默认提示对象
    return null;
  });

  // --- Actions ---

  // 4. 从后端获取所有学期列表的动作
  async function fetchAllTerms() {
    try {
      // 假设 getTermsApi 不传参数或传一个很大的 size 可以获取全部
      const res = await getTermsApi(); // API 可能需要调整为 { page: 0, size: 999 }
      termList.value = res.data.content || res.data || []; // 兼容分页和非分页返回

      const hasCurrent = termList.value.some(
        (term) => term.id == currentTermId.value
      );
      if (!hasCurrent && termList.value.length > 0) {
        setTerm(termList.value[0].id);
      }
    } catch (error) {
      console.error("获取学期列表失败", error);
      termList.value = [];
    }
  }

  async function fetchAllTermsSimple() {
    try {
      // 获取所有数据，可以设置一个很大的 size
      const res = await getTermsApi({ page: 0, size: 999 });
      termList.value = res.data.content || [];

      const hasCurrent = termList.value.some(
        (term) => term.id == currentTermId.value
      );
      if (!hasCurrent && termList.value.length > 0) {
        setTerm(termList.value[0].id);
      }
    } catch (error) {
      console.error("获取所有学期列表失败", error);
      termList.value = [];
    }
  }
  // 5. 设置当前学期的动作
  function setTerm(termId) {
    currentTermId.value = termId;
    // 将用户的选择保存到 localStorage，以便下次打开页面时能记住
    localStorage.setItem("current-term-id", termId);
  }

  return {
    termList,
    currentTermId,
    currentTerm,
    fetchAllTerms,
    setTerm,
  };
});
