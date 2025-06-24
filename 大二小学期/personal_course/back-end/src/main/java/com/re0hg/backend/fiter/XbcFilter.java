package com.re0hg.backend.fiter;

import jakarta.servlet.*;
import java.io.IOException;

//@WebFilter(urlPatterns = "/*")
public class XbcFilter implements Filter {
    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        System.out.println("Abc 拦截到了请求...放行前逻辑");
        //放行
        chain.doFilter(request,response);

        System.out.println("Abc 拦截到了请求...放行后逻辑");
    }
}
