package ch24;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;

public class Test {
	public static void main(String[] args) throws ClassNotFoundException {
		    //获取数据库连接
		      Connection conn;
			try {
				//注册数据库驱动
			     // Class.forName("com.mysql.jdbc.Driver");
			      Class.forName("com.mysql.cj.jdbc.Driver");
			     
				conn = DriverManager.getConnection("jdbc:mysql://localhost:3307/testmysql","root","12345678");
				  //创建Statement
			      Statement stmt = conn.createStatement();
			      //执行查询
			      ResultSet rs = stmt.executeQuery("select * from person");
			      // get ResultSet's meta data
			         ResultSetMetaData metaData = rs.getMetaData();
			         int numberOfColumns = metaData.getColumnCount();     
			         
			         System.out.printf("Authors Table of Books Database:%n%n");

			         // display the names of the columns in the ResultSet
			         for (int i = 1; i <= numberOfColumns; i++) {
			            System.out.printf("%-8s\t", metaData.getColumnName(i));
			         }
			         System.out.println();
			         // display query results
			         while (rs.next()) {
			            for (int i = 1; i <= numberOfColumns; i++) {
			               System.out.printf("%-8s\t", rs.getObject(i));
			            }
			            System.out.println();
			         } 
			      
			         
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		    
	}
		        
		 

}
