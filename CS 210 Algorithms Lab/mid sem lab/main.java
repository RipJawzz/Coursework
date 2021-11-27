//Java CS202
//File handling - https://stackoverflow.com/questions/13185727/reading-a-txt-file-using-scanner-class-in-java

import java.util.*;
import java.io.*;

class Avengers{
    //function to calculate max time we can get for Tony
    static double time_alive(double[][] arr,int n){

        double time=0,temp;
        int t;

        for(int i=0;i<n;i++){
            System.out.println("In "+i);
            temp=0;
            if(arr[1][i]==0){

                //time for ship destroyed beyond repair
                arr[1][i]=1;
                temp+=arr[0][i];

                //times for collaterally damaged ships
                t=i-1;
                while(t>=0){
                    if(arr[1][t]==0){
                        temp+=arr[0][t]/2.0;
                        break;
                    }
                    t--;
                }

                t=i+1;
                while(t<n){
                    if(arr[1][t]==0){
                        temp+=arr[0][t]/2.0;
                        break;
                    }
                    t++;
                }

                temp+=time_alive(arr,n);
                if(temp>time)
                    time=temp;
                arr[1][i]=0;

            }
        }
        System.out.println("The time returned is" +time);
        return time;
    }
}
public class main
{
    public static void main(String[] args) {
        int n;
        String file_loc;

        Scanner sc1=new Scanner(System.in);

        System.out.println("Enter file location");
        file_loc=sc1.nextLine();

        sc1.close();

        //trying to get input from file
        try(Scanner sc2 = new Scanner(new File(file_loc))) {

            n = sc2.nextInt();
            double[][] thanosShips = new double[2][n];

            for (int i = 0; i < n; i++) {
                thanosShips[0][i] = sc2.nextDouble();
                thanosShips[1][i]=0;
            }

            sc2.close();

            System.out.println("Tony is alive for "+Avengers.time_alive(thanosShips,n)+" Time");

        }
        catch(IOException ioException) {

            ioException.printStackTrace();

        }
    }
}