import java.sql.*;
import java.util.Scanner;

public class q2{
    public static void main(String[] args) {
        while (true) {
            try {
                String ip;

                Scanner sc=new Scanner(System.in);

                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/DB1", "root","0000");
                Statement stmt = conn.createStatement();
                ResultSet rs;
                ResultSetMetaData rm;

                while(true) {
                    System.out.print("Enter choice for excution:\n" +
                            "1 Enter name of room to get list of classes that meet there\n" +
                            "2 Enter name of course to get list of rooms and times where it will be conducted\n" +
                            "3 Enter name of faculty member to get list of courses taught by them\n");
                    int choice=Integer.parseInt(sc.nextLine());
                    switch(choice){
                        case 1:
                            ip=sc.nextLine();
                            PreparedStatement st=conn.prepareStatement("select cname from class where room=?");
                            st.setString(1, ip);
                            rs=st.executeQuery();
                            rm= rs.getMetaData();
                            int num_col=rm.getColumnCount();
                            for(int i=1;i<=num_col;i++)
                                System.out.print(rm.getColumnName(i)+" ");
                            System.out.println();
                            while (rs.next()){
                                for(int i=1;i<=num_col;i++)
                                    System.out.print(rs.getString(i)+", ");
                                System.out.println();
                            }
                            break;
                        case 2:
                            ip=sc.nextLine();
                            st=conn.prepareStatement("select room,meets_at from class where cname=?");
                            st.setString(1, ip);
                            rs=st.executeQuery();
                            rm= rs.getMetaData();
                            num_col=rm.getColumnCount();
                            for(int i=1;i<=num_col;i++)
                                System.out.print(rm.getColumnName(i)+" ");
                            System.out.println();
                            while (rs.next()){
                                for(int i=1;i<=num_col;i++)
                                    System.out.print(rs.getString(i)+", ");
                                System.out.println();
                            }
                            break;
                        case 3:
                            ip=sc.nextLine();
                            st=conn.prepareStatement("select cname from class natural join faculty where fname=?");
                            st.setString(1, ip);
                            rs=st.executeQuery();
                            rm= rs.getMetaData();
                            num_col=rm.getColumnCount();
                            for(int i=1;i<=num_col;i++)
                                System.out.print(rm.getColumnName(i)+" ");
                            System.out.println();
                            while (rs.next()){
                                for(int i=1;i<=num_col;i++)
                                    System.out.print(rs.getString(i)+", ");
                                System.out.println();
                            }
                            break;
                        default:
                            System.out.print("Wrong choice! No sql for you\n");
                            choice=0;

                    }
                    if(choice!=0)
                        break;
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
