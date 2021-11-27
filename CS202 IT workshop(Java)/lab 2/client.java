import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.Serializable;
import java.net.ServerSocket;
import java.net.Socket;

class client extends JFrame implements ActionListener{
    String choice="choose";
    client(){
        super("Student Info Record System");
        JButton admin=new JButton("Admin");
        JButton user=new JButton("User");

        admin.setBounds(300,200,160,30);
        user.setBounds(300,230,160,30);
        add(admin);
        add(user);
        admin.addActionListener(this);
        user.addActionListener(this);

        setSize(800,600);
        setLocation(100,100);
        setLayout(null);
        setVisible(true);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

    }
    public void actionPerformed(ActionEvent ae)
    {
        choice=ae.getActionCommand();
        if(choice=="Admin") {
            new admin();
            this.dispose();
            choice="choice";
        }
        else if(choice =="User") {
            new user();
            this.dispose();
            choice="choice";
        }
    }
    public static void main(String[] args){
        new client();
    }
}

class admin extends JFrame implements ActionListener{
    String choice="choose";
    Person p=new Person();
    JTextField f1 = new JTextField();
    JTextField f2 = new JTextField();
    JTextField f3 = new JTextField();
    admin(){
        super("Admin console( first enter the details)");
        JButton add=new JButton("add Details");
        JButton modify=new JButton("modify Details");
        JButton delete=new JButton("delete Details");
        add(add);
        add.addActionListener(this);
        add(modify);
        modify.addActionListener(this);
        add(delete);
        delete.addActionListener(this);
        add.setBounds(30,230,200,30);
        add(add);
        modify.setBounds(30,260,200,30);
        add(modify);
        delete.setBounds(30,290,200,30);
        add(delete);
        add.addActionListener(this);
        modify.addActionListener(this);
        delete.addActionListener(this);

        int x=300,y=300;
        JLabel l1 = new JLabel("Name");
        l1.setBounds(x,y,60,30);
        add(l1);


        f1.setBounds(x+70,y,60,30);
        add(f1);

        JLabel l2 = new JLabel("Roll");
        l2.setBounds(x,y+30,60,30);
        add(l2);

        f2.setBounds(x+70,y+30,60,30);
        add(f2);

        JLabel l3 = new JLabel("Age");
        l3.setBounds(x,y+60,60,30);
        add(l3);

        f3.setBounds(x+70,y+60,60,30);
        add(f3);

        setSize(800,600);
        setLocation(100,100);
        setLayout(null);
        setVisible(true);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }
    public void actionPerformed(ActionEvent ae)
    {
        String action;
        choice=ae.getActionCommand();
        p.name=f1.getText();
        p.rollno=f2.getText();
        p.age=f3.getText();
        if(choice=="add Details" || choice=="modify Details" || choice=="delete Details"){
            action=choice;
            choice="choose";
            try {
                new admin_action(p,action);
                this.dispose();
            }
            catch(Exception e){
                System.exit(0);
            }
            }

    }
}
class admin_action{
    admin_action(Person p,String action) throws Exception{
        Socket socket = new Socket("localhost",77);
        DataInputStream input=new DataInputStream(socket.getInputStream());
        DataOutputStream output=new DataOutputStream(socket.getOutputStream());
        output.writeUTF("1");
        output.writeUTF(action);
        output.writeUTF(p.name);
        if(action=="add Details" || action=="modify Details") {
            output.writeUTF(p.rollno);
            output.writeUTF(p.age);
        }
        System.out.println("Finished communicating with server");
        System.exit(0);
    }
}
class user extends JFrame implements ActionListener{
    String choice="choose";
    user(){
        super("User console");
        JButton b1=new JButton("View by roll");
        JButton b2=new JButton("View by name");
        b1.setBounds(200,100,300,30);
        b2.setBounds(200,130,300,30);
        b1.addActionListener(this);
        b2.addActionListener(this);
        add(b1);
        add(b2);
        setSize(800,600);
        setLocation(100,100);
        setLayout(null);
        setVisible(true);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }
    public void actionPerformed(ActionEvent ae)
    {
        choice=ae.getActionCommand();
        try {
            new user_action(choice);
        }catch(Exception e){

        }
        choice="choose";
    }
}
class user_action extends JFrame{

    user_action(String action)throws Exception{
        super(action);
        Socket socket = new Socket("localhost",77);
        DataInputStream input=new DataInputStream(socket.getInputStream());
        DataOutputStream output=new DataOutputStream(socket.getOutputStream());
        output.writeUTF("0");
        int num=Integer.parseInt(input.readUTF());
        String print="";
        Person p=new Person();
        for(int i=0;i<num;i++){
            p.name=input.readUTF();
            p.rollno=input.readUTF();
            p.age=input.readUTF();
            if(action=="view by roll"){
                print+=p.rollno+" ";
                print+=p.name+" ";
            }else{
                print+=p.name+" ";
                print+=p.rollno+" ";
            }
            print+=p.age+"\n";
        }
        JLabel l=new JLabel(print);
        l.setBounds(10,10,400,500);
        add(l);
        setSize(800,600);
        setLocation(100,100);
        setLayout(null);
        setVisible(true);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }
}