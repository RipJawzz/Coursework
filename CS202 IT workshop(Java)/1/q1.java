import java.io.*;
import java.util.*;
class name{
	public static void main(String args[]){
		Scanner sc=new Scanner(System.in);
		int n=1;
		String name=sc.nextLine();
		while(name.charAt(n)!=' ')
			n++;
		n++;
		System.out.println(name);
		System.out.println("\""+name+"\"");
		System.out.println(name.substring(n));
	}

}
