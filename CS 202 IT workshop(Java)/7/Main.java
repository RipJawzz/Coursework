import java.util.ArrayList;
import java.util.Scanner;

class Exception_Conditions extends RuntimeException{
    Exception_Conditions(String str,int code){
        switch(code){
            case 1:
                System.out.println(str+" contains alphabets but should only contain digits");
                break;
            case 2:
                System.out.println("The PAN should start with an Uppercase letter");
                break;
            case 3:
                System.out.println("The length of PIN should be 6 digits");
                break;
        }
    }
}
class Person extends RuntimeException{
    String pin;
    String PAN;
    Person(String pini,String PANI){
        pin=pini;
        PAN=PANI;
    }
    void validate()throws Exception_Conditions{
        int code=0;
        for(int i=0;i<pin.length();i++){
            if(!Character.isDigit(pin.charAt(i))){
                code=1;
                Exception_Conditions err=new Exception_Conditions(pin,code);
                throw err;
            }
        }
        if(Character.isDigit(PAN.charAt(0)) || !Character.isUpperCase(PAN.charAt(0))){
            code=2;
            Exception_Conditions err=new Exception_Conditions(PAN,code);
            throw err;
        }
        if(pin.length()!=6){
            code=3;
            Exception_Conditions err=new Exception_Conditions(pin,code);
            throw err;
        }
        System.out.println("Valid entries");

    }
}
class RAW extends Person{
    String Deployment;
    RAW(String Deploymenti,String pin, String PAN){
        super(pin,PAN);
        Deployment=Deploymenti;
    }
}
class Army extends Person{
    String Unit;
    int age;
    Army(String Uniti,int agei, String pin, String PAN){
        super(pin,PAN);
        age=agei;
        Unit=Uniti;
    }

}
class Under_cover extends Person{
    int assignment_number;
    Under_cover(int assi, String pin, String PAN){
        super(pin,PAN);
        assignment_number=assi;
    }

}
public class Main{

    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        ArrayList<Person> arr=new ArrayList<>();
        int choice=-1,type,num=-1;
        Integer[] intarr=new Integer[3];
        String[] strarr=new String[3];
        while(choice!=0){
            System.out.println("Enter your choice (100 for HELP)");
            choice=Integer.parseInt(sc.nextLine());
            switch(choice){
                case 1:
                    System.out.println("Enter the PIN and PAN");
                    strarr[0]=sc.nextLine();
                    strarr[1]=sc.nextLine();
                    System.out.println("Enter 1 for RAW agent, 2 for Army personnel, 3 for Undercover agent");
                    try {
                        type = Integer.parseInt(sc.nextLine());
                        switch (type) {
                            case 1:
                                System.out.println("Enter country of deployment");
                                strarr[2] = sc.nextLine();
                                arr.add(new RAW(strarr[2], strarr[0], strarr[1]));
                                break;
                            case 2:
                                System.out.println("Enter Unit and age");
                                strarr[2] = sc.nextLine();
                                intarr[0] = Integer.parseInt(sc.nextLine());
                                arr.add(new Army(strarr[2], intarr[0], strarr[0], strarr[1]));
                                break;
                            case 3:
                                System.out.println("Enter assignment number");
                                intarr[0] = Integer.parseInt(sc.nextLine());
                                arr.add(new Under_cover(intarr[0], strarr[0], strarr[1]));
                                break;
                            default:
                                System.out.println("Wrong input");
                        }
                        num++;
                    }
                    catch(NumberFormatException e){
                        System.err.printf( "\nException: %s\n",e );
                        System.out.println("The above field was an Integer field\n" );
                    }
                    break;
                case 2:
                    if(num>=0){
                    try{
                        arr.get(num).validate();
                    }catch ( Exception  e )
                    {
                        System.err.println( "Exception:");
                        e.printStackTrace();
                    }
                    }
                    else
                        System.out.println("No objects present");
                    break;
                case 3:
                    if(num>=0){
                        arr.remove(num);
                        num--;
                    }
                    else
                        System.out.println("No objects are remaining");
                    break;
                case 100:
                    System.out.println("1:Create new entry\n2:validate data entries of current Personnel\n3:Delete current\n100:Help\n0:Exit");
                    break;
                default:
                    System.out.println("Enter a correct choice");

            }
        }
    }
}
