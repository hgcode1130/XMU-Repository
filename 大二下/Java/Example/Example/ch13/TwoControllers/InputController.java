package ch13.TwoControllers;

import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;

public class InputController
{
    @FXML
    private TextField textEnter;
   
    // action event handler for button:
//    @FXML
//    private void sendText() {
//        // 获取结果界面控制器
//        FXMLLoader loader = new FXMLLoader(getClass().getResource("ResultPage.fxml"));
//        try
//        {
//            AnchorPane login = (AnchorPane) loader.load();
//        } catch (IOException e)
//        {
//            e.printStackTrace();
//        }
//        ResultController control = (ResultController) loader.getController();
//        // 设置结果界面内容
//        control.model.setText(textEnter.getText());
//    }

    public void confirm(ActionEvent actionEvent)
    {
    	System.out.println("confirm");
        //改变模板设置控制器的模板名列表属性，触发观察者
        String inputContent=textEnter.getText();
        ResultController.setText(inputContent);
        //关闭窗口
        ((Node) (actionEvent.getSource())).getScene().getWindow().hide();
    }

}
