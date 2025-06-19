package ch15;

// Fig. 14.23: RandomAccessAccountRecord.java
// Subclass of AccountRecord for random-access file programs.

import java.io.RandomAccessFile;
import java.io.IOException;

public class RandomAccessAccountRecord extends AccountRecord
{  
    public static final int SIZE = 72;

   // no-argument constructor calls other constructor with default values
   public RandomAccessAccountRecord()
   {
      this( 0, "", "", 0.0 );
   } // end no-argument RandomAccessAccountRecord constructor

   // initialize a RandomAccessAccountRecord
   public RandomAccessAccountRecord( int account, String firstName, 
      String lastName, double balance )
   {
      super( account, firstName, lastName, balance );
   } // end four-argument RandomAccessAccountRecord constructor

   // read a record from specified RandomAccessFile
   public void read( RandomAccessFile file ) throws IOException
   {
      setAccount( file.readInt() );
      setFirstName( readName( file ) );
      setLastName( readName( file ) );
      setBalance( file.readDouble() );
   } // end method read

   // ensure that name is proper length
   private String readName( RandomAccessFile file ) throws IOException
   {
      char name[] = new char[ 15 ], temp;

      for ( int count = 0; count < name.length; count++ )
      {
         temp = file.readChar();
         name[ count ] = temp;
      } // end for     
      
      return new String( name ).replace( '\0', ' ' );
   } // end method readName

   // write a record to specified RandomAccessFile
   public void write( RandomAccessFile file ) throws IOException
   {
      file.writeInt( getAccount() );
      writeName( file, getFirstName() );
      writeName( file, getLastName() );
      file.writeDouble( getBalance() );
   } // end method write

   // write a name to file; maximum of 15 characters
   private void writeName( RandomAccessFile file, String name )
      throws IOException
   {
      StringBuffer buffer = null;

      if ( name != null ) 
         buffer = new StringBuffer( name );
      else 
         buffer = new StringBuffer( 15 );

      buffer.setLength( 15 );
      file.writeChars( buffer.toString() );
   } // end method writeName
} // end class RandomAccessAccountRecord

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