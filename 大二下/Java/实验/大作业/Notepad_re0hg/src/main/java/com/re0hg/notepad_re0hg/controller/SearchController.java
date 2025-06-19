/**
 * 搜索控制器类
 * 处理文本查找和替换操作
 * MVC架构中处理搜索操作的Controller
 * 同时包含搜索对话框的控制逻辑
 */
package com.re0hg.notepad_re0hg.controller;

import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.re0hg.notepad_re0hg.model.AppModel;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TextField;
import javafx.scene.control.TextArea;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

/**
 * 搜索控制器类
 * 处理文本查找和替换操作
 * 同时包含搜索对话框的控制逻辑
 */
public class SearchController implements Controller {

    // 主窗口
    private final Stage mainStage;

    // 文档控制器引用
    private DocumentController documentController;

    // 搜索对话框引用
    private Stage searchDialog;

    // 搜索相关状态
    private String searchQuery = "";
    private String replaceText = "";
    private boolean isCaseSensitive = false;
    private int lastSearchIndex = -1;

    // FXML UI 组件
    @FXML
    private TextField searchTextField;

    @FXML
    private TextField replaceTextField;

    @FXML
    private Button searchButton;

    @FXML
    private Button previousSearchButton;

    @FXML
    private Button replaceButton;

    @FXML
    private Button replaceAllButton;

    @FXML
    private CheckBox IgnoreCaseBox;

    /**
     * 构造函数
     * 
     * @param appModel  应用模型（未使用）
     * @param mainStage 主窗口
     */
    public SearchController(AppModel appModel, Stage mainStage) {
        this.mainStage = mainStage;
    }

    @Override
    public void initialize() {
        // 搜索控制器初始化
    }

    @Override
    public String getName() {
        return "searchController";
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
     * 获取文本区域
     * 
     * @return 文本区域
     */
    private TextArea getTextArea() {
        return documentController != null ? documentController.getTextArea() : null;
    }

    /**
     * 显示查找替换对话框
     */
    public void showSearchDialog() {
        try {
            if (searchDialog == null) {
                // 加载FXML
                FXMLLoader loader = new FXMLLoader();
                loader.setLocation(getClass().getResource("/com/re0hg/notepad_re0hg/search.fxml"));
                loader.setController(this); // 使用当前类作为控制器
                Scene scene = new Scene(loader.load());

                // 创建对话框
                searchDialog = new Stage();
                searchDialog.setTitle("查找/替换");
                searchDialog.initModality(Modality.NONE); // 非模态对话框
                searchDialog.initOwner(mainStage);
                searchDialog.initStyle(StageStyle.UTILITY);
                searchDialog.setResizable(false);
                searchDialog.setScene(scene);

                // 初始化搜索框的值
                updateSearchDialogValues();
            } else {
                // 如果对话框已存在，更新其值
                updateSearchDialogValues();
            }

            // 显示对话框
            searchDialog.show();
            searchDialog.requestFocus();

        } catch (IOException e) {
            e.printStackTrace();
            showErrorAlert("错误", "无法加载查找替换对话框", e.getMessage());
        }
    }

    /**
     * 更新搜索对话框的值
     */
    private void updateSearchDialogValues() {
        if (searchTextField != null) {
            searchTextField.setText(searchQuery);
        }
        if (replaceTextField != null) {
            replaceTextField.setText(replaceText);
        }
        if (IgnoreCaseBox != null) {
            IgnoreCaseBox.setSelected(!isCaseSensitive);
        }
    }

    /**
     * 设置搜索查询文本
     * 
     * @param query 查询文本
     */
    public void setSearchQuery(String query) {
        this.searchQuery = query;
    }

    /**
     * 设置替换文本
     * 
     * @param text 替换文本
     */
    public void setReplaceText(String text) {
        this.replaceText = text;
    }

    /**
     * 设置是否区分大小写
     * 
     * @param sensitive 是否区分大小写
     */
    public void setCaseSensitive(boolean sensitive) {
        this.isCaseSensitive = sensitive;
    }

    /**
     * 执行查找操作
     * 
     * @param searchDown 是否向下查找
     * @return 是否找到匹配
     */
    public boolean search(boolean searchDown) {
        TextArea textArea = getTextArea();
        if (textArea == null || searchQuery.isEmpty()) {
            return false;
        }

        String text = textArea.getText();
        int startIndex;

        if (searchDown) {
            // 向下查找，从当前选择结束位置或上次查找位置之后开始
            int caretPos = textArea.getCaretPosition();
            int selectionEnd = textArea.getSelection().getEnd();
            startIndex = selectionEnd > caretPos ? selectionEnd : caretPos;

            // 如果没有选中文本或者光标在最后，使用上次查找位置
            if (startIndex == textArea.getSelection().getStart() || startIndex >= text.length()) {
                startIndex = lastSearchIndex > -1 ? lastSearchIndex + 1 : 0;
            }
        } else {
            // 向上查找，从当前选择开始位置或上次查找位置之前开始
            int caretPos = textArea.getCaretPosition();
            int selectionStart = textArea.getSelection().getStart();
            startIndex = selectionStart < caretPos ? selectionStart : caretPos;

            // 如果是首次查找或光标在最前面
            if (startIndex <= 0) {
                startIndex = text.length();
            }
        }

        // 创建匹配模式
        Pattern pattern = Pattern.compile(
                Pattern.quote(searchQuery),
                isCaseSensitive ? 0 : Pattern.CASE_INSENSITIVE);

        if (searchDown) {
            // 向下查找
            Matcher matcher = pattern.matcher(text);
            if (matcher.find(startIndex)) {
                // 找到匹配，选中文本
                int start = matcher.start();
                int end = matcher.end();

                textArea.selectRange(start, end);
                textArea.requestFocus();

                lastSearchIndex = start;
                return true;
            } else if (startIndex > 0) {
                // 如果从中间开始查找没找到，尝试从头开始（循环查找）
                Matcher fromStartMatcher = pattern.matcher(text);
                if (fromStartMatcher.find(0)) {
                    int start = fromStartMatcher.start();
                    int end = fromStartMatcher.end();

                    Alert alert = new Alert(AlertType.INFORMATION);
                    alert.setTitle("查找");
                    alert.setHeaderText("已到达文档末尾，从头继续查找");
                    alert.showAndWait();

                    textArea.selectRange(start, end);
                    textArea.requestFocus();

                    lastSearchIndex = start;
                    return true;
                }
            }
        } else {
            // 向上查找，需要从头到当前位置查找
            int lastMatchPos = -1;
            int lastMatchEnd = -1;

            Matcher matcher = pattern.matcher(text);
            while (matcher.find()) {
                if (matcher.start() < startIndex) {
                    lastMatchPos = matcher.start();
                    lastMatchEnd = matcher.end();
                } else {
                    break; // 已经超过当前位置
                }
            }

            if (lastMatchPos != -1) {
                // 找到前一个匹配
                textArea.selectRange(lastMatchPos, lastMatchEnd);
                textArea.requestFocus();

                lastSearchIndex = lastMatchPos;
                return true;
            } else if (startIndex < text.length()) {
                // 如果从头到当前位置没找到，尝试在整个文档中找最后一个（循环查找）
                matcher = pattern.matcher(text);
                lastMatchPos = -1;
                lastMatchEnd = -1;

                while (matcher.find()) {
                    lastMatchPos = matcher.start();
                    lastMatchEnd = matcher.end();
                }

                if (lastMatchPos != -1) {
                    Alert alert = new Alert(AlertType.INFORMATION);
                    alert.setTitle("查找");
                    alert.setHeaderText("已到达文档开头，从末尾继续查找");
                    alert.showAndWait();

                    textArea.selectRange(lastMatchPos, lastMatchEnd);
                    textArea.requestFocus();

                    lastSearchIndex = lastMatchPos;
                    return true;
                }
            }
        }

        // 没有找到匹配
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle("查找");
        alert.setHeaderText("找不到 \"" + searchQuery + "\"");
        alert.showAndWait();

        return false;
    }

    /**
     * 执行替换操作
     * 
     * @return 是否替换成功
     */
    public boolean replace() {
        TextArea textArea = getTextArea();
        if (textArea == null || searchQuery.isEmpty()) {
            return false;
        }

        // 获取当前选中的文本
        String selectedText = textArea.getSelectedText();

        // 检查当前选中的内容是否与搜索内容匹配
        if (selectedText != null && !selectedText.isEmpty()) {
            if ((isCaseSensitive && selectedText.equals(searchQuery)) ||
                    (!isCaseSensitive && selectedText.equalsIgnoreCase(searchQuery))) {
                // 替换文本
                textArea.replaceSelection(replaceText);

                // 替换后继续查找下一个
                search(true);
                return true;
            }
        }

        // 如果没有匹配的选择，先查找下一个
        return search(true);
    }

    /**
     * 执行全部替换操作
     * 
     * @return 替换的数量
     */
    public int replaceAll() {
        TextArea textArea = getTextArea();
        if (textArea == null || searchQuery.isEmpty()) {
            return 0;
        }

        String text = textArea.getText();
        if (text.isEmpty()) {
            return 0;
        }

        // 创建匹配模式
        Pattern pattern = Pattern.compile(
                Pattern.quote(searchQuery),
                isCaseSensitive ? 0 : Pattern.CASE_INSENSITIVE);

        // 执行替换
        Matcher matcher = pattern.matcher(text);
        String newText = matcher.replaceAll(Matcher.quoteReplacement(replaceText));

        // 计算替换次数
        int count = 0;
        matcher.reset();
        while (matcher.find()) {
            count++;
        }

        // 更新文本
        if (count > 0) {
            textArea.setText(newText);

            // 显示替换结果
            Alert alert = new Alert(AlertType.INFORMATION);
            alert.setTitle("替换完成");
            alert.setHeaderText("完成替换");
            alert.setContentText("共替换了 " + count + " 处");
            alert.showAndWait();
        } else {
            Alert alert = new Alert(AlertType.INFORMATION);
            alert.setTitle("替换");
            alert.setHeaderText("找不到 \"" + searchQuery + "\"");
            alert.showAndWait();
        }

        return count;
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

    // =============== FXML 事件处理方法 ===============

    /**
     * 查找下一个 - FXML 事件处理方法
     */
    @FXML
    private void search() {
        // 更新搜索参数
        setSearchQuery(searchTextField.getText());
        setCaseSensitive(!IgnoreCaseBox.isSelected());

        // 执行搜索
        search(true);
    }

    /**
     * 查找上一个 - FXML 事件处理方法
     */
    @FXML
    private void previousSearch() {
        // 更新搜索参数
        setSearchQuery(searchTextField.getText());
        setCaseSensitive(!IgnoreCaseBox.isSelected());

        // 执行搜索
        search(false);
    }

    /**
     * 替换 - FXML 事件处理方法
     */
    @FXML
    private void handleReplace() {
        // 更新搜索和替换参数
        setSearchQuery(searchTextField.getText());
        setReplaceText(replaceTextField.getText());
        setCaseSensitive(!IgnoreCaseBox.isSelected());

        // 执行替换
        replace();
    }

    /**
     * 全部替换 - FXML 事件处理方法
     */
    @FXML
    private void handleReplaceAll() {
        // 更新搜索和替换参数
        setSearchQuery(searchTextField.getText());
        setReplaceText(replaceTextField.getText());
        setCaseSensitive(!IgnoreCaseBox.isSelected());

        // 执行全部替换
        replaceAll();
    }
}
