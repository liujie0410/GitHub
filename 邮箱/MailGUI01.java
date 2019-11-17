package mail;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.security.GeneralSecurityException;

import javax.swing.*;
import javax.swing.event.*;

import java.awt.BorderLayout;
import java.awt.GridLayout;

import java.io.*;
import java.text.*;
import mail.Attachment;

public class MailGUI01 extends JFrame {
	private FlowLayout flow = new FlowLayout(FlowLayout.LEFT,10,6); 
	private GridLayout grid01 = new GridLayout(3,1,5,5); 
	private GridLayout grid02 = new GridLayout(3,1,5,5); 
	private JLabel ReceiverLabel = new JLabel("     ?????: ");
	private JLabel SubjectLabel = new JLabel("      ??   ??: ");
    static public JTextField ReceiverSpace= new JTextField(27); 
	static public JTextField SubjectSpace= new JTextField(27);
	static public JTextField AttachSpace= new JTextField(22);
	private JLabel ContentLabel = new JLabel("    ???????   13278883326@163.com sent this mail");
	//private JLabel ContentLabel02 = new JLabel("");
	private JLabel AttachLabel = new JLabel("?????????");
	static public JTextArea ContentSpace= new JTextArea(35,65); 
	private JButton SendButton = new JButton("              ????              ");
	private JButton ClearButton = new JButton("           ???             ");
	private JButton CancelButton = new JButton("        ???     ");
	private JButton AttachButton = new JButton("????????????");
	private JPanel Panel = new JPanel(grid01);
	private JPanel NorthPanel = new JPanel();
	private JPanel NorthPanel01 = new JPanel(grid02);
	private JPanel NorthPanel02 = new JPanel(grid02);
	private JPanel NorthPanel04 = new JPanel(flow);
	private JPanel NorthPanel03 = new JPanel(flow);
	private JPanel CenterPanel = new JPanel();
	private JPanel CenterPanel01 = new JPanel();
	//private JPanel CenterPanel02 = new JPanel();
	private JScrollPane ScrollPane = new JScrollPane();
	private JPanel SouthPanel = new JPanel();
	private JPanel SSouthPanel = new JPanel();

		public MailGUI01() {
			ContentSpace.setLineWrap(true);
	        NorthPanel01.add(ReceiverLabel);
	        NorthPanel01.add(SubjectLabel);
	        NorthPanel01.add(AttachLabel);
	        NorthPanel02.add(ReceiverSpace);
	        NorthPanel02.add(SubjectSpace);
	        NorthPanel02.add(AttachSpace); 
	        NorthPanel.add(NorthPanel01);
	        NorthPanel.add(NorthPanel02);
	        NorthPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
	        ScrollPane.setViewportView(ContentSpace);
	        CenterPanel01.add(ScrollPane);
	        CenterPanel.setPreferredSize(new java.awt.Dimension(1000,490));
	        CenterPanel.add(ContentLabel);
	        CenterPanel.add(CenterPanel01);
	        CenterPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
	        SouthPanel.setLayout(flow);
	        SouthPanel.add(SendButton);
	        SouthPanel.add(ClearButton);
	        SSouthPanel.setLayout(flow);
	        SSouthPanel.add(AttachButton);
			Panel.setLayout(new FlowLayout(FlowLayout.CENTER));
			Panel.add(NorthPanel);
			Panel.add(CenterPanel);
			Panel.add(SouthPanel);
			Panel.add(SSouthPanel);
			this.add(Panel);
			this.setSize(1000,688);
			this.setLocation(333, 37);
			this.setTitle("?????");
			this.setVisible(true);	
			
	        SendButton.addActionListener(new ActionListener() {
	        	public void actionPerformed(ActionEvent e) {
	        		try {
						new SendMail();
					} catch (GeneralSecurityException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
	        	}
	        });
	        
	        ClearButton.addActionListener(new ActionListener() {
	        	public void actionPerformed(ActionEvent e) {
	        		ContentSpace.setText(null);
	        	}
	        });

	        AttachButton.addActionListener(new ActionListener() {
	        	public void actionPerformed(ActionEvent e) {
	        		try {
						new Attachment();
					} catch (Exception e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
	        	}
	        });
     }
		//main????
		public static void main(String[] args) throws IOException {
			new MailGUI01();
		}
	
 }