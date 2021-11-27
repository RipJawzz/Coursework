import java.util.Scanner;
class Function{
        public int string_words(String s){
                int n=0;
                if(!s.isEmpty())
                  n++;
                for(int i=0;i<s.length();i++){
                  if(s.charAt(i)==' ')
                    n++;
                  }  
                return n;
        }
        public void palindrome(String s){
                String word;
                int p=1,len=s.length(),start=0;
                for(int i=0;i<len;i++){
                        if(s.charAt(i)==' ' || i==len-1){
                        		if(i==len-1)
                        			word=s.substring(start);
                        		else
                                	word=s.substring(start,i);
                                start=i+1;
                                for(int i1=0;i1<=word.length()/2;i1++){
                                        if(word.charAt(i1)!=word.charAt(word.length()-1-i1)){
                                                p=0;
                                                break;
                                        }
                                }
                                if(p==1){
                                        System.out.println(word);
                                }
                                p=1;
                        }
                }
        }
}
public class q1{
  public static void main(String args[]){
    Function fn=new Function();
    String s;
    int num;
    Scanner sc=new Scanner(System.in);
    System.out.println("Enter the string");
    s=sc.nextLine();
    num=fn.string_words(s);
    System.out.println("The number of words are "+num);
    fn.palindrome(s);
    sc.close();
  }
}
