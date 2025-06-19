/**
 * 文档模型类
 * 用于封装记事本文档的数据和业务逻辑
 * 实现MVC架构中的Model层
 */
package com.re0hg.notepad_re0hg.model;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import com.re0hg.notepad_re0hg.utils.FileIOUtils;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 * 文档模型类
 * 表示记事本中的一个文本文档
 * 管理文档的内容、路径、修改状态等
 */
public class DocumentModel {
    /**
     * 文档内容
     */
    private final StringProperty content = new SimpleStringProperty("");

    /**
     * 文档文件路径
     */
    private final ObjectProperty<File> file = new SimpleObjectProperty<>(null);

    /**
     * 文档是否已修改
     */
    private final BooleanProperty modified = new SimpleBooleanProperty(false);

    /**
     * 文档监听器列表
     */
    private final List<DocumentListener> listeners = new ArrayList<>();

    /**
     * 文档状态
     * 1：新建文档 - 初始状态
     * 2：已修改但未保存 - 内容有变更
     * 3：已保存 - 所有变更已保存到文件
     */
    private int status = 1;

    /**
     * 默认构造函数
     * 创建一个新的空文档
     */
    public DocumentModel() {
        // 监听内容变化，更新修改状态
        content.addListener((observable, oldValue, newValue) -> {
            if (!oldValue.equals(newValue)) {
                setModified(true);
                status = 2;
                notifyContentChanged();
            }
        });
    }

    /**
     * 使用文件路径构造文档
     * 
     * @param file 文档文件
     * @throws IOException 如果文件读取失败
     */
    public DocumentModel(File file) throws IOException {
        this();
        loadFile(file);
    }

    /**
     * 获取文档内容
     * 
     * @return 文档内容的字符串属性
     */
    public StringProperty contentProperty() {
        return content;
    }

    /**
     * 获取文档内容字符串
     * 
     * @return 文档内容字符串
     */
    public String getContent() {
        return content.get();
    }

    /**
     * 设置文档内容
     * 
     * @param newContent 新的文档内容
     */
    public void setContent(String newContent) {
        content.set(newContent);
    }

    /**
     * 获取文档文件
     * 
     * @return 文档文件对象
     */
    public File getFile() {
        return file.get();
    }

    /**
     * 设置文档文件
     * 
     * @param file 文档文件对象
     */
    public void setFile(File file) {
        this.file.set(file);
        notifyFileChanged();
    }

    /**
     * 获取文件属性
     * 
     * @return 文件对象属性
     */
    public ObjectProperty<File> fileProperty() {
        return file;
    }

    /**
     * 获取文档是否被修改
     * 
     * @return 如果文档被修改返回true，否则返回false
     */
    public boolean isModified() {
        return modified.get();
    }

    /**
     * 设置文档的修改状态
     * 
     * @param modified 修改状态
     */
    public void setModified(boolean modified) {
        this.modified.set(modified);
        if (modified) {
            status = 2;
        } else {
            status = 3;
        }
    }

    /**
     * 获取修改状态属性
     * 
     * @return 修改状态属性
     */
    public BooleanProperty modifiedProperty() {
        return modified;
    }

    /**
     * 获取文件名
     * 
     * @return 文件名，如果没有文件则返回"无标题"
     */
    public String getFileName() {
        File f = file.get();
        return f == null ? "无标题" : f.getName();
    }

    /**
     * 获取文件路径
     * 
     * @return 文件完整路径，如果没有文件则返回null
     */
    public String getFilePath() {
        File f = file.get();
        return f == null ? null : f.getAbsolutePath();
    }

    /**
     * 创建新文档
     * 清空内容并重置状态
     */
    public void newDocument() {
        setContent("");
        setFile(null);
        setModified(false);
        status = 1;
        notifyDocumentNew();
    }

    /**
     * 从文件加载文档
     * 
     * @param file 要加载的文件
     * @throws IOException 如果文件读取失败
     */
    public void loadFile(File file) throws IOException {
        if (file != null && file.exists() && file.canRead()) {
            String fileContent = FileIOUtils.readTextFile(file);
            setContent(fileContent);
            setFile(file);
            setModified(false);
            status = 3;
            notifyDocumentLoaded();
        } else {
            throw new IOException("无法读取文件: " + (file == null ? "null" : file.getAbsolutePath()));
        }
    }

    /**
     * 保存文档到当前文件
     * 如果没有关联的文件，则执行另存为操作
     * 
     * @return 如果保存成功返回true，否则返回false
     * @throws IOException 如果保存失败
     */
    public boolean save() throws IOException {
        File currentFile = file.get();
        if (currentFile == null) {
            return false;
        }

        return saveAs(currentFile);
    }

    /**
     * 将文档保存到指定文件
     * 
     * @param file 保存的目标文件
     * @return 如果保存成功返回true，否则返回false
     * @throws IOException 如果保存失败
     */
    public boolean saveAs(File file) throws IOException {
        if (file == null) {
            return false;
        }

        // 检查文件是否可写
        if (file.exists() && !file.canWrite()) {
            throw new IOException("没有足够的权限写入该文件");
        }

        // 使用FileIOUtils工具类保存文件
        boolean success = FileIOUtils.writeTextFile(file, getContent());
        if (success) {
            setFile(file);
            setModified(false);
            status = 3;
            notifyDocumentSaved();
            return true;
        } else {
            return false;
        }
    }

    /**
     * 获取当前文档状态
     * 
     * @return 当前状态码(1:新建, 2:已修改, 3:已保存)
     */
    public int getStatus() {
        return status;
    }

    /**
     * 添加文档监听器
     * 
     * @param listener 文档监听器
     */
    public void addDocumentListener(DocumentListener listener) {
        if (!listeners.contains(listener)) {
            listeners.add(listener);
        }
    }

    /**
     * 移除文档监听器
     * 
     * @param listener 要移除的监听器
     */
    public void removeDocumentListener(DocumentListener listener) {
        listeners.remove(listener);
    }

    /**
     * 通知内容变化
     */
    private void notifyContentChanged() {
        for (DocumentListener listener : listeners) {
            listener.onContentChanged(this);
        }
    }

    /**
     * 通知文件变化
     */
    private void notifyFileChanged() {
        for (DocumentListener listener : listeners) {
            listener.onFileChanged(this);
        }
    }

    /**
     * 通知新建文档
     */
    private void notifyDocumentNew() {
        for (DocumentListener listener : listeners) {
            listener.onDocumentNew(this);
        }
    }

    /**
     * 通知文档已加载
     */
    private void notifyDocumentLoaded() {
        for (DocumentListener listener : listeners) {
            listener.onDocumentLoaded(this);
        }
    }

    /**
     * 通知文档已保存
     */
    private void notifyDocumentSaved() {
        for (DocumentListener listener : listeners) {
            listener.onDocumentSaved(this);
        }
    }

    /**
     * 文档监听器接口
     * 用于通知文档状态变化
     */
    public interface DocumentListener {
        /**
         * 当文档内容变化时调用
         * 
         * @param document 发生变化的文档
         */
        void onContentChanged(DocumentModel document);

        /**
         * 当文档关联的文件变化时调用
         * 
         * @param document 发生变化的文档
         */
        void onFileChanged(DocumentModel document);

        /**
         * 当创建新文档时调用
         * 
         * @param document 新创建的文档
         */
        void onDocumentNew(DocumentModel document);

        /**
         * 当文档从文件加载时调用
         * 
         * @param document 加载的文档
         */
        void onDocumentLoaded(DocumentModel document);

        /**
         * 当文档保存时调用
         * 
         * @param document 保存的文档
         */
        void onDocumentSaved(DocumentModel document);
    }
}
