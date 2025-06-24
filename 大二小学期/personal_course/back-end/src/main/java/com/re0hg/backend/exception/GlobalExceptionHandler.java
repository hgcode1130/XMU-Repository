package com.re0hg.backend.exception;

import com.re0hg.backend.pojo.Result;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

/**
 * 全局异常处理器
 */
@RestControllerAdvice // = @ControllerAdvice + @ResponseBody
public class GlobalExceptionHandler {

    @ExceptionHandler(Exception.class)//捕获所有异常
    public Result ex(Exception ex){
        ex.printStackTrace();
        return Result.error(500,"对不起,操作失败,请联系管理员");
    }
}
