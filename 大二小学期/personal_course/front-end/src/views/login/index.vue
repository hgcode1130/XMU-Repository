<template>
  <div class="login-container">
    <!-- 背景装饰元素 -->
    <div class="bg-decoration">
      <div class="floating-shapes">
        <div class="shape shape-1"></div>
        <div class="shape shape-2"></div>
        <div class="shape shape-3"></div>
        <div class="shape shape-4"></div>
      </div>
    </div>

    <div class="login-wrapper">
      <!-- 左侧信息面板 -->
      <div class="info-panel">
        <div class="info-content">
          <div class="logo-section">
            <div class="logo-icon">
              <el-icon :size="48"><Calendar /></el-icon>
            </div>
            <h1 class="system-title">个人课表系统</h1>
            <p class="system-subtitle">Personal Course Management System</p>
          </div>
          
          <div class="features-list">
            <div class="feature-item">
              <el-icon class="feature-icon"><Calendar /></el-icon>
              <span>智能课表管理</span>
            </div>
            <div class="feature-item">
              <el-icon class="feature-icon"><Management /></el-icon>
              <span>学期灵活切换</span>
            </div>
            <div class="feature-item">
              <el-icon class="feature-icon"><User /></el-icon>
              <span>多用户权限控制</span>
            </div>
            <div class="feature-item">
              <el-icon class="feature-icon"><Document /></el-icon>
              <span>数据批量导入</span>
            </div>
          </div>

          <div class="quote-section">
            <p class="quote-text">"让课表管理变得简单而高效"</p>
            <p class="quote-author">— 专为学生与教师设计</p>
          </div>
        </div>
      </div>

      <!-- 右侧登录表单 -->
      <div class="form-panel">
        <el-card class="login-card">
          <div class="card-header">
            <h2 class="login-title">欢迎回来</h2>
            <p class="login-subtitle">请输入您的账号信息登录系统</p>
          </div>

          <el-form
            ref="loginFormRef"
            :model="loginForm"
            :rules="loginRules"
            class="login-form"
          >
            <el-form-item prop="username">
              <div class="input-group">
                <el-icon class="input-icon"><User /></el-icon>
                <el-input 
                  v-model="loginForm.username" 
                  placeholder="请输入用户名"
                  size="large"
                  class="custom-input"
                />
              </div>
            </el-form-item>

            <el-form-item prop="password">
              <div class="input-group">
                <el-icon class="input-icon"><Lock /></el-icon>
                <el-input
                  type="password"
                  v-model="loginForm.password"
                  show-password
                  placeholder="请输入密码"
                  size="large"
                  class="custom-input"
                  @keyup.enter="handleLogin"
                />
              </div>
            </el-form-item>

            <div class="form-options">
              <el-checkbox v-model="rememberMe" class="remember-checkbox">
                记住我
              </el-checkbox>
              <el-link type="primary" class="forgot-link">忘记密码？</el-link>
            </div>

            <el-form-item class="submit-item">
              <el-button
                type="primary"
                size="large"
                class="login-button"
                @click="handleLogin"
                :loading="loading"
              >
                <span v-if="!loading">立即登录</span>
                <span v-else>登录中...</span>
              </el-button>
            </el-form-item>
          </el-form>

          <div class="divider">
            <span class="divider-text">或</span>
          </div>

          <div class="register-section">
            <p class="register-text">还没有账号？</p>
            <el-button 
              text 
              type="primary" 
              class="register-button"
              @click="goToRegister"
            >
              立即注册
            </el-button>
          </div>
        </el-card>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, reactive } from "vue";
import { useUserStore } from "@/stores/user";
import { useRouter } from 'vue-router';
import { ElMessage } from 'element-plus';
import {
  Calendar,
  Management,
  User,
  Document,
  Lock
} from "@element-plus/icons-vue";

const router = useRouter();
const userStore = useUserStore();
const loginFormRef = ref(null);
const loading = ref(false);
const rememberMe = ref(false);

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
        await userStore.login(loginForm);
        console.log("4. userStore.login 执行成功");
        ElMessage.success('登录成功！即将跳转...');
        router.push('/');
      } catch (error) {
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
  position: relative;
  min-height: 100vh;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  display: flex;
  align-items: center;
  justify-content: center;
  overflow: hidden;
}

/* 背景装饰 */
.bg-decoration {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  pointer-events: none;
  z-index: 1;
}

.floating-shapes {
  position: relative;
  width: 100%;
  height: 100%;
}

.shape {
  position: absolute;
  border-radius: 50%;
  background: rgba(255, 255, 255, 0.1);
  animation: float 6s ease-in-out infinite;
}

.shape-1 {
  width: 80px;
  height: 80px;
  top: 20%;
  left: 10%;
  animation-delay: 0s;
}

.shape-2 {
  width: 60px;
  height: 60px;
  top: 60%;
  right: 15%;
  animation-delay: 2s;
}

.shape-3 {
  width: 40px;
  height: 40px;
  top: 80%;
  left: 20%;
  animation-delay: 4s;
}

.shape-4 {
  width: 100px;
  height: 100px;
  top: 30%;
  right: 25%;
  animation-delay: 1s;
}

@keyframes float {
  0%, 100% {
    transform: translateY(0px) rotate(0deg);
    opacity: 0.7;
  }
  50% {
    transform: translateY(-20px) rotate(180deg);
    opacity: 1;
  }
}

/* 主容器 */
.login-wrapper {
  position: relative;
  z-index: 2;
  display: flex;
  width: 90%;
  max-width: 1200px;
  min-height: 600px;
  background: rgba(255, 255, 255, 0.1);
  backdrop-filter: blur(20px);
  border-radius: 20px;
  border: 1px solid rgba(255, 255, 255, 0.2);
  box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
  overflow: hidden;
}

/* 左侧信息面板 */
.info-panel {
  flex: 1;
  background: linear-gradient(135deg, rgba(255, 255, 255, 0.1) 0%, rgba(255, 255, 255, 0.05) 100%);
  padding: 60px 40px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  color: white;
}

.logo-section {
  text-align: center;
  margin-bottom: 50px;
}

.logo-icon {
  width: 80px;
  height: 80px;
  background: rgba(255, 255, 255, 0.2);
  border-radius: 20px;
  display: flex;
  align-items: center;
  justify-content: center;
  margin: 0 auto 20px;
  backdrop-filter: blur(10px);
}

.system-title {
  font-size: 28px;
  font-weight: 700;
  margin: 0 0 10px;
  text-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
}

.system-subtitle {
  font-size: 14px;
  opacity: 0.9;
  margin: 0;
  letter-spacing: 1px;
}

.features-list {
  margin-bottom: 50px;
}

.feature-item {
  display: flex;
  align-items: center;
  margin-bottom: 20px;
  font-size: 16px;
  transition: all 0.3s ease;
}

.feature-item:hover {
  transform: translateX(5px);
}

.feature-icon {
  margin-right: 15px;
  font-size: 20px;
  color: rgba(255, 255, 255, 0.9);
}

.quote-section {
  text-align: center;
  border-top: 1px solid rgba(255, 255, 255, 0.2);
  padding-top: 30px;
}

.quote-text {
  font-size: 18px;
  font-style: italic;
  margin: 0 0 10px;
  opacity: 0.95;
}

.quote-author {
  font-size: 14px;
  opacity: 0.8;
  margin: 0;
}

/* 右侧表单面板 */
.form-panel {
  flex: 1;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 40px;
  background: rgba(255, 255, 255, 0.05);
}

.login-card {
  width: 100%;
  max-width: 400px;
  background: rgba(255, 255, 255, 0.95) !important;
  backdrop-filter: blur(20px);
  border-radius: 16px;
  border: none;
  box-shadow: 0 15px 35px rgba(0, 0, 0, 0.1);
}

.card-header {
  text-align: center;
  margin-bottom: 30px;
  padding: 0;
}

.login-title {
  font-size: 24px;
  font-weight: 600;
  color: #2c3e50;
  margin: 0 0 8px;
}

.login-subtitle {
  font-size: 14px;
  color: #7f8c8d;
  margin: 0;
}

.login-form {
  padding: 0;
}

.input-group {
  position: relative;
  display: flex;
  align-items: center;
}

.input-icon {
  position: absolute;
  left: 15px;
  z-index: 3;
  color: #7f8c8d;
  font-size: 18px;
}

:deep(.custom-input .el-input__wrapper) {
  padding-left: 45px;
  height: 50px;
  border-radius: 12px;
  background-color: #f8f9fa;
  border: 2px solid transparent;
  box-shadow: none;
  transition: all 0.3s ease;
}

:deep(.custom-input .el-input__wrapper:hover) {
  background-color: #e9ecef;
}

:deep(.custom-input.is-focus .el-input__wrapper) {
  border-color: #667eea;
  background-color: #fff;
  box-shadow: 0 0 0 3px rgba(102, 126, 234, 0.1);
}

:deep(.custom-input .el-input__inner) {
  color: #2c3e50;
  font-size: 15px;
}

:deep(.custom-input .el-input__inner::placeholder) {
  color: #adb5bd;
}

.form-options {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin: 20px 0;
}

.remember-checkbox :deep(.el-checkbox__label) {
  color: #6c757d;
  font-size: 14px;
}

.forgot-link {
  font-size: 14px;
  text-decoration: none;
}

.submit-item {
  margin-bottom: 0;
}

.login-button {
  width: 100%;
  height: 50px;
  border-radius: 12px;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  border: none;
  font-size: 16px;
  font-weight: 600;
  letter-spacing: 0.5px;
  transition: all 0.3s ease;
}

.login-button:hover {
  transform: translateY(-2px);
  box-shadow: 0 8px 25px rgba(102, 126, 234, 0.3);
}

.divider {
  position: relative;
  text-align: center;
  margin: 25px 0;
}

.divider::before {
  content: '';
  position: absolute;
  top: 50%;
  left: 0;
  right: 0;
  height: 1px;
  background: #e9ecef;
}

.divider-text {
  background: white;
  padding: 0 15px;
  color: #adb5bd;
  font-size: 14px;
  position: relative;
  z-index: 1;
}

.register-section {
  text-align: center;
}

.register-text {
  margin: 0 0 10px;
  color: #6c757d;
  font-size: 14px;
}

.register-button {
  font-size: 14px;
  font-weight: 600;
  padding: 0;
}

/* 响应式设计 */
@media (max-width: 1024px) {
  .login-wrapper {
    flex-direction: column;
    max-width: 500px;
  }
  
  .info-panel {
    padding: 40px 30px 30px;
  }
  
  .features-list {
    display: none;
  }
  
  .quote-section {
    display: none;
  }
}

@media (max-width: 768px) {
  .login-container {
    padding: 20px;
  }
  
  .login-wrapper {
    width: 100%;
    min-height: auto;
  }
  
  .info-panel {
    padding: 30px 20px 20px;
  }
  
  .form-panel {
    padding: 20px;
  }
  
  .system-title {
    font-size: 24px;
  }
  
  .logo-icon {
    width: 60px;
    height: 60px;
  }
}

/* 卡片内容样式覆盖 */
:deep(.el-card__body) {
  padding: 40px !important;
}

:deep(.el-form-item) {
  margin-bottom: 20px;
}

:deep(.el-form-item__error) {
  font-size: 12px;
  margin-top: 5px;
}
</style>