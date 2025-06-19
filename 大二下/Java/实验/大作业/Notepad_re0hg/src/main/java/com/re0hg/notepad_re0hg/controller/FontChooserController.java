/**
 * 字体选择器控制器类
 * 处理字体选择对话框的UI交互
 */
package com.re0hg.notepad_re0hg.controller;

import java.net.URL;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;

import com.re0hg.notepad_re0hg.model.AppModel;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;

/**
 * 字体选择器控制器类
 * 实现字体选择对话框的交互逻辑
 */
public class FontChooserController implements Initializable {

    @FXML
    private ListView<String> fontFamilyList;

    @FXML
    private ListView<String> fontStyleList;

    @FXML
    private ListView<String> fontSizeList;

    @FXML
    private CheckBox boldCheckBox;

    @FXML
    private CheckBox italicCheckBox;

    @FXML
    private Label previewLabel;

    // 格式控制器引用
    private FormatController formatController;

    // 应用模型引用
    private AppModel appModel;

    // 当前选择的字体属性
    private String selectedFontFamily;
    private FontWeight selectedFontWeight = FontWeight.NORMAL;
    private FontPosture selectedFontPosture = FontPosture.REGULAR;
    private double selectedFontSize = 12;
    private Color selectedFontColor = Color.BLACK;

    /**
     * 设置格式控制器引用
     * 
     * @param formatController 格式控制器
     */
    public void setFormatController(FormatController formatController) {
        this.formatController = formatController;
    }

    /**
     * 设置应用模型引用
     * 
     * @param appModel 应用模型
     */
    public void setAppModel(AppModel appModel) {
        this.appModel = appModel;
        initializeWithCurrentSettings();
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        // 加载字体系列列表
        List<String> fontFamilies = Font.getFamilies();
        fontFamilyList.setItems(FXCollections.observableArrayList(fontFamilies));

        // 设置字体样式列表
        fontStyleList.setItems(FXCollections.observableArrayList(
                "常规", "粗体", "斜体", "粗斜体"));

        // 设置字体大小列表
        List<String> fontSizes = Arrays.asList(
                "8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72");
        fontSizeList.setItems(FXCollections.observableArrayList(fontSizes));

        // 设置选择监听器
        setupListeners();
    }

    /**
     * 使用当前设置初始化界面
     */
    private void initializeWithCurrentSettings() {
        if (appModel != null) {
            Font currentFont = appModel.getConfig().getFont();
            if (currentFont != null) {
                // 设置字体系列
                selectedFontFamily = currentFont.getFamily();
                fontFamilyList.getSelectionModel().select(selectedFontFamily);

                // 设置字体大小
                selectedFontSize = currentFont.getSize();
                fontSizeList.getSelectionModel().select(String.valueOf((int) selectedFontSize));

                // 设置字体样式
                String fontStyle = getFontStyleName(
                        appModel.getConfig().getFontWeight(),
                        appModel.getConfig().getFontPosture());
                fontStyleList.getSelectionModel().select(fontStyle);

                // 设置字体效果
                boldCheckBox.setSelected(appModel.getConfig().getFontWeight() == FontWeight.BOLD);
                italicCheckBox.setSelected(appModel.getConfig().getFontPosture() == FontPosture.ITALIC);

                // 设置字体颜色
                String colorString = appModel.getConfig().getFontColor();
                selectedFontColor = (colorString != null) ? Color.web(colorString) : Color.BLACK;

                // 更新预览
                updatePreview();
            }
        }
    }

    /**
     * 设置列表选择监听器
     */
    private void setupListeners() {
        // 字体系列选择监听
        fontFamilyList.getSelectionModel().selectedItemProperty().addListener(
                (obs, oldValue, newValue) -> {
                    if (newValue != null) {
                        selectedFontFamily = newValue;
                        updatePreview();
                    }
                });

        // 字体样式选择监听
        fontStyleList.getSelectionModel().selectedItemProperty().addListener(
                (obs, oldValue, newValue) -> {
                    if (newValue != null) {
                        updateFontStyleFromSelection(newValue);
                        updatePreview();
                    }
                });

        // 字体大小选择监听
        fontSizeList.getSelectionModel().selectedItemProperty().addListener(
                (obs, oldValue, newValue) -> {
                    if (newValue != null) {
                        try {
                            selectedFontSize = Double.parseDouble(newValue);
                            updatePreview();
                        } catch (NumberFormatException e) {
                            // 忽略无效值
                        }
                    }
                });

        // 复选框监听
        boldCheckBox.selectedProperty().addListener(
                (obs, oldValue, newValue) -> {
                    selectedFontWeight = newValue ? FontWeight.BOLD : FontWeight.NORMAL;
                    updatePreview();
                });

        italicCheckBox.selectedProperty().addListener(
                (obs, oldValue, newValue) -> {
                    selectedFontPosture = newValue ? FontPosture.ITALIC : FontPosture.REGULAR;
                    updatePreview();
                });
    }

    /**
     * 根据字体样式名称更新字体属性
     * 
     * @param styleName 样式名称
     */
    private void updateFontStyleFromSelection(String styleName) {
        switch (styleName) {
            case "常规":
                selectedFontWeight = FontWeight.NORMAL;
                selectedFontPosture = FontPosture.REGULAR;
                boldCheckBox.setSelected(false);
                italicCheckBox.setSelected(false);
                break;
            case "粗体":
                selectedFontWeight = FontWeight.BOLD;
                selectedFontPosture = FontPosture.REGULAR;
                boldCheckBox.setSelected(true);
                italicCheckBox.setSelected(false);
                break;
            case "斜体":
                selectedFontWeight = FontWeight.NORMAL;
                selectedFontPosture = FontPosture.ITALIC;
                boldCheckBox.setSelected(false);
                italicCheckBox.setSelected(true);
                break;
            case "粗斜体":
                selectedFontWeight = FontWeight.BOLD;
                selectedFontPosture = FontPosture.ITALIC;
                boldCheckBox.setSelected(true);
                italicCheckBox.setSelected(true);
                break;
        }
    }

    /**
     * 根据字体属性获取样式名称
     * 
     * @param weight  字体粗细
     * @param posture 字体姿态
     * @return 样式名称
     */
    private String getFontStyleName(FontWeight weight, FontPosture posture) {
        if (weight == FontWeight.BOLD && posture == FontPosture.ITALIC) {
            return "粗斜体";
        } else if (weight == FontWeight.BOLD) {
            return "粗体";
        } else if (posture == FontPosture.ITALIC) {
            return "斜体";
        } else {
            return "常规";
        }
    }

    /**
     * 更新预览标签
     */
    private void updatePreview() {
        if (previewLabel != null && selectedFontFamily != null) {
            Font font = Font.font(
                    selectedFontFamily,
                    selectedFontWeight,
                    selectedFontPosture,
                    selectedFontSize);

            previewLabel.setFont(font);

            // 设置颜色
            String colorStyle = String.format("-fx-text-fill: #%02X%02X%02X;",
                    (int) (selectedFontColor.getRed() * 255),
                    (int) (selectedFontColor.getGreen() * 255),
                    (int) (selectedFontColor.getBlue() * 255));

            previewLabel.setStyle(colorStyle);
        }
    }

    /**
     * 应用字体设置并关闭对话框
     */
    @FXML
    public void applyFontAndClose() {
        if (formatController != null) {
            formatController.applyFont(
                    selectedFontFamily,
                    selectedFontWeight,
                    selectedFontPosture,
                    selectedFontSize,
                    selectedFontColor);
        }

        // 关闭对话框
        ((Stage) previewLabel.getScene().getWindow()).close();
    }

    /**
     * 取消操作并关闭对话框
     */
    @FXML
    public void cancel() {
        ((Stage) previewLabel.getScene().getWindow()).close();
    }
}
