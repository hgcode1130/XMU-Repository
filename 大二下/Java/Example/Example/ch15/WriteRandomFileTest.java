package ch15;

//Fig. 14.27: WriteRandomFileTest.java
//This program tests class WriteRandomFile.

public class WriteRandomFileTest
{
public static void main( String args[] )
{
   WriteRandomFile application = new WriteRandomFile();
   application.openFile();
   application.addRecords();
   application.closeFile();
} // end main
} // end class WriteRandomFileTest

/*************************************************************************
* (C) Copyright 1992-2005 by Deitel & Associates, Inc. and               *
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
