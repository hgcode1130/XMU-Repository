package com.re0hg.backend.config;

import com.re0hg.backend.interceptor.LoginCheckInterceptor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration // 配置类
public class WebConfig implements WebMvcConfigurer {

    @Autowired
    private LoginCheckInterceptor loginCheckInterceptor;

    // 添加拦截器
    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(loginCheckInterceptor)
                .addPathPatterns("/**")
                .excludePathPatterns("/api/auth/**");
    }

    /**
     * 添加此方法来配置全局CORS
     */
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/**") // 对所有路径应用CORS规则
                .allowedOrigins("http://localhost:5173") // 【重要】允许你的前端源，请根据实际情况修改端口
                .allowedMethods("GET", "POST", "PUT", "DELETE", "OPTIONS") // 允许所有常用方法
                .allowedHeaders("*") // 允许所有请求头
                .allowCredentials(true); // 允许携带凭证（如cookies）
    }
}
