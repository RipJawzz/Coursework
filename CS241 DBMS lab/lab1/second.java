import java.util.Scanner;
import java.io.*;
import java.util.StringTokenizer;

public class second {
    public static void main(String[] args)throws Exception{
        String loc="C:\\Users\\Ishan_Jawzz\\dev\\IntelliJ\\lab1\\Employee.txt",dept=args[0].trim();
        File file=new File(loc);
        Scanner sc=new Scanner(file);
        StringTokenizer st=new StringTokenizer(sc.nextLine());
        int num_col=st.countTokens(),dept_col=0,emp_col=0;
        int i=0;
        while(st.hasMoreTokens()){
            String tab=st.nextToken().trim();
            if(tab.equals("Dept_Id"))
                dept_col=i;
            if(tab.equals("Employee_Name"))
                emp_col=i;
            i++;
        }
        if(dept_col>=num_col || emp_col>=num_col)
            System.out.println("Column is missing");
        String name="",dept_name="",now="";
        while(sc.hasNext()){
            st=new StringTokenizer(sc.nextLine());
            for(int i1=0;i1<num_col;i1++) {
                now = st.nextToken().trim();
                if (i1 == dept_col)
                    dept_name = now;
                if (i1 == emp_col)
                    name = now;
            }
            if(dept_name.equals(dept))
                System.out.print(name+" ");
        }
        System.out.println();
    }
}
