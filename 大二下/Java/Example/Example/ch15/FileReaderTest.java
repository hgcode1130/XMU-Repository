package ch15;

    import  java.io.*;

    class FileReaderTest {

        public static void main (String args[ ] ) throws Exception {

            FileReader fr =  new FileReader ("ch15\\test.txt");

            BufferedReader br = new BufferedReader (fr);

            String s;

             while ((s = br.readLine() )!=null) {

                 System.out.println(s);

              }

            fr.close();

      }

    }

