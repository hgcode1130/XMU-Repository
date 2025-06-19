import java.sql.*;
import java.math.BigDecimal;

public class MysqlConnDemo {
    public static void main(String arg[]) {
        Connection conn = null;
        Statement stmt = null;
        try { // 注册 JDBC驱动
            Class.forName("com.mysql.cj.jdbc.Driver");// 打开连接
            System.out.println("connecting the database...");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/sales", "root", "00000000"); // jdbc:mysql为协议，
                                                                                                         // localhost为数据库位置，此处为本机，
                                                                                                         // ，3306为数据库端口号
                                                                                                         // sales为数据库名
            // michael和 root分别为用户名和密码，应替换为自己实际的用户名和密码
            // 执行查询
            System.out.println("Instantiating Statement Objects...");
            stmt = conn.createStatement();
            String sql;
            sql = "select name, website from customers;";
            ResultSet rs;
            rs = stmt.executeQuery(sql);
            // 处理 结果集 ，通常使用循环语句
            while (rs.next()) { // 通过字段查询 java中的 BigDecimal数据类型对应 Mysql中的 decimal数据类型
                String name = rs.getString("name");
                String website = rs.getString("website");
                // 输出数据
                System.out.println("name: " + name + " " + "website: " + website);
            } // 完成数据查询后依次关闭结果集、语句和连接
            rs.close();
            stmt.close();
            conn.close();
        } catch (Exception exception) {
            System.out.println(exception);
        }
    }
}