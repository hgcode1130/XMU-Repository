/**
 * 控制器接口
 * 定义控制器基本行为
 * MVC架构中Controller层的基础接口
 */
package com.re0hg.notepad_re0hg.controller;

/**
 * 所有控制器类的基础接口
 * 定义控制器的通用行为
 */
public interface Controller {

    /**
     * 初始化控制器
     * 在控制器创建后调用，用于设置初始状态和绑定事件
     */
    void initialize();

    /**
     * 获取控制器名称
     * 用于标识和注册控制器
     * 
     * @return 控制器的唯一名称
     */
    String getName();
}
