package mail;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.security.GeneralSecurityException;

import javax.mail.Authenticator;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.swing.*;
import javax.swing.event.*;

import com.sun.mail.util.MailSSLSocketFactory;

import java.io.*;
import java.text.*;
import mail.MailGUI; 
import mail.MailGUI01;

public class LoginSuccGUI extends JFrame{
	public static StringBuffer S = new StringBuffer();
	public static String[] String  = new String[100]; 
	public static String[] String01  = new String[100];
    public static int k=0;
	private JButton bjButton = new JButton("       写邮件     ");
	private JButton ckButton = new JButton("       收件箱    ");
	private JButton fjxButton = new JButton("       发件箱    ");
 	private JButton tcButton = new JButton("      退出界面    ");
 	private JPanel leftPanel = new JPanel(new BorderLayout());
 	private JPanel rightPanel = new JPanel();
 	private JPanel LabelPanel1 = new JPanel(new GridLayout(3,1,1,50));
 	private JPanel LabelPanel2 = new JPanel(new GridLayout(2,1,1,150));
 	private JTextArea rightTextArea = new JTextArea(37,90); //先行后列
 	private JPanel ButtonPanel = new JPanel();
	private JLabel cgMessage = new JLabel("                    "
			+ "                   登陆成功!");
	private JLabel m1 = new JLabel(".");
	private JLabel m2 = new JLabel(".");
	private JLabel m3 = new JLabel(".");
	private JLabel m4 = new JLabel(".");
	private JLabel m5 = new JLabel("                                                               "
	+"                                                                                                   "
			+"欢  迎  使  用！");
	private JLabel xzMessage = new JLabel("请选择所要进行的操作：                                              ");
	
	public LoginSuccGUI() {

		bjButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			    //LoginSuccGUI.setVisible(false);
				new MailGUI01();
			}
		});
		ckButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			    //LoginSuccGUI.setVisible(false);
				try {
					new ckGUI();
				} catch (MessagingException | IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		tcButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		fjxButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
                 try {
					new fjxGUI();
				} catch (MessagingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
		}});
		
		this.setLayout(new BorderLayout());
		leftPanel.setPreferredSize(new Dimension(300,738));
		leftPanel.setBorder(BorderFactory.createLineBorder(Color.blue,5));
		rightPanel.setBorder(BorderFactory.createLineBorder(Color.darkGray,5));
		LabelPanel1.add(m1);
		LabelPanel1.add(cgMessage);
		LabelPanel1.add(m2);
		LabelPanel2.add(m3);
		LabelPanel2.add(m4);
		ButtonPanel.setLayout(new GridLayout(4,1,5,10));
		ButtonPanel.add(bjButton);
		ButtonPanel.add(ckButton);
		ButtonPanel.add(fjxButton);
		ButtonPanel.add(tcButton);
		leftPanel.add(LabelPanel1,BorderLayout.NORTH);
		leftPanel.add(ButtonPanel,BorderLayout.CENTER);
		rightPanel.setLayout(new BorderLayout());
		rightPanel.add(m5,BorderLayout.CENTER);
		rightPanel.add(m4,BorderLayout.NORTH);
		leftPanel.add(LabelPanel2,BorderLayout.SOUTH);
		this.add(leftPanel,BorderLayout.WEST);
		this.add(rightPanel,BorderLayout.CENTER);
        this.setTitle("邮箱");
		this.setSize(1382,735);
		this.setLocation(-8, -2);
		this.setVisible(true);	
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new LoginSuccGUI();
	}

}
