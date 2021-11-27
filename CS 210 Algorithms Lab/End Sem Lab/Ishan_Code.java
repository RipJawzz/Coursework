import java.util.*;
import java.io.*;
class student{
    int id;
    ArrayList<student> friends=new ArrayList<>();
    boolean infected=false;
    boolean first=false;
    student(int id){
        this.id=id;
    }
}
public class Ishan_Code{
    //credentials list stores a unique combinations of credentials recieved from a successful infection
    //paths list stores the path taken for an element of credentials
    static ArrayList<String> credentials=new ArrayList<>();
    static ArrayList<String> paths=new ArrayList<>();

    public static void main(String[] args) throws Exception{
        //File handling
        Scanner sc=new Scanner(new File(args[0]));
        File opc=new File("D:\\1901077_Ishan_OUTPUT.txt");
        opc.createNewFile();
        FileWriter op=new FileWriter(opc);

        //necessary variables and data structures
        int nUser,nFriends;
        HashMap<Integer,student> map=new HashMap<>();

        //initial input from input file
        String[] ip=sc.nextLine().split("\\s");
        nUser=Integer.parseInt(ip[0]);
        nFriends=Integer.parseInt(ip[1]);

        //initializing all students in the network
        for(int i=0;i<nUser;i++)
            map.put(i, new student(i));

        //initializing all the friends(edges) among the users
        for(int i=0;i<nFriends;i++){
            ip=sc.nextLine().split("\\s");
            int student_1,student_2;
            student_1=Integer.parseInt(ip[0]);
            student_2=Integer.parseInt(ip[1]);
            map.get(student_1).friends.add(map.get(student_2));
            map.get(student_2).friends.add(map.get(student_1));
        }

        //infecting each student as the first vicitim independently
        for(student s:map.values()){
                s.first=true;
                s.infected=true;
                infect(s,"");
                s.first=false;
                s.infected=false;
        }

        //Writing to the output file
        op.write("Printing all possible paths:"+" ("+paths.size()+")\n");
        if(paths.isEmpty())
           op.write("No possible way to infect in a cycle\n");
        for(String path:paths){
            op.write(path+"\n");
        }
        op.write("Finished\n");


        op.close();
        sc.close();
    }

    //funtion to infect friends of the target user and validate path
    public static void infect(student head, String path) {
        path = path + head.id + " ";
        for (student next : head.friends) {

            if (!next.infected) {
                //infecting head's friends
                next.infected = true;
                infect(next,path);
                next.infected=false;

            } else if (next.first) {
                //validating uniqueness of the path
                String sorted_path= sortPath(path);
                if(!credentials.contains(sorted_path)) {
                    paths.add(path+path.charAt(0));
                    credentials.add(sorted_path);
                }
            }
        }
    }
    //Sorting paths to find credentials recieved in ascending order of id
    public static String sortPath(String inputString)
    {
        char tempArray[] = inputString.toCharArray();
        Arrays.sort(tempArray);
        return new String(tempArray).trim();
    }
}