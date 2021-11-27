import java.util.*;

abstract class User{
    int userID,PAN;
    String name,dob,address;
    User(int userI,int PA,String nam,String dobu,String addres){
        userID=userI;
        PAN=PA;
        name=nam;
        dob=dobu;
        address=addres;
    }
    User(){}
}
class admin extends User{
    String dateOfJoining,permOps;
    int salary;
    admin(String dateOfJoinin,String permOp,int salar,int userID,int PAN,String name,String dob,String address){
        super(userID,PAN,name,dob,address);
        dateOfJoining=dateOfJoinin;
        permOps=permOp;
        salary=salar;
    }

    void addNewStock(Item it,ArrayList<Item> itemList){
        itemList.add(it);
    }
    void deleteStock(String item_Code,ArrayList<Item> itemList){
        boolean exist=false;
        for(Item i:itemList){
            if(item_Code.equals(i.itemCode)){
                exist=true;
                itemList.remove(i);
            }
            if(exist)
                break;
        }
        if(exist)
            System.out.println("Item has been deleted");
        else
            System.out.println("Item never existed");
    }
    void modifyStock(String itemCode,ArrayList<Item> itemList,int price,int availableQty){
        for(Item i:itemList){
            if(i.itemCode.equals(itemCode)){
                i.price=price;
                i.availableQty=availableQty;
            }
        }
    }
}
class general extends User{
    String dateOfJoining;
    int salary,dutyHourPerDay;
    general(String dateOfJoinin,int salar,int dutyHourPerDa,int userID,int PAN,String name,String dob,String address){
        super(userID,PAN,name,dob,address);
        dateOfJoining=dateOfJoinin;
        dutyHourPerDay=dutyHourPerDa;
        salary=salar;
    }
    void sellItem(sell it,ArrayList<Item> itemList){
        itemList.add(it);
    }
    void returnItem(String itemCode,Return it,ArrayList<Item> itemList){
        if(itemCode.charAt(0)=='f')
            System.out.println("Cant return food item");
        else
            itemList.add(it);
    }
    void displayStock(String itemCode,ArrayList<Item> itemList){
        boolean exist=false;
        for(Item i:itemList){
            if(itemCode.equals(i.itemCode)) {
                i.displayStock();
                exist=true;
            }
        }
        if(!exist)
            System.out.println("The item does not exist");
    }
    void displaySell(int startDate,int endDate,ArrayList<Item> itemList){
        for(Item i:itemList){
            if(i instanceof sell)
                if(((sell) i).dateOfSell>startDate && ((sell) i).dateOfSell<endDate){
                    i.displayStock();
                }

        }
    }
}

abstract class Item{
    String itemCode;
    int availableQty,price;
    Item(String itemCod,int availableQt,int pric){
        itemCode=itemCod;
        availableQty=availableQt;
        price=pric;

    }
    void displayStock(){
        System.out.println("Displaying stock\n"+"Item code "+itemCode+"\nAvailable Quantity "+availableQty+"\nPrice"+price);
    };
}
class FoodItem extends Item {
    String dateOfExpiry;
    FoodItem(String itemCode,int availableQty,int price, String dateOfExpir){
        super(itemCode,availableQty,price);
        dateOfExpiry=dateOfExpiry;
    }
    @Override
    void displayStock(){
        super.displayStock();
        System.out.println("This is a food item.\n Date of expiry is "+dateOfExpiry);
    };
}
class NonFoodItem extends Item{
    int returnCount;
    NonFoodItem(String itemCode,int availableQty,int price, int returnCoun){
        super(itemCode,availableQty,price);
        returnCount=returnCoun;
    }
    @Override
    void displayStock(){
        super.displayStock();
        System.out.println("This is a non food item\nreturnCount is "+returnCount);
    };
}
class sell extends Item{

    public int quantity, totalAmount,dateOfSell;
    sell(String itemCode,int availableQty,int price,int quantit,int totalAmoun,int dateOfSel){
        super(itemCode,availableQty,price);
        quantity=quantit;
        totalAmount=totalAmoun;
        dateOfSell=dateOfSel;
    }
    @Override
    void displayStock(){
        super.displayStock();
        System.out.println("This is a sold item\ndate of sell "+dateOfSell+"\nquantity is "+quantity+"\ntotal Amount "+totalAmount);
    };
}
class Return extends Item{

    String dateOfReturn;
    int quantity, returnAmount;
    Return(String itemCode,int availableQty,int price,String dateOfRetur,int quantit,int returnAmoun){
        super(itemCode,availableQty,price);
        dateOfReturn=dateOfRetur;
        quantity=quantit;
        returnAmount=returnAmoun;
    }
    @Override
    void displayStock(){
        super.displayStock();
        System.out.println("This is a sold item\ndate of return "+dateOfReturn+"\nquantity is "+quantity+"\ntotal Amount "+returnAmount);
    };
}
class main{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        ArrayList<Item> itemList=new ArrayList<>();
        int choice=-1,admin=0;
        String[] strarr=new String[10];
        Integer[] intarr=new Integer[10];
        String strtrash;

        int inttrash;

        System.out.println("Enter 1 if admin and 0 if general");
        admin=Integer.parseInt(sc.nextLine());

        System.out.println("Enter userID,PAN,name,dob,address");
        intarr[0]=Integer.parseInt(sc.nextLine());
        intarr[1]=Integer.parseInt(sc.nextLine());
        strarr[0]=sc.nextLine();

        strarr[1]=sc.nextLine();

        strarr[2]=sc.nextLine();


            System.out.println("Enter date of joining, salary,permissible ops");
            strarr[3]=sc.nextLine();

            intarr[2]=Integer.parseInt(sc.nextLine());
            strarr[4]=sc.nextLine();


            admin ad=new admin(strarr[3],strarr[4],intarr[2],intarr[0],intarr[1],strarr[0],strarr[1],strarr[2]);

            System.out.println("Enter date of joining, salary,dutyhourperday");
            strarr[3]=sc.nextLine();
            intarr[2]=Integer.parseInt(sc.nextLine());
            intarr[3]=Integer.parseInt(sc.nextLine());
            general ge=new general(strarr[3],intarr[2],intarr[3],intarr[0],intarr[1],strarr[0],strarr[1],strarr[2]);



        while(choice!=0 && admin==1) {
            System.out.println("Enter your choice for operation. Enter 100 for help");
            choice=sc.nextInt();
            switch (choice) {
                case 1:
                    System.out.println("Adding new stock");
                    System.out.println("Enter itemcode");
                    strarr[0]=sc.nextLine();

                    System.out.println("Enter available quantity and price");
                    intarr[0]=Integer.parseInt(sc.nextLine());
                    intarr[1]=Integer.parseInt(sc.nextLine());
                    if(strarr[0].charAt(0)=='F'){
                        System.out.println("Enter date of expiry in yyyy-mm-dd");
                        strarr[1]=sc.nextLine();
                        FoodItem it=new FoodItem(strarr[0],intarr[0],intarr[1],strarr[1]);
                        ad.addNewStock(it,itemList);
                    }
                    break;
                case 2:
                    System.out.println("Enter the item code to be removed");
                    strarr[0]=sc.nextLine();
                    ad.deleteStock(strarr[0],itemList);
                    break;
                case 3:
                    System.out.println("Enter itemcode and new price and quantitiy");
                    strarr[0]=sc.nextLine();
                    intarr[0]=Integer.parseInt(sc.nextLine());
                    intarr[2]=Integer.parseInt(sc.nextLine());
                    ad.modifyStock(strarr[0],itemList,intarr[0],intarr[1]);
                    break;

                case 100:
                    System.out.println("1:Add new stock\n2:DeleteStock\n3:Modify Stock\n0:Exit");
                break;
                default:
                    System.out.println("Wrong option");
            }
        }
       while(choice!=0 && admin==0){
            System.out.println("Enter your choice for operation. Enter 100 for help");
            choice=Integer.parseInt(sc.nextLine());
            switch (choice) {
                case 1:


                    System.out.println("Enter item code,available qty,prce,quaantity,totalamt,dateofsell");
                    strarr[0]=sc.nextLine();
                    intarr[0]=Integer.parseInt(sc.nextLine());
                    intarr[1]=Integer.parseInt(sc.nextLine());
                    intarr[2]=Integer.parseInt(sc.nextLine());
                    intarr[3]=Integer.parseInt(sc.nextLine());
                    intarr[4]=Integer.parseInt(sc.nextLine());


                        sell it=new sell(strarr[0],intarr[0],intarr[1],intarr[2],intarr[3],intarr[4]);
                    ge.sellItem(it,itemList);
                    break;
                case 2:


                System.out.println("Enter item code,available qty,prce,dateof return,quantity,return amount");
                strarr[0]=sc.nextLine();
                intarr[0]=Integer.parseInt(sc.nextLine());
                intarr[1]=Integer.parseInt(sc.nextLine());
                    strarr[1]=sc.nextLine();
                intarr[2]=Integer.parseInt(sc.nextLine());
                intarr[3]=Integer.parseInt(sc.nextLine());



                Return it2=new Return(strarr[0],intarr[0],intarr[1],strarr[1],intarr[2],intarr[3]);
                ge.returnItem(strarr[0],it2,itemList);
                case 3:
                    System.out.println("Enter item code to be displayed");
                    strarr[0]=sc.nextLine();
                    ge.displayStock(strarr[0],itemList);
                    break;
                case 4:
                    break;
                case 100:
                    System.out.println("1:Sell item\n2:Return Item\n3:Display stock\n4:display sell\n0:Exit");
                    break;
                default:
                    System.out.println("Wrong option");
            }
        }
    }
}