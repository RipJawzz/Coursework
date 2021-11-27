import java.net.*;
import java.io.*;
import java.util.*;
class server
{
    public static void main(String args[]) throws Exception
    {
        ServerSocket server = new ServerSocket(77);

        System.out.println("Waiting for client to connect");

        Socket connection = server.accept();

        System.out.println("Just connected ");

        DataInputStream input=new DataInputStream(connection.getInputStream());
        DataOutputStream output=new DataOutputStream(connection.getOutputStream());
        Scanner sc=new Scanner(System.in);
        //C://Users//Ishan_Jawzz//dev//IntelliJ//Premade//src
        String str="",str2="";

        str=input.readUTF();
        String[] op=new String[5];
        try{
            op=file_read(str);
                for (int i = 0; i < 5; i++) {
                    output.writeUTF(op[i]);
                    output.flush();
                }

        }
        catch(Exception e){
            output.writeUTF("no");
            output.flush();
            op[0]="no";
        }

// similarity: 1st two characters mathcing and should be a .txt file
        if(op[0]=="no"){
            StringTokenizer tk=new StringTokenizer(str,"//");
            while(tk.countTokens()!=1){
                str2+=tk.nextToken()+"//";
            }
            String ori=tk.nextToken().trim();
            int iz=0;
            File f = new File(str2);
            String[] filenames=f.list();
            for(String file:filenames){
                if(ori.substring(0, 1).equals(file.substring(0, 1)) && !ori.equals(file) && file.substring(file.length()-4,file.length()).equals(".txt")){
                    output.writeUTF(file);
                    iz++;
                }
                if(iz==3)
                    break;
            }
            output.writeUTF("n");
            output.flush();

            try{

                str=input.readUTF();
                op=file_read(str);
                for (int i1 = 0; i1 < 5; i1++) {
                    output.writeUTF(op[i1]);
                }

            }
            catch(Exception e){
                output.writeUTF("n");
            }

            output.flush();
        }


        input.close();
        connection.close();
        server.close();
    }
    public static String[] file_read(String loc)throws Exception{
        String[] op=new String[5];
        char a=10,b=13;
        System.out.println(a+" "+b);
        int ch,pr=0;
        int lines=1,words=0,char_num=0,l_max=0,w_max=0,temp=0;
        //try{
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
                if(pr==10 && ch==13) {
                    System.out.println("Reducing");
                    words--;
                }
                pr=ch;
            }
            if(ch!='\n' || ch!=' ') {
                words++;
                temp++;
                if(temp>w_max){
                    w_max=temp;
                    l_max=lines;
                }
            }
            op[0]="The number of lines are "+lines;
            op[1]="The number of words are "+words;
            op[2]="The number of characters are "+char_num;
            op[3]="The number of bytes are "+char_num*2;
            op[4]="The line number "+l_max+" contains max words i.e. "+w_max;
            fileR.close();
            return op;
        //}
        /*catch(Exception e){
            op[0]="not available";
            return op;
        }*/

    }
}
