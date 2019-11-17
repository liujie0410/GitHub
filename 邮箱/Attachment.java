package mail;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Properties;
 
import javax.activation.DataHandler;
import javax.activation.FileDataSource;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.mail.internet.MimeUtility;
import javax.swing.JOptionPane;
 
public class Attachment {
    //发件人地址
    public static String senderAddress = MailGUI.UserNameSpace.getText();
    //收件人地址
    public static String recipientAddress2 = MailGUI01.ReceiverSpace.getText();
    //发件人账户名
    public static String senderAccount = MailGUI.UserNameSpace.getText();
    //发件人账户密码
    public static String senderPassword = "miranda888";
     
    public Attachment() throws Exception {
    	//1、连接邮件服务器的参数配置
        Properties props = new Properties();
        //设置用户的认证方式
        props.setProperty("mail.smtp.auth", "true");
        //设置传输协议
        props.setProperty("mail.transport.protocol", "smtp");
        //设置发件人的SMTP服务器地址
        props.setProperty("mail.smtp.host", "smtp.163.com");
        //2、创建定义整个应用程序所需的环境信息的 Session 对象
        Session session = Session.getInstance(props);
        //设置调试信息在控制台打印出来
        session.setDebug(true);
        //3、创建邮件的实例对象
        Message msg = getMimeMessage(session);
        //4、根据session对象获取邮件传输对象Transport
        Transport transport = session.getTransport();
        //设置发件人的账户名和密码
        transport.connect(senderAccount, senderPassword);
        //发送邮件，并发送到所有收件人地址，message.getAllRecipients() 获取到的是在创建邮件对象时添加的所有收件人, 抄送人, 密送人
        transport.sendMessage(msg,msg.getAllRecipients());
        JOptionPane.showMessageDialog(null,"发送成功！"); 
        //5、关闭邮件连接
        transport.close();
    }
    
    public static void main(String[] args) throws Exception {
        new Attachment();
    } 
    /**
     * 获得创建一封邮件的实例对象
     * @param session
     * @return
     * @throws MessagingException
     * @throws AddressException
     */
    public static MimeMessage getMimeMessage(Session session) throws Exception{
        //1.创建一封邮件的实例对象
        MimeMessage msg = new MimeMessage(session);
        //2.设置发件人地址
        msg.setFrom(new InternetAddress(senderAddress));
        /**
         * 3.设置收件人地址（可以增加多个收件人、抄送、密送），即下面这一行代码书写多行
         * MimeMessage.RecipientType.TO:发送
         * MimeMessage.RecipientType.CC：抄送
         * MimeMessage.RecipientType.BCC：密送
         */
        //msg.setRecipient(MimeMessage.RecipientType.TO,new InternetAddress(recipientAddress1));
        msg.setRecipient(MimeMessage.RecipientType.TO,new InternetAddress(recipientAddress2));
        //4.设置邮件主题
        msg.setSubject(MailGUI01.SubjectSpace.getText(),"UTF-8");
		
        StringBuffer temptBuffer = new StringBuffer(); 
		StringBuffer temptBuffer01 = new StringBuffer(); 
		temptBuffer.append("收件人： "+recipientAddress2);
        temptBuffer01.append(recipientAddress2+"                         ");
        temptBuffer.append("\n主题:  "+MailGUI01.SubjectSpace.getText());
        Date date=new Date();
        SimpleDateFormat format=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");  
        temptBuffer01.append("发件时间："+format.format(date)+"                         ");
        temptBuffer01.append("主题:"+MailGUI01.SubjectSpace.getText());
        temptBuffer.append("\n邮件内容: \n"+MailGUI01.ContentSpace.getText()+"\n");
        // 9. 创建附件"节点"
        MimeBodyPart attachment = new MimeBodyPart();
        MimeBodyPart mailbody = new MimeBodyPart();
        mailbody.setText(MailGUI01.ContentSpace.getText());
        // 读取本地文件
        DataHandler dh2 = new DataHandler(new FileDataSource("src\\"+MailGUI01.AttachSpace.getText()));
        // 将附件数据添加到"节点"
        temptBuffer.append("附件地址: "+"src\\"+MailGUI01.AttachSpace.getText());
        attachment.setDataHandler(dh2);
        // 设置附件的文件名（需要编码）
        attachment.setFileName(MimeUtility.encodeText(dh2.getName()));       
         
        // 10. 设置（文本）和 附件 的关系（合成一个大的混合"节点" / Multipart ）
        MimeMultipart mm = new MimeMultipart();
        mm.addBodyPart(attachment);     // 如果有多个附件，可以创建多个多次添加
        mm.addBodyPart(mailbody);
        mm.setSubType("mixed");         // 混合关系
 
        // 11. 设置整个邮件的关系（将最终的混合"节点"作为邮件的内容添加到邮件对象）
        msg.setContent(mm);
        //设置邮件的发送时间,默认立即发送
        msg.setSentDate(new Date());
        temptBuffer.append("\n发送成功!");
        LoginSuccGUI.S.append(temptBuffer.toString());
        LoginSuccGUI.k++;
	    LoginSuccGUI.String[LoginSuccGUI.k]=temptBuffer.toString();
	    LoginSuccGUI.String01[LoginSuccGUI.k]=temptBuffer01.toString();
        return msg;
    }
 
}