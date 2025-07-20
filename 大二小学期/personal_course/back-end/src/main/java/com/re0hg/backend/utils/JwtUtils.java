package com.re0hg.backend.utils;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import jakarta.servlet.http.HttpServletRequest;
import lombok.extern.slf4j.Slf4j;

import java.util.Date;
import java.util.Map;

@Slf4j
public class JwtUtils {

    private static String signKey = "re0hgsupersecretkeythatislongenoughforhs256";
    private static Long expire = 43200000L;

    /**
     * 生成JWT令牌
     * 
     * @param claims JWT第二部分负载 payload 中存储的内容
     * @return
     */
    public static String generateJwt(Map<String, Object> claims) {
        String jwt = Jwts.builder()
                .addClaims(claims)
                .signWith(SignatureAlgorithm.HS256, signKey)
                .setExpiration(new Date(System.currentTimeMillis() + expire))
                .compact();
        return jwt;
    }

    /**
     * 解析JWT令牌
     * 
     * @param jwt JWT令牌
     * @return JWT第二部分负载 payload 中存储的内容
     */
    public static Claims parseJWT(String jwt) {
        Claims claims = Jwts.parser()
                .setSigningKey(signKey)
                .parseClaimsJws(jwt)
                .getBody();
        return claims;
    }

    public static Long getCurrentUserId(HttpServletRequest request) {
        try {
            // 1. 获取请求头中的token
            String token = request.getHeader("token");

            if (token == null || token.trim().isEmpty()) {
                log.warn("请求头中缺少token信息");
                return null;
            }

            // 2. 解析JWT token
            Claims claims = JwtUtils.parseJWT(token);

            // 3. 从claims中获取用户ID
            Object idObj = claims.get("id");
            if (idObj == null) {
                log.warn("JWT token中缺少用户ID信息");
                return null;
            }

            // 4. 转换为Long类型
            Long userId;
            if (idObj instanceof Integer) {
                userId = ((Integer) idObj).longValue();
            } else if (idObj instanceof Long) {
                userId = (Long) idObj;
            } else if (idObj instanceof String) {
                userId = Long.parseLong((String) idObj);
            } else {
                log.warn("JWT token中用户ID格式不正确: {}", idObj.getClass());
                return null;
            }

            log.debug("成功解析用户ID: {}", userId);
            return userId;
        } catch (Exception e) {
            log.error("解析JWT token失败: ", e);
            return null;
        }
    }
}
