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
	JLabel MailNumberLabel = new JLabel("邮件数目： ");
	JLabel ckLabel = new JLabel("请输入查看邮件编号：");
	JLabel fjrLabel = new JLabel("发件人                                                              ");
	JLabel ztLabel = new JLabel("主题                                                                                                                                                      ");
	JLabel fjsjLabel = new JLabel("发件时间                                                                 ");
	JLabel MailLabel;
	static public JTextField MailNumber = new JTextField(10);
	static public JTextField chakan = new JTextField(10);
	static public JTextArea xianshi = new JTextArea(31,55);
	JButton xiazai = new JButton("下载附件");
	JButton xianshiButton = new JButton("查看");
	JButton shanchu = new JButton("  删除  ");
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
	   //准备连接服务器的会话信息  
	    Properties props = new Properties();  
	    props.setProperty("mail.store.protocol","pop3");       // 使用pop3协议  
	    props.setProperty("mail.pop3.port",duankou);           // 端口  
	    props.setProperty("mail.pop3.host", servicePath);       // pop3服务器  
	      
	    // 创建Session实例对象  
	    Session session = Session.getInstance(props);  
	    Store store = session.getStore("pop3");  
	    store.connect("13278883326@163.com", "miranda888"); //163邮箱程序登录属于第三方登录所以这里的密码是163给的授权密码而并非普通的登录密码      
	 // 获得收件箱  
	    Folder folder = store.getFolder("INBOX");  
	    /* Folder.READ_ONLY：只读权限 
	     * Folder.READ_WRITE：可读可写（可以修改邮件的状态） 
	     */  
	    folder.open(Folder.READ_WRITE); //打开收件箱
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
		MailNumberLabel.setText("  邮件总数：   "+Integer.toString(youjianzs));
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
        this.setTitle("邮箱");
		
	    xianshiButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				MimeMessage msg = (MimeMessage) messages[Integer.parseInt(chakan.getText())-1];
		        msg = (MimeMessage) messages[Integer.parseInt(chakan.getText())-1]; 
		        try {
					xianshi.setText("------------------解析第" + msg.getMessageNumber() + "封邮件-------------------- "
					                +"\n主题: " + msg.getSubject()+"\n收件人：" + getFrom(msg)+"\n发送时间："+ getSentDate(msg, null)
					                +"\n邮件大小："+ msg.getSize() * 1024 + "kb"+"\n是否包含附件：");
					if (isContainAttachment(msg)) {  
						xianshi.append("是");
			        }   
			        else {
			        	xianshi.append("否");
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
	            xianshi.append("\n邮件正文：\n" + (content.length() > 100 ? content.substring(0,100) + "..." : content));  
			}
		});
	    
		xiazai.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					MimeMessage msg = (MimeMessage) messages[con];
					saveAttachment(msg, "E:\\mailTest\\"+msg.getSubject() + "_"+con+"_");
					JOptionPane.showMessageDialog(null,"下载成功！");
					} catch (NumberFormatException | MessagingException | IOException e1) {
						 //TODO Auto-generated catch block
						e1.printStackTrace();
					}//保存附件
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
	            	JOptionPane.showMessageDialog(null,"删除成功！");
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
     * 解析邮件 
     * @param messages 要解析的邮件列表 
     */  
    public static void deleteMessage(Message ...messages) throws MessagingException, IOException {  
        if (messages == null || messages.length < 1)   
            throw new MessagingException("未找到要解析的邮件!");  
          
        // 解析所有邮件  
        for (int i = 0, count = messages.length; i < count; i++) {  

            /**
             *   邮件删除      
             */
            Message message = messages[i];
            String subject = message.getSubject();
            // set the DELETE flag to true
            message.setFlag(Flags.Flag.DELETED, true);
            System.out.println("Marked DELETE for message: " + subject);    
       
            
        }
    } 
      
    /** 
     * 获得邮件主题 
     * @param msg 邮件内容 
     * @return 解码后的邮件主题 
     */  
    public static String getSubject(MimeMessage msg) throws UnsupportedEncodingException, MessagingException {  
        return MimeUtility.decodeText(msg.getSubject());  
    }  
      
    /** 
     * 获得邮件发件人 
     * @param msg 邮件内容 
     * @return 姓名 <Email地址> 
     * @throws MessagingException 
     * @throws UnsupportedEncodingException  
     */  
    public static String getFrom(MimeMessage msg) throws MessagingException, UnsupportedEncodingException {  
        String from = "";  
        Address[] froms = msg.getFrom();  
        if (froms.length < 1)  
            throw new MessagingException("没有发件人!");  
          
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
     * 根据收件人类型，获取邮件收件人、抄送和密送地址。如果收件人类型为空，则获得所有的收件人 
     * <p>Message.RecipientType.TO  收件人</p> 
     * <p>Message.RecipientType.CC  抄送</p> 
     * <p>Message.RecipientType.BCC 密送</p> 
     * @param msg 邮件内容 
     * @param type 收件人类型 
     * @return 收件人1 <邮件地址1>, 收件人2 <邮件地址2>, ... 
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
            throw new MessagingException("没有收件人!");  
        for (Address address : addresss) {  
            InternetAddress internetAddress = (InternetAddress)address;  
            receiveAddress.append(internetAddress.toUnicodeString()).append(",");  
        }  
          
        receiveAddress.deleteCharAt(receiveAddress.length()-1); //删除最后一个逗号  
          
        return receiveAddress.toString();  
    }  
      
    /** 
     * 获得邮件发送时间 
     * @param msg 邮件内容 
     * @return yyyy年mm月dd日 星期X HH:mm 
     * @throws MessagingException 
     */  
    public static String getSentDate(MimeMessage msg, String pattern) throws MessagingException {  
        Date receivedDate = msg.getSentDate();  
        if (receivedDate == null)  
            return "";  
          
        if (pattern == null || "".equals(pattern))  
            pattern = "yyyy年MM月dd日 E HH:mm ";  
          
        return new SimpleDateFormat(pattern).format(receivedDate);  
    }  
      
    /** 
     * 判断邮件中是否包含附件 
     * @param msg 邮件内容 
     * @return 邮件中存在附件返回true，不存在返回false 
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
     * 获得邮件文本内容 
     * @param part 邮件体 
     * @param content 存储邮件文本内容的字符串 
     * @throws MessagingException 
     * @throws IOException 
     */  
    public static void getMailTextContent(Part part, StringBuffer content) throws MessagingException, IOException {  
        //如果是文本类型的附件，通过getContent方法可以取到文本内容，但这不是我们需要的结果，所以在这里要做判断  
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
     * 保存附件  
     * @param part 邮件中多个组合体中的其中一个组合体  
     * @param destDir  附件保存目录  
     * @throws UnsupportedEncodingException  
     * @throws MessagingException  
     * @throws FileNotFoundException  
     * @throws IOException  
     */  
    public static void saveAttachment(Part part, String destDir) throws UnsupportedEncodingException, MessagingException,  
            FileNotFoundException, IOException {  
        if (part.isMimeType("multipart/*")) {  
            Multipart multipart = (Multipart) part.getContent();    //复杂体邮件  
            //复杂体邮件包含多个邮件体  
            int partCount = multipart.getCount();  
            for (int i = 0; i < partCount; i++) {  
                //获得复杂体邮件中其中一个邮件体  
                BodyPart bodyPart = multipart.getBodyPart(i);  
                //某一个邮件体也有可能是由多个邮件体组成的复杂体  
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
     * 文本解码 
     * @param encodeText 解码MimeUtility.encodeText(String text)方法编码后的文本 
     * @return 解码后的文本 
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
   * 读取输入流中的数据保存至指定目录  
   * @param is 输入流  
   * @param fileName 文件名  
   * @param destDir 文件存储目录  
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
				 // 准备连接服务器的会话信息  
			    Properties props = new Properties();  
			    props.setProperty("mail.store.protocol","pop3");       // 使用pop3协议  
			    props.setProperty("mail.pop3.port",duankou);           // 端口  
			    props.setProperty("mail.pop3.host", servicePath);       // pop3服务器  
			      
			    // 创建Session实例对象  
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
				} //163邮箱程序登录属于第三方登录所以这里的密码是163给的授权密码而并非普通的登录密码

	        // 获得收件箱  
		    Folder folder = null;
			try {
				folder = store.getFolder("INBOX");
			} catch (MessagingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}  
		    /* Folder.READ_ONLY：只读权限 
		     * Folder.READ_WRITE：可读可写（可以修改邮件的状态） 
		     */  
		    try {
				folder.open(Folder.READ_WRITE);
			} catch (MessagingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} //打开收件箱
	       Message[] messages = null;
		try {
			messages = folder.getMessages();
		} catch (MessagingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
			MimeMessage msg = (MimeMessage) messages[i];

	        msg = (MimeMessage) messages[i]; 
	       MailLabel.setText("------------------解析第" + msg.getMessageNumber() + "封邮件-------------------- ");
	        try {
				xianshi.setText("主题: " + msg.getSubject()+"\n收件人：" + getReceiveAddress(msg, null)+"\n发送时间："+ getSentDate(msg, null)
				                +"\n邮件大小："+ msg.getSize() * 1024 + "kb"+"\n是否包含附件：");
				if (isContainAttachment(msg)) {  
					xianshi.append("是");
		        }   
		        else {
		        	xianshi.append("否");
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
            xianshi.append("\n邮件正文：\n" + (content.length() >200 ? content.substring(0,200) + "..." : content));
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




