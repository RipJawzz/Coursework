import java.util.ArrayList;
import java.util.Scanner;
class dat{
    void get_type(int a){
        switch (a) {
            case 1 -> System.out.println("Its a normal employee");
            case 2 -> System.out.println("Its a Faculty");
            case 3 -> System.out.println("Its a staff");
            case 4 -> System.out.println("Its a temporary employee");
        }
    }
}
abstract class Employee {
    final int userID,age;
    final String name;
    Employee(int a, int b,String e){
        userID=a;
        age=b;
        name=e;
    }
    void showDetails(){
        System.out.println("Name="+name+"\nUserId="+userID+"\nage="+age);
    }
    abstract int getType();
}
class Faculty extends Employee {
    final int noPub;
    Faculty(int a,int b,int c,String n){
        super(a,b,n);
        noPub=c;
    }
    int getType(){
        return 2;
    }
    @Override
    void showDetails(){
        super.showDetails();
        System.out.println("no of publication="+noPub);
    }
}
class emp extends Employee {
    final int Salary;
    emp(int a, int b, int c,String n){
        super(a,b,n);
        Salary=c;
    }
    int getType(){
        return 1;
    }
    @Override
    void showDetails(){
        super.showDetails();
        System.out.println("Salary="+Salary);
    }
}
class Staff extends Employee {
    final int Salary;
    Staff(int a,int b,int c,String n){
        super(a,b,n);
        Salary=c;
    }
    int getType(){
        return 3;
    }
    @Override
    void showDetails(){
        super.showDetails();
        System.out.println("Salary="+Salary);
    }
}
class temp_emp extends Employee {
    final int duration;

    temp_emp(int a, int b, int c,String name) {
        super(a, b,name);
        duration = c;
    }

    int getType() {
        return 4;
    }

    @Override
    void showDetails() {
        super.showDetails();
        System.out.println("duration=" + duration);
    }
}
public class q1{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        dat ob=new dat();
        int choice=-1,num=-1,type,admin;
        System.out.println("Are you an admin?1=yes,0=no");
        admin=sc.nextInt();
        ArrayList<Employee> arr=new ArrayList<Employee>();
        int[] dint=new int[3];
        String[] dstr=new String[3];
        while(choice!=0){
            System.out.println("Enter your choice, 100 for help");
            choice=sc.nextInt();
            if(admin==0 && (choice==1 || choice==3)){
                System.out.println("You do not have authorization");
                continue;
            }
            switch(choice){
                case 1:
                    System.out.println("Enter 1:employee,2:faculty,3:staff,4:temporary employee");
                    type=sc.nextInt();
                    if(type>=0 && type<=4){
                        num++;
                        System.out.println("Enter userid and age and name");
                        dint[0]=sc.nextInt();
                        dint[1]=sc.nextInt();
                        dstr[0]=sc.nextLine();
                        dstr[0]=sc.nextLine();
                    }
                    switch(type){
                        case 1:
                            System.out.println("Enter salary");
                            dint[2]=sc.nextInt();
                            emp e1=new emp(dint[0], dint[1],dint[2],dstr[0]);
                            arr.add(e1);
                            break;
                        case 2:
                            System.out.println("Enter no of publications");
                            dint[2]=sc.nextInt();
                            Faculty e2=new Faculty(dint[0], dint[1],dint[2],dstr[0]);
                            arr.add(e2);
                            break;
                        case 3:
                            System.out.println("Enter salary");
                            dint[2]=sc.nextInt();
                            Staff e3=new Staff(dint[0], dint[1],dint[2],dstr[0]);
                            arr.add(e3);
                            break;
                        case 4:
                            System.out.println("Enter duration");
                            dint[2]=sc.nextInt();
                            temp_emp e4=new temp_emp(dint[0], dint[1],dint[2],dstr[0]);
                            arr.add(e4);
                            break;
                        default:
                            System.out.println("This type doesn't exist");
                    }
                    break;
                case 2:
                    if(num>=0)
                        arr.get(num).showDetails();
                    else
                        System.out.println("No objects remaining");
                    break;
                case 3:
                    if(num>=0){
                        arr.remove(num);
                        num--;
                    }
                    else
                        System.out.println("No more object remaining");
                    break;
                case 4:
                    if(num>=0) {
                        type = arr.get(num).getType();
                        ob.get_type(type);
                    }
                    else
                        System.out.println("No more object remaining");
                    break;
                case 100:
                    if(admin==1)
                        System.out.println("Help\n1:set details\n2:get details\n3:Delete object\n4:Get type of user");
                    else
                        System.out.println("Help\n2:get details");
                    break;
                case 0:
                    System.out.println("Exiting the program");
                    break;
                default:
                    System.out.println("Invalid input");
            }
        }
    }

}
