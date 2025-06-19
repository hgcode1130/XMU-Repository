package ch12;

	import javafx.application.Application;
	import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
	import javafx.scene.Group;
	import javafx.scene.Scene;
	import javafx.scene.control.Menu;
	import javafx.scene.control.MenuBar;
	import javafx.scene.control.MenuItem;
	import javafx.scene.layout.BorderPane;
	import javafx.scene.paint.Color;
	import javafx.stage.Stage;

	public class EventHandleMenu extends Application{

	    public static void main(String[] args) {
	        Application.launch(args);
	    }

	    @Override
	    public void start(Stage primaryStage) {
	        primaryStage.setTitle("Event Handle");
	        Group root = new Group();
	        Scene scene = new Scene(root, 400, 250, Color.WHITE);

	        MenuBar menuBar = new MenuBar();
	        EventHandler<ActionEvent> action = changeTabPlacement();

	        Menu menu = new Menu("Direction");
	        MenuItem left = new MenuItem("Left");
 
	        left.setOnAction(action);
	        menu.getItems().add(left);

	        MenuItem right = new MenuItem("Right");
	        right.setOnAction(action);
	        menu.getItems().add(right);

	        MenuItem top = new MenuItem("Top");
	        top.setOnAction(action);
	        menu.getItems().add(top);

	        MenuItem bottom = new MenuItem("Bottom");
	        bottom.setOnAction(new newHandler());
	        menu.getItems().add(bottom);

	        menuBar.getMenus().add(menu);

	        BorderPane borderPane = new BorderPane();

	        borderPane.prefHeightProperty().bind(scene.heightProperty());
	        borderPane.prefWidthProperty().bind(scene.widthProperty());
	        
	        borderPane.setTop(menuBar);
	        
	        root.getChildren().add(borderPane);

	        primaryStage.setScene(scene);
	        primaryStage.show();
	    }

	    private EventHandler<ActionEvent> changeTabPlacement() {
	    	int s[] = new int[10];
        	s[0]=new Integer(123);
	        return new EventHandler<ActionEvent>() {

	            public void handle(ActionEvent event) {
	            	
	                MenuItem mItem = (MenuItem) event.getSource();
	                String side = mItem.getText();
	                if ("left".equalsIgnoreCase(side)) {
	                    System.out.println("left"  +  s[0]);
	                    s[1] = 1;
	                    
	                } else if ("right".equalsIgnoreCase(side)) {
	                    System.out.println("right");
	                } else if ("top".equalsIgnoreCase(side)) {
	                    System.out.println("top");
	                } 
	            }
	        };
	        
	    }
	     class newHandler<ActionEvent> implements EventHandler<Event>{
			@Override
			public void handle(Event event) {
				// TODO Auto-generated method stub
				MenuItem mItem = (MenuItem) event.getSource();
                String side = mItem.getText();
			// TODO Auto-generated method stub
			if ("bottom".equalsIgnoreCase(side)) {
                System.out.println("bottom");
            }
			}
	    	
	    }
	    
	    
}
