import java.util.Scanner;
class Book{
  private int bookId,yearOfPublication,numberOfAvailableCopies,totalCopies;
  private String bookTitle,authorName,publisherName;
  Book(){
    bookId=0;
    yearOfPublication=0;
    numberOfAvailableCopies=0;
    totalCopies=0;
    bookTitle="NA";
    authorName="NA";
    publisherName="NA";
  }
  Book(int totalcopies){
    bookId=0;
    yearOfPublication=0;
    numberOfAvailableCopies=0;
    totalCopies=totalCopies;
    bookTitle="NA";
    authorName="NA";
    publisherName="NA";
  }
  public void setDetails(){
  	bookId=1901077;
    yearOfPublication=2000;
    numberOfAvailableCopies=2000;
    totalCopies=2000;
    bookTitle="The ultimate book";
    authorName="Ishan Acharyya";
    publisherName="ishan Acharyya";
  }
  public void setDetails(int id,String title,int year,String author,String publisher,int count){
  	bookId=id;
    yearOfPublication=year;
    numberOfAvailableCopies=count;
    totalCopies=count;
    bookTitle=title;
    authorName=author;
    publisherName=publisher;
  }
  public int getId(){
  	return bookId;
  }
  public void getDetails(){
  	System.out.println("year of publication "+yearOfPublication);
  	System.out.println("number of available copies "+numberOfAvailableCopies);
  	System.out.println("total copies "+totalCopies);
  	System.out.println("bookTitle "+bookTitle);
  	System.out.println("author name "+authorName);
  	System.out.println("publisher name "+publisherName);
  }
  public void issue(){
  	if(numberOfAvailableCopies<=0)
  		System.out.println("No copies left to issue");
  	else
  		numberOfAvailableCopies--;
  
  }
  public void returN(){
  	if(numberOfAvailableCopies>=totalCopies)
  		System.out.println("All copies already returned");
  	else
  		numberOfAvailableCopies++;
  }
}
class books{
  public static void main(String someting[]){
    Scanner sc=new Scanner(System.in);
    int a,b,c,d,choice=100;
    String s1,s2,s3,t;
    Book[] array=new Book[5];
    for(int i=0;i<5;i++){
    	array[i]=new Book();
    }
    while(choice!=0){
    	System.out.println("Enter choice or 5 for help");	
    	choice=sc.nextInt();
    	switch(choice){
    		case 1:
    			System.out.println("Enter book slot number to set details");
    			a=sc.nextInt()-1;
    			System.out.println("Enter id");
    			b=sc.nextInt();
    				t=sc.nextLine();
    			System.out.println("Enter title");
    			s1=sc.nextLine();
    			System.out.println("Enter year");
    			c=sc.nextInt();
    				t=sc.nextLine();
    			System.out.println("Enter author name");
    			s2=sc.nextLine();
    			System.out.println("Enter publisher");	
    			s3=sc.nextLine();
    			System.out.println("Enter total copies");
    			d=sc.nextInt();
    			array[a].setDetails(b,s1,c,s2,s3,d);
    		break;
    		case 2:
    			System.out.println("Enter id to get details");
    			a=sc.nextInt();
    			for(int i=0;i<5;i++){
    				if(array[i].getId()==a)
    					array[i].getDetails();
    			}
    		break;
    		case 3:
    			System.out.println("Enter id to issue");
    			a=sc.nextInt();
    			for(int i=0;i<5;i++){
    				if(array[i].getId()==a){
    					System.out.println("Issuing");
    					array[i].issue();
    					}
    			}
    		break;
    		case 4:
    			System.out.println("Enter id to return");
    			a=sc.nextInt();
    			for(int i=0;i<5;i++){
    				if(array[i].getId()==a){
    					System.out.println("Returning");
    					array[i].returN();	
    				}
    			}
    		break;
    		case 5:
    			System.out.println("1 Set details,2Get details,3 Issue,4 Return,0 Exit");
    		break;
    		case 0:
    			System.out.println("Exiting program");
    		break;
    		default:
    			System.out.println("wrong input");
    	}
    }

  }
}

