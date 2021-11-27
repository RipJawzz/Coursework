import java.sql.*;
import java.util.ArrayList;
import java.util.Scanner;

public class q1{

    public static void main(String[] args) {
        while (true) {
            try {
                String choice;
                ArrayList<String> name_tables=new ArrayList<>();
                Scanner sc=new Scanner(System.in);

                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/DB1", "root","0000");
                Statement stmt = conn.createStatement();
                ResultSet rset = stmt.executeQuery("show tables");

                while (rset.next()) {
                    System.out.println(rset.getString(1));
                    name_tables.add(rset.getString(1));
                }

                System.out.println("Enter the name of the table to be printed");
                choice=sc.next().trim().toLowerCase();
                if(name_tables.contains(choice)){
                    rset=stmt.executeQuery("select *" +
                            "from "+choice);
                    ResultSetMetaData rm= rset.getMetaData();
                    int num_col=rm.getColumnCount();
                    for(int i=1;i<=num_col;i++)
                        System.out.print(rm.getColumnName(i)+" ");
                    System.out.println();
                    while (rset.next()){
                        for(int i=1;i<=num_col;i++)
                            System.out.print(rset.getString(i)+", ");
                        System.out.println();
                    }
                }else{
                    System.out.println("Enter correct table name!");
                }
                stmt.close();
                conn.close();
                sc.close();
                break;
            } catch (Exception e) {
                System.out.println("Something happened!"+e);
            }
        }
    }
}
