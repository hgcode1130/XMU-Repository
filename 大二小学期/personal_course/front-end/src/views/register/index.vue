<template>
  <div class="register-container">
    <el-card class="register-card">
      <template #header>
        <div class="card-header">
          <span>欢迎注册 - 个人课表系统</span>
        </div>
      </template>
      <el-form
        ref="registerFormRef"
        :model="registerForm"
        :rules="registerRules"
        label-width="100px"
      >
        <el-form-item label="用户名" prop="username">
          <el-input
            v-model="registerForm.username"
            placeholder="请输入用户名"
          />
        </el-form-item>
                <el-form-item label="邮箱" prop="email">
          <el-input v-model="registerForm.email" placeholder="请输入邮箱" />
        </el-form-item>
        <el-form-item label="密码" prop="password">
          <el-input
            type="password"
            v-model="registerForm.password"
            show-password
            placeholder="请输入密码"
          />
        </el-form-item>
        <el-form-item label="确认密码" prop="confirmPassword">
          <el-input
            type="password"
            v-model="registerForm.confirmPassword"
            show-password
            placeholder="请再次输入密码"
          />
        </el-form-item>
        <el-form-item>
          <el-button
            type="primary"
            style="width: 100%"
            @click="handleRegister"
            :loading="loading"
          >
            注 册
          </el-button>
        </el-form-item>
        <div class="login-link">
          <el-link type="primary" @click="goToLogin"
            >已有账号？立即登录</el-link
          >
        </div>
      </el-form>
    </el-card>
  </div>
</template>

<script setup>
import { ref, reactive } from 'vue'
import { ElMessage } from 'element-plus'
import { useRouter } from 'vue-router'
import { registerApi } from '@/api/auth' // 【修改】1. 引入真实的注册API

const router = useRouter()
const registerFormRef = ref(null)
const loading = ref(false)

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
    { min: 3, max: 10, message: '用户名长度应为 3 到 10 个字符', trigger: 'blur' },
  ],
    email: [ //email 验证规则
    { required: true, message: '请输入邮箱地址', trigger: 'blur' },
    { type: 'email', message: '请输入正确的邮箱地址', trigger: ['blur', 'change'] },
  ],
  password: [
    { required: true, message: '请输入密码', trigger: 'blur' },
    { min: 6, message: '密码长度不能少于6位', trigger: 'blur' },
  ],
  confirmPassword: [{ required: true, validator: validatePass, trigger: 'blur' }],
}

// 【修改】2. 修改 handleRegister 方法，调用真实 API
const handleRegister = () => {
  registerFormRef.value.validate(async (valid) => {
    if (valid) {
      loading.value = true
      try {
        // 准备提交给后端的数据
        const data = {
          username: registerForm.username,
          password: registerForm.password,
          email: registerForm.email,
        }
        // 调用API
        await registerApi(data)
        ElMessage.success('注册成功！即将跳转到登录页...')
        // 注册成功后，延时一会再跳转，给用户看提示的时间
        setTimeout(() => {
          router.push('/login')
        }, 1500)
      } catch (error) {
        // API调用失败，错误信息会由 request.js 中的响应拦截器统一弹出
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
  router.push('/login') // 导航到登录页面
}
</script>

<style scoped>
.register-container {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100vh;
  background-image: linear-gradient(to top, #a8edea 0%, #fed6e3 100%);
}

.register-card {
  width: 480px;
  border-radius: 15px;
  box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
  background-color: rgba(255, 255, 255, 0.9);
}

.card-header {
  text-align: center;
  font-size: 24px;
  font-weight: 600;
  color: #333;
}

.el-form-item {
  margin-bottom: 25px;
}

.el-button {
  border-radius: 8px;
  font-size: 16px;
  letter-spacing: 2px;
}

.login-link {
  text-align: center;
  margin-top: -10px;
  font-size: 14px;
  color: #606266;
}
</style>