package com.re0hg.backend.fiter;

import jakarta.servlet.*;
import jakarta.servlet.annotation.WebFilter;

import java.io.IOException;

/**
 * @author re0hg
 * @version 1.0
 * @date 2025/4/24
 */

//@WebFilter(urlPatterns = "/*")
public class DemoFilter implements Filter {
    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        System.out.println("DemoFilter doFilter");

        filterChain.doFilter(servletRequest, servletResponse);
    }
}
