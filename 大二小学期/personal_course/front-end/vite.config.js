import { fileURLToPath, URL } from 'node:url'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    vue(),
  ],
  resolve: {
    alias: {
      // 【关键配置】
      // 这行代码告诉 Vite，所有以 '@' 开头的路径，
      // 都应该从项目的 'src' 目录开始解析。
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  },
  server: {
    // 【可选配置】
    // 配置开发服务器的代理，用于解决跨域问题
    // 我们的 request.js 中 baseURL 设置为 '/api'，
    // Vite 会将所有 /api 开头的请求转发到 http://localhost:8080
    proxy: {
      '/api': {
        // 【重要】这里要换成您后端服务器的真实地址
        target: 'http://localhost:8080', 
        changeOrigin: true,
        // 如果您的后端接口路径本身就带 /api，就不需要重写
        // 如果后端接口是 /users, 而前端请求是 /api/users，就需要重写掉 /api
        // rewrite: (path) => path.replace(/^\/api/, '') 
      }
    }
  }
})
