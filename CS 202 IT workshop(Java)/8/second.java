import java.io.*;

public class second{
    public static void main(String args[])throws Exception{
        String loc=args[0];
        int ch,pr=0;
        int lines=1,words=0,char_num=0,l_max=0,w_max=0,temp=0;
        FileReader fileR=new FileReader(loc);
        while((ch=fileR.read()) != -1 ){
            char_num++;
            if((char)ch=='\n'){
                char_num--;
                if(pr!=ch) {
                    words++;
                    temp++;
                }
                if(temp>w_max){
                    w_max=temp;
                    temp=0;
                    l_max=lines;
                }
                lines++;
            }
            if((char)ch==' ') {
                words++;
                temp++;
                }
            if(pr==10 && ch==13)
                words--;
            pr=ch;
        }

        System.out.println("The number of lines are "+lines);
        System.out.println("The number of words are "+words);
        System.out.println("The number of characters are "+char_num);
        System.out.println("The number of bytes are "+char_num*2);
        System.out.println("The line number "+l_max+" contains max words i.e. "+w_max);
        fileR.close();
    }
}
