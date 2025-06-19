package ch15;

import org.w3c.dom.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

//import java.awt.print.Book;
import java.io.*;

public class Writexml {
	private Document document;
	private String filename;

	public Writexml(String name) throws ParserConfigurationException {
		filename = name;
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = factory.newDocumentBuilder();
		document = builder.newDocument();
	}

	public void toWrite(Book books[]) {
		Element root = document.createElement("books");
		document.appendChild(root);
		for(int i=0;i<books.length ;i++){
			Element book = document.createElement("book");
			root.appendChild(book);
			book.setAttribute("email", books[i].getEmail());
			Element title = document.createElement("Name");
			title.appendChild(document.createTextNode(books[i].getName()));
			book.appendChild(title);
			Element content = document.createElement("Price");
			content.appendChild(document.createTextNode(String.valueOf(books[i].getPrice())));
			book.appendChild(content);
		}
		
	}

	public void toSave() {
		try {
			TransformerFactory tf = TransformerFactory.newInstance();
			Transformer transformer = tf.newTransformer();
			DOMSource source = new DOMSource(document);
			transformer.setOutputProperty(OutputKeys.ENCODING, "GB2312");
			transformer.setOutputProperty(OutputKeys.INDENT, "yes");
			PrintWriter pw = new PrintWriter(new FileOutputStream(filename));
			StreamResult result = new StreamResult(pw);
			transformer.transform(source, result);
		} catch (TransformerException mye) {
			mye.printStackTrace();
		} catch (IOException exp) {
			exp.printStackTrace();
		}
	}

	public static void main(String args[]) {
		try {
			Writexml myxml = new Writexml(
					"src/ch15/data.xml");
			Book[] books = new Book[3];
		    books[0] = new Book("Java",30.5,"java@xmu.edu.cn");
		    books[1] = new Book("C++",38,"c++@xmu.edu.cn");
		    books[2] = new Book("OOAD",39.5,"ooad@xmu.edu.cn");
			myxml.toWrite(books);
			myxml.toSave();
			System.out.print("Your writing is successful.");
		} catch (ParserConfigurationException exp) {
			exp.printStackTrace();
			System.out.print("Your writing is failed.");
		}
		
	}
}

class Book{
	private String name;
	private double price;
	private String email;
	public Book(String name, double price,String email){
		this.name = name;
		this.price = price;
		this.email = email;
	}
	public String getName(){
		return name;
	}
	public double getPrice(){
		return price;
	}
	public String getEmail(){
		return email;
	}
}
