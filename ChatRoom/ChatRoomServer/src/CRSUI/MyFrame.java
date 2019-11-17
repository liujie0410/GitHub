package CRSUI;

import javax.swing.*;
import java.awt.*;

public class MyFrame extends JFrame {

    private MessagePanel messagePanel = new MessagePanel();
    private OfflinePanel offlinePanel = new OfflinePanel();

    public  MyFrame(){
        this.setTitle("服务器");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.add(messagePanel, BorderLayout.EAST);
        this.add(offlinePanel, BorderLayout.CENTER);

        this.offlinePanel.messagePanel = this.messagePanel;
        this.messagePanel.offlinePanel = this.offlinePanel;

        // 设置Frame属性
        this.setSize(600,500);
        this.setResizable(false);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }
}
