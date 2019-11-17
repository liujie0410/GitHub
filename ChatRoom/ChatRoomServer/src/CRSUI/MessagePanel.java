package CRSUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class MessagePanel extends JPanel implements Runnable ,ActionListener{
    private BorderLayout messageLayout = new BorderLayout();
    private BorderLayout layout2 = new BorderLayout();
    private JLabel topLabel = new JLabel("广播信息", JLabel.CENTER);
    private JTextArea textArea = new JTextArea("以下是聊天记录\n");
    private JButton sendBut = new JButton("发送");
    private JTextField textField = new JTextField("请您输入聊天信息");
    private Font textFieldFont = new Font("标楷体", Font.PLAIN,18);
    private Font textAreaFont = new Font("标楷体", Font.PLAIN,16);
    private JPanel bottomPanel= new JPanel();

    // 通信
    private Socket s = null;
    private ServerSocket ss = null;

    public OfflinePanel offlinePanel = null;

    // 存放socket的数组
    public ArrayList<ChatThread> socketArray = new ArrayList<ChatThread>();


    public MessagePanel() {
        this.setPreferredSize(new Dimension(395, 500));
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
        this.bottomPanel.setSize(new Dimension(395, 100));
        this.bottomPanel.setLayout(layout2);
        this.bottomPanel.add(textField,BorderLayout.CENTER);
        this.bottomPanel.add(sendBut,BorderLayout.SOUTH);
        this.add(bottomPanel,BorderLayout.SOUTH);
        this.sendBut.addActionListener(this);
        try{
            ss = new ServerSocket(9999);
            new Thread(this).start();
        }catch (Exception e){}


    }

    @Override
    public void run() {
        try{
            while(true){
                s = ss.accept();
                ChatThread ct = new ChatThread(s);
                this.socketArray.add(ct);
                ct.start();
            }
        }catch(Exception ex){}
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        for(int i = 0; i < socketArray.size();++i){
            ChatThread ct = (ChatThread)socketArray.get(i);
            ct.ps.println("msg##"+"[系统消息]:"+ this.textField.getText());
        }
        this.textField.setText("");
    }

    class ChatThread extends Thread{
        private boolean nameMark = true;
        private Socket socket = null;
        private BufferedReader br = null;
        public PrintStream ps = null;
        public String name = null;
        public ChatThread(Socket s) throws Exception{
            this.socket = s;
            br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            ps = new PrintStream(s.getOutputStream());
        }
        public void run(){
            try {
                while(true){
//                    System.out.println("1");
                    String str = br.readLine();
//                    System.out.println("2");
                    // 如果是姓名信息
                    if(nameMark){
                        this.name = str;
                        nameMark = false;
                        freshInfo();
                        for(int i = 0; i < socketArray.size(); ++i){
                            ChatThread ct = (ChatThread)socketArray.get(i);
                            if(!ct.name.equals(this.name))
                                ct.ps.println("msg##[系统消息]:"+this.name+"已上线");
                        }
                        continue;
                    }
                    String splitString[] = str.split("##");
                    // 发信息
                    if(splitString[0].equals("群聊")){
                        textArea.append(splitString[1]+"\n");
                        for(int i = 0; i < socketArray.size(); ++i){
                            ChatThread ct = (ChatThread)socketArray.get(i);
                            ct.ps.println("msg##[群发消息]"+splitString[1]);
                        }
                    }else{
                        for(int i = 0; i < socketArray.size(); ++i){
                            ChatThread ct = (ChatThread)socketArray.get(i);
                            if(ct.name.equals(splitString[0])){
                                ct.ps.println("msg##"+splitString[1]);
                                break;
                            }
                        }
                    }
                }
            }catch (Exception e){
                try{
//                    System.out.println(socketArray.size());
                    socketArray.remove(this);
//                    System.out.println(socketArray.size());
                    socket.close();
                    freshInfo();
                    for(int i = 0; i < socketArray.size(); ++i){
                        ChatThread ct = (ChatThread)socketArray.get(i);
                        ct.ps.println("msg##[系统消息]:"+this.name+"已下线");
                    }
                }catch(Exception ex){
                    ex.printStackTrace();
                }

            }
        }

    }
    public void freshInfo(){
        offlinePanel.freshData();
        String str = offlinePanel.nameArea.getText();
        // 发送信息
        for(int i = 0; i < socketArray.size(); ++i){
            ChatThread ct = (ChatThread)socketArray.get(i);
            ct.ps.println("info##"+str);
        }
    }
    public void removeClientWithName(String name){
        for(int i = 0; i < this.socketArray.size(); ++i){
            ChatThread ct = (ChatThread)socketArray.get(i);
            if(ct.name.equals(name)) {
                try {
                    ct.socket.close();
//                    this.socketArray.remove(ct);
//                    this.freshInfo();

                } catch (Exception e) {
                    e.printStackTrace();
                }
//                for(int j = 0; j < socketArray.size(); ++j){
//                    ChatThread ct2 = (ChatThread)socketArray.get(i);
//                    ct2.ps.println("msg##[系统消息]:"+ct.name+"已下线");
//                }
            }
        }
    }

}

