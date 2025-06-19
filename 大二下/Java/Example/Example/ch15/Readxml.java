package ch15;


/*import java.io.*;
import java.util.Vector;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.io.File;
import org.w3c.dom.Document;
import org.w3c.dom.*;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException; 


public class Readxml {
	static Document document;
	private boolean validating;

	public Readxml() {
	}

	public Vector toRead(String filename) {
		Vector all = new Vector();
		Vector title = new Vector();
		Vector content = new Vector();
		String myStr = new String();

		all.add(title);
		all.add(content);
		return all;
	}

	public static void main(String[] args) {
		Vector A;
		Readxml my = new Readxml();
		A = my.toRead("E:\\JAVA_XML\\data.xml");
		for (int i = 0; i < A.size(); i++) {
			System.out.println(A.elementAt(i));
		}
	}
}
*/


import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
//下面主要是org.xml.sax包的类
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class Readxml {

    public Readxml(){
        //（1）得到DOM解析器的工厂实例
        DocumentBuilderFactory domfac=DocumentBuilderFactory.newInstance();
        //得到javax.xml.parsers.DocumentBuilderFactory;类的实例就是我们要的解析器工厂
        try {
            //（2）从DOM工厂获得DOM解析器
            DocumentBuilder dombuilder=domfac.newDocumentBuilder();
            //通过javax.xml.parsers.DocumentBuilderFactory实例的静态方法newDocumentBuilder()得到DOM解析器
            //（3）把要解析的XML文档转化为输入流，以便DOM解析器解析它
            InputStream is=new FileInputStream("ch14\\data.xml");            
            //（4）解析XML文档的输入流，得到一个Document
            Document doc=dombuilder.parse(is);
            //由XML文档的输入流得到一个org.w3c.dom.Document对象，以后的处理都是对Document对象进行的
            //（5）得到XML文档的根节点
            Element root=doc.getDocumentElement();
            //在DOM中只有根节点是一个org.w3c.dom.Element对象。
            //（6）得到节点的子节点
            NodeList books=root.getChildNodes();
            
            if(books!=null){
                for(int i=0;i<books.getLength();i++){
                    Node book=books.item(i);
                    if(book.getNodeType()==Node.ELEMENT_NODE){
                        //（7）取得节点的属性值
                       String email=book.getAttributes().getNamedItem("email").getNodeValue();
                        System.out.println(email);
                        //注意，节点的属性也是它的子节点。它的节点类型也是Node.ELEMENT_NODE
                        //（8）轮循子节点
                        for(Node node=book.getFirstChild();node!=null;node=node.getNextSibling()){
                            if(node.getNodeType()==Node.ELEMENT_NODE){
                                if(node.getNodeName().equals("Name")){
                                    String name=node.getNodeValue();
                                    String name1=node.getFirstChild().getNodeValue();
                                    System.out.println(name);
                                    System.out.println(name1);
                                }
                                if(node.getNodeName().equals("Price")){
                                    String price=node.getFirstChild().getNodeValue();
                                    System.out.println(price);
                                }
                            }
                        }
                    }
                    
                }//（6）这是用一个org.w3c.dom.NodeList接口来存放它所有子节点的，还有一种轮循子节点的方法，后面有介绍
            }
            else {
            	System.out.println("books is null");
            }
            is.close();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
            
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }

    public static void main(String[] args) {
        new Readxml();
    }
}