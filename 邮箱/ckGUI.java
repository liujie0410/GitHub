package mail;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.security.GeneralSecurityException;

import javax.mail.Address;
import javax.mail.Authenticator;
import javax.mail.BodyPart;
import javax.mail.Flags;
import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.NoSuchProviderException;
import javax.mail.Part;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Store;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.mail.internet.MimeUtility;
import javax.swing.*;
import javax.swing.event.*;

import com.sun.mail.util.MailSSLSocketFactory;
import java.io.*;
import java.text.*;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;

import javax.mail.Address;
import javax.mail.BodyPart;
import javax.mail.Flags;
import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.Part;
import javax.mail.Session;
import javax.mail.Store;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.mail.internet.MimeUtility;
import java.io.*;
import java.text.*;

public class ckGUI extends JFrame{
	
	static int con;
    static int youjianzs;
	JLabel MailNumberLabel = new JLabel("�ʼ���Ŀ�� ");
	JLabel ckLabel = new JLabel("������鿴�ʼ���ţ�");
	JLabel fjrLabel = new JLabel("������                                                              ");
	JLabel ztLabel = new JLabel("����                                                                                                                                                      ");
	JLabel fjsjLabel = new JLabel("����ʱ��                                                                 ");
	JLabel MailLabel;
	static public JTextField MailNumber = new JTextField(10);
	static public JTextField chakan = new JTextField(10);
	static public JTextArea xianshi = new JTextArea(31,55);
	JButton xiazai = new JButton("���ظ���");
	JButton xianshiButton = new JButton("�鿴");
	JButton shanchu = new JButton("  ɾ��  ");
	JPanel ckNorthPanel = new JPanel(new FlowLayout());
	JPanel ckCenterPanel = new JPanel();
	JPanel ckSouthPanel = new JPanel();
	JPanel ckWestPanel = new JPanel(new BorderLayout());
	JPanel sjxLabelPanel = new JPanel();
	JPanel sjxPanel =  new JPanel();
	JList  sjxList = new JList();
	JScrollPane xianshiPane = new JScrollPane();
	JScrollPane sjxPane = new JScrollPane();

	public ckGUI() throws MessagingException, IOException {

		
		String duankou ="110";
		String servicePath ="pop3.163.com";  
	   //׼�����ӷ������ĻỰ��Ϣ  
	    Properties props = new Properties();  
	    props.setProperty("mail.store.protocol","pop3");       // ʹ��pop3Э��  
	    props.setProperty("mail.pop3.port",duankou);           // �˿�  
	    props.setProperty("mail.pop3.host", servicePath);       // pop3������  
	      
	    // ����Sessionʵ������  
	    Session session = Session.getInstance(props);  
	    Store store = session.getStore("pop3");  
	    store.connect("13278883326@163.com", "miranda888"); //163��������¼���ڵ�������¼���������������163������Ȩ�����������ͨ�ĵ�¼����      
	 // ����ռ���  
	    Folder folder = store.getFolder("INBOX");  
	    /* Folder.READ_ONLY��ֻ��Ȩ�� 
	     * Folder.READ_WRITE���ɶ���д�������޸��ʼ���״̬�� 
	     */  
	    folder.open(Folder.READ_WRITE); //���ռ���
        Message[] messages = folder.getMessages();
			
        int i=0;
		int j;
		
		StringBuffer tempt;
		String list[] = new String[100];	
		for(i=0;i<=messages.length-1;i++) {
			MimeMessage msg = (MimeMessage)messages[i];
			tempt = new StringBuffer();
			tempt.append(getFrom(msg));
			if(tempt.length()<=50) {
				for(j=50-tempt.length();j>=1;j--) {
				tempt.append(" ");
	   		   }
			}
			
			StringBuffer tempt1 = new StringBuffer(getSentDate(msg,null));
			if(tempt1.length()<=50) {
				for(j=50-tempt1.length();j>=1;j--) {
					tempt1.append(" ");
				}
			}
			tempt.append(tempt1.toString());
			
			StringBuffer tempt2 = new StringBuffer(msg.getSubject());
			if(tempt2.length()<=20) {
			for(j=20-tempt2.length();j>=1;j--) {
				tempt2.append(" ");
			 }
		    }
			tempt.append(tempt2.toString());
			list[i]=tempt.toString();
		}

		sjxPane.setPreferredSize(new java.awt.Dimension(970,520));
		sjxList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		sjxList.addListSelectionListener(new DisplayMailListener());
		sjxList.setListData(list);
		sjxPane.setViewportView(sjxList);
	    youjianzs=folder.getMessageCount();    
		MailNumberLabel.setText("  �ʼ�������   "+Integer.toString(youjianzs));
		ckNorthPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
		ckNorthPanel.add(MailNumberLabel);
		sjxLabelPanel.add(fjrLabel);
		sjxLabelPanel.add(fjsjLabel);
		sjxLabelPanel.add(ztLabel);
		ckWestPanel.add(sjxLabelPanel,BorderLayout.NORTH);
		ckWestPanel.add(sjxPanel,BorderLayout.CENTER);
		sjxPanel.add(sjxPane);
		xianshiPane.setViewportView(xianshi);
		xianshi.setLineWrap(true);
		this.setLayout(new BorderLayout());
		this.add(ckNorthPanel,BorderLayout.NORTH);
		this.add(ckCenterPanel,BorderLayout.CENTER);
		this.add(ckWestPanel,BorderLayout.WEST);
		this.setSize(1000,688);
		this.setLocation(333, 37);
		this.setVisible(true);
        this.setTitle("����");
		
	    xianshiButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				MimeMessage msg = (MimeMessage) messages[Integer.parseInt(chakan.getText())-1];
		        msg = (MimeMessage) messages[Integer.parseInt(chakan.getText())-1]; 
		        try {
					xianshi.setText("------------------������" + msg.getMessageNumber() + "���ʼ�-------------------- "
					                +"\n����: " + msg.getSubject()+"\n�ռ��ˣ�" + getFrom(msg)+"\n����ʱ�䣺"+ getSentDate(msg, null)
					                +"\n�ʼ���С��"+ msg.getSize() * 1024 + "kb"+"\n�Ƿ����������");
					if (isContainAttachment(msg)) {  
						xianshi.append("��");
			        }   
			        else {
			        	xianshi.append("��");
			        }  
				} catch (MessagingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
		        StringBuffer content = new StringBuffer(30);  
	            try {
					getMailTextContent(msg, content);
				} catch (MessagingException | IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}  
	            xianshi.append("\n�ʼ����ģ�\n" + (content.length() > 100 ? content.substring(0,100) + "..." : content));  
			}
		});
	    
		xiazai.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					MimeMessage msg = (MimeMessage) messages[con];
					saveAttachment(msg, "E:\\mailTest\\"+msg.getSubject() + "_"+con+"_");
					JOptionPane.showMessageDialog(null,"���سɹ���");
					} catch (NumberFormatException | MessagingException | IOException e1) {
						 //TODO Auto-generated catch block
						e1.printStackTrace();
					}//���渽��
			}
		});
		
		shanchu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Message message = messages[con];
	            String subject=null;
				try {
					subject = message.getSubject();
				} catch (MessagingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
	            // set the DELETE flag to true
	            try {
	            	messages[con].setFlag(Flags.Flag.DELETED, true);
	            	folder.close(true); 
	            	JOptionPane.showMessageDialog(null,"ɾ���ɹ���");
				} catch (MessagingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
	
}

	//static public String[] list;	
	public static void main(String [] args) throws GeneralSecurityException, MessagingException, IOException
	   {   
		new ckGUI();
	   }
	
	
    /** 
     * �����ʼ� 
     * @param messages Ҫ�������ʼ��б� 
     */  
    public static void deleteMessage(Message ...messages) throws MessagingException, IOException {  
        if (messages == null || messages.length < 1)   
            throw new MessagingException("δ�ҵ�Ҫ�������ʼ�!");  
          
        // ���������ʼ�  
        for (int i = 0, count = messages.length; i < count; i++) {  

            /**
             *   �ʼ�ɾ��      
             */
            Message message = messages[i];
            String subject = message.getSubject();
            // set the DELETE flag to true
            message.setFlag(Flags.Flag.DELETED, true);
            System.out.println("Marked DELETE for message: " + subject);    
       
            
        }
    } 
      
    /** 
     * ����ʼ����� 
     * @param msg �ʼ����� 
     * @return �������ʼ����� 
     */  
    public static String getSubject(MimeMessage msg) throws UnsupportedEncodingException, MessagingException {  
        return MimeUtility.decodeText(msg.getSubject());  
    }  
      
    /** 
     * ����ʼ������� 
     * @param msg �ʼ����� 
     * @return ���� <Email��ַ> 
     * @throws MessagingException 
     * @throws UnsupportedEncodingException  
     */  
    public static String getFrom(MimeMessage msg) throws MessagingException, UnsupportedEncodingException {  
        String from = "";  
        Address[] froms = msg.getFrom();  
        if (froms.length < 1)  
            throw new MessagingException("û�з�����!");  
          
        InternetAddress address = (InternetAddress) froms[0];  
        String person = address.getPersonal();  
        if (person != null) {  
            person = MimeUtility.decodeText(person) + " ";  
        } else {  
            person = "";  
        }  
        from = person + "<" + address.getAddress() + ">";  
          
        return from;  
    }  
      
    /** 
     * �����ռ������ͣ���ȡ�ʼ��ռ��ˡ����ͺ����͵�ַ������ռ�������Ϊ�գ��������е��ռ��� 
     * <p>Message.RecipientType.TO  �ռ���</p> 
     * <p>Message.RecipientType.CC  ����</p> 
     * <p>Message.RecipientType.BCC ����</p> 
     * @param msg �ʼ����� 
     * @param type �ռ������� 
     * @return �ռ���1 <�ʼ���ַ1>, �ռ���2 <�ʼ���ַ2>, ... 
     * @throws MessagingException 
     */  
    public static String getReceiveAddress(MimeMessage msg, Message.RecipientType type) throws MessagingException {  
        StringBuffer receiveAddress = new StringBuffer();  
        Address[] addresss = null;  
        if (type == null) {  
            addresss = msg.getAllRecipients();  
        } else {  
            addresss = msg.getRecipients(type);  
        }  
          
        if (addresss == null || addresss.length < 1)  
            throw new MessagingException("û���ռ���!");  
        for (Address address : addresss) {  
            InternetAddress internetAddress = (InternetAddress)address;  
            receiveAddress.append(internetAddress.toUnicodeString()).append(",");  
        }  
          
        receiveAddress.deleteCharAt(receiveAddress.length()-1); //ɾ�����һ������  
          
        return receiveAddress.toString();  
    }  
      
    /** 
     * ����ʼ�����ʱ�� 
     * @param msg �ʼ����� 
     * @return yyyy��mm��dd�� ����X HH:mm 
     * @throws MessagingException 
     */  
    public static String getSentDate(MimeMessage msg, String pattern) throws MessagingException {  
        Date receivedDate = msg.getSentDate();  
        if (receivedDate == null)  
            return "";  
          
        if (pattern == null || "".equals(pattern))  
            pattern = "yyyy��MM��dd�� E HH:mm ";  
          
        return new SimpleDateFormat(pattern).format(receivedDate);  
    }  
      
    /** 
     * �ж��ʼ����Ƿ�������� 
     * @param msg �ʼ����� 
     * @return �ʼ��д��ڸ�������true�������ڷ���false 
     * @throws MessagingException 
     * @throws IOException 
     */  
    public static boolean isContainAttachment(Part part) throws MessagingException, IOException {  
        boolean flag = false;  
        if (part.isMimeType("multipart/*")) {  
            MimeMultipart multipart = (MimeMultipart) part.getContent();  
            int partCount = multipart.getCount();  
            for (int i = 0; i < partCount; i++) {  
                BodyPart bodyPart = multipart.getBodyPart(i);  
                String disp = bodyPart.getDisposition();  
                if (disp != null && (disp.equalsIgnoreCase(Part.ATTACHMENT) || disp.equalsIgnoreCase(Part.INLINE))) {  
                    flag = true;  
                } else if (bodyPart.isMimeType("multipart/*")) {  
                    flag = isContainAttachment(bodyPart);  
                } else {  
                    String contentType = bodyPart.getContentType();  
                    if (contentType.indexOf("application") != -1) {  
                        flag = true;  
                    }    
                      
                    if (contentType.indexOf("name") != -1) {  
                        flag = true;  
                    }   
                }  
                  
                if (flag) break;  
            }  
        } else if (part.isMimeType("message/rfc822")) {  
            flag = isContainAttachment((Part)part.getContent());  
        }  
        return flag;  
    }  
        
    
    /** 
     * ����ʼ��ı����� 
     * @param part �ʼ��� 
     * @param content �洢�ʼ��ı����ݵ��ַ��� 
     * @throws MessagingException 
     * @throws IOException 
     */  
    public static void getMailTextContent(Part part, StringBuffer content) throws MessagingException, IOException {  
        //������ı����͵ĸ�����ͨ��getContent��������ȡ���ı����ݣ����ⲻ��������Ҫ�Ľ��������������Ҫ���ж�  
        boolean isContainTextAttach = part.getContentType().indexOf("name") > 0;   
        if (part.isMimeType("text/*") && !isContainTextAttach) {  
            content.append(part.getContent().toString());  
        } else if (part.isMimeType("message/rfc822")) {   
            getMailTextContent((Part)part.getContent(),content);  
        } else if (part.isMimeType("multipart/*")) {  
            Multipart multipart = (Multipart) part.getContent();  
            int partCount = multipart.getCount();  
            for (int i = 0; i < partCount; i++) {  
                BodyPart bodyPart = multipart.getBodyPart(i);  
                getMailTextContent(bodyPart,content);  
            }  
        }  
    }  
      
    /**  
     * ���渽��  
     * @param part �ʼ��ж��������е�����һ�������  
     * @param destDir  ��������Ŀ¼  
     * @throws UnsupportedEncodingException  
     * @throws MessagingException  
     * @throws FileNotFoundException  
     * @throws IOException  
     */  
    public static void saveAttachment(Part part, String destDir) throws UnsupportedEncodingException, MessagingException,  
            FileNotFoundException, IOException {  
        if (part.isMimeType("multipart/*")) {  
            Multipart multipart = (Multipart) part.getContent();    //�������ʼ�  
            //�������ʼ���������ʼ���  
            int partCount = multipart.getCount();  
            for (int i = 0; i < partCount; i++) {  
                //��ø������ʼ�������һ���ʼ���  
                BodyPart bodyPart = multipart.getBodyPart(i);  
                //ĳһ���ʼ���Ҳ�п������ɶ���ʼ�����ɵĸ�����  
                String disp = bodyPart.getDisposition();  
                if (disp != null && (disp.equalsIgnoreCase(Part.ATTACHMENT) || disp.equalsIgnoreCase(Part.INLINE))) {  
                    InputStream is = bodyPart.getInputStream();  
                    saveFile(is, destDir, decodeText(bodyPart.getFileName()));  
                } else if (bodyPart.isMimeType("multipart/*")) {  
                    saveAttachment(bodyPart,destDir);  
                } else {  
                    String contentType = bodyPart.getContentType();  
                    if (contentType.indexOf("name") != -1 || contentType.indexOf("application") != -1) {  
                        saveFile(bodyPart.getInputStream(), destDir, decodeText(bodyPart.getFileName()));  
                    }  
                }  
            }  
        } else if (part.isMimeType("message/rfc822")) {  
            saveAttachment((Part) part.getContent(),destDir);  
        }  
    }
    /** 
     * �ı����� 
     * @param encodeText ����MimeUtility.encodeText(String text)�����������ı� 
     * @return �������ı� 
     * @throws UnsupportedEncodingException 
     */  
    public static String decodeText(String encodeText) throws UnsupportedEncodingException {  
        if (encodeText == null || "".equals(encodeText)) {  
            return "";  
        } else {  
            return MimeUtility.decodeText(encodeText);  
        }  
    }
    
  /**  
   * ��ȡ�������е����ݱ�����ָ��Ŀ¼  
   * @param is ������  
   * @param fileName �ļ���  
   * @param destDir �ļ��洢Ŀ¼  
   * @throws FileNotFoundException  
   * @throws IOException  
   */  
  private static void saveFile(InputStream is, String destDir, String fileName)  
          throws FileNotFoundException, IOException {  
      BufferedInputStream bis = new BufferedInputStream(is);  
      BufferedOutputStream bos = new BufferedOutputStream(  
              new FileOutputStream(new File(destDir + fileName)));  
      int len = -1;  
      while ((len = bis.read()) != -1) {  
          bos.write(len);  
          bos.flush();  
      }  
      bos.close();  
      bis.close();  
  } 
     
	class DisplayMailListener extends JFrame implements ListSelectionListener {
		JPanel xianshiPanel=new JPanel();
     	JLabel MailLabel = new JLabel();
		JPanel LabelPanel = new JPanel();
		JPanel ButtonPanel = new JPanel();
		public void valueChanged(ListSelectionEvent event) {
			if (! sjxList.getValueIsAdjusting()) { 
				con = sjxList.getSelectedIndex();
				int i = sjxList.getSelectedIndex();
				String duankou ="110";
				String servicePath ="pop3.163.com";  
				 // ׼�����ӷ������ĻỰ��Ϣ  
			    Properties props = new Properties();  
			    props.setProperty("mail.store.protocol","pop3");       // ʹ��pop3Э��  
			    props.setProperty("mail.pop3.port",duankou);           // �˿�  
			    props.setProperty("mail.pop3.host", servicePath);       // pop3������  
			      
			    // ����Sessionʵ������  
			    Session session = Session.getInstance(props);  
			    Store store = null;
				try {
					store = session.getStore("pop3");
				} catch (NoSuchProviderException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}  
			    try {
					store.connect("13278883326@163.com", "miranda888");
				} catch (MessagingException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} //163��������¼���ڵ�������¼���������������163������Ȩ�����������ͨ�ĵ�¼����

	        // ����ռ���  
		    Folder folder = null;
			try {
				folder = store.getFolder("INBOX");
			} catch (MessagingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}  
		    /* Folder.READ_ONLY��ֻ��Ȩ�� 
		     * Folder.READ_WRITE���ɶ���д�������޸��ʼ���״̬�� 
		     */  
		    try {
				folder.open(Folder.READ_WRITE);
			} catch (MessagingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} //���ռ���
	       Message[] messages = null;
		try {
			messages = folder.getMessages();
		} catch (MessagingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
			MimeMessage msg = (MimeMessage) messages[i];

	        msg = (MimeMessage) messages[i]; 
	       MailLabel.setText("------------------������" + msg.getMessageNumber() + "���ʼ�-------------------- ");
	        try {
				xianshi.setText("����: " + msg.getSubject()+"\n�ռ��ˣ�" + getReceiveAddress(msg, null)+"\n����ʱ�䣺"+ getSentDate(msg, null)
				                +"\n�ʼ���С��"+ msg.getSize() * 1024 + "kb"+"\n�Ƿ����������");
				if (isContainAttachment(msg)) {  
					xianshi.append("��");
		        }   
		        else {
		        	xianshi.append("��");
		        }  
			} catch (MessagingException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
	        StringBuffer content = new StringBuffer(30);  
            try {
				getMailTextContent(msg, content);
			} catch (MessagingException | IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}  
            xianshi.append("\n�ʼ����ģ�\n" + (content.length() >200 ? content.substring(0,200) + "..." : content));
            }
		   xianshiPanel.add(MailLabel);
	       xianshiPanel.add(xianshiPane);
	       xianshiPanel.setPreferredSize(new Dimension(250,300));
	       xianshiPanel.add(xiazai);
	       LabelPanel.add(MailLabel);
	       ButtonPanel.add(xiazai);
	       ButtonPanel.add(shanchu);
	       this.setLayout(new BorderLayout());
	       this.add(LabelPanel,BorderLayout.NORTH);
		   this.add(xianshiPanel,BorderLayout.CENTER);
		   this.add(ButtonPanel,BorderLayout.SOUTH);
           this.setVisible(true);
           this.setSize(1000,688);
   		   this.setLocation(333, 37);
	}
  }
}




