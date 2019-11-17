package CRCFrame;

import javax.swing.*;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;


public class MyFrame extends JFrame{
    private MessagePanel messagePanel = new MessagePanel();
    private ControlPanel controlPanel = new ControlPanel();

    public  MyFrame(){

        String name = JOptionPane.showInputDialog("输入昵称");
        this.setTitle("客户端:"+name);

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.add(messagePanel, BorderLayout.EAST);
        this.add(controlPanel, BorderLayout.CENTER);

        this.controlPanel.messagePanel = this.messagePanel;
        this.messagePanel.controlPanel = this.controlPanel;

        // 设置Frame属性
        this.setSize(700,600);
        this.setResizable(false);
        this.setLocationRelativeTo(null);
        this.setVisible(true);

        this.messagePanel.nickName = name;
        this.messagePanel.startWorking();

        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                super.windowClosing(e);
                try {
                    messagePanel.socket.close();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        });


    }
//    public void setTitleName(String s){
//        this.
//    }


}
