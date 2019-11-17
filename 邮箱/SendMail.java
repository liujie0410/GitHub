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
		// 收件人电子邮箱
	      //String to = MailGUI01.ReceiverSpace.getText();
		String to = MailGUI01.ReceiverSpace.getText();
		int i,j;
		temptBuffer.append("收件人： "+to);
		temptBuffer01.append("收件人: "+to+"                         ");

	      // 发件人电子邮箱
	     // String from = MailGUI.UserNameSpace.getText();
		  String from = "13278883326@163.com";
	      // 指定发送邮件的主机为 QQ邮件系统
	      String host = "smtp.163.com";
	 
	      // 获取系统属性
	      Properties properties = System.getProperties();
	 
	      // 设置邮件服务器
	      properties.setProperty("mail.smtp.host", host);
	      properties.put("mail.smtp.auth", "true");
	        MailSSLSocketFactory sf = new MailSSLSocketFactory();
	        sf.setTrustAllHosts(true);
	        properties.put("mail.smtp.ssl.enable", "true");
	        properties.put("mail.smtp.ssl.socketFactory", sf);
	      // 获取默认session对象
	      Session session = Session.getDefaultInstance(properties,new Authenticator(){
	      public PasswordAuthentication getPasswordAuthentication()
        {
            return new PasswordAuthentication(from,"miranda888"); //发件人邮件用户名、密码
        }
    });
	      try{
	         // 创建默认的 MimeMessage 对象
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
	 
	         // Set From: 头部头字段
	         message.setFrom(new InternetAddress(from));
	 
	         // Set To: 头部头字段
	         message.addRecipient(Message.RecipientType.TO,
	                                  new InternetAddress(to));
	 
	         // Set Subject: 头部头字段
	         message.setSubject(MailGUI01.SubjectSpace.getText());
	         temptBuffer.append("\n主题:  "+MailGUI01.SubjectSpace.getText());
	         Date date=new Date();
	         SimpleDateFormat format=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");  
	         temptBuffer01.append("发件时间："+format.format(date)+"                         ");
	         temptBuffer01.append("主题:"+MailGUI01.SubjectSpace.getText());
	         // 设置消息体
	         message.setText(MailGUI01.ContentSpace.getText());
	         temptBuffer.append("\n邮件内容: \n"+MailGUI01.ContentSpace.getText()+"\n");
	         // 发送消息
	         Transport.send(message);
	
	         System.out.println("Sent message successfully！");
	         JOptionPane.showMessageDialog(null,"发送成功！");
	         temptBuffer.append("发送成功!\n");
	         LoginSuccGUI.S.append(temptBuffer.toString());
	         
	      }catch (MessagingException mex) {
	         mex.printStackTrace();
	         JOptionPane.showMessageDialog(null,"发送失败！");
	         temptBuffer.append("发送失败!\n");
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




