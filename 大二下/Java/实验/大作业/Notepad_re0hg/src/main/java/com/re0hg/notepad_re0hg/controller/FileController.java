/**
 * 文件控制器类
 * 处理文件操作相关的功能
 * MVC架构中处理文件操作的Controller
 */
package com.re0hg.notepad_re0hg.controller;

import java.io.File;
import java.io.IOException;
import java.util.Optional;

import com.re0hg.notepad_re0hg.model.AppModel;
import com.re0hg.notepad_re0hg.model.DocumentModel;
import com.re0hg.notepad_re0hg.utils.FileIOUtils;

import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.FileChooser;
import javafx.stage.FileChooser.ExtensionFilter;
import javafx.stage.Stage;
import javafx.scene.control.Dialog;
import javafx.scene.control.DialogPane;
import javafx.fxml.FXMLLoader;

/**
 * 文件控制器类
 * 处理文件操作，如新建、打开、保存等
 */
public class FileController implements Controller {

    // 应用模型
    private final AppModel appModel;

    // 主窗口
    private final Stage stage;

    // 文件选择器过滤器
    private final ExtensionFilter txtFilter = new FileChooser.ExtensionFilter("文本文档", "*.txt");
    private final ExtensionFilter allFilter = new FileChooser.ExtensionFilter("所有文件", "*.*");

    /**
     * 构造函数
     * 
     * @param appModel 应用模型
     * @param stage    主窗口
     */
    public FileController(AppModel appModel, Stage stage) {
        this.appModel = appModel;
        this.stage = stage;
    }

    @Override
    public void initialize() {
        // 文件控制器初始化，无需特殊操作
    }

    @Override
    public String getName() {
        return "fileController";
    }

    /**
     * 创建新文档
     * 
     * @return 新建的文档模型
     */
    public DocumentModel newDocument() {
        // 先询问用户是否保存当前文档的更改
        SaveResult saveResult = promptSaveChanges();

        // 用户取消了操作
        if (saveResult == SaveResult.CANCEL) {
            return null;
        }

        // 创建新文档并设置为活动文档
        DocumentModel newDoc = new DocumentModel();
        appModel.setActiveDocument(newDoc);

        // 更新窗口标题
        updateWindowTitle();

        return newDoc;
    }

    /**
     * 打开文档
     * 
     * @return 是否成功打开文档
     */
    public boolean openDocument() {
        // 首先创建文件选择器
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("打开文件");
        fileChooser.getExtensionFilters().addAll(txtFilter, allFilter);

        // 先显示打开文件对话框
        File selectedFile = fileChooser.showOpenDialog(stage);

        // 如果用户取消了文件选择，直接返回
        if (selectedFile == null) {
            return false;
        }

        // 用户已选择文件，现在检查当前文档是否需要保存
        SaveResult saveResult = promptSaveChanges();

        // 用户取消了保存操作
        if (saveResult == SaveResult.CANCEL) {
            return false;
        }

        // 处理打开选择的文件
        try {
            // 尝试打开文件
            String content = FileIOUtils.readTextFile(selectedFile);
            if (content != null) {
                // 创建新文档模型
                DocumentModel doc = new DocumentModel();
                doc.setContent(content);
                doc.setFile(selectedFile);
                doc.setModified(false);

                // 设置为活动文档
                appModel.setActiveDocument(doc);

                // 更新窗口标题
                updateWindowTitle();

                return true;
            }
        } catch (Exception e) {
            showErrorAlert("打开文件", "无法打开文件", "文件读取错误: " + e.getMessage());
        }

        return false;
    }

    /**
     * 保存当前文档
     * 
     * @return 是否成功保存
     */
    public boolean saveDocument() {
        DocumentModel doc = appModel.getActiveDocument();
        if (doc == null) {
            return false;
        }

        // 如果文档没有关联文件，则执行"另存为"
        if (doc.getFile() == null) {
            return saveAsDocument();
        }

        // 执行保存操作
        boolean success = saveDocumentToFile(doc, doc.getFile());
        if (success) {
            // 更新文档状态和窗口标题
            doc.setModified(false);
            updateWindowTitle();
        }

        return success;
    }

    /**
     * 将文档另存为新文件
     * 
     * @return 是否成功保存
     */
    public boolean saveAsDocument() {
        DocumentModel doc = appModel.getActiveDocument();
        if (doc == null) {
            return false;
        }

        // 创建文件选择器
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("另存为");
        fileChooser.getExtensionFilters().addAll(txtFilter, allFilter);

        // 设置初始目录和文件名
        if (doc.getFile() != null) {
            fileChooser.setInitialDirectory(doc.getFile().getParentFile());
            fileChooser.setInitialFileName(doc.getFile().getName());
        }

        // 显示保存文件对话框
        File file = fileChooser.showSaveDialog(stage);
        if (file != null) {
            // 执行保存操作
            boolean success = saveDocumentToFile(doc, file);
            if (success) {
                // 更新文档关联的文件
                doc.setFile(file);
                doc.setModified(false);

                // 更新窗口标题
                updateWindowTitle();
            }
            return success;
        }

        return false;
    }

    /**
     * 保存文档到指定文件
     * 
     * @param doc  文档模型
     * @param file 目标文件
     * @return 是否成功保存
     */
    private boolean saveDocumentToFile(DocumentModel doc, File file) {
        try {
            // 使用FileIOUtils工具类保存文件
            boolean success = FileIOUtils.writeTextFile(file, doc.getContent());
            if (!success) {
                showErrorAlert("保存文件", "无法保存文件", "文件写入失败");
            }
            return success;
        } catch (Exception e) {
            showErrorAlert("保存文件", "无法保存文件", "文件写入错误: " + e.getMessage());
            return false;
        }
    }

    /**
     * 提示用户保存更改
     * 
     * @return 用户是否取消了操作
     */
    /**
     * 提示用户保存更改，提供保存、不保存、取消三个选项
     * 
     * @return 保存操作结果：
     *         - SAVE_SUCCEEDED: 用户选择保存并成功保存
     *         - DONT_SAVE: 用户选择不保存
     *         - CANCEL: 用户取消操作或保存失败
     */
    private SaveResult promptSaveChanges() {
        DocumentModel doc = appModel.getActiveDocument();
        if (doc == null || !doc.isModified()) {
            return SaveResult.DONT_SAVE; // 没有需要保存的内容
        }

        String title = doc.getFile() != null ? doc.getFile().getName() : "无标题";

        Alert alert = new Alert(AlertType.CONFIRMATION);
        alert.setTitle("记事本");
        alert.setHeaderText("你想将更改保存到 " + title + " 吗？");

        ButtonType saveButton = new ButtonType("保存");
        ButtonType dontSaveButton = new ButtonType("不保存");
        ButtonType cancelButton = ButtonType.CANCEL;

        alert.getButtonTypes().setAll(saveButton, dontSaveButton, cancelButton);

        Optional<ButtonType> result = alert.showAndWait();
        if (result.isPresent()) {
            if (result.get() == saveButton) {
                // 用户选择保存
                boolean saved = saveDocument();
                return saved ? SaveResult.SAVE_SUCCEEDED : SaveResult.CANCEL;
            } else if (result.get() == dontSaveButton) {
                // 用户选择不保存
                return SaveResult.DONT_SAVE;
            } else {
                // 用户取消操作
                return SaveResult.CANCEL;
            }
        }

        // 默认取消
        return SaveResult.CANCEL;
    }

    /**
     * 保存操作的结果枚举
     */
    private enum SaveResult {
        SAVE_SUCCEEDED, // 保存成功
        DONT_SAVE, // 不保存
        CANCEL // 取消操作
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
     * 更新窗口标题
     */
    private void updateWindowTitle() {
        DocumentModel doc = appModel.getActiveDocument();
        if (doc != null) {
            String modified = doc.isModified() ? "*" : "";
            String fileName = doc.getFile() != null ? doc.getFile().getName() : "无标题";
            stage.setTitle(modified + fileName + " - 记事本");
        }
    }

    /**
     * 显示页面设置对话框
     */
    public void showPageSetupDialog() {
        try {
            // 加载FXML
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/com/re0hg/notepad_re0hg/PageSetup.fxml"));
            DialogPane dialogPane = loader.load();

            // 创建对话框
            Dialog<ButtonType> dialog = new Dialog<>();
            dialog.setDialogPane(dialogPane);
            dialog.setTitle("页面设置");

            // 获取控制器并设置模型
            PageSetupController controller = loader.getController();
            controller.setPageSetupModel(appModel.getPageSetup());

            // 显示对话框并等待响应
            Optional<ButtonType> result = dialog.showAndWait();

            // 如果用户点击了确定，更新模型
            if (result.isPresent() && result.get() == ButtonType.OK) {
                controller.updateModel();
            }
        } catch (IOException e) {
            showErrorAlert("页面设置", "无法打开页面设置对话框", "错误: " + e.getMessage());
        }
    }
}
