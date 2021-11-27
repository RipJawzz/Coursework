import java.io.*;
import java.util.*;
class Student implements Serializable{
    String firstName,lastName;
    int rollNo;
    float CPI;
    Student(String a,String b,int c,float d){
        firstName=a;
        lastName=b;
        rollNo=c;
        CPI=d;
    }
    void showDet(){
        System.out.println(firstName+" "+lastName+" "+rollNo+" "+CPI);
    }
    static void displayMin(ArrayList<Student> arr){
        float min=Float.MAX_VALUE;
        for(Student i:arr){
            if(i.CPI<min)
                min=i.CPI;
        }
        if(arr.isEmpty())
                System.out.println("The list is empty");
        else
            System.out.println("The minimum CPI is "+min);
    }
    static void displayAvg(ArrayList<Student> arr){
        float avg=0;
        int len=arr.size();
        for(Student i:arr){
                avg+=i.CPI;
        }
        if(arr.isEmpty())
            System.out.println("The list is empty");
        else {
            avg=avg/len;
            System.out.println("The minimum CPI is " + avg);
        }
    }
}
class first{
    public static void main(String args[])throws Exception{
        String loc;
        Scanner sc=new Scanner(System.in);
        Random rand=new Random();
        ArrayList<Student> arr=new ArrayList<Student>();

        System.out.println("Enter the location for the file creation and write");
        loc=sc.nextLine();
        sc.close();

        FileOutputStream fileOut = new FileOutputStream(loc);
        ObjectOutputStream out = new ObjectOutputStream(fileOut);
        Student[] ars=new Student[10];

        for(int i=0;i<10;i++){
                out.writeObject(new Student(Integer.toString(i)+"f",Integer.toString(i)+"l",rand.nextInt(100),((float)rand.nextInt(100))/10));
        }

        out.close();
        fileOut.close();

        FileInputStream fin = new FileInputStream(loc);
        ObjectInputStream oim = new ObjectInputStream(fin);

        for(int i=0;i<10;i++){
            arr.add((Student)oim.readObject());
            arr.get(i).showDet();
        }

        Student.displayMin(arr);
        Student.displayAvg(arr);

        fin.close();
        oim.close();
    }
}