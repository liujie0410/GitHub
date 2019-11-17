package CRSUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class OfflinePanel extends JPanel implements ActionListener{
    private BorderLayout borderLayout = new BorderLayout();
    private BorderLayout borderLayout2 = new BorderLayout();
    private Font chooseFont = new Font("标楷体", Font.PLAIN,16);
    private JComboBox nameBox = new JComboBox();
    public TextArea nameArea = new TextArea("在线列表\n");
    private JPanel panelTop = new JPanel();
    private JPanel panelbottom = new JPanel();

    private String markString = null;
    public MessagePanel messagePanel = null;

    public OfflinePanel(){
        this.setLayout(borderLayout);

        JScrollPane containSP = new JScrollPane(this.nameArea);
        this.nameArea.setEditable(false);
        containSP.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
//        containSP.setBorder(new EmptyBorder(0,0,0,0));
        containSP.setPreferredSize(new Dimension(200,410));
        this.panelTop.add(containSP);
        this.add(panelTop, BorderLayout.CENTER);

//        this.setBackground(Color.green);
        this.nameBox.setFont(chooseFont);
        this.nameBox.addActionListener(this);
//        this.setPreferredSize(new Dimension(200,200));

        JButton button = new JButton("强制下线");
        button.addActionListener(this);
        this.panelbottom.setLayout(borderLayout2);
        panelbottom.add(nameBox, BorderLayout.CENTER);

        panelbottom.add(button, BorderLayout.SOUTH);
        this.add(panelbottom, BorderLayout.SOUTH);

    }
    public void freshData(){
        this.nameBox.removeAllItems();
        this.nameArea.setText("在线列表\n");
        for(int i = 0; i < this.messagePanel.socketArray.size(); ++i){
            String str = this.messagePanel.socketArray.get(i).name;
            this.nameBox.addItem(str);
            this.nameArea.append(str+"\n");
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == this.nameBox){
            this.markString = (String)this.nameBox.getSelectedItem();
        }else{
            this.messagePanel.removeClientWithName(this.markString);
        }

    }
}
