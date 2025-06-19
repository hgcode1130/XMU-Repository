/**
 * 文档控制器类
 * 管理文档的显示和交互
 * MVC架构中处理文档相关UI操作的Controller
 */
package com.re0hg.notepad_re0hg.controller;

import com.re0hg.notepad_re0hg.model.AppModel;
import com.re0hg.notepad_re0hg.model.DocumentModel;
import com.re0hg.notepad_re0hg.utils.UndoRedoManager;

import javafx.beans.binding.Bindings;
import javafx.scene.control.TextArea;
import javafx.scene.input.KeyEvent;

/**
 * 文档控制器类
 * 处理文本编辑区域的操作和事件
 */
public class DocumentController implements Controller {
    // 应用模型
    private AppModel appModel;

    // 撤销/重做管理器
    private UndoRedoManager undoRedoManager;

    // 文本编辑区
    private TextArea textArea;

    /**
     * 构造函数
     * 
     * @param appModel 应用模型
     */
    public DocumentController(AppModel appModel) {
        this.appModel = appModel;
    }

    @Override
    public void initialize() {
        if (textArea != null) {
            // 初始化撤销/重做管理器
            undoRedoManager = new UndoRedoManager(textArea);

            // 设置文本区域
            setupTextArea();
        }

        // 观察活动文档变化
        appModel.activeDocumentProperty().addListener((obs, oldDoc, newDoc) -> {
            if (textArea != null && newDoc != null) {
                // 解除旧绑定
                if (oldDoc != null) {
                    Bindings.unbindBidirectional(textArea.textProperty(), oldDoc.contentProperty());
                }

                // 更新到新文档
                textArea.setText(newDoc.getContent());

                // 建立新的双向绑定
                Bindings.bindBidirectional(textArea.textProperty(), newDoc.contentProperty());

                // 重置撤销/重做管理器状态
                if (undoRedoManager != null) {
                    undoRedoManager.clear();
                } else {
                    // 如果管理器不存在，创建一个新的
                    undoRedoManager = new UndoRedoManager(textArea);
                }
            }
        });
    }

    /**
     * 设置文本区域和事件处理
     */
    private void setupTextArea() {
        // 设置字体
        updateFont();

        // 设置自动换行
        textArea.setWrapText(appModel.getConfig().isWordWrap());

        // 绑定到当前活动文档
        DocumentModel activeDoc = appModel.getActiveDocument();
        if (activeDoc != null) {
            textArea.setText(activeDoc.getContent());
            Bindings.bindBidirectional(textArea.textProperty(), activeDoc.contentProperty());
        }

        // 设置键盘事件
        textArea.addEventFilter(KeyEvent.KEY_PRESSED, event -> {
            if (event.isControlDown()) {
                switch (event.getCode()) {
                    case Z:
                        if (canUndo()) {
                            undo();
                            event.consume();
                        }
                        break;
                    case Y:
                        if (canRedo()) {
                            redo();
                            event.consume();
                        }
                        break;
                    default:
                        break;
                }
            }
        });
    }

    @Override
    public String getName() {
        return "documentController";
    }

    /**
     * 设置文本区域的引用
     * 
     * @param textArea 文本区域
     */
    public void setTextArea(TextArea textArea) {
        this.textArea = textArea;
        if (textArea != null) {
            // 初始化撤销/重做管理器
            undoRedoManager = new UndoRedoManager(textArea);
            setupTextArea();
        }
    }

    /**
     * 获取文本区域
     * 
     * @return 文本区域
     */
    public TextArea getTextArea() {
        return textArea;
    }

    /**
     * 更新字体设置
     */
    public void updateFont() {
        if (textArea != null) {
            textArea.setFont(appModel.getConfig().getFont());

            // 更新文本颜色
            String fontColor = appModel.getConfig().getFontColor();
            if (fontColor != null && !fontColor.isEmpty()) {
                textArea.setStyle("-fx-text-fill: " + fontColor + ";");
            }
        }
    }

    /**
     * 设置自动换行
     * 
     * @param wrap 是否自动换行
     */
    public void setWordWrap(boolean wrap) {
        if (textArea != null) {
            textArea.setWrapText(wrap);
            appModel.getConfig().setWordWrap(wrap);
        }
    }

    /**
     * 获取当前是否自动换行
     * 
     * @return 是否自动换行
     */
    public boolean isWordWrap() {
        return textArea != null && textArea.isWrapText();
    }

    /**
     * 撤销编辑操作
     */
    public void undo() {
        if (undoRedoManager != null) {
            undoRedoManager.undo();
        }
    }

    /**
     * 重做编辑操作
     */
    public void redo() {
        if (undoRedoManager != null) {
            undoRedoManager.redo();
        }
    }

    /**
     * 剪切所选文本
     */
    public void cut() {
        if (textArea != null) {
            textArea.cut();
        }
    }

    /**
     * 复制所选文本
     */
    public void copy() {
        if (textArea != null) {
            textArea.copy();
        }
    }

    /**
     * 粘贴文本
     */
    public void paste() {
        if (textArea != null) {
            textArea.paste();
        }
    }

    /**
     * 删除所选文本
     */
    public void delete() {
        if (textArea != null && textArea.getSelectedText() != null && !textArea.getSelectedText().isEmpty()) {
            textArea.replaceSelection("");
        }
    }

    /**
     * 全选文本
     */
    public void selectAll() {
        if (textArea != null) {
            textArea.selectAll();
        }
    }

    /**
     * 获取选定的文本
     * 
     * @return 选定的文本，如果未选定则返回null
     */
    public String getSelectedText() {
        if (textArea != null) {
            return textArea.getSelectedText();
        }
        return null;
    }

    /**
     * 插入文本到当前光标位置
     * 
     * @param text 要插入的文本
     */
    public void insertText(String text) {
        if (textArea != null) {
            textArea.insertText(textArea.getCaretPosition(), text);
        }
    }

    /**
     * 获取光标位置
     * 
     * @return 光标位置
     */
    public int getCaretPosition() {
        return textArea != null ? textArea.getCaretPosition() : 0;
    }

    /**
     * 设置光标位置
     * 
     * @param position 光标位置
     */
    public void setCaretPosition(int position) {
        if (textArea != null) {
            textArea.positionCaret(position);
        }
    }

    /**
     * 检查是否可以撤销
     * 
     * @return 如果可以撤销返回true，否则返回false
     */
    public boolean canUndo() {
        return undoRedoManager != null && undoRedoManager.canUndo();
    }

    /**
     * 检查是否可以重做
     * 
     * @return 如果可以重做返回true，否则返回false
     */
    public boolean canRedo() {
        return undoRedoManager != null && undoRedoManager.canRedo();
    }
}
