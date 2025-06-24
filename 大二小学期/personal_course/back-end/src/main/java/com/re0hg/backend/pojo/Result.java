package com.re0hg.backend.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class Result {
    private Integer code;// 响应码
    private String msg; // 响应信息 描述字符串
    private Object data; // 返回的数据

    // 增删改 成功响应
    public static Result success(int code, String meg) {
        return new Result(code, meg, null);
    }

    // 查询 成功响应
    public static Result success(int code, String meg, Object data) {
        return new Result(code, meg, data);
    }

    // 失败响应
    public static Result error(int code, String msg) {
        return new Result(code, msg, null);
    }
}
