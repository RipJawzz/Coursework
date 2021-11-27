import java.io.*;
import java.lang.reflect.Array;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
class whole implements Serializable{
    ArrayList<Person> arr=new ArrayList<>();
    whole(){

    }
}
public class server {
    public static void main(String[] args) throws Exception{
        int num=0;
        Person ini=new Person();
        ServerSocket server = new ServerSocket(77);
        Socket connection = server.accept();
        DataInputStream input=new DataInputStream(connection.getInputStream());
        DataOutputStream output=new DataOutputStream(connection.getOutputStream());
        System.out.println("Made connection");
        String loc="D://stud.ser";
        File f=new File(loc);
        FileOutputStream fileOut = new FileOutputStream(loc);
        ObjectOutputStream out = new ObjectOutputStream(fileOut);
        ArrayList<Person> arr=new ArrayList<>();
        FileInputStream fin = new FileInputStream(loc);
        ObjectInputStream oin = new ObjectInputStream(fin);

        if(!f.exists()){
            out.writeObject(ini);
        }
        ini=(Person)oin.readObject();
        arr.add(ini);
        for(int i=0;i<ini.num;i++){
            arr.add((Person)oin.readObject());
        }
        int user=Integer.parseInt(input.readUTF());
        String action;
        action=input.readUTF();
        String s1,s2,s3;
        if(user==0){
            if(action=="delete Details"){
                s1= input.readUTF();
                for(Person p:arr){
                    if(p.name==s1) {
                        arr.remove(p);
                        arr.get(0).num--;
                    }
                }
            }
            else if(action=="add Details"){
                Person p=new Person();
                p.name=input.readUTF();
                p.rollno= input.readUTF();
                p.age=input.readUTF();
                arr.add(p);
                arr.get(0).num++;
            }else if(action=="modify Details"){
                Person p=new Person();
                p.name=input.readUTF();
                p.rollno= input.readUTF();
                p.age=input.readUTF();
                for(Person a:arr){
                    if(a.name==p.name)
                        arr.remove(a);
                }
                arr.add(p);
            }

        }else if(user==1){
            output.writeUTF(Integer.toString(arr.size()));
            for(Person p:arr){
                output.writeUTF(p.name);
                output.writeUTF(p.rollno);
                output.writeUTF(p.age);
            }
        }
        if(user==0){
            for(Person p:arr)
                out.writeObject(p);
        }
    }
}
