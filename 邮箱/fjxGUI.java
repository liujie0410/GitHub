package mail;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.security.GeneralSecurityException;

import javax.mail.Authenticator;
import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.NoSuchProviderException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Store;
import javax.mail.internet.MimeMessage;
import javax.swing.*;
import javax.swing.event.*;

import com.sun.mail.util.MailSSLSocketFactory;

import java.io.*;
import java.text.*;
import mail.MailGUI; 
import mail.MailGUI01;
import mail.ckGUI.DisplayMailListener;
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

public class fjxGUI extends JFrame{
    JPanel Panel = new JPanel();
	JPanel leftPanel = new JPanel(new BorderLayout());
	JPanel leftNorthPanel = new JPanel();
	JPanel leftCenterPanel = new JPanel();
    JPanel rightPanel = new JPanel();
    JLabel SJXLabel = new JLabel("发件箱");
	JScrollPane leftPane = new JScrollPane();
	JList fjxList = new JList();
	JTextArea ta = new JTextArea(15,42);
    public fjxGUI() throws MessagingException {    	
        int i=0;
		int j;
    	fjxList.setListData(LoginSuccGUI.String01);
		fjxList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		fjxList.addListSelectionListener(new fDisplayMailListener());
    	leftPane.setViewportView(fjxList);
    	leftPane.setPreferredSize(new java.awt.Dimension(970,520));
    	leftNorthPanel.add(SJXLabel);
    	leftCenterPanel.add(leftPane);
    	leftPanel.add(leftNorthPanel,BorderLayout.NORTH);
    	leftPanel.add(leftCenterPanel,BorderLayout.CENTER);
    	rightPanel.add(ta);
    	ta.setLineWrap(true);
    	this.setLayout(new BorderLayout());
    	this.add(leftPanel);
    	this.setVisible(true);
    	this.setSize(1000,688);
		this.setLocation(333, 37);
		this.setTitle("发件箱");
    }
	public static void main(String[] args) throws MessagingException {
		// TODO Auto-generated method stub
         new fjxGUI();
	}
	
	class fDisplayMailListener extends JFrame implements ListSelectionListener {
		JPanel xianshiPanel=new JPanel();
		JLabel MailLabel = new JLabel();
		JPanel LabelPanel = new JPanel();
		JPanel ButtonPanel = new JPanel();
		public void valueChanged(ListSelectionEvent event) {
			if (! fjxList.getValueIsAdjusting()) {               
				int i = fjxList.getSelectedIndex();
	       ta.append(LoginSuccGUI.String[i]);
	       rightPanel.add(ta);
	       rightPanel.setPreferredSize(new Dimension(800,600));
	       this.setLayout(new BorderLayout());
	       this.add(LabelPanel,BorderLayout.NORTH);
		   this.add(rightPanel,BorderLayout.CENTER);
           this.setVisible(true);
           this.setSize(1000,688);
   		   this.setLocation(333, 37);
	}
  }
 }
}
