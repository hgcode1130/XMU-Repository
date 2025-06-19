package ch13.CoverViewer;

// Fig. 13.14: CoverViewerController.java
// Controller for Cover Viewer application
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

public class CoverViewerController {
   // instance variables for interacting with GUI
   @FXML private ListView<Book> booksListView;
   @FXML private ImageView coverImageView;

   // stores the list of Book Objects
   private final ObservableList<Book> books = 
      FXCollections.observableArrayList();

   // initialize controller
   public void initialize() {
      // populate the ObservableList<Book>
      books.add(new Book("Android How to Program", 
    		  this.getClass().getResource("images/small/androidhtp.jpg").getPath(), 
    		  this.getClass().getResource("images/large/androidhtp.jpg").getPath()));
      books.add(new Book("C How to Program", 
    		  this.getClass().getResource("images/small/chtp.jpg").getPath(), 
    		  this.getClass().getResource("images/large/chtp.jpg").getPath()));
      books.add(new Book("C++ How to Program",
    		  this.getClass().getResource("images/small/cpphtp.jpg").getPath(),
    		  this.getClass().getResource( "images/large/cpphtp.jpg").getPath()));
      books.add(new Book("Internet and World Wide Web How to Program",  
    		  this.getClass().getResource("images/small/iw3htp.jpg").getPath(), 
    		  this.getClass().getResource("images/large/iw3htp.jpg").getPath()));
      books.add(new Book("Java How to Program", 
    		  this.getClass().getResource("images/small/jhtp.jpg").getPath(), 
    		  this.getClass().getResource("images/large/jhtp.jpg").getPath()));
      books.add(new Book("Visual Basic How to Program", 
    		  this.getClass().getResource("images/small/vbhtp.jpg").getPath(), 
    		  this.getClass().getResource("images/large/vbhtp.jpg").getPath()));
      books.add(new Book("Visual C# How to Program", 
    		  this.getClass().getResource("images/small/vcshtp.jpg").getPath(),
    		  this.getClass().getResource( "images/large/vcshtp.jpg").getPath()));
      booksListView.setItems(books); // bind booksListView to books

      // when ListView selection changes, show large cover in ImageView
      booksListView.getSelectionModel().selectedItemProperty().
         addListener(
            new ChangeListener<Book>() {                                   
               @Override                                                     
               public void changed(ObservableValue<? extends Book> ov,
                  Book oldValue, Book newValue) {  
                  coverImageView.setImage(
                		  new Image("file:" + newValue.getLargeImage()));
                  
               }
            }
         );                                                                  
   }             

}

/**************************************************************************
 * (C) Copyright 1992-2018 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
