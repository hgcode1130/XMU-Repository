
import { createApp } from 'vue'

// 1. 引入根组件 App.vue
import App from './App.vue'

// 2. 引入路由配置
import router from './router'

// 3. 引入 Pinia 状态管理
// import { createPinia } from 'pinia'
import pinia from './stores' 

// 4. 完整引入 Element Plus UI 库及其样式
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'

// 5. 引入 Element Plus 的图标库
import * as ElementPlusIconsVue from '@element-plus/icons-vue'

// 6. (可选但推荐) 引入全局基础样式
import './assets/css/main.css'
// 【新增】引入主题样式文件
import './assets/css/theme.css'

// --- 开始组装应用 ---

// 首先，创建 Vue 应用实例
const app = createApp(App)

// 注册所有 Element Plus 图标，使其可以在项目任意组件中通过 <el-icon><IconName /></el-icon> 的方式使用
for (const [key, component] of Object.entries(ElementPlusIconsVue)) {
  app.component(key, component)
}

// 使用 Pinia
// app.use(createPinia())
app.use(pinia)

// 使用 Vue Router
app.use(router)

// 使用 Element Plus
app.use(ElementPlus)

// 最后，将配置好的应用挂载到 public/index.html 文件中 id 为 'app' 的 DOM 元素上
app.mount('#app')

