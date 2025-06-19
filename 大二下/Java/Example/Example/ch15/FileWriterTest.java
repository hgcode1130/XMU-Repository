package ch15;

import java.io.*;

class FileWriterTest {

	public static void main(String args[]) throws Exception {

		String buffer = "learn how to write to file";

		FileWriter f1 = new FileWriter("ch14\\test.txt");

		f1.write(buffer);

		f1.close();

	}

}
