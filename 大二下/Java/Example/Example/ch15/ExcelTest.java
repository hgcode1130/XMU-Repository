package ch15;

import java.io.*;
import jxl.*;
import jxl.read.biff.BiffException;
import jxl.write.*;
import jxl.write.Number;

import jxl.read.biff.BiffException;
import jxl.write.*;

public class ExcelTest {


	public void writeData(File file) {
		try {
			System.out.println("write to file!");

			WritableWorkbook testxls = Workbook.createWorkbook(file);
			WritableSheet sheet = testxls.createSheet("第一页", 0);
			for (int i = 0; i < 10; i++) {
				String str = "北京" + i;
				Label label = new Label(0, i, str);
				sheet.addCell(label);
				// System.out.println("rownum:"+rownum+" value:"+str);
			}

			 jxl.write.Number number = new jxl.write.Number(1,0,789.123);
			 sheet.addCell(number);
			 
			// 写入数据并关闭文件
			testxls.write();
			testxls.close();
		} catch (Exception e1) {
			System.out.println(e1);
		}
	}

	public void readData(File file) {
		InputStream is = null;
		try {
			System.out.println("read from file!");
			is = new FileInputStream(file);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		try {
			jxl.Workbook rwb = Workbook.getWorkbook(is);
			int num = rwb.getSheet(0).getRows();
			System.out.println(num);
			for (int i = 0; i < num; i++) {
				Sheet rs = rwb.getSheet(0);
				Cell c = rs.getCell(0, i);
				String strc = c.getContents();
				System.out.println(i + "-------&gt; " + strc);
			}
			rwb.close();
		} catch (BiffException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String args[]) {
		File file1 = new File("ch15\\excel.xls");
		ExcelTest test = new ExcelTest();
		test.writeData(file1);
		test.readData(file1);
		
	}
}
