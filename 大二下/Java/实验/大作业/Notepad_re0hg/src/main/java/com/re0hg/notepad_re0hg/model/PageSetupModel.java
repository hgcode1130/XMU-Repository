/**
 * 页面设置模型类
 * 存储页面设置相关的属性
 */
package com.re0hg.notepad_re0hg.model;

import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 * 页面设置模型
 * 存储打印和页面布局相关的参数
 */
public class PageSetupModel { // 页面大小（纸张类型）
    private final StringProperty paperSize = new SimpleStringProperty("A4 (210 x 297 mm)");

    // 页面方向
    private final StringProperty orientation = new SimpleStringProperty("纵向");

    // 页边距（单位：厘米）
    private final DoubleProperty leftMargin = new SimpleDoubleProperty(2.0);
    private final DoubleProperty rightMargin = new SimpleDoubleProperty(2.0);
    private final DoubleProperty topMargin = new SimpleDoubleProperty(2.0);
    private final DoubleProperty bottomMargin = new SimpleDoubleProperty(2.0);

    // 页眉
    private final StringProperty header = new SimpleStringProperty("");

    // 页脚
    private final StringProperty footer = new SimpleStringProperty("");

    /**
     * 默认构造函数
     */
    public PageSetupModel() {
        // 使用默认值
    }

    // Getter和Setter方法
    public String getPaper() {
        return paperSize.get();
    }

    public void setPaper(String paper) {
        this.paperSize.set(paper);
    }

    public StringProperty paperProperty() {
        return paperSize;
    }

    public String getOrientation() {
        return orientation.get();
    }

    public void setOrientation(String orientation) {
        this.orientation.set(orientation);
    }

    public StringProperty orientationProperty() {
        return orientation;
    }

    public double getLeftMargin() {
        return leftMargin.get();
    }

    public void setLeftMargin(double margin) {
        this.leftMargin.set(margin);
    }

    public DoubleProperty leftMarginProperty() {
        return leftMargin;
    }

    public double getRightMargin() {
        return rightMargin.get();
    }

    public void setRightMargin(double margin) {
        this.rightMargin.set(margin);
    }

    public DoubleProperty rightMarginProperty() {
        return rightMargin;
    }

    public double getTopMargin() {
        return topMargin.get();
    }

    public void setTopMargin(double margin) {
        this.topMargin.set(margin);
    }

    public DoubleProperty topMarginProperty() {
        return topMargin;
    }

    public double getBottomMargin() {
        return bottomMargin.get();
    }

    public void setBottomMargin(double margin) {
        this.bottomMargin.set(margin);
    }

    public DoubleProperty bottomMarginProperty() {
        return bottomMargin;
    }

    public String getHeader() {
        return header.get();
    }

    public void setHeader(String header) {
        this.header.set(header);
    }

    public StringProperty headerProperty() {
        return header;
    }

    public String getFooter() {
        return footer.get();
    }

    public void setFooter(String footer) {
        this.footer.set(footer);
    }

    public StringProperty footerProperty() {
        return footer;
    }
}
