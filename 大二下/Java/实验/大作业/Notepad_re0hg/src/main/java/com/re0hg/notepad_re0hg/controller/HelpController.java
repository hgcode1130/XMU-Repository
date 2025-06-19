/**
 * 帮助控制器类
 * 处理帮助菜单相关功能
 * MVC架构中处理帮助和关于对话框的Controller
 */
package com.re0hg.notepad_re0hg.controller;

import com.re0hg.notepad_re0hg.model.AppModel;

import javafx.application.HostServices;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.TextArea;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Priority;
import javafx.stage.Stage;

/**
 * 帮助控制器类
 * 处理帮助菜单项和关于对话框
 */
public class HelpController implements Controller { // 主窗口引用，用于对话框的所有者设置
    // 主机服务，用于打开外部链接
    private HostServices hostServices;

    /**
     * 构造函数
     * 
     * @param appModel 应用模型（未使用）
     * @param stage    主窗口
     */
    public HelpController(AppModel appModel, Stage stage) {
        // 构造函数参数保留以保持一致性，但实际未使用
    }

    @Override
    public void initialize() {
        // 帮助控制器初始化
    }

    @Override
    public String getName() {
        return "helpController";
    }

    /**
     * 设置主机服务
     * 
     * @param hostServices JavaFX主机服务
     */
    public void setHostServices(HostServices hostServices) {
        this.hostServices = hostServices;
    }

    /**
     * 显示帮助内容
     */
    public void showHelp() {
        // 在浏览器中打开帮助页面或显示帮助对话框
        if (hostServices != null) {
            // 如果有帮助网页，可以在浏览器中打开
            // hostServices.showDocument("https://example.com/help");

            // 或者显示本地帮助对话框
            showHelpDialog();
        } else {
            showHelpDialog();
        }
    }

    /**
     * 显示本地帮助对话框
     */
    private void showHelpDialog() {
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle("帮助");
        alert.setHeaderText("记事本使用帮助");

        // 帮助内容
        String helpContent = "记事本使用指南：\n\n" +
                "文件菜单：\n" +
                "- 新建(Ctrl+N)：创建新文档\n" +
                "- 打开(Ctrl+O)：打开现有文档\n" +
                "- 保存(Ctrl+S)：保存当前文档\n" +
                "- 另存为(Ctrl+Shift+S)：将文档保存为新文件\n\n" +
                "编辑菜单：\n" +
                "- 撤销(Ctrl+Z)：撤销上一步操作\n" +
                "- 恢复(Ctrl+Y)：重做被撤销的操作\n" +
                "- 剪切(Ctrl+X)：剪切选定内容\n" +
                "- 复制(Ctrl+C)：复制选定内容\n" +
                "- 粘贴(Ctrl+V)：粘贴剪贴板内容\n" +
                "- 查找(Ctrl+F)：查找文本\n" +
                "- 替换(Ctrl+H)：查找并替换文本\n\n" +
                "格式菜单：\n" +
                "- 字体：设置文本字体、样式和大小\n" +
                "- 自动换行：开启/关闭文本自动换行\n\n" +
                "查看菜单：\n" +
                "- 状态栏：显示/隐藏状态栏\n\n" +
                "更多帮助请联系开发者。";

        // 创建可滚动的文本区域
        TextArea textArea = new TextArea(helpContent);
        textArea.setEditable(false);
        textArea.setWrapText(true);

        GridPane.setVgrow(textArea, Priority.ALWAYS);
        GridPane.setHgrow(textArea, Priority.ALWAYS);

        GridPane content = new GridPane();
        content.setMaxWidth(Double.MAX_VALUE);
        content.add(textArea, 0, 0);

        alert.getDialogPane().setContent(content);
        alert.getDialogPane().setPrefSize(500, 400);

        alert.showAndWait();
    }

    /**
     * 显示关于对话框
     */
    public void showAbout() {
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle("关于记事本");
        alert.setHeaderText("JavaFX记事本 v1.0");

        String aboutText = "JavaFX记事本\n" +
                "版本：1.0\n" +
                "作者：re0hg\n\n" +
                "基于JavaFX的简单文本编辑器，实现了记事本的核心功能。\n" +
                "采用MVC架构设计，具有良好的可扩展性和可维护性。\n\n" +
                "© 2025 All Rights Reserved.";

        alert.setContentText(aboutText);

        alert.showAndWait();
    }
}
