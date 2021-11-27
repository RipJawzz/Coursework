import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import DBcons.*;

public class Update_selection extends JFrame implements ActionListener
{
    JLabel l1;
    JButton b1,b2,back;
    String agent_id;
    Update_selection(String agent_id)
    {
        super("Update Selection");
        this.agent_id=agent_id;

        Font button_font=new Font("Pacifico",Font.BOLD,25);

        l1 = new JLabel("Please select the property sales type:");
        l1.setBounds(20,200,1000,50);
        l1.setFont(new Font("Times New Roman", Font.ITALIC, 30));
        l1.setForeground(Color.white);
        add(l1);

        b1 = new JButton("Property sold");
        b1.setBounds(400,500, 200, 100);
        b1.setForeground(AppData.SelectButtonFore);
        b1.setBackground(AppData.SelectButtonBack);
        b1.setFont(button_font);
        b1.addActionListener(this);
        add(b1);

        b2 = new JButton("Property rented");
        b2.setBounds(610,500,300,100);
        b2.setForeground(AppData.SelectButtonFore);
        b2.setBackground(AppData.SelectButtonBack);
        b2.setFont(button_font);
        b2.addActionListener(this);
        add(b2);

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
    public void actionPerformed(ActionEvent e){
        if(e.getSource()==b1) {
            new Property_Update(agent_id);
        }
        if(e.getSource()==b2) {
            new Rental_Change(agent_id);
        }
        if(e.getSource()==back){
            dispose();
            new Agent_verification();
        }
    }

    public static void main(String[] args)
    {
        new Update_selection("00000");
    }

}
