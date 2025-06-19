/**
 * 撤销重做管理器
 * 实现多级撤销和重做功能
 * 记录文本编辑操作的历史，支持不同类型的编辑操作
 * 
 * @author re0hg
 */
package com.re0hg.notepad_re0hg.utils;

import java.util.Stack;
import javafx.scene.control.TextArea;

/**
 * 撤销重做管理器类
 * 提供高级的撤销和重做功能，支持多级操作历史
 */
public class UndoRedoManager {

    /**
     * 文本变更操作的抽象类
     * 所有具体的操作类型都继承自此类
     */
    private abstract static class TextOperation {
        protected int position; // 操作位置
        protected String text; // 操作涉及的文本内容

        /**
         * 撤销此操作
         * 
         * @param textArea 操作的文本区域
         */
        public abstract void undo(TextArea textArea);

        /**
         * 重做此操作
         * 
         * @param textArea 操作的文本区域
         */
        public abstract void redo(TextArea textArea);
    }

    /**
     * 插入文本操作
     */
    private static class InsertOperation extends TextOperation {

        public InsertOperation(int position, String text) {
            this.position = position;
            this.text = text;
        }

        @Override
        public void undo(TextArea textArea) {
            textArea.replaceText(position, position + text.length(), "");
            textArea.positionCaret(position);
        }

        @Override
        public void redo(TextArea textArea) {
            textArea.insertText(position, text);
            textArea.positionCaret(position + text.length());
        }
    }

    /**
     * 删除文本操作
     */
    private static class DeleteOperation extends TextOperation {

        public DeleteOperation(int position, String text) {
            this.position = position;
            this.text = text;
        }

        @Override
        public void undo(TextArea textArea) {
            textArea.insertText(position, text);
            textArea.positionCaret(position + text.length());
        }

        @Override
        public void redo(TextArea textArea) {
            textArea.replaceText(position, position + text.length(), "");
            textArea.positionCaret(position);
        }
    }

    /**
     * 替换文本操作
     */
    private static class ReplaceOperation extends TextOperation {
        private String oldText; // 替换前的文本

        public ReplaceOperation(int position, String oldText, String newText) {
            this.position = position;
            this.oldText = oldText;
            this.text = newText; // 替换后的文本
        }

        @Override
        public void undo(TextArea textArea) {
            textArea.replaceText(position, position + text.length(), oldText);
            textArea.positionCaret(position + oldText.length());
        }

        @Override
        public void redo(TextArea textArea) {
            textArea.replaceText(position, position + oldText.length(), text);
            textArea.positionCaret(position + text.length());
        }
    }

    // 最大撤销级数限制，防止内存占用过多
    private static final int MAX_HISTORY_SIZE = 100; // 文本区域引用
    private final TextArea textArea;

    // 撤销栈和重做栈
    private final Stack<TextOperation> undoStack;
    private final Stack<TextOperation> redoStack;

    // 文本的上一个状态，用于检测变化
    private String lastText;

    // 是否正在执行撤销/重做操作（避免操作过程中触发监听器）
    private boolean isUndoRedoOperation;

    /**
     * 构造函数
     * 
     * @param textArea 需要管理撤销/重做的文本区域
     */
    public UndoRedoManager(TextArea textArea) {
        this.textArea = textArea;
        this.undoStack = new Stack<>();
        this.redoStack = new Stack<>();
        this.lastText = textArea.getText();
        this.isUndoRedoOperation = false;

        // 添加文本变化监听器
        setupTextListener();
    }

    /**
     * 设置文本变化监听器
     * 监听文本变化并记录操作历史
     */
    private void setupTextListener() {
        textArea.textProperty().addListener((observable, oldValue, newValue) -> {
            if (isUndoRedoOperation) {
                // 如果是执行撤销/重做操作导致的文本变化，不记录历史
                return;
            }

            // 文本没有变化
            if (oldValue.equals(newValue)) {
                return;
            }

            // 检测操作类型并记录
            detectAndRecordOperation(oldValue, newValue);

            // 更新最后状态
            lastText = newValue;

            // 清空重做栈，因为有了新操作
            redoStack.clear();
        });
    }

    /**
     * 检测操作类型并记录
     * 
     * @param oldText 操作前的文本
     * @param newText 操作后的文本
     */
    private void detectAndRecordOperation(String oldText, String newText) {
        // 文本相同，无需记录
        if (oldText.equals(newText)) {
            return;
        }

        // 文本增加（插入操作）
        if (newText.length() > oldText.length()) {
            // 找出新增的文本及其位置
            if (newText.startsWith(oldText)) {
                // 在末尾添加
                String insertedText = newText.substring(oldText.length());
                addOperation(new InsertOperation(oldText.length(), insertedText));
            } else if (newText.endsWith(oldText)) {
                // 在开头添加
                String insertedText = newText.substring(0, newText.length() - oldText.length());
                addOperation(new InsertOperation(0, insertedText));
            } else { // 在中间插入，需要查找位置
                int diffIndex = findDiffIndex(oldText, newText);
                // 计算共同前缀（用于调试，当前未使用）
                // String commonPrefix = oldText.substring(0, diffIndex);

                // 查找插入后的共同后缀的起始位置
                int oldSuffixStart = diffIndex;
                int newSuffixStart = -1;

                for (int i = diffIndex; i < newText.length(); i++) {
                    if (i + oldText.length() - oldSuffixStart <= newText.length()) {
                        String potentialSuffix = newText.substring(i, i + oldText.length() - oldSuffixStart);
                        String remainingOldText = oldText.substring(oldSuffixStart);

                        if (potentialSuffix.equals(remainingOldText)) {
                            newSuffixStart = i;
                            break;
                        }
                    }
                }

                if (newSuffixStart != -1) {
                    String insertedText = newText.substring(diffIndex, newSuffixStart);
                    addOperation(new InsertOperation(diffIndex, insertedText));
                } else {
                    // 复杂变更，作为替换处理
                    addOperation(new ReplaceOperation(0, oldText, newText));
                }
            }
        }
        // 文本减少（删除操作）
        else if (newText.length() < oldText.length()) {
            // 找出删除的文本及其位置
            if (oldText.startsWith(newText)) {
                // 从末尾删除
                String deletedText = oldText.substring(newText.length());
                addOperation(new DeleteOperation(newText.length(), deletedText));
            } else if (oldText.endsWith(newText)) {
                // 从开头删除
                String deletedText = oldText.substring(0, oldText.length() - newText.length());
                addOperation(new DeleteOperation(0, deletedText));
            } else {
                // 从中间删除，需要查找位置
                int diffIndex = findDiffIndex(oldText, newText);

                // 查找删除后的共同后缀的起始位置
                int oldSuffixStart = -1;

                for (int i = diffIndex; i < oldText.length(); i++) {
                    if (i + newText.length() - diffIndex <= oldText.length()) {
                        String potentialSuffix = oldText.substring(i, i + newText.length() - diffIndex);
                        String remainingNewText = newText.substring(diffIndex);

                        if (potentialSuffix.equals(remainingNewText)) {
                            oldSuffixStart = i;
                            break;
                        }
                    }
                }

                if (oldSuffixStart != -1) {
                    String deletedText = oldText.substring(diffIndex, oldSuffixStart);
                    addOperation(new DeleteOperation(diffIndex, deletedText));
                } else {
                    // 复杂变更，作为替换处理
                    addOperation(new ReplaceOperation(0, oldText, newText));
                }
            }
        }
        // 文本长度相同但内容不同（替换操作）
        else {
            int diffIndex = findDiffIndex(oldText, newText);
            if (diffIndex != -1) {
                int diffEndOld = diffIndex;
                int diffEndNew = diffIndex;

                // 找出差异的结束位置
                while (diffEndOld < oldText.length() && diffEndNew < newText.length() &&
                        oldText.charAt(diffEndOld) != newText.charAt(diffEndNew)) {
                    diffEndOld++;
                    diffEndNew++;
                }

                String oldTextPart = oldText.substring(diffIndex, diffEndOld);
                String newTextPart = newText.substring(diffIndex, diffEndNew);

                addOperation(new ReplaceOperation(diffIndex, oldTextPart, newTextPart));
            }
        }
    }

    /**
     * 查找两个字符串中第一个不同字符的索引
     * 
     * @param s1 第一个字符串
     * @param s2 第二个字符串
     * @return 不同字符的索引，如果没有找到返回-1
     */
    private int findDiffIndex(String s1, String s2) {
        int minLength = Math.min(s1.length(), s2.length());

        for (int i = 0; i < minLength; i++) {
            if (s1.charAt(i) != s2.charAt(i)) {
                return i;
            }
        }

        // 如果前面部分都相同，但长度不同
        if (s1.length() != s2.length()) {
            return minLength;
        }

        // 完全相同
        return -1;
    }

    /**
     * 添加操作到撤销栈
     * 
     * @param operation 要添加的操作
     */
    private void addOperation(TextOperation operation) {
        undoStack.push(operation);

        // 如果历史记录过多，移除最早的记录
        if (undoStack.size() > MAX_HISTORY_SIZE) {
            undoStack.remove(0);
        }
    }

    /**
     * 执行撤销操作
     * 
     * @return 是否成功撤销
     */
    public boolean undo() {
        if (undoStack.isEmpty()) {
            return false;
        }

        TextOperation operation = undoStack.pop();
        isUndoRedoOperation = true;

        try {
            operation.undo(textArea);
            redoStack.push(operation);
            lastText = textArea.getText();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            isUndoRedoOperation = false;
        }
    }

    /**
     * 执行重做操作
     * 
     * @return 是否成功重做
     */
    public boolean redo() {
        if (redoStack.isEmpty()) {
            return false;
        }

        TextOperation operation = redoStack.pop();
        isUndoRedoOperation = true;

        try {
            operation.redo(textArea);
            undoStack.push(operation);
            lastText = textArea.getText();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            isUndoRedoOperation = false;
        }
    }

    /**
     * 检查是否可以撤销
     * 
     * @return 是否可以撤销
     */
    public boolean canUndo() {
        return !undoStack.isEmpty();
    }

    /**
     * 检查是否可以重做
     * 
     * @return 是否可以重做
     */
    public boolean canRedo() {
        return !redoStack.isEmpty();
    }

    /**
     * 获取撤销栈大小
     * 
     * @return 撤销栈大小
     */
    public int getUndoStackSize() {
        return undoStack.size();
    }

    /**
     * 获取重做栈大小
     * 
     * @return 重做栈大小
     */
    public int getRedoStackSize() {
        return redoStack.size();
    }

    /**
     * 清空撤销和重做栈
     */
    public void clear() {
        undoStack.clear();
        redoStack.clear();
        lastText = textArea != null ? textArea.getText() : "";
    }
}
