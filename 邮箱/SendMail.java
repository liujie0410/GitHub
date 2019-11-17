package mail;

import java.security.GeneralSecurityException;
import java.text.SimpleDateFormat;
import java.util.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.swing.JOptionPane;
import javax.activation.*;
import com.sun.mail.util.MailSSLSocketFactory;
import mail.MailGUI01;


public class SendMail {
	public SendMail() throws GeneralSecurityException {
		StringBuffer temptBuffer = new StringBuffer(); 
		StringBuffer temptBuffer01 = new StringBuffer(); 
		// �ռ��˵�������
	      //String to = MailGUI01.ReceiverSpace.getText();
		String to = MailGUI01.ReceiverSpace.getText();
		int i,j;
		temptBuffer.append("�ռ��ˣ� "+to);
		temptBuffer01.append("�ռ���: "+to+"                         ");

	      // �����˵�������
	     // String from = MailGUI.UserNameSpace.getText();
		  String from = "13278883326@163.com";
	      // ָ�������ʼ�������Ϊ QQ�ʼ�ϵͳ
	      String host = "smtp.163.com";
	 
	      // ��ȡϵͳ����
	      Properties properties = System.getProperties();
	 
	      // �����ʼ�������
	      properties.setProperty("mail.smtp.host", host);
	      properties.put("mail.smtp.auth", "true");
	        MailSSLSocketFactory sf = new MailSSLSocketFactory();
	        sf.setTrustAllHosts(true);
	        properties.put("mail.smtp.ssl.enable", "true");
	        properties.put("mail.smtp.ssl.socketFactory", sf);
	      // ��ȡĬ��session����
	      Session session = Session.getDefaultInstance(properties,new Authenticator(){
	      public PasswordAuthentication getPasswordAuthentication()
        {
            return new PasswordAuthentication(from,"miranda888"); //�������ʼ��û���������
        }
    });
	      try{
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
	                                  new InternetAddress(to));
	 
	         // Set Subject: ͷ��ͷ�ֶ�
	         message.setSubject(MailGUI01.SubjectSpace.getText());
	         temptBuffer.append("\n����:  "+MailGUI01.SubjectSpace.getText());
	         Date date=new Date();
	         SimpleDateFormat format=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");  
	         temptBuffer01.append("����ʱ�䣺"+format.format(date)+"                         ");
	         temptBuffer01.append("����:"+MailGUI01.SubjectSpace.getText());
	         // ������Ϣ��
	         message.setText(MailGUI01.ContentSpace.getText());
	         temptBuffer.append("\n�ʼ�����: \n"+MailGUI01.ContentSpace.getText()+"\n");
	         // ������Ϣ
	         Transport.send(message);
	
	         System.out.println("Sent message successfully��");
	         JOptionPane.showMessageDialog(null,"���ͳɹ���");
	         temptBuffer.append("���ͳɹ�!\n");
	         LoginSuccGUI.S.append(temptBuffer.toString());
	         
	      }catch (MessagingException mex) {
	         mex.printStackTrace();
	         JOptionPane.showMessageDialog(null,"����ʧ�ܣ�");
	         temptBuffer.append("����ʧ��!\n");
	      }
	      LoginSuccGUI.k++;
	      LoginSuccGUI.String[LoginSuccGUI.k]=temptBuffer.toString();
	      LoginSuccGUI.String01[LoginSuccGUI.k]=temptBuffer01.toString();
	}
	public static void main(String [] args) throws GeneralSecurityException
	   {   
		new SendMail();
	   }
}




