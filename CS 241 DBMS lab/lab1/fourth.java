import java.util.Scanner;
import java.io.*;

public class fourth {
    public static void main(String[] args)throws Exception{
        String Employee_txt="C:\\Users\\Ishan_Jawzz\\dev\\IntelliJ\\lab1\\Employee.txt",arg_city=args[0];
        String Department_txt="C:\\Users\\Ishan_Jawzz\\dev\\IntelliJ\\lab1\\Department.txt";
        File file=new File(Employee_txt);
        Scanner sc=new Scanner(file);
        String[] arr=sc.nextLine().split("\\s+");
        int city_col=0,emp_name_col=0;
        for(int i=0;i<arr.length;i++){
            if(arr[i].equals("Employee_Name"))
                emp_name_col=i;
            if(arr[i].equals("City"))
                city_col=i;
        }
        while(sc.hasNext()){
            arr=sc.nextLine().split("\\s+");
            if(arr[city_col].equals(arg_city)){
                System.out.print(arr[emp_name_col]+" ");
            }
        }
        System.out.println();

    }
}
