/**
 * 文件IO工具类
 * 提供文件读写操作的工具方法，并进行统一的异常处理
 * 
 * @author re0hg
 */
package com.re0hg.notepad_re0hg.utils;

import java.io.*;
import java.nio.charset.*;
import java.nio.file.*;
import java.util.logging.Level;
import java.util.logging.Logger;

import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;

public class FileIOUtils {

    private static final Logger logger = Logger.getLogger(FileIOUtils.class.getName());

    /**
     * 读取文本文件内容
     * 
     * @param file 要读取的文件
     * @return 文件内容的字符串，如果读取失败返回null
     */
    public static String readTextFile(File file) {
        if (file == null || !file.exists()) {
            showErrorDialog("文件错误", "文件不存在", "无法找到文件: " + (file != null ? file.getAbsolutePath() : "null"));
            return null;
        }

        try {
            // 使用NIO读取文件，自动关闭资源
            return Files.readString(file.toPath(), StandardCharsets.UTF_8);
        } catch (MalformedInputException e) {
            // 处理编码问题，尝试使用其他编码
            try {
                // 尝试使用GBK编码读取
                return Files.readString(file.toPath(), Charset.forName("GBK"));
            } catch (IOException ex) {
                handleReadException(file, ex);
                return null;
            }
        } catch (IOException e) {
            handleReadException(file, e);
            return null;
        }
    }

    /**
     * 写入文本到文件
     * 
     * @param file    目标文件
     * @param content 要写入的内容
     * @return 是否写入成功
     */
    public static boolean writeTextFile(File file, String content) {
        if (file == null) {
            showErrorDialog("文件错误", "文件不存在", "无法创建或写入文件");
            return false;
        }

        try {
            // 使用NIO写入文件，自动关闭资源
            Files.writeString(file.toPath(), content, StandardCharsets.UTF_8);
            return true;
        } catch (IOException e) {
            handleWriteException(file, e);
            return false;
        }
    }

    /**
     * 处理文件读取异常
     * 
     * @param file 读取的文件
     * @param e    捕获的异常
     */
    private static void handleReadException(File file, Exception e) {
        logger.log(Level.WARNING, "读取文件失败: " + file.getAbsolutePath(), e);

        String errorDetail;
        if (e instanceof FileNotFoundException) {
            errorDetail = "找不到文件，可能已被删除或移动";
        } else if (e instanceof SecurityException) {
            errorDetail = "没有权限读取该文件";
        } else if (e instanceof CharacterCodingException) {
            errorDetail = "文件编码不兼容，无法正确读取内容";
        } else {
            errorDetail = "读取文件时出错: " + e.getMessage();
        }

        showErrorDialog("读取错误", "无法读取文件", errorDetail);
    }

    /**
     * 处理文件写入异常
     * 
     * @param file 写入的文件
     * @param e    捕获的异常
     */
    private static void handleWriteException(File file, Exception e) {
        logger.log(Level.WARNING, "写入文件失败: " + file.getAbsolutePath(), e);

        String errorDetail;
        if (e instanceof FileNotFoundException) {
            errorDetail = "无法创建或访问文件";
        } else if (e instanceof SecurityException) {
            errorDetail = "没有权限写入该文件";
        } else if (e instanceof IOException && e.getMessage().contains("disk")) {
            errorDetail = "磁盘空间不足或磁盘写入错误";
        } else {
            errorDetail = "写入文件时出错: " + e.getMessage();
        }

        showErrorDialog("保存错误", "无法保存文件", errorDetail);
    }

    /**
     * 显示错误对话框
     * 
     * @param title   对话框标题
     * @param header  对话框头部文本
     * @param content 对话框内容
     */
    private static void showErrorDialog(String title, String header, String content) {
        Alert alert = new Alert(AlertType.ERROR);
        alert.setTitle(title);
        alert.setHeaderText(header);
        alert.setContentText(content);
        alert.showAndWait();
    }
}
