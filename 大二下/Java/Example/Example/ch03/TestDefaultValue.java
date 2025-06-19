//验证不同类型变量的默认初值；验证简单变量和引用变量的部分区别
package ch03;

import com.sun.org.apache.xalan.internal.xsltc.compiler.sym;

public class TestDefaultValue {
	
	private int intVar;
	private float floatVar;
	private boolean booleanVar;
	private char charVar;
	private String stringVar;
	
	public static void main(String args[]){
		
		TestDefaultValue testDefaultValue = new TestDefaultValue();
		testDefaultValue.printFieldsInitValue();
		testDefaultValue.testLocalVar();
		
	}//end method main
	
	public void printFieldsInitValue(){
		
		System.out.printf( "the init value of int is %d\n", intVar);
		System.out.printf("the init value of float is %.2f\n" , floatVar);
		System.out.printf("the init value of boolean is %b\n" , booleanVar);
		System.out.printf("the init value of char is %c\n" , charVar);
		System.out.printf("the init value of reference type String is %s\n" , stringVar);
		
	}//end method printFieldsInitValue
	
	public void testLocalVar(){
	//	int intVar = 3;
		float floatVar;
		boolean booleanVar;
		char charVar;
		String stringVar;
//		
//		
//		System.out.printf( "the init value of int is %d\n", intVar);
//		System.out.printf("the init value of float is %.2f\n" , floatVar);
//		System.out.printf("the init value of boolean is %b\n" , booleanVar);
//		System.out.printf("the init value of char is %c\n" , charVar);
//		System.out.printf("the init value of reference type String is %s\n" , stringVar);
//	
		for(;intVar<4;intVar++){
			System.out.println(intVar);
			for(int intVar = 0; intVar < 4; intVar++) 
				System.out.println(intVar);

//			}
		}
//		
	}
	

}
