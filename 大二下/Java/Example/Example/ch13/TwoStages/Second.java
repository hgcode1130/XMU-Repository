package ch13.TwoStages;

import java.io.IOException;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;
 
public class Second extends Application {
	 Stage stage=new Stage();
 
	@Override
	public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("Second.fxml"));
        primaryStage.setTitle("Hello World");
        primaryStage.setScene(new Scene(root, 600, 400));
        primaryStage.show(); 
    }
 
	public static void main(String[] args) {
		launch(args);
	}
	
	public void  showWindow() throws Exception {
		start(stage);
	}
	
}