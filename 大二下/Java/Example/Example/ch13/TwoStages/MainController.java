package ch13.TwoStages;


import java.net.URL;
import java.util.ResourceBundle;
 
import javafx.fxml.Initializable;
 
public class MainController implements Initializable {
 
	public MainController() {
		// TODO Auto-generated constructor stub
	}
 
	@Override
	public void initialize(URL arg0, ResourceBundle arg1) {
		// TODO Auto-generated method stub
 
	}
	
	public void changeWindow() throws Exception {
		Second second=new Second();
		second.showWindow();
		
		
	}
 
}