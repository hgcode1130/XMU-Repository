package ch13.TwoStages;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
 
public class Main extends Application { 
 
    @Override
    public void start(Stage primaryStage) throws Exception{
    	//如果需要获得controller信息，可以用下面几条语句。
//    	   FXMLLoader fxmlLoader1 = new FXMLLoader(getClass().getResource("Main.fxml"));
//    	 Parent root =   fxmlLoader1.load();
//    	 fxmlLoader1.getController(); 
    	
        Parent root = FXMLLoader.load(getClass().getResource("Main.fxml"));
     
        primaryStage.setTitle("Hello World");
        primaryStage.setScene(new Scene(root, 600, 400));
        primaryStage.show(); 
    }
 
    public static void main(String[] args) {
        launch(args);
    }
}