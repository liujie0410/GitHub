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
    //�����˵�ַ
    public static String senderAddress = MailGUI.UserNameSpace.getText();
    //�ռ��˵�ַ
    public static String recipientAddress2 = MailGUI01.ReceiverSpace.getText();
    //�������˻���
    public static String senderAccount = MailGUI.UserNameSpace.getText();
    //�������˻�����
    public static String senderPassword = "miranda888";
     
    public Attachment() throws Exception {
    	//1�������ʼ��������Ĳ�������
        Properties props = new Properties();
        //�����û�����֤��ʽ
        props.setProperty("mail.smtp.auth", "true");
        //���ô���Э��
        props.setProperty("mail.transport.protocol", "smtp");
        //���÷����˵�SMTP��������ַ
        props.setProperty("mail.smtp.host", "smtp.163.com");
        //2��������������Ӧ�ó�������Ļ�����Ϣ�� Session ����
        Session session = Session.getInstance(props);
        //���õ�����Ϣ�ڿ���̨��ӡ����
        session.setDebug(true);
        //3�������ʼ���ʵ������
        Message msg = getMimeMessage(session);
        //4������session�����ȡ�ʼ��������Transport
        Transport transport = session.getTransport();
        //���÷����˵��˻���������
        transport.connect(senderAccount, senderPassword);
        //�����ʼ��������͵������ռ��˵�ַ��message.getAllRecipients() ��ȡ�������ڴ����ʼ�����ʱ��ӵ������ռ���, ������, ������
        transport.sendMessage(msg,msg.getAllRecipients());
        JOptionPane.showMessageDialog(null,"���ͳɹ���"); 
        //5���ر��ʼ�����
        transport.close();
    }
    
    public static void main(String[] args) throws Exception {
        new Attachment();
    } 
    /**
     * ��ô���һ���ʼ���ʵ������
     * @param session
     * @return
     * @throws MessagingException
     * @throws AddressException
     */
    public static MimeMessage getMimeMessage(Session session) throws Exception{
        //1.����һ���ʼ���ʵ������
        MimeMessage msg = new MimeMessage(session);
        //2.���÷����˵�ַ
        msg.setFrom(new InternetAddress(senderAddress));
        /**
         * 3.�����ռ��˵�ַ���������Ӷ���ռ��ˡ����͡����ͣ�����������һ�д�����д����
         * MimeMessage.RecipientType.TO:����
         * MimeMessage.RecipientType.CC������
         * MimeMessage.RecipientType.BCC������
         */
        //msg.setRecipient(MimeMessage.RecipientType.TO,new InternetAddress(recipientAddress1));
        msg.setRecipient(MimeMessage.RecipientType.TO,new InternetAddress(recipientAddress2));
        //4.�����ʼ�����
        msg.setSubject(MailGUI01.SubjectSpace.getText(),"UTF-8");
		
        StringBuffer temptBuffer = new StringBuffer(); 
		StringBuffer temptBuffer01 = new StringBuffer(); 
		temptBuffer.append("�ռ��ˣ� "+recipientAddress2);
        temptBuffer01.append(recipientAddress2+"                         ");
        temptBuffer.append("\n����:  "+MailGUI01.SubjectSpace.getText());
        Date date=new Date();
        SimpleDateFormat format=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");  
        temptBuffer01.append("����ʱ�䣺"+format.format(date)+"                         ");
        temptBuffer01.append("����:"+MailGUI01.SubjectSpace.getText());
        temptBuffer.append("\n�ʼ�����: \n"+MailGUI01.ContentSpace.getText()+"\n");
        // 9. ��������"�ڵ�"
        MimeBodyPart attachment = new MimeBodyPart();
        MimeBodyPart mailbody = new MimeBodyPart();
        mailbody.setText(MailGUI01.ContentSpace.getText());
        // ��ȡ�����ļ�
        DataHandler dh2 = new DataHandler(new FileDataSource("src\\"+MailGUI01.AttachSpace.getText()));
        // ������������ӵ�"�ڵ�"
        temptBuffer.append("������ַ: "+"src\\"+MailGUI01.AttachSpace.getText());
        attachment.setDataHandler(dh2);
        // ���ø������ļ�������Ҫ���룩
        attachment.setFileName(MimeUtility.encodeText(dh2.getName()));       
         
        // 10. ���ã��ı����� ���� �Ĺ�ϵ���ϳ�һ����Ļ��"�ڵ�" / Multipart ��
        MimeMultipart mm = new MimeMultipart();
        mm.addBodyPart(attachment);     // ����ж�����������Դ������������
        mm.addBodyPart(mailbody);
        mm.setSubType("mixed");         // ��Ϲ�ϵ
 
        // 11. ���������ʼ��Ĺ�ϵ�������յĻ��"�ڵ�"��Ϊ�ʼ���������ӵ��ʼ�����
        msg.setContent(mm);
        //�����ʼ��ķ���ʱ��,Ĭ����������
        msg.setSentDate(new Date());
        temptBuffer.append("\n���ͳɹ�!");
        LoginSuccGUI.S.append(temptBuffer.toString());
        LoginSuccGUI.k++;
	    LoginSuccGUI.String[LoginSuccGUI.k]=temptBuffer.toString();
	    LoginSuccGUI.String01[LoginSuccGUI.k]=temptBuffer01.toString();
        return msg;
    }
 
}