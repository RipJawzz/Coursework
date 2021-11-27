import DBcons.AppData;
import DBcons.SQL_Updates;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Property_Update extends JFrame implements ActionListener {
    String agent_id;
    JFrame frame;
    JButton button1;
    JLabel rn_label,sd_label,ag_label,hello,error;
    JTextField rn_text,sd_text,ag_text;
    Property_Update(String agent_id){
        super("Property_Update");
        this.agent_id=agent_id;

        hello = new JLabel();
        hello.setText("Enter the required details");
        hello.setFont(new Font("Times New Roman", Font.ITALIC+Font.BOLD, 30));
        hello.setBounds(20,50,400,30);
        hello.setForeground(Color.white);
        add(hello);

        rn_label = new JLabel();
        rn_label.setText("Registration Number :");
        rn_label.setBounds(20,200,175,30);
        rn_label.setForeground(Color.white);
        add(rn_label);

        sd_label = new JLabel();
        sd_label.setText("Selling Date :");
        sd_label.setBounds(20,300,175,30);
        sd_label.setForeground(Color.white);
        add(sd_label);

        sd_text = new JTextField();
        sd_text.setBounds(200,300,200,30);
        add(sd_text);

        rn_text = new JTextField();
        rn_text.setBounds(200,200,200,30);
        add(rn_text);

        button1 = new JButton();
        button1.setBounds(175,375,100,30);
        button1.setText("Submit");
        button1.setForeground(AppData.SelectButtonFore);
        button1.setBackground(AppData.SelectButtonBack);
        button1.addActionListener(this);
        add(button1);



        error = new JLabel("SQL Exception occured! Try again!");
        error.setBounds(10, 400, 1000, 130);
        error.setFont(new Font("Times New Roman", Font.ITALIC, 35));
        error.setForeground(Color.RED);
        error.setBackground(Color.DARK_GRAY);
        error.setOpaque(true);
        error.setVisible(false);
        add(error);

        setSize(700,700);
        setLayout(null);
        setVisible(true);
        getContentPane().setBackground(Color.black);
        setLocation(400, 100);
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
    }
    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if(actionEvent.getSource()==button1){
            String reg_num,sel_date;
            reg_num = rn_text.getText();
            sel_date = sd_text.getText();
            String re = new SQL_Updates().property_sell_update(agent_id,reg_num,sel_date);
            System.out.println(re);
            if(re=="o")
                frame.dispose();
            else{
                error.setVisible(true);
            }
        }
    }
    public static void main(String args[]){
        new Property_Update("00000");
    }
}
