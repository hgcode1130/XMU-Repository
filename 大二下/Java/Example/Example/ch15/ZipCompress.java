package ch15;


import java.io.*;
import java.util.zip.*;
public class ZipCompress
{
	public static void main(String[] args) 
	{
		try
		{
			//建立输出文件流
			FileOutputStream fileOut=
				new FileOutputStream("Example.zip");
			//建立冗余验证流
			CheckedOutputStream checkedOut=
				new CheckedOutputStream(fileOut,new CRC32());
			//建立Zip流
			ZipOutputStream zipOut=
				new ZipOutputStream(
					new BufferedOutputStream(checkedOut));
			//设置注释内容
			zipOut.setComment("This is a java zipping test file");
			//文件名
			String fileName=
				"F:\\eclipse3.2\\workspace\\Book6\\ch14\\"+
					"ZipCompress.java";
			//读取被压速文件流
			BufferedReader in=
				new BufferedReader(new FileReader(fileName));
			//建立压缩实体
			zipOut.putNextEntry(new ZipEntry(fileName));
			int ch;
			//当被压缩文件没有结束时继续读写
			while ((ch=in.read())!=-1)
			{
				zipOut.write(ch);
			}
			//关闭文件流，释放资源
			in.close();
			zipOut.close();
		}
		catch (IOException e)
		{
			System.out.println(e.toString());
		}
	}
}

