import java.util.*;
import java.lang.*;
import java.io.*;

class fileToWords extends Thread{
    HashMap<String,String> words=new HashMap<>();
    ArrayList<String> lwords=new ArrayList<>();
    String file;
    fileToWords(String file){
        this.file=file;
    }
    public void run(){
        try {

            Scanner sc=new Scanner(new File(file));
            int line=1,word;
            String pos,str;
            while(sc.hasNext()) {
                StringTokenizer tk = new StringTokenizer(sc.nextLine(), " ");
                word=1;
                while(tk.hasMoreTokens()){
                    str=tk.nextToken();
                    pos=words.get(str);
                    if(pos==null){
                        words.put(str, line+" "+word+" ");
                        lwords.add(str);
                    }else{
                        words.put(str, words.get(str)+line+" "+word+" ");
                    }
                    word++;
                }
                line++;
            }
            sc.close();
        }catch(Exception e){
            System.out.println("Something went wrong");
        }
    }
}
public class main{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        String f1,f2;
        System.out.println("Enter the location of first file");
        f1=sc.nextLine();
        System.out.println("Enter the location of second file");
        f2=sc.nextLine();
        sc.close();
        fileToWords ftw1=new fileToWords(f1);
        ftw1.start();

        fileToWords ftw2=new fileToWords(f2);
        ftw2.start();

        try {
            System.out.println("Waiting for threads to finish.");
            ftw1.join();
            ftw2.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread Interrupted");
        }


        findCommon(ftw1.words,ftw2.words,f1,f2,ftw1.lwords,ftw2.lwords);

    }
    public static void findCommon(HashMap<String,String> words1,HashMap<String,String> words2,String f1,String f2,ArrayList<String> lWords1,ArrayList<String> lWords2){

        for(String str:lWords1){
            if(lWords2.contains(str)) {
                System.out.println(str + " of length " + str.length() + " is found in the following positions:");
                System.out.println("In file " + f1);
                StringTokenizer tk = new StringTokenizer(words1.get(str), " ");
                while (tk.hasMoreTokens()) {
                    System.out.println("line " + tk.nextToken() + " at position " + tk.nextToken());
                }
                System.out.println("In file " + f2);
                tk = new StringTokenizer(words2.get(str), " ");
                while (tk.hasMoreTokens()) {
                    System.out.println("line " + tk.nextToken() + " at position " + tk.nextToken());
                }
            }
        }
    }
}