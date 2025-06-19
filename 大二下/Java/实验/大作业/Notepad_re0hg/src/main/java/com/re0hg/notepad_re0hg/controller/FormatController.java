/**
 * 格式控制器类
 * 处理文本格式相关的操作，如字体设置、自动换行等
 * MVC架构中处理格式设置的Controller
 */
package com.re0hg.notepad_re0hg.controller;

import com.re0hg.notepad_re0hg.model.AppModel;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.stage.Modality;
import javafx.stage.Stage;

/**
 * 格式控制器类
 * 处理文本格式设置，如字体、自动换行等
 */
public class FormatController implements Controller {

    // 应用模型
    private final AppModel appModel;

    // 主窗口
    private final Stage stage;

    // 字体选择窗口
    private Stage fontStage;

    // 文档控制器引用
    private DocumentController documentController;

    /**
     * 构造函数
     * 
     * @param appModel 应用模型
     * @param stage    主窗口
     */
    public FormatController(AppModel appModel, Stage stage) {
        this.appModel = appModel;
        this.stage = stage;
    }

    @Override
    public void initialize() {
        // 初始化格式控制器
    }

    @Override
    public String getName() {
        return "formatController";
    }

    /**
     * 检查是否启用了自动换行
     * 
     * @return 自动换行是否启用
     */
    public boolean isWordWrap() {
        return appModel.getConfig().isWordWrap();
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
     * 切换自动换行
     * 
     * @param wrap 是否自动换行
     */
    public void toggleWordWrap(boolean wrap) {
        if (documentController != null) {
            documentController.setWordWrap(wrap);
            appModel.getConfig().setWordWrap(wrap);
        }
    }

    /**
     * 显示字体选择对话框
     */
    public void showFontChooser() {
        try {
            if (fontStage == null) {
                // 创建字体选择器窗口
                fontStage = new Stage();
                fontStage.initModality(Modality.APPLICATION_MODAL);
                fontStage.initOwner(stage);
                fontStage.setTitle("字体");
                fontStage.setResizable(false);

                // 加载字体选择器FXML
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/re0hg/notepad_re0hg/font.fxml"));
                javafx.scene.layout.Pane root = loader.load(); // 获取并设置控制器
                FontController controller = loader.getController();
                controller.setFormatController(this);

                // 设置场景
                Scene scene = new Scene(root);
                fontStage.setScene(scene);
            }

            // 显示字体选择器
            fontStage.showAndWait();
        } catch (Exception e) {
            showErrorAlert("字体选择器", "无法打开字体选择器", e.getMessage());
            e.printStackTrace();
        }
    }

    /**
     * 应用字体设置
     * 
     * @param fontFamily  字体系列
     * @param fontWeight  字体粗细
     * @param fontPosture 字体姿态（如斜体）
     * @param fontSize    字体大小
     * @param fontColor   字体颜色
     */
    public void applyFont(String fontFamily, FontWeight fontWeight, FontPosture fontPosture, double fontSize,
            Color fontColor) {
        // 创建新字体
        Font font = Font.font(fontFamily, fontWeight, fontPosture, fontSize);

        // 更新应用配置
        appModel.getConfig().setFont(font);
        appModel.getConfig().setFontColor(String.format("#%02X%02X%02X",
                (int) (fontColor.getRed() * 255),
                (int) (fontColor.getGreen() * 255),
                (int) (fontColor.getBlue() * 255)));

        // 更新文档控制器
        if (documentController != null) {
            documentController.updateFont();
        }
    }

    /**
     * 获取当前字体
     * 
     * @return 当前字体
     */
    public Font getCurrentFont() {
        if (documentController != null && documentController.getTextArea() != null) {
            return documentController.getTextArea().getFont();
        } else if (appModel != null && appModel.getConfig().getFont() != null) {
            return appModel.getConfig().getFont();
        }
        return Font.font("宋体", 14);
    }

    /**
     * 获取当前文本颜色
     * 
     * @return 当前文本颜色
     */
    public Color getCurrentTextColor() {
        if (appModel != null && appModel.getConfig().getFontColor() != null) {
            try {
                return Color.web(appModel.getConfig().getFontColor());
            } catch (Exception e) {
                return Color.BLACK;
            }
        }
        return Color.BLACK;
    }

    /**
     * 设置字体和颜色
     * 
     * @param font  字体
     * @param color 颜色
     */
    public void setFont(Font font, Color color) {
        // 获取字体样式
        String style = font.getStyle().toLowerCase();
        FontWeight weight = style.contains("bold") ? FontWeight.BOLD : FontWeight.NORMAL;
        FontPosture posture = (style.contains("italic") || style.contains("oblique")) ? FontPosture.ITALIC
                : FontPosture.REGULAR;

        // 应用字体设置
        applyFont(font.getFamily(), weight, posture, font.getSize(), color);
    }

    /**
     * 显示错误提示对话框
     * 
     * @param title   标题
     * @param header  头部信息
     * @param content 详细内容
     */
    private void showErrorAlert(String title, String header, String content) {
        Alert alert = new Alert(AlertType.ERROR);
        alert.setTitle(title);
        alert.setHeaderText(header);
        alert.setContentText(content);
        alert.showAndWait();
    }
}
