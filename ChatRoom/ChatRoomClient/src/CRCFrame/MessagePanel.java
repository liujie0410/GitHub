package CRCFrame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.Socket;

public class MessagePanel extends JPanel implements ActionListener, Runnable{
    private BorderLayout messageLayout = new BorderLayout();
    private BorderLayout layout2 = new BorderLayout();
    private JLabel topLabel = new JLabel("top Label", JLabel.CENTER);
    private JTextArea textArea = new JTextArea("以下是聊天记录\n");
    private JButton sendBut = new JButton("发送");
    private JTextField textField = new JTextField("请您输入聊天信息");
    private Font textFieldFont = new Font("标楷体", Font.PLAIN,18);
    private Font textAreaFont = new Font("标楷体", Font.PLAIN,16);
    private JPanel bottomPanel= new JPanel();


    public ControlPanel controlPanel = null;
    // 标记String
    public String markString = "群聊";
    public String nickName = null;
    // 通信
    public Socket socket = null;



    public MessagePanel(){
        this.setPreferredSize(new Dimension(450, 600));
        this.setBorder(BorderFactory.createLineBorder(Color.gray, 1));
        JScrollPane containSP = new JScrollPane(this.textArea);
//        containSP.setBorder(new EmptyBorder(0,0,0,0));
        this.setLayout(messageLayout);
        this.add(containSP, BorderLayout.CENTER);
        this.add(bottomPanel, BorderLayout.SOUTH);
        this.topLabel.setFont(textFieldFont);
        this.add(topLabel, BorderLayout.NORTH);
        this.textArea.setFont(textAreaFont);
        this.textArea.setEditable(false);
        this.textField.setFont(textFieldFont);
        this.bottomPanel.setSize(new Dimension(450, 100));
        this.bottomPanel.setLayout(layout2);
        this.bottomPanel.add(textField,BorderLayout.CENTER);
        this.bottomPanel.add(sendBut,BorderLayout.SOUTH);
        this.add(bottomPanel,BorderLayout.SOUTH);
        this.sendBut.addActionListener(this);

//        this.controlPanel.nameLabel.setText(this.nickName);



    }

    public void startWorking(){
        try{
            socket = new Socket("127.0.0.1",9999);
            JOptionPane.showMessageDialog(null,"连接成功");
            OutputStream os = socket.getOutputStream();
            PrintStream ps = new PrintStream(os);
            ps.println(this.nickName);
            new Thread(this).start();

        }catch (Exception e){

        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        try{
            OutputStream os = socket.getOutputStream();
            PrintStream ps = new PrintStream(os);
            ps.println(this.markString+"##"+this.nickName + "说:"+ textField.getText());
            if(!this.markString.equals("群聊"))
                textArea.append(this.nickName + "说:"+ textField.getText()+"\n");
            textField.setText("");
        }catch (Exception ex){

        }
    }

    @Override
    public void run() {
        try{
            while(true){
                InputStream is = socket.getInputStream();
                BufferedReader br = new BufferedReader(new InputStreamReader(is));
                String str = null;
                int count = 0;
                while((str = br.readLine())!=null){
                    String stringGet[] = str.split("##");
//                    System.out.println(str);
//                    System.out.println("str1"+stringGet[0]);
//                    System.out.println("str2"+stringGet[1]);
                    if(stringGet.length == 1){
                        if(!stringGet[0].equals(this.nickName))
                            this.controlPanel.addPeople(stringGet[0]);
                        continue;
                    }
                    // 更新消息信息
                    if(stringGet[0].equals("msg")){
                        this.textArea.append(stringGet[1]+"\n");
                    }else{
                        // 更新在线信息
                        this.controlPanel.clearData();
                        }
                    }
                }
        }catch (Exception e){}

    }
}
//    String[] bookNameArr = this.bookName.split("\\.");

