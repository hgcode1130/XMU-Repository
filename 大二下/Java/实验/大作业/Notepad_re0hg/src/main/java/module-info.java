/**
 * 记事本应用程序模块定义
 * 声明了应用程序的模块依赖关系和导出配置
 * 修改后支持MVC架构
 */
module com.re0hg.notepad_re0hg {
    // 引入JavaFX控件库，提供UI组件支持
    requires transitive javafx.controls;

    // 引入JavaFX的FXML支持，用于加载和解析FXML界面文件
    requires javafx.fxml;

    // 明确引入JavaFX图形库，以便访问Stage等类
    requires transitive javafx.graphics;

    // 使用传递关键字确保依赖可被导出
    requires transitive javafx.base;

    // 引入logging库，用于记录日志
    requires java.logging;

    // 引入Java桌面API，用于访问系统字体等资源
    requires java.desktop;

    // 打开包以允许JavaFX的FXML加载器通过反射访问包中的类和成员
    opens com.re0hg.notepad_re0hg to javafx.fxml;

    // 打开MVC相关包以允许JavaFX的FXML加载器访问
    opens com.re0hg.notepad_re0hg.controller to javafx.fxml;
    opens com.re0hg.notepad_re0hg.model to javafx.fxml;
    opens com.re0hg.notepad_re0hg.utils to javafx.fxml;

    // 导出包，使包中的类可以被其他模块访问
    exports com.re0hg.notepad_re0hg;
    exports com.re0hg.notepad_re0hg.controller;
    exports com.re0hg.notepad_re0hg.model;
    exports com.re0hg.notepad_re0hg.utils;
}