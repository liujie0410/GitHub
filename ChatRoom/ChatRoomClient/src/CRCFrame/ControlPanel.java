package CRCFrame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class ControlPanel extends JPanel implements ActionListener{
    private BorderLayout borderLayout = new BorderLayout();
    private Font chooseFont = new Font("标楷体", Font.PLAIN,16);
    private JComboBox nameBox = new JComboBox();
    private TextArea nameArea = new TextArea("在线好友列表:\n");
    private JPanel panelTop = new JPanel();
    public MessagePanel messagePanel;

    public ControlPanel(){
        this.setLayout(borderLayout);

//        this.setBackground(Color.green);
        this.nameBox.setFont(chooseFont);
        this.nameBox.addItem("群聊");
        this.nameBox.addActionListener(this);
//        this.setPreferredSize(new Dimension(200,200));
        this.add(nameBox, BorderLayout.NORTH);

        JScrollPane containSP = new JScrollPane(this.nameArea);
        this.nameArea.setEditable(false);
        containSP.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        containSP.setPreferredSize(new Dimension(200,500));
        this.panelTop.add(containSP);
        this.add(panelTop,BorderLayout.CENTER);



    }
//    public void freshData(){
//        this.nameBox.removeAllItems();
//        ArrayList<String> sArray = this.messagePanel.nameArray;
//        for(int i = 0; i < sArray.size(); ++i){
//            this.nameBox.addItem(sArray.get(i));
//        }
//    }

    public void clearData(){
        this.nameArea.setText("");
        this.nameArea.append("在线好友列表:\n");
        this.nameBox.removeAllItems();
        this.nameBox.addItem("群聊");
    }
    public void addPeople(String s){
        this.nameArea.append(s+"\n");
        this.nameBox.addItem(s);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        this.messagePanel.markString = (String)this.nameBox.getSelectedItem();
    }
}



//  信息交换

// name##信息
// 如果name 等于 -1， 则群发
// 如果name 等于 0-n， 则单独发
// 需要将获得的index-1后发送

// 从客户端发回的信息
// info##信息   则为登录信息
// msg##信息    则为消息
