import java.util.Scanner;
class functions{
	public void sort(int[] arr){
		int len=arr.length,t;
		for(int i=0;i<len;i++){
			for(int i1=0;i1<len-1-i;i1++){
				if(arr[i1]<arr[i1+1]){
					t=arr[i1];
					arr[i1]=arr[i1+1];
					arr[i1+1]=t;
				}
			}
		}

	}

}
public class q2{
	public static void main(String args[]){
		functions fn=new functions();
		int len_arr,k;
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter the number of numbers");
		len_arr=sc.nextInt();
		int[] arr=new int[len_arr];
		System.out.println("Enter the numbers");
		for(int i=0;i<len_arr;i++)
			arr[i]=sc.nextInt();
		fn.sort(arr);
		System.out.println("Enter k");
		k=sc.nextInt();
		for(int i=0;i<k;i++)
			System.out.print(arr[i]+" ");
		System.out.println();
		sc.close();
	}

}
