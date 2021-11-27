import java.util.Scanner;
import java.io.*;

public class third {
    public static void main(String[] args)throws Exception{
        String Employee_txt="C:\\Users\\Ishan_Jawzz\\dev\\IntelliJ\\lab1\\Employee.txt",arg_emp_id=args[0];
        String Department_txt="C:\\Users\\Ishan_Jawzz\\dev\\IntelliJ\\lab1\\Department.txt";
        File file=new File(Employee_txt);
        Scanner sc=new Scanner(file);
        String[] arr=sc.nextLine().split("\\s+");
        int emp_id_col=0,dept_id_col=0;
        String dept_id="";
        for(int i=0;i<arr.length;i++){
            if(arr[i].equals("Employee_Id"))
                emp_id_col=i;
            if(arr[i].equals("Dept_Id"))
                dept_id_col=i;
        }
        while(sc.hasNext()){
            arr=sc.nextLine().split("\\s+");
            if(arr[emp_id_col].equals(arg_emp_id)){
                dept_id=arr[dept_id_col];
                break;
            }
        }
        file=new File(Department_txt);
        sc=new Scanner(file);
        arr=sc.nextLine().split("\\s+");
        int budget_col=0;
        for(int i=0;i<arr.length;i++){
            if(arr[i].equals("Budget"))
                budget_col=i;
            if(arr[i].equals("Department_Id"))
                dept_id_col=i;
        }
        while(sc.hasNext()){
            arr=sc.nextLine().split("\\s+");
            if(arr[dept_id_col].equals(dept_id)){
                System.out.print(arr[budget_col]+" ");

            }
        }
        System.out.println();
    }
}
