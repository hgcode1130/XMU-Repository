/**
 * 字体选择对话框的控制器类
 * 处理字体选择操作
 * MVC架构中处理字体选择的Controller
 */
package com.re0hg.notepad_re0hg.controller;

import java.net.URL;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;

/**
 * 字体对话框控制器类
 * 处理字体选择对话框的交互逻辑
 */
public class FontController implements Initializable {

    // FXML注入的UI元素
    @FXML
    private ListView<String> fontSelector;

    @FXML
    private ListView<String> glyphSelector;

    @FXML
    private ListView<String> sizeSelector;

    @FXML
    private TextArea fontShowTextArea;

    @FXML
    private ComboBox<String> fontColorSelector;

    @FXML
    private Button fontInterfaceConfirmButton;

    @FXML
    private Button fontInterfaceCancelButton;

    @FXML
    private TextField fontTextField;

    @FXML
    private TextField glyphTextField;

    @FXML
    private TextField sizeTextField;

    // 数据字段
    private FormatController formatController;
    private Font currentFont;
    private Color currentColor = Color.BLACK;

    // 常量
    private static final String SAMPLE_TEXT = "AaBbYyZz 中文示例";
    private static final List<String> FONT_STYLES = Arrays.asList("常规", "斜体", "粗体", "粗斜体");
    private static final List<String> FONT_SIZES = IntStream
            .of(8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72)
            .mapToObj(String::valueOf)
            .collect(Collectors.toList());
    private static final List<String> FONT_COLORS = Arrays.asList(
            "黑色", "红色", "绿色", "蓝色", "黄色", "紫色", "青色", "灰色", "白色");

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        // 初始化字体列表
        ObservableList<String> fontFamilies = FXCollections.observableArrayList(Font.getFamilies());
        fontSelector.setItems(fontFamilies);

        // 初始化字形列表
        glyphSelector.setItems(FXCollections.observableArrayList(FONT_STYLES));

        // 初始化字号列表
        sizeSelector.setItems(FXCollections.observableArrayList(FONT_SIZES));

        // 初始化颜色下拉框
        fontColorSelector.setItems(FXCollections.observableArrayList(FONT_COLORS));

        // 设置默认选择
        fontSelector.getSelectionModel().select("宋体");
        glyphSelector.getSelectionModel().select("常规");
        sizeSelector.getSelectionModel().select("12");
        fontColorSelector.getSelectionModel().select("黑色");

        // 更新文本框
        updateFontTextFields();

        // 设置列表选择监听器
        setupListeners();

        // 设置示例文本
        fontShowTextArea.setText(SAMPLE_TEXT);
        updateSampleText();
    }

    /**
     * 设置格式控制器
     * 
     * @param formatController 格式控制器
     */
    public void setFormatController(FormatController formatController) {
        this.formatController = formatController;

        // 获取当前字体
        if (formatController != null && formatController.getCurrentFont() != null) {
            currentFont = formatController.getCurrentFont();
            currentColor = formatController.getCurrentTextColor();

            // 根据当前字体设置选择
            selectCurrentFont();
        } else {
            currentFont = Font.font("宋体", FontWeight.NORMAL, FontPosture.REGULAR, 12);
        }
    }

    /**
     * 根据当前字体设置选择
     */
    private void selectCurrentFont() {
        String family = currentFont.getFamily();
        double size = currentFont.getSize();
        String style = getFontStyleString(currentFont);

        // 设置选择
        fontSelector.getSelectionModel().select(family);
        sizeSelector.getSelectionModel().select(String.valueOf((int) size));
        glyphSelector.getSelectionModel().select(style);

        // 设置颜色
        String colorName = getColorName(currentColor);
        fontColorSelector.getSelectionModel().select(colorName);

        // 更新文本框
        updateFontTextFields();
    }

    /**
     * 设置UI元素的监听器
     */
    private void setupListeners() {
        // 字体选择监听
        fontSelector.getSelectionModel().selectedItemProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal != null) {
                fontTextField.setText(newVal);
                updateSampleText();
            }
        });

        // 字形选择监听
        glyphSelector.getSelectionModel().selectedItemProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal != null) {
                glyphTextField.setText(newVal);
                updateSampleText();
            }
        });

        // 字号选择监听
        sizeSelector.getSelectionModel().selectedItemProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal != null) {
                sizeTextField.setText(newVal);
                updateSampleText();
            }
        });

        // 颜色选择监听
        fontColorSelector.getSelectionModel().selectedItemProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal != null) {
                currentColor = getColorFromName(newVal);
                updateSampleText();
            }
        });

        // 字体文本框监听
        fontTextField.textProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal != null && !newVal.isEmpty()) {
                String fontName = newVal;
                for (String family : Font.getFamilies()) {
                    if (family.toLowerCase().startsWith(fontName.toLowerCase())) {
                        fontSelector.getSelectionModel().select(family);
                        fontSelector.scrollTo(fontSelector.getSelectionModel().getSelectedIndex());
                        break;
                    }
                }
            }
        });

        // 字形文本框监听
        glyphTextField.textProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal != null && !newVal.isEmpty()) {
                String styleName = newVal;
                for (String style : FONT_STYLES) {
                    if (style.startsWith(styleName)) {
                        glyphSelector.getSelectionModel().select(style);
                        break;
                    }
                }
            }
        });

        // 字号文本框监听
        sizeTextField.textProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal != null && !newVal.isEmpty()) {
                try {
                    int size = Integer.parseInt(newVal);
                    String sizeStr = String.valueOf(size);
                    if (FONT_SIZES.contains(sizeStr)) {
                        sizeSelector.getSelectionModel().select(sizeStr);
                    }
                } catch (NumberFormatException e) {
                    // 忽略非数字输入
                }
                updateSampleText();
            }
        });
    }

    /**
     * 更新示例文本的字体
     */
    private void updateSampleText() {
        String fontFamily = fontSelector.getSelectionModel().getSelectedItem();
        String fontStyle = glyphSelector.getSelectionModel().getSelectedItem();
        String fontSize = sizeTextField.getText();

        if (fontFamily != null && fontStyle != null && fontSize != null && !fontSize.isEmpty()) {
            try {
                double size = Double.parseDouble(fontSize);

                // 创建字体
                Font font = createFont(fontFamily, fontStyle, size);

                // 更新示例文本
                fontShowTextArea.setFont(font);
                fontShowTextArea.setStyle("-fx-text-fill: " + colorToHex(currentColor) + ";");

                // 保存当前字体
                currentFont = font;
            } catch (NumberFormatException e) {
                // 忽略非数字格式的字号
            }
        }
    }

    /**
     * 更新字体文本框内容
     */
    private void updateFontTextFields() {
        if (fontSelector.getSelectionModel().getSelectedItem() != null) {
            fontTextField.setText(fontSelector.getSelectionModel().getSelectedItem());
        }

        if (glyphSelector.getSelectionModel().getSelectedItem() != null) {
            glyphTextField.setText(glyphSelector.getSelectionModel().getSelectedItem());
        }

        if (sizeSelector.getSelectionModel().getSelectedItem() != null) {
            sizeTextField.setText(sizeSelector.getSelectionModel().getSelectedItem());
        }
    }

    /**
     * 根据字体样式名称创建字体
     * 
     * @param family 字体名称
     * @param style  字体样式
     * @param size   字体大小
     * @return 字体对象
     */
    private Font createFont(String family, String style, double size) {
        FontWeight weight = FontWeight.NORMAL;
        FontPosture posture = FontPosture.REGULAR;

        switch (style) {
            case "常规":
                weight = FontWeight.NORMAL;
                posture = FontPosture.REGULAR;
                break;
            case "粗体":
                weight = FontWeight.BOLD;
                posture = FontPosture.REGULAR;
                break;
            case "斜体":
                weight = FontWeight.NORMAL;
                posture = FontPosture.ITALIC;
                break;
            case "粗斜体":
                weight = FontWeight.BOLD;
                posture = FontPosture.ITALIC;
                break;
        }

        return Font.font(family, weight, posture, size);
    }

    /**
     * 获取字体样式字符串
     * 
     * @param font 字体对象
     * @return 样式字符串
     */
    private String getFontStyleString(Font font) {
        String style = font.getStyle();
        boolean isBold = style.contains("Bold");
        boolean isItalic = style.contains("Italic") || style.contains("Oblique");

        if (isBold && isItalic) {
            return "粗斜体";
        } else if (isBold) {
            return "粗体";
        } else if (isItalic) {
            return "斜体";
        } else {
            return "常规";
        }
    }

    /**
     * 将颜色转换为16进制表示
     * 
     * @param color 颜色对象
     * @return 十六进制颜色字符串
     */
    private String colorToHex(Color color) {
        return String.format("#%02X%02X%02X",
                (int) (color.getRed() * 255),
                (int) (color.getGreen() * 255),
                (int) (color.getBlue() * 255));
    }

    /**
     * 根据颜色名称获取颜色对象
     * 
     * @param colorName 颜色名称
     * @return 颜色对象
     */
    private Color getColorFromName(String colorName) {
        switch (colorName) {
            case "黑色":
                return Color.BLACK;
            case "红色":
                return Color.RED;
            case "绿色":
                return Color.GREEN;
            case "蓝色":
                return Color.BLUE;
            case "黄色":
                return Color.YELLOW;
            case "紫色":
                return Color.PURPLE;
            case "青色":
                return Color.CYAN;
            case "灰色":
                return Color.GRAY;
            case "白色":
                return Color.WHITE;
            default:
                return Color.BLACK;
        }
    }

    /**
     * 根据颜色获取颜色名称
     * 
     * @param color 颜色对象
     * @return 颜色名称
     */
    private String getColorName(Color color) {
        if (color.equals(Color.BLACK))
            return "黑色";
        if (color.equals(Color.RED))
            return "红色";
        if (color.equals(Color.GREEN))
            return "绿色";
        if (color.equals(Color.BLUE))
            return "蓝色";
        if (color.equals(Color.YELLOW))
            return "黄色";
        if (color.equals(Color.PURPLE))
            return "紫色";
        if (color.equals(Color.CYAN))
            return "青色";
        if (color.equals(Color.GRAY))
            return "灰色";
        if (color.equals(Color.WHITE))
            return "白色";
        return "黑色";
    }

    /**
     * 确认按钮点击事件处理
     */
    @FXML
    public void fontInterfaceConfirmButtonPressed() {
        if (formatController != null) {
            formatController.setFont(currentFont, currentColor);
        }
        closeDialog();
    }

    /**
     * 取消按钮点击事件处理
     */
    @FXML
    public void fontInterfaceCancelButtonPressed() {
        closeDialog();
    }

    /**
     * 关闭对话框
     */
    private void closeDialog() {
        Stage stage = (Stage) fontInterfaceConfirmButton.getScene().getWindow();
        stage.close();
    }
}
