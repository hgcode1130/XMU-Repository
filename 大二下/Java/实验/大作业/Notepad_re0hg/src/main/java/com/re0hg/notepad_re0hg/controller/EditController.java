/**
 * 编辑控制器类
 * 处理文本编辑操作，如剪切、复制、粘贴、查找、替换等
 * MVC架构中处理编辑操作的Controller
 */
package com.re0hg.notepad_re0hg.controller;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import com.re0hg.notepad_re0hg.model.AppModel;

import javafx.scene.control.Alert;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextInputDialog;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.Stage;

/**
 * 编辑控制器类
 * 处理文本编辑、查找替换等操作
 */
public class EditController implements Controller {
    // 文档控制器引用
    private DocumentController documentController;

    // 搜索相关状态
    private boolean isCaseIgnored = false;

    /**
     * 构造函数
     * 
     * @param appModel 应用模型
     * @param stage    主窗口
     */
    public EditController(AppModel appModel, Stage stage) {
        // 构造函数参数保留以保持一致性，但实际未使用
    }

    @Override
    public void initialize() {
        // 编辑控制器初始化，目前无需特殊初始化代码
    }

    @Override
    public String getName() {
        return "editController";
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
     * 撤销操作
     */
    public void undo() {
        if (documentController != null) {
            documentController.undo();
            notifyEditComplete();
        }
    }

    /**
     * 重做操作
     */
    public void redo() {
        if (documentController != null) {
            documentController.redo();
            notifyEditComplete();
        }
    }

    /**
     * 剪切操作
     */
    public void cut() {
        if (documentController != null) {
            documentController.cut();
            notifyEditComplete();
        }
    }

    /**
     * 复制操作
     */
    public void copy() {
        if (documentController != null) {
            documentController.copy();
            notifyEditComplete();
        }
    }

    /**
     * 粘贴操作
     */
    public void paste() {
        if (documentController != null) {
            documentController.paste();
            notifyEditComplete();
        }
    }

    /**
     * 删除操作
     */
    public void delete() {
        if (documentController != null) {
            documentController.delete();
            notifyEditComplete();
        }
    }

    /**
     * 全选操作
     */
    public void selectAll() {
        if (documentController != null) {
            documentController.selectAll();
        }
    }

    /**
     * 插入时间日期
     */
    public void insertTimeAndDate() {
        if (documentController != null) {
            // 获取当前时间日期
            LocalDateTime now = LocalDateTime.now();
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm yyyy-MM-dd");
            String timeDate = now.format(formatter);

            // 在当前位置插入
            documentController.insertText(timeDate);
        }
    }

    /**
     * 在百度中搜索选定文本
     */
    public void baiduSearch() {
        if (documentController != null) {
            String selectedText = documentController.getSelectedText();
            if (selectedText != null && !selectedText.isEmpty()) {
                // 创建百度搜索URL
                String searchUrl = "https://www.baidu.com/s?wd=" + selectedText.trim().replace(" ", "+");

                // 打开默认浏览器
                try {
                    java.awt.Desktop.getDesktop().browse(java.net.URI.create(searchUrl));
                } catch (Exception e) {
                    showErrorAlert("搜索错误", "无法打开浏览器", e.getMessage());
                }
            }
        }
    }

    /**
     * 查找和替换功能已移至 SearchController
     * 以下方法保留作为兼容性支持，但不再实现具体功能
     */

    /**
     * 查找文本（已废弃）
     * 
     * @return 是否找到匹配
     */
    @Deprecated
    public boolean findText() {
        // 此功能已移至 SearchController
        return false;
    }

    /**
     * 查找下一个匹配（已废弃）
     * 
     * @param fromStart 是否从头开始查找
     * @return 是否找到匹配
     */
    @Deprecated
    public boolean findNext(boolean fromStart) {
        // 此功能已移至 SearchController
        return false;
    }

    /**
     * 查找上一个匹配（已废弃）
     * 
     * @return 是否找到匹配
     */
    @Deprecated
    public boolean findPrevious() {
        // 此功能已移至 SearchController
        return false;
    }

    /**
     * 替换文本（已废弃）
     */
    @Deprecated
    public void replaceText() {
        // 此功能已移至 SearchController
    }

    /**
     * 转到指定行
     */
    public void goToLine() {
        TextArea textArea = getTextArea();
        if (textArea == null) {
            return;
        }

        // 显示转到行对话框
        TextInputDialog dialog = new TextInputDialog("1");
        dialog.setTitle("转到行");
        dialog.setHeaderText("行号:");
        dialog.setContentText("转到行:");

        dialog.showAndWait().ifPresent(lineStr -> {
            try {
                int lineNumber = Integer.parseInt(lineStr);

                // 获取文本内容并分割为行
                String[] lines = textArea.getText().split("\n", -1);

                if (lineNumber < 1) {
                    lineNumber = 1;
                } else if (lineNumber > lines.length) {
                    lineNumber = lines.length;
                }

                // 计算目标行的起始位置
                int position = 0;
                for (int i = 0; i < lineNumber - 1; i++) {
                    position += lines[i].length() + 1; // +1 是换行符
                }

                // 将光标定位到目标行
                textArea.positionCaret(position);
                textArea.requestFocus();

            } catch (NumberFormatException e) {
                Alert alert = new Alert(AlertType.ERROR);
                alert.setTitle("错误");
                alert.setHeaderText("无效的行号");
                alert.setContentText("请输入有效的数字");
                alert.showAndWait();
            }
        });
    }

    /**
     * 设置查找时是否忽略大小写
     * 
     * @param ignore 是否忽略大小写
     */
    public void setCaseIgnored(boolean ignore) {
        this.isCaseIgnored = ignore;
    }

    /**
     * 获取查找时是否忽略大小写
     * 
     * @return 是否忽略大小写
     */
    public boolean isCaseIgnored() {
        return isCaseIgnored;
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

    /**
     * 检查是否可以撤销
     * 
     * @return 是否可以撤销
     */
    public boolean canUndo() {
        return documentController != null && documentController.canUndo();
    }

    /**
     * 检查是否可以重做
     * 
     * @return 是否可以重做
     */
    public boolean canRedo() {
        return documentController != null && documentController.canRedo();
    }

    /**
     * 检查是否可以复制或剪切
     * 
     * @return 是否可以复制或剪切
     */
    public boolean canCopyOrCut() {
        TextArea textArea = getTextArea();
        return textArea != null && textArea.getSelectedText() != null && !textArea.getSelectedText().isEmpty();
    }

    /**
     * 编辑操作监听器接口
     * 当编辑操作执行后通知 UI 更新
     */
    public interface EditListener {
        /**
         * 当编辑操作执行完成时调用
         */
        void onEditOperationComplete();
    }

    // 编辑监听器
    private EditListener editListener;

    /**
     * 设置编辑监听器
     * 
     * @param listener 编辑监听器
     */
    public void setEditListener(EditListener listener) {
        this.editListener = listener;
    }

    /**
     * 通知编辑操作完成
     */
    private void notifyEditComplete() {
        if (editListener != null) {
            editListener.onEditOperationComplete();
        }
    }
}
