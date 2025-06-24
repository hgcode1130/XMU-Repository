<template>
  <div class="login-container">
    <el-card class="login-card">
      <template #header>
        <div class="card-header">
          <span>欢迎登录 - 个人课表系统</span>
        </div>
      </template>
      <el-form
        ref="loginFormRef"
        :model="loginForm"
        :rules="loginRules"
        label-width="80px"
      >
        <el-form-item label="用户名" prop="username">
          <el-input v-model="loginForm.username" placeholder="请输入用户名" />
        </el-form-item>
        <el-form-item label="密码" prop="password">
          <el-input
            type="password"
            v-model="loginForm.password"
            show-password
            placeholder="请输入密码"
            @keyup.enter="handleLogin"
          />
        </el-form-item>
        <el-form-item>
          <el-button
            type="primary"
            style="width: 100%"
            @click="handleLogin"
            :loading="loading"
          >
            登 录
          </el-button>
        </el-form-item>
      </el-form>
      <div class="register-link" style="text-align: right; margin-top: 10px">
        <el-link type="primary" @click="goToRegister">立即注册</el-link>
      </div>
    </el-card>
  </div>
</template>

<script setup>
import { ref, reactive } from "vue";
import { useUserStore } from "@/stores/user";
import { useRouter } from 'vue-router';
import { ElMessage } from 'element-plus'; // 确保引入 ElMessage

const router = useRouter();
const userStore = useUserStore();
const loginFormRef = ref(null);
const loading = ref(false);

const loginForm = reactive({
  username: "",
  password: "",
});

const loginRules = {
  username: [{ required: true, message: "请输入用户名", trigger: "blur" }],
  password: [{ required: true, message: "请输入密码", trigger: "blur" }],
};

const handleLogin = () => {
  console.log("1. '登录'按钮点击，开始处理...");
  loginFormRef.value.validate(async (valid) => {
    console.log("2. 表单验证结果:", valid);
    if (valid) {
      loading.value = true;
      console.log("3. 表单验证通过，准备调用 userStore.login，参数:", loginForm);
      try {
        // 调用 store 的 login action
        await userStore.login(loginForm);
        
        console.log("4. userStore.login 执行成功");
        ElMessage.success('登录成功！即将跳转...');
        
        // 【重要】登录成功后，跳转到课表页或主页
        router.push('/');
      } catch (error) {
        // 这个 catch 会捕获 request.js 中 reject 的错误
        // 错误提示已由 request.js 的响应拦截器统一处理，这里只需记录日志
        console.error("5. 登录流程捕获到错误:", error);
      } finally {
        loading.value = false;
        console.log("6. 登录流程结束 (finally)");
      }
    } else {
      console.log("2a. 表单验证失败");
      return false;
    }
  });
};

const goToRegister = () => {
  router.push('/register');
};
</script>

<style scoped>
.login-container {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100vh;
  background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab);
  background-size: 400% 400%;
  animation: gradient 15s ease infinite;
  overflow: hidden; /* 隐藏溢出，防止滚动条出现 */
}

@keyframes gradient {
  0% {
    background-position: 0% 50%;
  }
  50% {
    background-position: 100% 50%;
  }
  100% {
    background-position: 0% 50%;
  }
}

.login-card {
  width: 90%;
  max-width: 450px;
  /* 玻璃拟态效果 */
  background: rgba(255, 255, 255, 0.15) !important;
  backdrop-filter: blur(10px);
  -webkit-backdrop-filter: blur(10px); /* 兼容 Safari */
  border-radius: 15px;
  border: 1px solid rgba(255, 255, 255, 0.2);
  box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37) !important;
  transition: transform 0.3s ease;
}

.login-card:hover {
    transform: scale(1.02); /* 鼠标悬浮时轻微放大 */
}

.card-header {
  text-align: center;
  font-size: 24px;
  font-weight: bold;
  color: #ffffff;
  text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.3); /* 文字阴影增加立体感 */
}

/* 使用 :deep() 来穿透 scoped 样式，修改 Element Plus 组件内部样式 */
:deep(.el-card__header) {
  border-bottom: 1px solid rgba(255, 255, 255, 0.2) !important;
}

:deep(.el-card__body) {
    padding: 30px !important;
}

:deep(.el-form-item__label) {
  color: #fff !important;
  font-weight: bold;
}

:deep(.el-input__wrapper) {
  background-color: rgba(255, 255, 255, 0.2) !important;
  border-radius: 8px !important;
  border: 1px solid rgba(255, 255, 255, 0.3) !important;
  box-shadow: none !important;
}

:deep(.el-input__inner) {
  color: #fff !important;
}

/* 修改输入框 placeholder 颜色 */
:deep(.el-input__inner::placeholder) {
  color: rgba(255, 255, 255, 0.7) !important;
}

:deep(.el-button--primary) {
    border: none;
    background: linear-gradient(45deg, #f66, #f99);
    transition: all 0.3s ease;
    box-shadow: 0 4px 15px rgba(0,0,0,0.2);
}

:deep(.el-button--primary:hover) {
    transform: translateY(-2px);
    box-shadow: 0 6px 20px rgba(0,0,0,0.3);
}

.register-link :deep(.el-link) {
    color: #fff;
    font-weight: bold;
}

.register-link :deep(.el-link:hover) {
    color: #f99;
}

/* 响应式布局 */
@media (max-width: 768px) {
  .login-card {
    width: 95%;
    max-width: none;
  }
  :deep(.el-card__body) {
    padding: 20px !important;
  }
  .card-header {
    font-size: 20px;
  }
}
</style>