<template>
  <div class="register-container">
    <!-- 背景装饰 -->
    <div class="bg-decoration">
      <div class="floating-elements">
        <div class="element element-1"></div>
        <div class="element element-2"></div>
        <div class="element element-3"></div>
      </div>
    </div>

    <div class="register-wrapper">
      <!-- 左侧欢迎面板 -->
      <div class="welcome-panel">
        <div class="welcome-content">
          <div class="welcome-header">
            <div class="logo-container">
              <el-icon :size="40"><Calendar /></el-icon>
            </div>
            <h1 class="welcome-title">加入我们</h1>
            <p class="welcome-subtitle">开始您的课表管理之旅</p>
          </div>

          <div class="benefits-list">
            <div class="benefit-item">
              <div class="benefit-icon">
                <el-icon><CircleCheck /></el-icon>
              </div>
              <div class="benefit-content">
                <h4>智能课表</h4>
                <p>自动生成个性化课表，支持多种视图模式</p>
              </div>
            </div>

            <div class="benefit-item">
              <div class="benefit-icon">
                <el-icon><DataAnalysis /></el-icon>
              </div>
              <div class="benefit-content">
                <h4>数据统计</h4>
                <p>课程统计分析，帮助您更好地管理时间</p>
              </div>
            </div>

            <div class="benefit-item">
              <div class="benefit-icon">
                <el-icon><Share /></el-icon>
              </div>
              <div class="benefit-content">
                <h4>便捷导入</h4>
                <p>支持Excel批量导入，快速建立课表数据</p>
              </div>
            </div>
          </div>

          <div class="testimonial">
            <div class="testimonial-content">
              <p>"这个系统让我的课表管理变得前所未有的简单！"</p>
              <div class="testimonial-author">
                <span>— 张同学，大三学生</span>
              </div>
            </div>
          </div>
        </div>
      </div>

      <!-- 右侧注册表单 -->
      <div class="form-container">
        <el-card class="register-card">
          <div class="register-header">
            <h2 class="register-title">创建新账号</h2>
            <p class="register-description">填写以下信息即可开始使用</p>
          </div>

          <el-form
            ref="registerFormRef"
            :model="registerForm"
            :rules="registerRules"
            class="register-form"
          >
            <div class="input-row">
              <el-form-item prop="username">
                <div class="input-wrapper">
                  <el-icon class="input-prefix"><User /></el-icon>
                  <el-input
                    v-model="registerForm.username"
                    placeholder="用户名"
                    size="large"
                    class="styled-input"
                  />
                </div>
              </el-form-item>
            </div>

            <div class="input-row">
              <el-form-item prop="email">
                <div class="input-wrapper">
                  <el-icon class="input-prefix"><Message /></el-icon>
                  <el-input
                    v-model="registerForm.email"
                    placeholder="邮箱地址"
                    size="large"
                    class="styled-input"
                  />
                </div>
              </el-form-item>
            </div>

            <div class="input-row">
              <el-form-item prop="password">
                <div class="input-wrapper">
                  <el-icon class="input-prefix"><Lock /></el-icon>
                  <el-input
                    type="password"
                    v-model="registerForm.password"
                    placeholder="密码"
                    size="large"
                    class="styled-input"
                    show-password
                  />
                </div>
              </el-form-item>
            </div>

            <div class="input-row">
              <el-form-item prop="confirmPassword">
                <div class="input-wrapper">
                  <el-icon class="input-prefix"><Lock /></el-icon>
                  <el-input
                    type="password"
                    v-model="registerForm.confirmPassword"
                    placeholder="确认密码"
                    size="large"
                    class="styled-input"
                    show-password
                  />
                </div>
              </el-form-item>
            </div>

            <div class="terms-section">
              <el-checkbox v-model="agreeTerms" class="terms-checkbox">
                我已阅读并同意
                <el-link type="primary" class="terms-link">服务条款</el-link>
                和
                <el-link type="primary" class="terms-link">隐私政策</el-link>
              </el-checkbox>
            </div>

            <el-form-item class="submit-section">
              <el-button
                type="primary"
                size="large"
                class="register-button"
                @click="handleRegister"
                :loading="loading"
                :disabled="!agreeTerms"
              >
                <span v-if="!loading">立即注册</span>
                <span v-else>注册中...</span>
              </el-button>
            </el-form-item>
          </el-form>

          <div class="login-link-section">
            <p class="login-text">已经有账号了？</p>
            <el-button 
              text 
              type="primary" 
              class="login-link-button"
              @click="goToLogin"
            >
              立即登录
            </el-button>
          </div>
        </el-card>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, reactive } from 'vue'
import { ElMessage } from 'element-plus'
import { useRouter } from 'vue-router'
import { registerApi } from '@/api/auth'
import {
  Calendar,
  User,
  Message,
  Lock,
  CircleCheck,
  DataAnalysis,
  Share
} from '@element-plus/icons-vue'

const router = useRouter()
const registerFormRef = ref(null)
const loading = ref(false)
const agreeTerms = ref(false)

const registerForm = reactive({
  username: '',
  email: '',
  password: '',
  confirmPassword: '',
})

// 自定义确认密码校验器
const validatePass = (rule, value, callback) => {
  if (value === '') {
    callback(new Error('请再次输入密码'))
  } else if (value !== registerForm.password) {
    callback(new Error('两次输入的密码不一致!'))
  } else {
    callback()
  }
}

const registerRules = {
  username: [
    { required: true, message: '请输入用户名', trigger: 'blur' },
    { min: 3, max: 20, message: '用户名长度应为 3 到 20 个字符', trigger: 'blur' },
  ],
  email: [
    { required: true, message: '请输入邮箱地址', trigger: 'blur' },
    { type: 'email', message: '请输入正确的邮箱地址', trigger: ['blur', 'change'] },
  ],
  password: [
    { required: true, message: '请输入密码', trigger: 'blur' },
    { min: 6, max: 20, message: '密码长度应为 6 到 20 个字符', trigger: 'blur' },
  ],
  confirmPassword: [{ required: true, validator: validatePass, trigger: 'blur' }],
}

const handleRegister = () => {
  if (!agreeTerms.value) {
    ElMessage.warning('请先同意服务条款和隐私政策')
    return
  }

  registerFormRef.value.validate(async (valid) => {
    if (valid) {
      loading.value = true
      try {
        const data = {
          username: registerForm.username,
          password: registerForm.password,
          email: registerForm.email,
        }
        await registerApi(data)
        ElMessage.success('注册成功！即将跳转到登录页...')
        setTimeout(() => {
          router.push('/login')
        }, 1500)
      } catch (error) {
        console.error('注册失败', error)
      } finally {
        loading.value = false
      }
    } else {
      console.log('表单验证失败')
      return false
    }
  })
}

const goToLogin = () => {
  router.push('/login')
}
</script>
<style scoped>
.register-container {
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

.floating-elements {
  position: relative;
  width: 100%;
  height: 100%;
}

.element {
  position: absolute;
  background: rgba(255, 255, 255, 0.08);
  border-radius: 50%;
  animation: float 8s ease-in-out infinite;
  filter: blur(1px);
}

.element-1 {
  width: 120px;
  height: 120px;
  top: 15%;
  left: 10%;
  animation-delay: 0s;
}

.element-2 {
  width: 80px;
  height: 80px;
  top: 70%;
  right: 20%;
  animation-delay: 3s;
}

.element-3 {
  width: 60px;
  height: 60px;
  top: 40%;
  right: 10%;
  animation-delay: 6s;
}

@keyframes float {
  0%, 100% {
    transform: translateY(0px) scale(1);
    opacity: 0.5;
  }
  50% {
    transform: translateY(-30px) scale(1.1);
    opacity: 0.8;
  }
}

/* 主容器 */
.register-wrapper {
  position: relative;
  z-index: 2;
  display: flex;
  width: 90%;
  max-width: 1200px;
  min-height: 700px;
  background: rgba(255, 255, 255, 0.12);
  backdrop-filter: blur(25px);
  border-radius: 24px;
  border: 1px solid rgba(255, 255, 255, 0.25);
  box-shadow: 0 25px 50px rgba(0, 0, 0, 0.15);
  overflow: hidden;
}

/* 左侧欢迎面板 */
.welcome-panel {
  flex: 1;
  background: linear-gradient(135deg, rgba(255, 255, 255, 0.15) 0%, rgba(255, 255, 255, 0.08) 100%);
  padding: 60px 50px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  color: white;
  position: relative;
}

.welcome-panel::before {
  content: '';
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background: rgba(0, 0, 0, 0.1);
  backdrop-filter: blur(10px);
  z-index: -1;
}

.welcome-header {
  text-align: center;
  margin-bottom: 50px;
}

.logo-container {
  width: 70px;
  height: 70px;
  background: rgba(255, 255, 255, 0.25);
  border-radius: 16px;
  display: flex;
  align-items: center;
  justify-content: center;
  margin: 0 auto 20px;
  backdrop-filter: blur(15px);
  border: 1px solid rgba(255, 255, 255, 0.3);
  box-shadow: 0 8px 20px rgba(0, 0, 0, 0.1);
}

.welcome-title {
  font-size: 32px;
  font-weight: 700;
  margin: 0 0 12px;
  text-shadow: 0 4px 8px rgba(0, 0, 0, 0.3);
  color: #ffffff;
  letter-spacing: 0.5px;
}

.welcome-subtitle {
  font-size: 16px;
  margin: 0;
  color: rgba(255, 255, 255, 0.95);
  text-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
  font-weight: 400;
}

.benefits-list {
  margin-bottom: 50px;
}

.benefit-item {
  display: flex;
  align-items: flex-start;
  margin-bottom: 30px;
  transition: all 0.3s ease;
  padding: 8px;
  border-radius: 12px;
}

.benefit-item:hover {
  transform: translateX(8px);
  background: rgba(255, 255, 255, 0.08);
}

.benefit-icon {
  width: 40px;
  height: 40px;
  background: rgba(255, 255, 255, 0.25);
  border-radius: 12px;
  display: flex;
  align-items: center;
  justify-content: center;
  margin-right: 20px;
  flex-shrink: 0;
  backdrop-filter: blur(10px);
  border: 1px solid rgba(255, 255, 255, 0.2);
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
}

.benefit-content h4 {
  font-size: 18px;
  font-weight: 600;
  margin: 0 0 5px;
  color: #ffffff;
  text-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
}

.benefit-content p {
  font-size: 14px;
  margin: 0;
  line-height: 1.6;
  color: rgba(255, 255, 255, 0.9);
  text-shadow: 0 1px 2px rgba(0, 0, 0, 0.1);
}

.testimonial {
  background: rgba(255, 255, 255, 0.15);
  border-radius: 16px;
  padding: 25px;
  backdrop-filter: blur(15px);
  border: 1px solid rgba(255, 255, 255, 0.25);
  box-shadow: 0 8px 20px rgba(0, 0, 0, 0.1);
}

.testimonial-content p {
  font-size: 16px;
  font-style: italic;
  margin: 0 0 15px;
  line-height: 1.6;
  color: #ffffff;
  text-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
}

.testimonial-author span {
  font-size: 14px;
  color: rgba(255, 255, 255, 0.85);
  text-shadow: 0 1px 2px rgba(0, 0, 0, 0.1);
}

/* 右侧表单容器 */
.form-container {
  flex: 1;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 50px;
  background: rgba(255, 255, 255, 0.08);
}

.register-card {
  width: 100%;
  max-width: 420px;
  background: rgba(255, 255, 255, 0.98) !important;
  backdrop-filter: blur(25px);
  border-radius: 20px;
  border: 1px solid rgba(255, 255, 255, 0.5);
  box-shadow: 0 25px 50px rgba(0, 0, 0, 0.15);
}

.register-header {
  text-align: center;
  margin-bottom: 35px;
}

.register-title {
  font-size: 28px;
  font-weight: 700;
  color: #1a202c;
  margin: 0 0 10px;
  text-shadow: 0 1px 2px rgba(0, 0, 0, 0.05);
}

.register-description {
  font-size: 15px;
  color: #4a5568;
  margin: 0;
  font-weight: 400;
}

.register-form {
  margin-bottom: 25px;
}

.input-row {
  margin-bottom: 22px;
}

.input-wrapper {
  position: relative;
  display: flex;
  align-items: center;
}

.input-prefix {
  position: absolute;
  left: 16px;
  z-index: 3;
  color: #718096;
  font-size: 18px;
  transition: color 0.3s ease;
}

:deep(.styled-input .el-input__wrapper) {
  padding-left: 52px;
  height: 54px;
  border-radius: 14px;
  background-color: #f7fafc;
  border: 2px solid #e2e8f0;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02);
  transition: all 0.3s ease;
}

:deep(.styled-input .el-input__wrapper:hover) {
  background-color: #edf2f7;
  border-color: #cbd5e0;
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.06);
}

:deep(.styled-input.is-focus .el-input__wrapper) {
  border-color: #667eea;
  background-color: #ffffff;
  box-shadow: 0 0 0 3px rgba(102, 126, 234, 0.1);
}

:deep(.styled-input.is-focus) .input-prefix {
  color: #667eea;
}

:deep(.styled-input .el-input__inner) {
  color: #2d3748;
  font-size: 15px;
  font-weight: 400;
}

:deep(.styled-input .el-input__inner::placeholder) {
  color: #a0aec0;
}

/* 密码显示按钮样式 */
:deep(.styled-input .el-input__suffix) {
  right: 16px;
}

:deep(.styled-input .el-input__password) {
  color: #718096;
}

.terms-section {
  margin: 25px 0;
  text-align: center;
  padding: 15px;
  background-color: #f7fafc;
  border-radius: 12px;
  border: 1px solid #e2e8f0;
}

.terms-checkbox :deep(.el-checkbox__label) {
  color: #4a5568;
  font-size: 14px;
  line-height: 1.6;
  font-weight: 400;
}

.terms-link {
  font-size: 14px;
  margin: 0 2px;
  font-weight: 500;
  text-decoration: none;
}

.terms-link:hover {
  text-decoration: underline;
}

.submit-section {
  margin-bottom: 0;
}

.register-button {
  width: 100%;
  height: 54px;
  border-radius: 14px;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  border: none;
  font-size: 16px;
  font-weight: 600;
  letter-spacing: 0.5px;
  transition: all 0.3s ease;
  color: #ffffff;
  text-shadow: 0 1px 2px rgba(0, 0, 0, 0.1);
  box-shadow: 0 4px 15px rgba(102, 126, 234, 0.3);
}

.register-button:hover:not(:disabled) {
  transform: translateY(-2px);
  box-shadow: 0 8px 25px rgba(102, 126, 234, 0.4);
}

.register-button:active:not(:disabled) {
  transform: translateY(0);
}

.register-button:disabled {
  opacity: 0.5;
  cursor: not-allowed;
  background: #cbd5e0;
  color: #a0aec0;
  box-shadow: none;
}

.login-link-section {
  text-align: center;
  padding-top: 25px;
  border-top: 1px solid #e2e8f0;
}

.login-text {
  margin: 0 0 10px;
  color: #4a5568;
  font-size: 14px;
  font-weight: 400;
}

.login-link-button {
  font-size: 15px;
  font-weight: 600;
  padding: 0;
  color: #667eea;
}

.login-link-button:hover {
  color: #553c9a;
}

/* 表单验证错误样式 */
:deep(.el-form-item__error) {
  font-size: 12px;
  margin-top: 6px;
  color: #e53e3e;
  font-weight: 400;
  background: rgba(229, 62, 62, 0.1);
  padding: 4px 8px;
  border-radius: 6px;
  border-left: 3px solid #e53e3e;
}

/* 复选框样式优化 */
:deep(.el-checkbox__input.is-checked .el-checkbox__inner) {
  background-color: #667eea;
  border-color: #667eea;
}

:deep(.el-checkbox__inner:hover) {
  border-color: #667eea;
}

/* 响应式设计 */
@media (max-width: 1024px) {
  .register-wrapper {
    flex-direction: column;
    max-width: 500px;
    min-height: auto;
  }
  
  .welcome-panel {
    padding: 40px 30px 30px;
  }
  
  .benefits-list {
    display: none;
  }
  
  .testimonial {
    display: none;
  }
  
  .welcome-title {
    font-size: 28px;
  }
}

@media (max-width: 768px) {
  .register-container {
    padding: 20px;
  }
  
  .register-wrapper {
    width: 100%;
    min-height: auto;
    border-radius: 16px;
  }
  
  .welcome-panel {
    padding: 30px 20px 20px;
  }
  
  .form-container {
    padding: 20px;
  }
  
  .welcome-title {
    font-size: 24px;
  }
  
  .register-title {
    font-size: 24px;
  }
  
  .logo-container {
    width: 60px;
    height: 60px;
  }
}

@media (max-width: 480px) {
  .register-wrapper {
    margin: 10px;
    width: calc(100% - 20px);
  }
  
  .form-container {
    padding: 15px;
  }
  
  .welcome-panel {
    padding: 25px 15px 15px;
  }
  
  :deep(.styled-input .el-input__wrapper) {
    height: 48px;
    padding-left: 45px;
  }
  
  .input-prefix {
    left: 14px;
    font-size: 16px;
  }
  
  .register-button {
    height: 48px;
    font-size: 15px;
  }
}

/* 卡片样式覆盖 */
:deep(.el-card__body) {
  padding: 45px !important;
}

:deep(.el-form-item) {
  margin-bottom: 0;
}

/* 加载状态优化 */
:deep(.el-button.is-loading) {
  pointer-events: none;
}

/* 焦点状态优化 */
:deep(.el-input.is-focus .el-input__wrapper) {
  box-shadow: 0 0 0 3px rgba(102, 126, 234, 0.1) !important;
}

/* 链接悬停效果 */
.terms-link:hover,
.login-link-button:hover {
  transform: translateY(-1px);
  transition: all 0.2s ease;
}

/* 平滑滚动 */
.register-container {
  scroll-behavior: smooth;
}

/* 高对比度模式支持 */
@media (prefers-contrast: high) {
  .welcome-title,
  .welcome-subtitle,
  .benefit-content h4,
  .benefit-content p,
  .testimonial-content p,
  .testimonial-author span {
    text-shadow: 0 0 4px rgba(0, 0, 0, 0.8);
  }
  
  .register-title {
    color: #000000;
  }
  
  .register-description {
    color: #2d3748;
  }
}

/* 动画性能优化 */
.element,
.benefit-item,
.register-button {
  will-change: transform;
}

/* 无障碍支持 */
@media (prefers-reduced-motion: reduce) {
  * {
    animation-duration: 0.01ms !important;
    animation-iteration-count: 1 !important;
    transition-duration: 0.01ms !important;
  }
}
</style>
<!-- <style scoped>
.register-container {
  position: relative;
  min-height: 100vh;
  background: linear-gradient(135deg, #a8edea 0%, #fed6e3 100%);
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

.floating-elements {
  position: relative;
  width: 100%;
  height: 100%;
}

.element {
  position: absolute;
  background: rgba(255, 255, 255, 0.1);
  border-radius: 50%;
  animation: float 8s ease-in-out infinite;
}

.element-1 {
  width: 120px;
  height: 120px;
  top: 15%;
  left: 10%;
  animation-delay: 0s;
}

.element-2 {
  width: 80px;
  height: 80px;
  top: 70%;
  right: 20%;
  animation-delay: 3s;
}

.element-3 {
  width: 60px;
  height: 60px;
  top: 40%;
  right: 10%;
  animation-delay: 6s;
}

@keyframes float {
  0%, 100% {
    transform: translateY(0px) scale(1);
    opacity: 0.7;
  }
  50% {
    transform: translateY(-30px) scale(1.1);
    opacity: 1;
  }
}

/* 主容器 */
.register-wrapper {
  position: relative;
  z-index: 2;
  display: flex;
  width: 90%;
  max-width: 1200px;
  min-height: 700px;
  background: rgba(255, 255, 255, 0.1);
  backdrop-filter: blur(20px);
  border-radius: 24px;
  border: 1px solid rgba(255, 255, 255, 0.2);
  box-shadow: 0 25px 50px rgba(0, 0, 0, 0.1);
  overflow: hidden;
}

/* 左侧欢迎面板 */
.welcome-panel {
  flex: 1;
  background: linear-gradient(135deg, rgba(255, 255, 255, 0.1) 0%, rgba(255, 255, 255, 0.05) 100%);
  padding: 60px 50px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  color: white;
}

.welcome-header {
  text-align: center;
  margin-bottom: 50px;
}

.logo-container {
  width: 70px;
  height: 70px;
  background: rgba(255, 255, 255, 0.2);
  border-radius: 16px;
  display: flex;
  align-items: center;
  justify-content: center;
  margin: 0 auto 20px;
  backdrop-filter: blur(10px);
}

.welcome-title {
  font-size: 32px;
  font-weight: 700;
  margin: 0 0 12px;
  text-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
}

.welcome-subtitle {
  font-size: 16px;
  opacity: 0.9;
  margin: 0;
}

.benefits-list {
  margin-bottom: 50px;
}

.benefit-item {
  display: flex;
  align-items: flex-start;
  margin-bottom: 30px;
  transition: all 0.3s ease;
}

.benefit-item:hover {
  transform: translateX(8px);
}

.benefit-icon {
  width: 40px;
  height: 40px;
  background: rgba(255, 255, 255, 0.2);
  border-radius: 10px;
  display: flex;
  align-items: center;
  justify-content: center;
  margin-right: 20px;
  flex-shrink: 0;
  backdrop-filter: blur(10px);
}

.benefit-content h4 {
  font-size: 18px;
  font-weight: 600;
  margin: 0 0 5px;
}

.benefit-content p {
  font-size: 14px;
  opacity: 0.9;
  margin: 0;
  line-height: 1.5;
}

.testimonial {
  background: rgba(255, 255, 255, 0.1);
  border-radius: 16px;
  padding: 25px;
  backdrop-filter: blur(10px);
  border: 1px solid rgba(255, 255, 255, 0.2);
}

.testimonial-content p {
  font-size: 16px;
  font-style: italic;
  margin: 0 0 15px;
  line-height: 1.6;
}

.testimonial-author span {
  font-size: 14px;
  opacity: 0.8;
}

/* 右侧表单容器 */
.form-container {
  flex: 1;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 50px;
  background: rgba(255, 255, 255, 0.05);
}

.register-card {
  width: 100%;
  max-width: 420px;
  background: rgba(255, 255, 255, 0.95) !important;
  backdrop-filter: blur(20px);
  border-radius: 20px;
  border: none;
  box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
}

.register-header {
  text-align: center;
  margin-bottom: 35px;
}

.register-title {
  font-size: 28px;
  font-weight: 700;
  color: #2c3e50;
  margin: 0 0 10px;
}

.register-description {
  font-size: 15px;
  color: #7f8c8d;
  margin: 0;
}

.register-form {
  margin-bottom: 25px;
}

.input-row {
  margin-bottom: 20px;
}

.input-wrapper {
  position: relative;
  display: flex;
  align-items: center;
}

.input-prefix {
  position: absolute;
  left: 15px;
  z-index: 3;
  color: #7f8c8d;
  font-size: 18px;
}

:deep(.styled-input .el-input__wrapper) {
  padding-left: 50px;
  height: 52px;
  border-radius: 14px;
  background-color: #f8f9fa;
  border: 2px solid transparent;
  box-shadow: none;
  transition: all 0.3s ease;
}

:deep(.styled-input .el-input__wrapper:hover) {
  background-color: #e9ecef;
  border-color: rgba(168, 237, 234, 0.3);
}

:deep(.styled-input.is-focus .el-input__wrapper) {
  border-color: #a8edea;
  background-color: #fff;
  box-shadow: 0 0 0 3px rgba(168, 237, 234, 0.15);
}

:deep(.styled-input .el-input__inner) {
  color: #2c3e50;
  font-size: 15px;
}

:deep(.styled-input .el-input__inner::placeholder) {
  color: #adb5bd;
}

.terms-section {
  margin: 25px 0;
  text-align: center;
}

.terms-checkbox :deep(.el-checkbox__label) {
  color: #6c757d;
  font-size: 14px;
  line-height: 1.5;
}

.terms-link {
  font-size: 14px;
  margin: 0 2px;
}

.submit-section {
  margin-bottom: 0;
}

.register-button {
  width: 100%;
  height: 52px;
  border-radius: 14px;
  background: linear-gradient(135deg, #a8edea 0%, #fed6e3 100%);
  border: none;
  font-size: 16px;
  font-weight: 600;
  letter-spacing: 0.5px;
  transition: all 0.3s ease;
  color: #2c3e50;
}

.register-button:hover:not(:disabled) {
  transform: translateY(-2px);
  box-shadow: 0 10px 30px rgba(168, 237, 234, 0.4);
}

.register-button:disabled {
  opacity: 0.6;
  cursor: not-allowed;
}

.login-link-section {
  text-align: center;
  padding-top: 20px;
  border-top: 1px solid #e9ecef;
}

.login-text {
  margin: 0 0 10px;
  color: #6c757d;
  font-size: 14px;
}

.login-link-button {
  font-size: 15px;
  font-weight: 600;
  padding: 0;
}

/* 响应式设计 */
@media (max-width: 1024px) {
  .register-wrapper {
    flex-direction: column;
    max-width: 500px;
  }
  
  .welcome-panel {
    padding: 40px 30px 30px;
  }
  
  .benefits-list {
    display: none;
  }
  
  .testimonial {
    display: none;
  }
}

@media (max-width: 768px) {
  .register-container {
    padding: 20px;
  }
  
  .register-wrapper {
    width: 100%;
    min-height: auto;
  }
  
  .welcome-panel {
    padding: 30px 20px 20px;
  }
  
  .form-container {
    padding: 20px;
  }
  
  .welcome-title {
    font-size: 26px;
  }
  
  .register-title {
    font-size: 24px;
  }
}

/* 卡片样式覆盖 */
:deep(.el-card__body) {
  padding: 45px !important;
}

:deep(.el-form-item) {
  margin-bottom: 0;
}

:deep(.el-form-item__error) {
  font-size: 12px;
  margin-top: 5px;
}
</style> -->