/**
 * 应用程序模型类
 * 管理记事本应用的全局状态和数据
 * 作为MVC架构中Model层的核心组件
 */
package com.re0hg.notepad_re0hg.model;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javafx.beans.property.ListProperty;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;

/**
 * 应用程序模型类
 * 管理记事本应用的全局状态、设置和多个文档
 */
public class AppModel {

    /**
     * 当前活动文档
     */
    private final ObjectProperty<DocumentModel> activeDocument = new SimpleObjectProperty<>();

    /**
     * 打开的文档列表
     */
    private final ListProperty<DocumentModel> documents = new SimpleListProperty<>(FXCollections.observableArrayList());

    /**
     * 应用配置
     */
    private final AppConfig config = new AppConfig();

    /**
     * 应用模型监听器列表
     */
    private final List<AppModelListener> listeners = new ArrayList<>();

    /**
     * 页面设置模型
     */
    private final PageSetupModel pageSetup = new PageSetupModel();

    /**
     * 构造函数
     * 创建应用模型并初始化默认文档
     */
    public AppModel() {
        // 创建默认文档
        DocumentModel defaultDoc = new DocumentModel();
        documents.add(defaultDoc);
        setActiveDocument(defaultDoc);
    }

    /**
     * 获取应用配置
     * 
     * @return 应用配置对象
     */
    public AppConfig getConfig() {
        return config;
    }

    /**
     * 获取当前活动文档
     * 
     * @return 当前活动文档
     */
    public DocumentModel getActiveDocument() {
        return activeDocument.get();
    }

    /**
     * 设置当前活动文档
     * 
     * @param document 要设置为活动的文档
     */
    public void setActiveDocument(DocumentModel document) {
        if (document != null && !documents.contains(document)) {
            documents.add(document);
        }
        activeDocument.set(document);
        notifyActiveDocumentChanged();
    }

    /**
     * 获取活动文档属性
     * 
     * @return 活动文档属性
     */
    public ObjectProperty<DocumentModel> activeDocumentProperty() {
        return activeDocument;
    }

    /**
     * 获取文档列表
     * 
     * @return 文档列表
     */
    public ObservableList<DocumentModel> getDocuments() {
        return documents.get();
    }

    /**
     * 获取文档列表属性
     * 
     * @return 文档列表属性
     */
    public ListProperty<DocumentModel> documentsProperty() {
        return documents;
    }

    /**
     * 创建新文档
     * 
     * @return 新创建的文档
     */
    public DocumentModel createNewDocument() {
        DocumentModel newDoc = new DocumentModel();
        documents.add(newDoc);
        setActiveDocument(newDoc);
        return newDoc;
    }

    /**
     * 打开文件
     * 
     * @param file 要打开的文件
     * @return 加载的文档
     * @throws IOException 如果文件加载失败
     */
    public DocumentModel openDocument(File file) throws IOException {
        // 检查文件是否已经打开
        for (DocumentModel doc : documents) {
            File docFile = doc.getFile();
            if (docFile != null && docFile.equals(file)) {
                setActiveDocument(doc);
                return doc;
            }
        }

        // 创建新文档并加载文件
        DocumentModel newDoc = new DocumentModel();
        newDoc.loadFile(file);
        documents.add(newDoc);
        setActiveDocument(newDoc);
        return newDoc;
    }

    /**
     * 关闭文档
     * 
     * @param document 要关闭的文档
     * @return 如果成功关闭返回true，否则返回false
     */
    public boolean closeDocument(DocumentModel document) {
        if (document == null || !documents.contains(document)) {
            return false;
        }

        // 从列表中移除文档
        boolean removed = documents.remove(document);

        // 如果关闭的是当前活动文档，则激活另一个文档
        if (removed && document == getActiveDocument()) {
            if (!documents.isEmpty()) {
                setActiveDocument(documents.get(documents.size() - 1));
            } else {
                // 如果没有文档了，创建一个新文档
                setActiveDocument(createNewDocument());
            }
        }

        return removed;
    }

    /**
     * 保存活动文档
     * 
     * @return 如果保存成功返回true，否则返回false
     * @throws IOException 如果保存失败
     */
    public boolean saveActiveDocument() throws IOException {
        DocumentModel doc = getActiveDocument();
        if (doc != null) {
            return doc.save();
        }
        return false;
    }

    /**
     * 将活动文档另存为指定文件
     * 
     * @param file 保存的目标文件
     * @return 如果保存成功返回true，否则返回false
     * @throws IOException 如果保存失败
     */
    public boolean saveActiveDocumentAs(File file) throws IOException {
        DocumentModel doc = getActiveDocument();
        if (doc != null) {
            return doc.saveAs(file);
        }
        return false;
    }

    /**
     * 添加应用模型监听器
     * 
     * @param listener 监听器
     */
    public void addAppModelListener(AppModelListener listener) {
        if (!listeners.contains(listener)) {
            listeners.add(listener);
        }
    }

    /**
     * 移除应用模型监听器
     * 
     * @param listener 监听器
     */
    public void removeAppModelListener(AppModelListener listener) {
        listeners.remove(listener);
    }

    /**
     * 通知活动文档变化
     */
    private void notifyActiveDocumentChanged() {
        for (AppModelListener listener : listeners) {
            listener.onActiveDocumentChanged(getActiveDocument());
        }
    }

    /**
     * 应用模型监听器接口
     */
    public interface AppModelListener {
        /**
         * 当活动文档变化时调用
         * 
         * @param document 新的活动文档
         */
        void onActiveDocumentChanged(DocumentModel document);
    }

    /**
     * 应用配置类
     * 存储应用程序的全局设置
     */
    public class AppConfig {
        // 搜索相关
        private String searchText = "";
        private String replaceText = "";
        private boolean ignoreCase = false;

        // 字体相关
        private Font font = Font.font("微软雅黑", FontWeight.NORMAL, FontPosture.REGULAR, 20);
        private String fontFamily = "微软雅黑";
        private FontWeight fontWeight = FontWeight.NORMAL;
        private FontPosture fontPosture = FontPosture.REGULAR;
        private double fontSize = 20;
        private String fontColor = "black";

        // 界面相关
        private boolean wordWrap = false;
        private boolean statusBarVisible = true;
        private int zoomPercentage = 100;

        // 转到行号
        private int gotoLineNum = 1;

        /**
         * 获取搜索文本
         * 
         * @return 搜索文本
         */
        public String getSearchText() {
            return searchText;
        }

        /**
         * 设置搜索文本
         * 
         * @param searchText 搜索文本
         */
        public void setSearchText(String searchText) {
            this.searchText = searchText;
        }

        /**
         * 获取替换文本
         * 
         * @return 替换文本
         */
        public String getReplaceText() {
            return replaceText;
        }

        /**
         * 设置替换文本
         * 
         * @param replaceText 替换文本
         */
        public void setReplaceText(String replaceText) {
            this.replaceText = replaceText;
        }

        /**
         * 是否忽略大小写
         * 
         * @return 如果忽略大小写返回true，否则返回false
         */
        public boolean isIgnoreCase() {
            return ignoreCase;
        }

        /**
         * 设置是否忽略大小写
         * 
         * @param ignoreCase 是否忽略大小写
         */
        public void setIgnoreCase(boolean ignoreCase) {
            this.ignoreCase = ignoreCase;
        }

        /**
         * 获取当前字体
         * 
         * @return 字体对象
         */
        public Font getFont() {
            return font;
        }

        /**
         * 设置字体
         * 
         * @param font 字体对象
         */
        public void setFont(Font font) {
            this.font = font;
            if (font != null) {
                this.fontFamily = font.getFamily();
                this.fontSize = font.getSize();
            }
        }

        /**
         * 获取字体家族
         * 
         * @return 字体家族名称
         */
        public String getFontFamily() {
            return fontFamily;
        }

        /**
         * 设置字体家族
         * 
         * @param fontFamily 字体家族名称
         */
        public void setFontFamily(String fontFamily) {
            this.fontFamily = fontFamily;
            updateFont();
        }

        /**
         * 获取字体粗细
         * 
         * @return 字体粗细
         */
        public FontWeight getFontWeight() {
            return fontWeight;
        }

        /**
         * 设置字体粗细
         * 
         * @param fontWeight 字体粗细
         */
        public void setFontWeight(FontWeight fontWeight) {
            this.fontWeight = fontWeight;
            updateFont();
        }

        /**
         * 获取字体姿态
         * 
         * @return 字体姿态
         */
        public FontPosture getFontPosture() {
            return fontPosture;
        }

        /**
         * 设置字体姿态
         * 
         * @param fontPosture 字体姿态
         */
        public void setFontPosture(FontPosture fontPosture) {
            this.fontPosture = fontPosture;
            updateFont();
        }

        /**
         * 获取字体大小
         * 
         * @return 字体大小
         */
        public double getFontSize() {
            return fontSize;
        }

        /**
         * 设置字体大小
         * 
         * @param fontSize 字体大小
         */
        public void setFontSize(double fontSize) {
            this.fontSize = fontSize;
            updateFont();
        }

        /**
         * 获取字体颜色
         * 
         * @return 字体颜色
         */
        public String getFontColor() {
            return fontColor;
        }

        /**
         * 设置字体颜色
         * 
         * @param fontColor 字体颜色
         */
        public void setFontColor(String fontColor) {
            this.fontColor = fontColor;
        }

        /**
         * 是否自动换行
         * 
         * @return 如果自动换行返回true，否则返回false
         */
        public boolean isWordWrap() {
            return wordWrap;
        }

        /**
         * 设置是否自动换行
         * 
         * @param wordWrap 是否自动换行
         */
        public void setWordWrap(boolean wordWrap) {
            this.wordWrap = wordWrap;
        }

        /**
         * 状态栏是否可见
         * 
         * @return 如果状态栏可见返回true，否则返回false
         */
        public boolean isStatusBarVisible() {
            return statusBarVisible;
        }

        /**
         * 设置状态栏是否可见
         * 
         * @param statusBarVisible 状态栏可见性
         */
        public void setStatusBarVisible(boolean statusBarVisible) {
            this.statusBarVisible = statusBarVisible;
        }

        /**
         * 获取缩放百分比
         * 
         * @return 缩放百分比
         */
        public int getZoomPercentage() {
            return zoomPercentage;
        }

        /**
         * 设置缩放百分比
         * 
         * @param zoomPercentage 缩放百分比
         */
        public void setZoomPercentage(int zoomPercentage) {
            this.zoomPercentage = zoomPercentage;
            // 更新字体大小以反映缩放
            updateFont();
        }

        /**
         * 获取转到行号
         * 
         * @return 目标行号
         */
        public int getGotoLineNum() {
            return gotoLineNum;
        }

        /**
         * 设置转到行号
         * 
         * @param gotoLineNum 目标行号
         */
        public void setGotoLineNum(int gotoLineNum) {
            this.gotoLineNum = gotoLineNum;
        }

        /**
         * 更新字体对象
         * 根据当前字体设置重新创建Font对象
         */
        private void updateFont() {
            this.font = Font.font(fontFamily, fontWeight, fontPosture, fontSize);
        }
    }

    /**
     * 获取页面设置模型
     * 
     * @return 页面设置模型对象
     */
    public PageSetupModel getPageSetup() {
        return pageSetup;
    }
}
