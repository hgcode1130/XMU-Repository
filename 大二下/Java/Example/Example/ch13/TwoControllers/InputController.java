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
//        // ��ȡ������������
//        FXMLLoader loader = new FXMLLoader(getClass().getResource("ResultPage.fxml"));
//        try
//        {
//            AnchorPane login = (AnchorPane) loader.load();
//        } catch (IOException e)
//        {
//            e.printStackTrace();
//        }
//        ResultController control = (ResultController) loader.getController();
//        // ���ý����������
//        control.model.setText(textEnter.getText());
//    }

    public void confirm(ActionEvent actionEvent)
    {
    	System.out.println("confirm");
        //�ı�ģ�����ÿ�������ģ�����б����ԣ������۲���
        String inputContent=textEnter.getText();
        ResultController.setText(inputContent);
        //�رմ���
        ((Node) (actionEvent.getSource())).getScene().getWindow().hide();
    }

}
