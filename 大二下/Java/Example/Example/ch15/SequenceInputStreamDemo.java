package ch15;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.SequenceInputStream;
import java.util.Enumeration;
import java.util.Vector;

class InputStreamEnumerator implements Enumeration {
	private Enumeration files;

	public InputStreamEnumerator(Vector files) {
		this.files = files.elements();
	}

	public boolean hasMoreElements() {

		return files.hasMoreElements();
	}

	public Object nextElement() {
		try {
			return new FileInputStream(files.nextElement().toString());
		} catch (Exception e) {
			return null;
		}

	}

}// end class InputStreamEnumerator

public class SequenceInputStreamDemo {

	public static void main(String[] args) {
		int c;
		Vector files = new Vector();

		files.addElement("ch15\\test1.dat");
		files.addElement("ch15\\test2.dat");
		InputStreamEnumerator e = new InputStreamEnumerator(files);
		InputStream input = new SequenceInputStream(e);

		try {
			while ((c = input.read()) != -1) {
				System.out.println((char) c);

			}
			input.close();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		

	}

}
