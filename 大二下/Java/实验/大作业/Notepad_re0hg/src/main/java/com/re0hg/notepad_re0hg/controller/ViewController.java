/**
 * 视图控制器类
 * 处理视图相关的设置和操作
 * MVC架构中处理UI视图设置的Controller
 */
package com.re0hg.notepad_re0hg.controller;

import com.re0hg.notepad_re0hg.model.AppModel;

import javafx.scene.control.CheckMenuItem;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

/**
 * 视图控制器类
 * 处理状态栏显示、缩放等UI视图相关功能
 */
public class ViewController implements Controller {

    // 应用模型
    private final AppModel appModel;

    // 主窗口
    private final Stage stage;

    // 状态栏标签
    private Label statusLabel;

    // 状态栏是否可见
    private boolean statusBarVisible = true;

    // 缩放百分比
    private int zoomPercentage = 100;

    // 文档控制器引用
    private DocumentController documentController;

    /**
     * 构造函数
     * 
     * @param appModel 应用模型
     * @param stage    主窗口
     */
    public ViewController(AppModel appModel, Stage stage) {
        this.appModel = appModel;
        this.stage = stage;
    }

    @Override
    public void initialize() {
        // 视图控制器初始化
    }

    @Override
    public String getName() {
        return "viewController";
    }

    /**
     * 设置文档控制器引用
     * 
     * @param documentController 文档控制器
     */
    public void setDocumentController(DocumentController documentController) {
        this.documentController = documentController;
    }

    /**
     * 设置状态栏标签
     * 
     * @param statusLabel 状态栏标签
     */
    public void setStatusLabel(Label statusLabel) {
        this.statusLabel = statusLabel;
        updateStatusBar();
    }

    /**
     * 切换状态栏可见性
     * 
     * @param visible 状态栏是否可见
     */
    public void toggleStatusBar(boolean visible) {
        this.statusBarVisible = visible;
        if (statusLabel != null) {
            statusLabel.setVisible(visible);
            statusLabel.setManaged(visible);
        }
    }

    /**
     * 获取状态栏可见性
     * 
     * @return 状态栏是否可见
     */
    public boolean isStatusBarVisible() {
        return statusBarVisible;
    }

    /**
     * 更新状态栏信息
     */
    public void updateStatusBar() {
        if (statusLabel != null && statusBarVisible) {
            TextArea textArea = documentController != null ? documentController.getTextArea() : null;
            if (textArea != null) {
                String text = textArea.getText();
                int caretPosition = textArea.getCaretPosition();

                // 计算当前行和列
                int line = 1;
                int col = 1;
                for (int i = 0; i < caretPosition; i++) {
                    if (i < text.length() && text.charAt(i) == '\n') {
                        line++;
                        col = 1;
                    } else {
                        col++;
                    }
                }

                // 更新状态栏文本
                statusLabel.setText("行 " + line + "，列 " + col + " | " + zoomPercentage + "% | UTF-8");
            }
        }
    }

    /**
     * 设置缩放百分比
     * 
     * @param percentage 缩放百分比
     */
    public void setZoomPercentage(int percentage) {
        if (percentage >= 10 && percentage <= 500) {
            zoomPercentage = percentage;

            // 更新字体大小
            if (documentController != null) {
                TextArea textArea = documentController.getTextArea();
                if (textArea != null) {
                    double baseSize = appModel.getConfig().getFontSize();
                    double newSize = baseSize * percentage / 100.0;

                    // 更新字体大小
                    textArea.setStyle("-fx-font-size: " + newSize + "pt;");
                }
            }

            // 更新状态栏
            updateStatusBar();
        }
    }

    /**
     * 放大文本
     */
    public void zoomIn() {
        setZoomPercentage(Math.min(500, zoomPercentage + 10));
    }

    /**
     * 缩小文本
     */
    public void zoomOut() {
        setZoomPercentage(Math.max(10, zoomPercentage - 10));
    }

    /**
     * 重置缩放
     */
    public void resetZoom() {
        setZoomPercentage(100);
    }

    /**
     * 获取当前缩放百分比
     * 
     * @return 缩放百分比
     */
    public int getZoomPercentage() {
        return zoomPercentage;
    }
}
