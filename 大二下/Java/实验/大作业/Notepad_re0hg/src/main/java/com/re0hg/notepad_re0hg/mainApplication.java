/**
 * 记事本应用程序的主入口类
 * 基于MVC架构实现
 * 用于启动程序，加载主界面，并设置窗口属性和事件监听器
 */
package com.re0hg.notepad_re0hg;

import java.util.HashMap;
import java.util.Map;

import com.re0hg.notepad_re0hg.controller.MainController;
import com.re0hg.notepad_re0hg.model.AppModel;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.fxml.JavaFXBuilderFactory;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

/**
 * 主应用程序类
 * 实现JavaFX应用程序生命周期方法
 * MVC架构版本
 */
public class mainApplication extends Application {
    /**
     * 存储应用程序中所有控制器的静态Map集合
     * 用于在不同控制器间共享访问
     */
    public static Map<String, Object> controllers = new HashMap<>();

    /**
     * 存储应用程序全局变量的静态Map集合
     * 用于在整个应用程序中共享数据
     */
    public static Map<String, Object> globals = new HashMap<>();

    /**
     * 应用模型实例
     */
    private AppModel appModel;

    /**
     * 主控制器实例
     */
    private MainController mainController;

    /**
     * JavaFX应用程序启动方法
     * 负责初始化应用程序界面和设置各种属性
     * 
     * @param primaryStage 应用程序的主舞台
     * @throws Exception 初始化过程中可能发生的异常
     */
    @Override
    public void start(Stage primaryStage) throws Exception {
        // 初始化应用模型
        appModel = new AppModel();

        // 将应用模型添加到全局变量
        globals.put("appModel", appModel);

        // 创建FXML加载器，用于加载UI布局
        FXMLLoader fxmlLoader = new FXMLLoader();
        // 设置FXML文件位置，使用MVC版本的FXML
        fxmlLoader.setLocation(getClass().getResource("Main.fxml"));
        // 设置JavaFX构建工厂
        fxmlLoader.setBuilderFactory(new JavaFXBuilderFactory());
        // 加载FXML文件并创建UI根节点
        Parent root = fxmlLoader.load();

        // 设置窗口标题
        primaryStage.setTitle("无标题 - 记事本");
        // 创建场景并设置到舞台上
        primaryStage.setScene(new Scene(root));
        // 设置应用程序图标
        primaryStage.getIcons().add(new Image("file:src/main/java/com/re0hg/notepad_re0hg/icon.png"));

        // 获取FXML桥接控制器
        FXMLBridgeController fxmlController = fxmlLoader.getController();

        // 创建主控制器
        mainController = new MainController(appModel, primaryStage);

        // 添加到控制器映射
        controllers.put("mainController", mainController);

        // 初始化主控制器
        mainController.initialize();

        // 设置桥接控制器的引用
        fxmlController.setStage(primaryStage);
        fxmlController.setAppModel(appModel);
        fxmlController.setControllers(mainController);

        // 显示主窗口
        primaryStage.show();
    }

    /**
     * 应用程序入口点
     * 
     * @param args 命令行参数
     */
    public static void main(String[] args) {
        launch(args);
    }
}
