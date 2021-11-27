import DBcons.AppData;
import DBcons.SQL_Updates;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Agent_verification extends JFrame implements ActionListener {

    JFrame frame;
    JButton submit,back;
    JLabel id_l,pwd_l,error,error_pwd,ask;
    JTextField id_t,pwd_t;
    Agent_verification(){
        super("Agent Verification");

        ask = new JLabel();
        ask.setText("Enter your credentials");
        ask.setFont(new Font("Times New Roman", Font.ITALIC+Font.BOLD, 30));
        ask.setBounds(20,100,400,30);
        ask.setForeground(Color.white);
        add(ask);

        id_l = new JLabel();
        id_l.setText("Agent Id : ");
        id_l.setBounds(20,200,175,30);
        id_l.setForeground(Color.white);
        add(id_l);

        pwd_l = new JLabel();
        pwd_l.setText("Agent password :");
        pwd_l.setBounds(20,300,175,30);
        pwd_l.setForeground(Color.white);
        add(pwd_l);

        id_t = new JTextField();
        id_t.setBounds(200,200,200,30);
        add(id_t);

        pwd_t = new JTextField();
        pwd_t.setBounds(200,300,200,30);
        add(pwd_t);

        submit = new JButton();
        submit.setBounds(175,375,200,30);
        submit.setText("Submit");
        submit.setFont(AppData.button_font);
        submit.setForeground(AppData.SelectButtonFore);
        submit.setBackground(AppData.SelectButtonBack);
        submit.addActionListener(this);
        add(submit);

        error = new JLabel("SQL Exception occured! Try again!");
        error.setBounds(10, 450, 1000, 130);
        error.setFont(new Font("Times New Roman", Font.ITALIC, 35));
        error.setForeground(Color.RED);
        error.setBackground(Color.DARK_GRAY);
        error.setOpaque(true);
        error.setVisible(false);
        add(error);

        error_pwd = new JLabel("Wrong id/pwd! Try again!");
        error_pwd.setBounds(10, 450, 1000, 130);
        error_pwd.setFont(new Font("Times New Roman", Font.ITALIC, 35));
        error_pwd.setForeground(Color.RED);
        error_pwd.setBackground(Color.DARK_GRAY);
        error_pwd.setOpaque(true);
        error_pwd.setVisible(false);
        add(error_pwd);

        back = new JButton("<-");
        back.setBounds(10,10,70,50);
        back.setForeground(Color.WHITE);
        back.setBackground(Color.RED);
        back.setFont(new Font("Pacifico", Font.BOLD, 15));
        back.addActionListener(this);
        add(back);

        getContentPane().setBackground(Color.black);
        setLocation(200, 300);
        setSize(400, 500);
        setLayout(null);
        setVisible(true);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource()== submit){
            error.setVisible(false);
            error_pwd.setVisible(false);
            String agent_id,agent_pwd;
            agent_id = id_t.getText();
            agent_pwd= pwd_t.getText();
            String re = new SQL_Updates().verify_agent(agent_id, agent_pwd);
            System.out.println(re);
            if(re=="o") {
                dispose();
                new Update_selection(agent_id);
            }
            else if(re=="wrong"){
                error_pwd.setVisible(true);
            }else if(re=="error")
                error.setVisible(true);
        }
        if(e.getSource()==back){
            dispose();
            new DB_interface();
        }
    }
    public static void main(String args[]){
        new Agent_verification();
    }
}
