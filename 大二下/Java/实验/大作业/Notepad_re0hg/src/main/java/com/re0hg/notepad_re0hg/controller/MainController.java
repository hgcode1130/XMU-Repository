/**
 * 主应用控制器类
 * 管理记事本应用的核心功能和其他子控制器
 * MVC架构中的主Controller
 */
package com.re0hg.notepad_re0hg.controller;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

import com.re0hg.notepad_re0hg.model.AppModel;
import com.re0hg.notepad_re0hg.model.DocumentModel;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.Stage;

/**
 * 主应用控制器
 * 协调各个子控制器，管理全局应用逻辑
 */
public class MainController implements Controller {

    // 应用模型
    private AppModel appModel;

    // 主窗口
    private Stage primaryStage;

    // 子控制器映射
    private Map<String, Controller> controllers = new HashMap<>();

    /**
     * 构造函数
     * 
     * @param appModel     应用模型
     * @param primaryStage 主窗口
     */
    public MainController(AppModel appModel, Stage primaryStage) {
        this.appModel = appModel;
        this.primaryStage = primaryStage;
    }

    @Override
    public void initialize() {
        // 注册子控制器
        registerControllers();

        // 初始化所有子控制器
        controllers.values().forEach(Controller::initialize);

        // 设置窗口关闭事件
        setupWindowCloseHandler();

        // 更新窗口标题
        updateWindowTitle();
    }

    @Override
    public String getName() {
        return "mainController";
    }

    /**
     * 注册所有子控制器
     */
    private void registerControllers() {
        // 创建并注册文档控制器
        DocumentController documentController = new DocumentController(appModel);
        registerController(documentController);

        // 创建并注册文件控制器
        FileController fileController = new FileController(appModel, primaryStage);
        registerController(fileController); // 创建并注册编辑控制器
        EditController editController = new EditController(appModel, primaryStage);
        registerController(editController);

        // 创建并注册搜索控制器
        SearchController searchController = new SearchController(appModel, primaryStage);
        registerController(searchController);

        // 创建并注册格式控制器
        com.re0hg.notepad_re0hg.controller.FormatController formatController = new com.re0hg.notepad_re0hg.controller.FormatController(
                appModel, primaryStage);
        registerController(formatController);
        // 创建并注册视图控制器
        com.re0hg.notepad_re0hg.controller.ViewController viewController = new com.re0hg.notepad_re0hg.controller.ViewController(
                appModel, primaryStage);
        registerController(viewController);
        // 创建并注册帮助控制器
        com.re0hg.notepad_re0hg.controller.HelpController helpController = new com.re0hg.notepad_re0hg.controller.HelpController(
                appModel, primaryStage);
        registerController(helpController);
    }

    /**
     * 注册子控制器
     * 
     * @param controller 要注册的控制器
     */
    private void registerController(Controller controller) {
        controllers.put(controller.getName(), controller);
    }

    /**
     * 获取子控制器
     * 
     * @param <T>  控制器类型
     * @param name 控制器名称
     * @return 对应的控制器实例
     */
    @SuppressWarnings("unchecked")
    public <T extends Controller> T getController(String name) {
        return (T) controllers.get(name);
    }

    /**
     * 设置窗口关闭事件处理
     */
    private void setupWindowCloseHandler() {
        primaryStage.setOnCloseRequest(event -> {
            DocumentModel document = appModel.getActiveDocument();

            // 如果文档已修改但未保存，询问用户是否保存
            if (document != null && document.isModified()) {
                String title = document.getFile() != null ? document.getFile().getName() : "无标题";

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
                        FileController fileController = getController("fileController");
                        boolean saved = document.getFile() != null ? fileController.saveDocument()
                                : fileController.saveAsDocument();

                        if (!saved) {
                            event.consume(); // 取消关闭
                        }
                    } else if (result.get() == cancelButton) {
                        // 用户选择取消
                        event.consume(); // 取消关闭
                    }
                    // 如选择"不保存"，则不做任何处理，让应用程序关闭
                }
            }
        });
    }

    /**
     * 更新窗口标题
     */
    public void updateWindowTitle() {
        DocumentModel document = appModel.getActiveDocument();
        String modified = document.isModified() ? "*" : "";
        String fileName = document.getFile() != null ? document.getFile().getName() : "无标题";

        primaryStage.setTitle(modified + fileName + " - 记事本");
    }

    /**
     * 创建新窗口
     */
    public void createNewWindow() {
        try {
            // 创建新的应用实例
            javafx.application.Platform.runLater(() -> {
                try {
                    // 创建新的Stage
                    Stage newStage = new Stage();

                    // 加载FXML
                    FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/re0hg/notepad_re0hg/Main.fxml"));
                    Parent root = loader.load();

                    // 创建场景
                    Scene scene = new Scene(root);
                    newStage.setScene(scene);

                    // 设置窗口标题
                    newStage.setTitle("无标题 - 记事本");

                    // 设置窗口图标
                    newStage.getIcons()
                            .add(new javafx.scene.image.Image("file:src/main/java/com/re0hg/notepad_re0hg/icon.png"));

                    // 显示新窗口
                    newStage.show();

                } catch (Exception e) {
                    e.printStackTrace();
                    Alert alert = new Alert(AlertType.ERROR);
                    alert.setTitle("错误");
                    alert.setHeaderText("无法创建新窗口");
                    alert.setContentText("创建新窗口时出错: " + e.getMessage());
                    alert.showAndWait();
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 退出应用程序
     */
    public void exitApplication() {
        primaryStage.close();
    }
}
