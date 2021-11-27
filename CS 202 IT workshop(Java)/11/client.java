import java.net.*;
import java.io.*;
import java.util.*;
class client
{
    public static void main(String args[])throws Exception
    {
        System.out.println("Connecting to server... ");

        Socket socket = new Socket("localhost",77);

        System.out.println("Connected to server... ");

        DataInputStream input=new DataInputStream(socket.getInputStream());
        DataOutputStream output=new DataOutputStream(socket.getOutputStream());

        Scanner sc=new Scanner(System.in);
        String str="",str2="";
        System.out.println("Start communicating with Server. Write stop to finish ");

        System.out.println("Enter the name of the file");
        str=sc.nextLine();
        output.writeUTF(str);
        output.flush();
        for(int i=0;i<5;i++){
            str=input.readUTF();
            if(str.length()<4) {
                System.out.println("File not available");
                break;
            }
            else{
                System.out.println(str);
            }
        }

        if(str.length()<3) {
            System.out.println("Listing similar files");
            while (true) {
                str = input.readUTF();
                if (str.length()>3)
                    System.out.println(str);
                if(str.length()<3)
                    break;
            }
            System.out.println("Enter name of new file to be processed or enter stop");
            str=sc.nextLine();
            if(str!="stop"){
                output.writeUTF(str);
                output.flush();
                for(int i=0;i<5;i++){
                    str=input.readUTF();
                    if(str.length()<3) {
                        System.out.println("File not available");
                        break;
                    }
                    else{
                        System.out.println(str);
                    }
                }
            }

        }

        output.close();
        socket.close();

    }

}
