package mail;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.security.GeneralSecurityException;

import javax.mail.Authenticator;
import javax.mail.BodyPart;
import javax.mail.Message;
import javax.mail.Multipart;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.swing.*;
import javax.swing.event.*;

import com.sun.mail.util.MailSSLSocketFactory;

import java.awt.BorderLayout;
import java.awt.GridLayout;

import java.io.*;
import java.text.*;
import mail.SendMail;
import mail.LoginSuccGUI;

public class MailGUI extends JFrame {
	private FlowLayout grid = new FlowLayout(FlowLayout.CENTER,10,20); 
	private JLabel SloganLabel = new JLabel("                     Please login your 163 mail                     ");
	private JLabel UserNameLabel = new JLabel("username:");
	private JLabel PasswordLabel = new JLabel("password:");
	private JButton LoginButton = new JButton("Log in");
	private JPanel Panel = new JPanel();
    static public JTextField UserNameSpace= new JTextField(16); 
    static public JPasswordField PasswordSpace = new JPasswordField(16);
	static private int WIDTH = 300, HEIGHT = 230;

	
		public MailGUI() {
			Panel.setLayout(grid);
	        Panel.add(SloganLabel);
	        Panel.add(UserNameLabel);
	        Panel.add(UserNameSpace);
	        Panel.add(PasswordLabel);
	        Panel.add(PasswordSpace);
	        Panel.add(LoginButton);
	        this.add(Panel);
	        this.setLocation(530, 300);
			this.setSize(WIDTH, HEIGHT);
			this.setVisible(true);	
			this.setDefaultCloseOperation(EXIT_ON_CLOSE);
			LoginButton.addActionListener(new LoginSuccButtonOpe());
			
     }
		//main����
		public static void main(String[] args) throws IOException{
			new MailGUI();
		}
	
		class LoginSuccButtonOpe implements ActionListener{
			public void actionPerformed(ActionEvent e){
				if(e.getSource()==LoginButton) {
				      // ��½�û���������
				      String from = UserNameSpace.getText();
				      if(from==null) {
				    	  JOptionPane.showMessageDialog(null,"��¼������Ϊ�գ�");
				      }
				      //��¼�û�����
				      String password = new String(PasswordSpace.getPassword());
				      if(password==null) {
				    	  JOptionPane.showMessageDialog(null,"��¼���벻��Ϊ�գ�");;
				      }
				      // ָ�������ʼ�������Ϊ 163�ʼ�ϵͳ
				      String host = "smtp.163.com";
				 
				      // ��ȡϵͳ����
				
				      Properties properties = System.getProperties();
				 
				      // �����ʼ�������
				      properties.setProperty("mail.smtp.host", host);
				      properties.put("mail.smtp.auth", "true");
				        MailSSLSocketFactory sf = null;
						try {
							sf = new MailSSLSocketFactory();
						} catch (GeneralSecurityException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
				        sf.setTrustAllHosts(true);
				        properties.put("mail.smtp.ssl.enable", "true");
				        properties.put("mail.smtp.ssl.socketFactory", sf);
				        //�ж������Ƿ���ȷ
				        try{
						Session session = Session.getDefaultInstance(properties,new Authenticator(){
						      public PasswordAuthentication getPasswordAuthentication()
					        {
					            return new PasswordAuthentication(from,new String(MailGUI.PasswordSpace.getPassword())); //�������ʼ��û���������
					        }
					    });
						// ����Ĭ�ϵ� MimeMessage ����
				         MimeMessage message = new MimeMessage(session);
				         message.setSubject("subject");
				         message.setContent("test", "text/plain;charset=UTF-8");
				         Multipart multipart = new MimeMultipart();
				         BodyPart messageBodyPart = new MimeBodyPart();
				         messageBodyPart.setText("test");
				         multipart.addBodyPart(messageBodyPart);
				         message.setContent(multipart);
				         messageBodyPart = new MimeBodyPart();
				         //messageBodyPart.setDataHandler(new DataHandler(new DataSource("xxxx")));
				         messageBodyPart.setFileName("filename");
				         multipart.addBodyPart(messageBodyPart);
				 
				         // Set From: ͷ��ͷ�ֶ�
				         message.setFrom(new InternetAddress(from));
				 
				         // Set To: ͷ��ͷ�ֶ�
				         message.addRecipient(Message.RecipientType.TO,
				                                  new InternetAddress(from));
				 
				         // Set Subject: ͷ��ͷ�ֶ�
				         message.setSubject(MailGUI01.SubjectSpace.getText());
				 
				         // ������Ϣ��
				         message.setText(MailGUI01.ContentSpace.getText());
				 
				         // ������Ϣ
				         Transport.send(message);
				         System.out.println("Sent message successfully��");
				         //JOptionPane.showMessageDialog(null,"���ͳɹ���");
				         new LoginSuccGUI();	
					//
					}
					catch(Exception e1) {
						JOptionPane.showMessageDialog(null,"������󣬵�½ʧ�ܣ�");
						//System.exit(0);
					}
					
					}
				}
			}
		} 


