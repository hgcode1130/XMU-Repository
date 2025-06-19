package ch13.TwoControllers;
//https://www.jianshu.com/p/6950b68970da

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;
public class Main extends Application
{
    @Override
    public void start(Stage primaryStage) {
        Parent root;
        try
        {
            root = FXMLLoader.load(getClass().getResource("ResultPage.fxml"));
          
            Scene scene = new Scene(root);
         
            primaryStage.setTitle("控制器间数据传递");
            primaryStage.setScene(scene);
            primaryStage.show();
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}