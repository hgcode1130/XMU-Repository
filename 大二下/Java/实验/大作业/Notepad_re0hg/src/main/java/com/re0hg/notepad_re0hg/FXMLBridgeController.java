/**
 * FXML桥接控制器类
 * 连接FXML界面和MVC控制器
 * 接收UI事件并代理到对应的控制器
 */
package com.re0hg.notepad_re0hg;

import com.re0hg.notepad_re0hg.controller.DocumentController;
import com.re0hg.notepad_re0hg.controller.EditController;
import com.re0hg.notepad_re0hg.controller.FileController;
import com.re0hg.notepad_re0hg.controller.FormatController;
import com.re0hg.notepad_re0hg.controller.HelpController;
import com.re0hg.notepad_re0hg.controller.MainController;
import com.re0hg.notepad_re0hg.controller.SearchController;
import com.re0hg.notepad_re0hg.controller.ViewController;
import com.re0hg.notepad_re0hg.model.AppModel;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.CheckMenuItem;
import javafx.scene.control.ContextMenu;
import javafx.scene.control.Label;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.net.URL;
import java.util.ResourceBundle;

/**
 * FXML桥接控制器
 * 作为FXML视图和MVC控制器之间的桥梁
 */
public class FXMLBridgeController implements Initializable, EditController.EditListener {

    // FXML注入的UI元素
    @FXML
    private MenuBar menuBar;
    @FXML
    private Menu fileMenu;
    @FXML
    private Menu editMenu;
    @FXML
    private Menu formatMenu;
    @FXML
    private Menu viewMenu;
    @FXML
    private Menu helpMenu;

    @FXML
    private MenuItem newFileMenuItem;
    @FXML
    private MenuItem openMenuItem;
    @FXML
    private MenuItem saveMenuItem;
    @FXML
    private MenuItem saveAsMenuItem;
    @FXML
    private MenuItem pageSetupMenuItem;
    @FXML
    private MenuItem exitMenuItem;

    @FXML
    private MenuItem undoMenuItem;
    @FXML
    private MenuItem redoMenuItem;
    @FXML
    private MenuItem cutMenuItem;
    @FXML
    private MenuItem copyMenuItem;
    @FXML
    private MenuItem pasteMenuItem;
    @FXML
    private MenuItem deleteMenuItem;
    @FXML
    private MenuItem searchMenuItem;
    @FXML
    private MenuItem nextSearchMenuItem;
    @FXML
    private MenuItem previousSearchMenuItem;
    @FXML
    private MenuItem replaceMenuItem;
    @FXML
    private MenuItem goToLineMenuItem;
    @FXML
    private MenuItem selectAllMenuItem;
    @FXML
    private MenuItem timeDateMenuItem;
    @FXML
    private MenuItem baiduSearchMenuItem;

    @FXML
    private MenuItem fontMenuItem;
    @FXML
    private CheckMenuItem wordWrapCheckItem;

    @FXML
    private CheckMenuItem statusBarCheckItem;

    @FXML
    private MenuItem helpMenuItem;
    @FXML
    private MenuItem aboutMenuItem;

    @FXML
    private TextArea textArea;
    @FXML
    private Label statusLabel;
    @FXML
    private ContextMenu contextMenu; // MVC控制器引用
    private MainController mainController;
    private DocumentController documentController;
    private FileController fileController;
    private EditController editController;
    private SearchController searchController;
    private FormatController formatController;
    private ViewController viewController;
    private HelpController helpController;

    // 应用模型（仅用于setAppModel方法，当前类中未直接使用）
    private AppModel appModel;

    // 主窗口（供其他方法使用）
    private Stage primaryStage;

    /**
     * 设置主窗口引用
     * 
     * @param stage 主窗口
     */
    public void setStage(Stage stage) {
        this.primaryStage = stage;
    }

    /**
     * 设置应用模型
     * 
     * @param appModel 应用模型
     */
    public void setAppModel(AppModel appModel) {
        this.appModel = appModel;
    }

    /**
     * 设置控制器
     * 
     * @param mainController 主控制器
     */
    public void setControllers(MainController mainController) {
        this.mainController = mainController;

        // 获取各个子控制器
        this.fileController = mainController.getController("fileController");
        this.documentController = mainController.getController("documentController");
        this.editController = mainController.getController("editController");
        this.searchController = mainController.getController("searchController");
        this.formatController = mainController.getController("formatController");
        this.viewController = mainController.getController("viewController");
        this.helpController = mainController.getController("helpController");

        // 设置文本区域
        if (documentController != null) {
            documentController.setTextArea(textArea);
        }

        // 设置状态栏
        if (viewController != null) {
            viewController.setStatusLabel(statusLabel);
        }

        // 设置控制器间的关系
        if (editController != null) {
            editController.setDocumentController(documentController);
            editController.setEditListener(this);
        }

        if (searchController != null) {
            searchController.setDocumentController(documentController);
        }

        if (formatController != null) {
            formatController.setDocumentController(documentController);
        }

        if (viewController != null) {
            viewController.setDocumentController(documentController);
        }

        // 设置UI状态
        updateUIState();
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        // 初始化UI状态
        Platform.runLater(() -> {
            updateUIState();
            setupTextAreaEvents();
        });
    }

    /**
     * 设置文本区域事件
     */
    private void setupTextAreaEvents() {
        if (textArea != null && viewController != null) {
            // 光标位置变化监听，更新状态栏
            textArea.caretPositionProperty().addListener((obs, oldPos, newPos) -> {
                viewController.updateStatusBar();
                // 当光标位置变化时，更新编辑菜单状态（可能有文本选择变化）
                updateEditMenuState();
            });

            // 文本区域获取焦点时更新菜单状态
            textArea.focusedProperty().addListener((obs, oldVal, newVal) -> {
                if (newVal) {
                    updateUIState();
                }
            });

            // 监听文本变化以更新撤销/重做状态
            textArea.textProperty().addListener((obs, oldText, newText) -> {
                updateEditMenuState();
            });

            // 监听选择范围变化
            textArea.selectionProperty().addListener((obs, oldSelection, newSelection) -> {
                updateEditMenuState();
            });
        }
    }

    /**
     * 更新UI状态
     */
    private void updateUIState() {
        if (formatController != null && viewController != null) {
            // 更新自动换行菜单项
            wordWrapCheckItem.setSelected(formatController.isWordWrap());

            // 更新状态栏菜单项
            statusBarCheckItem.setSelected(viewController.isStatusBarVisible());
        }

        // 更新编辑菜单状态
        updateEditMenuState();
    }

    /**
     * 更新编辑菜单状态
     * 根据当前文档状态启用或禁用相关菜单项
     */
    private void updateEditMenuState() {
        if (documentController == null) {
            return;
        }

        // 获取文本区域
        TextArea textArea = documentController.getTextArea();
        if (textArea == null) {
            return;
        }

        // 获取撤销/重做管理器状态
        boolean canUndo = documentController.canUndo();
        boolean canRedo = documentController.canRedo();

        // 更新撤销/重做菜单项状态
        undoMenuItem.setDisable(!canUndo);
        redoMenuItem.setDisable(!canRedo);

        // 检查是否有选中的文本
        boolean hasSelection = textArea.getSelectedText() != null && !textArea.getSelectedText().isEmpty();

        // 更新复制/剪切/删除菜单项状态
        copyMenuItem.setDisable(!hasSelection);
        cutMenuItem.setDisable(!hasSelection);
        deleteMenuItem.setDisable(!hasSelection);

        // 检查剪贴板中是否有文本内容
        boolean canPaste = true; // JavaFX没有直接的API检查剪贴板内容，默认启用粘贴
        pasteMenuItem.setDisable(!canPaste);
    }

    // ===== 文件菜单 =====

    @FXML
    private void handleNewFile(ActionEvent event) {
        if (fileController != null) {
            fileController.newDocument();
        }
    }

    @FXML
    private void handleOpen(ActionEvent event) {
        if (fileController != null) {
            fileController.openDocument();
        }
    }

    @FXML
    private void handleSave(ActionEvent event) {
        if (fileController != null) {
            fileController.saveDocument();
        }
    }

    @FXML
    private void handleSaveAs(ActionEvent event) {
        if (fileController != null) {
            fileController.saveAsDocument();
        }
    }

    @FXML
    private void handlePageSetup(ActionEvent event) {
        if (fileController != null) {
            fileController.showPageSetupDialog();
        }
    }

    @FXML
    private void handleExit(ActionEvent event) {
        if (mainController != null) {
            mainController.exitApplication();
        }
    }

    // ===== 编辑菜单 =====

    @FXML
    private void handleUndo(ActionEvent event) {
        if (editController != null) {
            editController.undo();
        }
    }

    @FXML
    private void handleRedo(ActionEvent event) {
        if (editController != null) {
            editController.redo();
        }
    }

    @FXML
    private void handleCut(ActionEvent event) {
        if (editController != null) {
            editController.cut();
        }
    }

    @FXML
    private void handleCopy(ActionEvent event) {
        if (editController != null) {
            editController.copy();
        }
    }

    @FXML
    private void handlePaste(ActionEvent event) {
        if (editController != null) {
            editController.paste();
        }
    }

    @FXML
    private void handleDelete(ActionEvent event) {
        if (editController != null) {
            editController.delete();
        }
    }

    @FXML
    private void handleBaiduSearch(ActionEvent event) {
        if (editController != null) {
            editController.baiduSearch();
        }
    }

    @FXML
    private void handleSearch(ActionEvent event) {
        if (searchController != null) {
            searchController.showSearchDialog();
        }
    }

    @FXML
    private void handleNextSearch(ActionEvent event) {
        if (searchController != null) {
            searchController.search(true);
        }
    }

    @FXML
    private void handlePreviousSearch(ActionEvent event) {
        if (searchController != null) {
            searchController.search(false);
        }
    }

    @FXML
    private void handleReplace(ActionEvent event) {
        if (searchController != null) {
            searchController.showSearchDialog();
        }
    }

    @FXML
    private void handleGoToLine(ActionEvent event) {
        if (editController != null) {
            editController.goToLine();
        }
    }

    @FXML
    private void handleSelectAll(ActionEvent event) {
        if (editController != null) {
            editController.selectAll();
        }
    }

    @FXML
    private void handleTimeDate(ActionEvent event) {
        if (editController != null) {
            editController.insertTimeAndDate();
        }
    }

    // ===== 格式菜单 =====

    @FXML
    private void handleFont(ActionEvent event) {
        if (formatController != null) {
            formatController.showFontChooser();
        }
    }

    @FXML
    private void handleWordWrap(ActionEvent event) {
        if (formatController != null) {
            boolean wrap = wordWrapCheckItem.isSelected();
            formatController.toggleWordWrap(wrap);
        }
    }

    // ===== 查看菜单 =====

    @FXML
    private void handleStatusBar(ActionEvent event) {
        if (viewController != null) {
            boolean visible = statusBarCheckItem.isSelected();
            viewController.toggleStatusBar(visible);
        }
    }

    // ===== 帮助菜单 =====

    @FXML
    private void handleHelp(ActionEvent event) {
        if (helpController != null) {
            helpController.showHelp();
        }
    }

    @FXML
    private void handleAbout(ActionEvent event) {
        if (helpController != null) {
            helpController.showAbout();
        }
    }

    /**
     * 编辑操作完成时的回调
     * 实现 EditController.EditListener 接口
     */
    @Override
    public void onEditOperationComplete() {
        // 更新编辑菜单状态
        updateEditMenuState();
    }
}
