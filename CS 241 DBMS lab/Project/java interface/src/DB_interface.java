import DBcons.AppData;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class DB_interface extends JFrame implements ActionListener
{
    JLabel l1,l2,l1b;
    JButton b1,b2;
    DB_interface() {
        super("DB interface");

        l1 = new JLabel("Welcome to Real Estate DataBase interface");
        l1.setBounds(20, 20, 1500, 150);
        l1.setFont(new Font("Times New Roman", Font.ITALIC, 45));
        l1.setForeground(Color.BLACK);
        l1.setBackground(Color.WHITE);
        l1.setOpaque(true);
        add(l1);

        l2 = new JLabel("Please select your user type:");
        l2.setBounds(20, 390, 1000, 30);
        l2.setFont(new Font("Times New Roman", Font.ITALIC, 30));
        l2.setForeground(Color.white);
        add(l2);

        b1 = new JButton("Agent");
        b1.setBounds(400, 500, 200, 100);
        b1.setForeground(AppData.SelectButtonFore);
        b1.setBackground(AppData.SelectButtonBack);
        b1.setFont(AppData.button_font);
        b1.addActionListener(this);
        add(b1);

        b2 = new JButton("RE Office Employee");
        b2.setBounds(610, 500, 400, 100);
        b2.setForeground(AppData.SelectButtonFore);
        b2.setBackground(AppData.SelectButtonBack);
        b2.setFont(AppData.button_font);
        b2.addActionListener(this);
        add(b2);

        /*ImageIcon ii = new ImageIcon("D:/IIIT docs/SEM 4/CS 241 - DBMS lab/Project tp/java interface/src/house.jpg");
        JLabel lable = new JLabel(ii);
        JScrollPane jsp = new JScrollPane(lable);
        getContentPane().add(jsp);*/

        setLocation(200, 300);
        setSize(400, 500);
        setLayout(null);
        setVisible(true);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        getContentPane().setBackground(Color.BLACK);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }
    public void actionPerformed(ActionEvent e){
        if(e.getSource()==b1) {
            dispose();
            new Agent_verification();
        }
        if(e.getSource()==b2) {
            dispose();
            new RE_Office();
        }
    }

    public static void main(String[] args)
    {
        new DB_interface();

    }

}
