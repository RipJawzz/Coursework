package DBcons;
import java.sql.*;
public class SQL_Updates {

    public SQL_Updates(){

    }
    public String property_sell_update(String agent_id,String reg_num,String sell_date){
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/db_re","root","0000");
            Statement stmt = conn.createStatement();
            PreparedStatement pstmt;
            //System.out.println(reg_num + " " + sell_date);
            ResultSet rs;
            ResultSetMetaData rm;
            pstmt=conn.prepareStatement("insert into Sold values (?,?,?);");
            pstmt.setString(1,agent_id);
            pstmt.setString(2,reg_num);
            pstmt.setString(3,sell_date);
            pstmt.execute();
            pstmt = conn.prepareStatement("update Property set status='taken' where reg_no = ?;");
            pstmt.setString(1, reg_num);
            pstmt.execute();
            return "o";
        }
        catch (Exception e){
            System.out.println(e);
            return "error";
        }
    }
    public String property_rent_update(String agent_id,String reg_num,String sell_date,String end_date){
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/"+AppData.db_name,"root",AppData.db_pwd);
            Statement stmt = conn.createStatement();
            PreparedStatement pstmt;
            ResultSet rs;
            ResultSetMetaData rm;
            pstmt=conn.prepareStatement("insert into Rented values (?,?,?,?);");
            pstmt.setString(1,agent_id);
            pstmt.setString(2,reg_num);
            pstmt.setString(3,sell_date);
            pstmt.setString(4,end_date);
            pstmt.execute();
            pstmt = conn.prepareStatement("update Rental set status='taken' where reg_no = ?;");
            pstmt.setString(1, reg_num);
            pstmt.execute();
            return "0";
        }
        catch (Exception e){
            System.out.println(e);
            return "error";
        }
    }
    public String verify_agent(String agent_id,String agent_pwd){
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/"+AppData.db_name,"root",AppData.db_pwd);
            Statement stmt = conn.createStatement();
            PreparedStatement pstmt;
            ResultSet rs;
            ResultSetMetaData rm;
            pstmt=conn.prepareStatement("SELECT agent_password\nFROM Agent\nwhere agent_id=?;");
            pstmt.setString(1,agent_id);
            pstmt.execute();
            rs=pstmt.getResultSet();
            if(rs.next())
                if(rs.getInt(1)==Integer.parseInt(agent_pwd))
                    return "o";
            return "wrong";
        }
        catch(Exception e){
            System.out.println(e);
            return "error";
        }
    }
}
