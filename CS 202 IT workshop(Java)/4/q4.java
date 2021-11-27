import java.io.*;
import java.util.*;
class User{
  private int userID;
  private String name,dob;
  User(){
    userID=0;
    name="NA";
    dob="0";
  }
  public void showDetails(){
    System.out.println("userID "+userID);
    System.out.println("name "+name);
    System.out.println("dob "+dob);
  }
  public void setDetails(int a,String b,String c){
    userID=a;
    name=b;
    dob=c;
  }
  public String retdob(){
    return dob;
  }
  public int retuserID(){
    return userID;
  }
}
class Student extends User{
  private int rollno,semester,cpi;
  Student(){
    rollno=0;
    semester=0;
    cpi=0;
  }
  @Override
  public void showDetails(){
    super.showDetails();
    System.out.println("rollno "+rollno);
    System.out.println("semester "+semester);
    System.out.println("cpi "+cpi);
    System.out.println("");
  }

  public void setDetails(int a1,int a2,int a3,int a,String b,String c){
    rollno=a1;
    semester=a2;
    cpi=a3;
    super.setDetails(a,b,c);
  }
}
class Staff extends User{
  private int employeeID;
  private String sectionName,designation;
  Staff(){
    employeeID=0;
    sectionName="NA";
    designation="NA";
  }
  @Override
  public void showDetails(){
    super.showDetails();
    System.out.println("employeeID "+employeeID);
    System.out.println("sectionName "+sectionName);
    System.out.println("designation "+designation);
    System.out.prinln("");
  }
  //@Override
  public void setDetails(int a1,String a2,String a3,int a,String b,String c){
    employeeID=a1;
    sectionName=a2;
    designation=a3;
    super.setDetails(a,b,c);
  }
  public void check(Staff obj){
    if(designation.equals(obj.designation)==true)
      System.out.println("Same");
    else
      System.out.println("Different");
  }

}
class Faculty extends User{
  private int employeeID,noPublications;
  private String departmentName;
  Faculty(){
    employeeID=0;
    noPublications=0;
    departmentName="NA";
  }
  @Override
  public void showDetails(){
    super.showDetails();
    System.out.println("employeeID "+employeeID);
    System.out.println("noPublications "+noPublications);
    System.out.println("departmentName "+departmentName);
    System.out.prinln("");
  }

  public void setDetails(int a1,int a2,String a3,int a,String b,String c){
    employeeID=a1;
    noPublications=a2;
    departmentName=a3;
    super.setDetails(a,b,c);
  }
  public void check(Faculty obj){
    if(departmentName.equals(obj.departmentName)==true)
      System.out.println("Same");
    else
      System.out.println("Different");
  }
}
class q4{
  public static void main(String args[]){
    Scanner sc=new Scanner(System.in);
    Faculty[] fac=new Faculty[3];
    Student[] stu=new Student[3];
    Staff[] sta=new Staff[3];
    for(int i=0;i<3;i++){
      fac[i]=new Faculty();
      stu[i]=new Student();
      sta[i]=new Staff();
    }
    int i1,i2,i3,i4;
    String s1,s2,s3,s4;
    int ch=-1,sl=0,tr;
    String trash;
    while(ch!=0){
      System.out.println("Enter your choice(100 for help,0 for exit)\n");
      ch=sc.nextInt();
      switch(ch){
        case 0:
          System.out.println("Exiting");
        break;
        case 1:
          System.out.println("Enter 1/2/3 for setting Student/Staff/Faculty and slot number");
          ch=sc.nextInt();
          sl=sc.nextInt();
          System.out.println("Enter userID");
          i1=sc.nextInt();
          trash=sc.nextLine();
          System.out.println("Enter name");
          s1=sc.nextLine();
          System.out.println("Enter dob dd/mm/yy");
          s2=sc.nextLine();
          switch(ch){
            case 1:
              System.out.println("Enter rollno,semester,cpi");
              i2=sc.nextInt();
              i3=sc.nextInt();
              i4=sc.nextInt();
              stu[sl].setDetails(i2,i3,i4,i1,s1,s2);
            break;
            case 2:
              System.out.println("Enter employeeid, section name , designation");
              i2=sc.nextInt();
              trash=sc.nextLine();
              s3=sc.nextLine();
              s4=sc.nextLine();
              sta[sl].setDetails(i2,s3,s4,i1,s1,s2);
            break;
            case 3:
              System.out.println("Enter employee Id,no of publications ,department name");
              i2=sc.nextInt();
              i3=sc.nextInt();
              trash=sc.nextLine();
              s3=sc.nextLine();
              fac[sl].setDetails(i2,i3,s3,i1,s1,s2);
            break;
            default:
              System.out.println("Wrong input");
          }
        break;
        case 2:
          System.out.println("Enter bday to show details");
          trash=sc.nextLine();
          s1=sc.nextLine();
          for(int i=0;i<3;i++){
            if(fac[i].retdob().equals(s1)==true)
              fac[i].showDetails();
          }
          for(int i=0;i<3;i++){
            if(sta[i].retdob().equals(s1)==true)
              sta[i].showDetails();
          }
          for(int i=0;i<3;i++){
            if(stu[i].retdob().equals(s1)==true)
              stu[i].showDetails();
          }
          break;
          case 3:
          System.out.println("Enter userID to show details");
          i1=sc.nextInt();
          for(int i=0;i<3;i++){
            if(fac[i].retuserID()==i1)
              fac[i].showDetails();
          }
          for(int i=0;i<3;i++){
            if(sta[i].retuserID()==i1)
              sta[i].showDetails();
          }
          for(int i=0;i<3;i++){
            if(stu[i].retuserID()==i1)
              stu[i].showDetails();
          }
          break;
          case 4:
            System.out.println("Enter the two slots to comapre for designation");
            i1=sc.nextInt();
            i2=sc.nextInt();
            sta[i1].check(sta[i2]);
          break;
          case 5:
          System.out.println("Enter the two slots to comapre for department");
          i1=sc.nextInt();
          i2=sc.nextInt();
          fac[i1].check(fac[i2]);
          break;
        case 100:
          System.out.println("1:set Details,2:showdetails acc to bday,3:show details by userID,4:check if 2 staff have same designation\n5:if 2 faculty have same department");
        break;
        default:
          System.out.println("Wrong choice!");
      }
    }
  }
}
