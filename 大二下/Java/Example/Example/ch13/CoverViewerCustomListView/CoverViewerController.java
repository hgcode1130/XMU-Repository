package ch13.CoverViewerCustomListView;

// CoverViewerController.java
// Controller for Cover Viewer application
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.util.Callback;

public class CoverViewerController {
   // instance variables for interacting with GUI
   @FXML private ListView<Book> booksListView;
   @FXML private ImageView coverImageView;

   // stores the list of Book Objects
   private final ObservableList<Book> books = 
      FXCollections.observableArrayList();

   public void initialize() {
      // populate the ObservableList<Book>
      books.add(new Book("Android How to Program", 
         this.getClass().getResource("images/small/androidhtp.jpg").getFile(), this.getClass().getResource("images/large/androidhtp.jpg").getFile()));
      books.add(new Book("C How to Program", 
    		  this.getClass().getResource("images/small/chtp.jpg").getFile(), this.getClass().getResource("images/large/chtp.jpg").getFile()));
      books.add(new Book("C++ How to Program",
    		  this.getClass().getResource("images/small/cpphtp.jpg").getFile(), this.getClass().getResource("images/large/cpphtp.jpg").getFile()));
      books.add(new Book("Internet and World Wide Web How to Program",  
    		  this.getClass().getResource("images/small/iw3htp.jpg").getFile(),  this.getClass().getResource("images/large/iw3htp.jpg").getFile()));
      books.add(new Book("Java How to Program", 
    		  this.getClass().getResource( "images/small/jhtp.jpg").getFile(), this.getClass().getResource("images/large/jhtp.jpg").getFile()));
      books.add(new Book("Visual Basic How to Program", 
    		  this.getClass().getResource("images/small/vbhtp.jpg").getFile(), this.getClass().getResource("images/large/vbhtp.jpg").getFile()));
      books.add(new Book("Visual C# How to Program", 
    		  this.getClass().getResource("images/small/vcshtp.jpg").getFile(), this.getClass().getResource("images/large/vcshtp.jpg").getFile()));
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
         
      // set custom ListView cell factory
      booksListView.setCellFactory(
         new Callback<ListView<Book>, ListCell<Book>>() {
            @Override
            public ListCell<Book> call(ListView<Book> listView) {
               return new ImageTextCell();
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
