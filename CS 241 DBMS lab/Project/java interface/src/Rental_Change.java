import DBcons.AppData;
import DBcons.SQL_Updates;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Rental_Change extends JFrame implements ActionListener {

    String agent_id;
    JFrame frame;
    JButton button1;
    JLabel rn_label,sd_label,ed_label,ag_label,hello,error;
    JTextField rn_text,sd_text,ed_text,ag_text;

    Rental_Change(String agent_id){
        super("Rental Change");

        this.agent_id=agent_id;
        hello = new JLabel();
        hello.setText("Enter the required details");
        hello.setFont(new Font("Times New Roman", Font.ITALIC+Font.BOLD, 30));
        hello.setBounds(20,50,400,30);
        hello.setForeground(Color.white);
        add(hello);

        rn_label = new JLabel();
        rn_label.setText("Registration Number :");
        rn_label.setForeground(Color.WHITE);
        rn_label.setBounds(20,200,175,30);
        add(rn_label);

        sd_label = new JLabel();
        sd_label.setText("Start Date :");
        sd_label.setForeground(Color.WHITE);
        sd_label.setBounds(20,300,175,30);
        add(sd_label);

        ed_label = new JLabel();
        ed_label.setText("Ending Date :");
        ed_label.setForeground(Color.WHITE);
        ed_label.setBounds(20,400,175,30);
        add(ed_label);


        ed_text = new JTextField();
        ed_text.setBounds(200,400,200,30);
        add(ed_text);

        sd_text = new JTextField();
        sd_text.setBounds(200,300,200,30);
        add(sd_text);

        rn_text = new JTextField();
        rn_text.setBounds(200,200,200,30);
        add(rn_text);

        button1 = new JButton();
        button1.setBounds(175,475,100,30);
        button1.setText("Submit");
        button1.setBackground(AppData.SelectButtonBack);
        button1.setBackground(AppData.SelectButtonFore);
        button1.addActionListener(this);
        add(button1);

        error = new JLabel("SQL Exception occured! Try again!");
        error.setBounds(0, 550, 1000, 130);
        error.setFont(new Font("Times New Roman", Font.ITALIC, 35));
        error.setForeground(Color.RED);
        error.setBackground(Color.DARK_GRAY);
        error.setOpaque(true);
        error.setVisible(false);
        add(error);

        getContentPane().setBackground(Color.black);
        setLocation(500, 100);
        setSize(700,700);
        setLayout(null);
        setVisible(true);
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

    }
    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if(actionEvent.getSource()==button1){
            String reg_num,sel_date,end_date;
            reg_num = rn_text.getText();
            sel_date = sd_text.getText();
            end_date = ed_text.getText();
            String re = new SQL_Updates().property_rent_update(agent_id,reg_num,sel_date,end_date);

            if(re=="o")
                frame.dispose();
            else{
                error.setVisible(true);
            }

        }
    }
    public static void main(String args[]){
        new Rental_Change("00000");
    }

}
