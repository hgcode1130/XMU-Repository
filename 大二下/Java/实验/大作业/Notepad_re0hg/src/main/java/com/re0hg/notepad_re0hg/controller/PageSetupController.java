/**
 * 页面设置控制器类
 * 处理页面设置对话框的UI交互和数据绑定
 */
package com.re0hg.notepad_re0hg.controller;

import java.util.Arrays;
import java.util.List;

import com.re0hg.notepad_re0hg.model.PageSetupModel;

import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;

/**
 * 页面设置控制器
 * 处理页面设置对话框的逻辑
 */
public class PageSetupController {
    @FXML
    private ComboBox<String> paperSizeComboBox;

    @FXML
    private RadioButton portraitRadioButton;

    @FXML
    private RadioButton landscapeRadioButton;

    @FXML
    private TextField leftMarginField;

    @FXML
    private TextField rightMarginField;

    @FXML
    private TextField topMarginField;

    @FXML
    private TextField bottomMarginField;

    @FXML
    private TextField headerField;

    @FXML
    private TextField footerField;

    // 页面设置模型
    private PageSetupModel pageSetupModel;

    /**
     * 初始化方法，由JavaFX在加载FXML后自动调用
     */
    @FXML
    private void initialize() {
        // 设置纸张大小下拉框
        List<String> paperSizes = Arrays.asList(
                "A0 (841 x 1189 mm)",
                "A1 (594 x 841 mm)",
                "A2 (420 x 594 mm)",
                "A3 (297 x 420 mm)",
                "A4 (210 x 297 mm)",
                "A5 (148 x 210 mm)",
                "A6 (105 x 148 mm)",
                "Legal (8.5 x 14 in)",
                "Letter (8.5 x 11 in)",
                "Tabloid (11 x 17 in)");

        paperSizeComboBox.getItems().addAll(paperSizes);

        // 为数字输入字段添加验证
        setupNumericTextField(leftMarginField);
        setupNumericTextField(rightMarginField);
        setupNumericTextField(topMarginField);
        setupNumericTextField(bottomMarginField);
    }

    /**
     * 设置页面模型并初始化UI
     * 
     * @param model 页面设置模型
     */
    public void setPageSetupModel(PageSetupModel model) {
        this.pageSetupModel = model;

        // 初始化UI状态
        paperSizeComboBox.setValue(model.getPaper());

        if (model.getOrientation().equals("纵向")) {
            portraitRadioButton.setSelected(true);
        } else {
            landscapeRadioButton.setSelected(true);
        }

        leftMarginField.setText(String.valueOf(model.getLeftMargin()));
        rightMarginField.setText(String.valueOf(model.getRightMargin()));
        topMarginField.setText(String.valueOf(model.getTopMargin()));
        bottomMarginField.setText(String.valueOf(model.getBottomMargin()));

        headerField.setText(model.getHeader());
        footerField.setText(model.getFooter());
    } // getPaperSize方法已移除，因为它未被使用

    /**
     * 配置数字输入文本框，只允许输入数字和小数点
     * 
     * @param textField 文本框
     */
    private void setupNumericTextField(TextField textField) {
        textField.textProperty().addListener((obs, oldValue, newValue) -> {
            if (newValue == null)
                return;

            // 只允许数字和小数点
            if (!newValue.matches("\\d*\\.?\\d*")) {
                textField.setText(oldValue);
            }
        });
    }

    /**
     * 更新模型，应在对话框确认之前调用
     */
    public void updateModel() {
        if (pageSetupModel == null)
            return;

        // 更新纸张大小
        pageSetupModel.setPaper(paperSizeComboBox.getValue());
        // 更新页面方向
        pageSetupModel.setOrientation(
                portraitRadioButton.isSelected() ? "纵向" : "横向");

        // 更新边距
        try {
            pageSetupModel.setLeftMargin(Double.parseDouble(leftMarginField.getText()));
            pageSetupModel.setRightMargin(Double.parseDouble(rightMarginField.getText()));
            pageSetupModel.setTopMargin(Double.parseDouble(topMarginField.getText()));
            pageSetupModel.setBottomMargin(Double.parseDouble(bottomMarginField.getText()));
        } catch (NumberFormatException e) {
            // 忽略错误，使用默认值
        }

        // 更新页眉/页脚
        pageSetupModel.setHeader(headerField.getText());
        pageSetupModel.setFooter(footerField.getText());
    }
}
