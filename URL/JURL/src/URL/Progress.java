package URL;


import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.regex.*;
import java.lang.String;

import javax.swing.*;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;

public class Progress extends JFrame implements ActionListener{
	//初始化
	private JTextPane show= new JTextPane();
	private Style style = null;
	private Style style2 = null;
	private JTextField urlField = null;
	private JButton seed = null;
	private JButton but = null;
	private ArrayList<String> arrayList = null;
	private ArrayList list = null;
	private ArrayList all = new ArrayList();
	private ArrayList allUrl = null;
	static int k=1;
	//函数调用
	public Progress(){
		styleIni();//文本样式设置
		Ini();//窗口样式设置
		InitialText();
		InitialUrl();
	}
	//爬取的文本样式设置
	public void styleIni(){
		/* 为组件编辑器关联的模型添加了一个样式normal，作为最基本的一个样式，其他样式在此基础上进行修改 */
		Style style = show.getStyledDocument().addStyle(null, null);// 获取组件空样式，返回一个空样式
		StyleConstants.setFontFamily(style, "楷体");// 为style样式设置字体属性
		StyleConstants.setFontSize(style, 18);// 为style样式设置字体大小
		Style normal = show.addStyle("normal", style);// 将style样式添加到组件，并命名为normal，返回一个样式由Style
		/*添加两个与normal一样的样式，命名为style1，style2*/
		style = show.addStyle("style1", normal);
		style2 = show.addStyle("style2", normal);
		/*修改style1和style2的颜色*/
		StyleConstants.setForeground(style, Color.BLACK);// style1为黑色，是爬取的文本
		StyleConstants.setForeground(style2, Color.RED);// style2为红色，对敏感词标红高亮
	}
	//窗口及控件样式设置
	public void Ini(){
		this.setBounds(200, 150, 640, 560);
		this.setLayout(null);
		//网址输入框
		urlField = new JTextField();
		urlField.setBounds(10,30,445,30);
		this.add(urlField);
		//文本提示1
		JLabel lb=new JLabel("请输入您要爬取的网址:");
		add(lb);
		lb.setBounds(13,7,150,30);
		//爬虫确定按钮
		seed = new JButton("确定");
		seed.addActionListener(this);
		seed.setBounds(526, 30, 60, 30);
		this.add(seed);
		//文本提示2
		JLabel lb2=new JLabel("！！是否需要解析'其他网址'文件中保存的URL，并提示敏感词数量？");
		add(lb2);
		lb2.setBounds(13,485,500,30);
		//文本提示3
		JLabel lb3=new JLabel("以下是爬取出的结果：");
		add(lb3);
		lb3.setBounds(13,55,160,30);
		//解析确定按钮
		but = new JButton("确定");
		but.addActionListener(this);
		but.setBounds(530,487,60,30);
		this.add(but);
		// 定义滚动面板，放历史面板，以实现滚动条（有需要的时候显示）和换行
		this.show.setEditable(false);
		JScrollPane js_show = new JScrollPane(show,JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
				JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		// 爬取文本显示框的位置和大小
		js_show.setBounds(13, 90, 605, 380);
		// 添加到窗体
		this.add(js_show);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}

	//按两个确定键分别对应的操作
	public void actionPerformed(ActionEvent e) {
		//如果按钮按了"爬虫确定按钮"
		if(e.getSource()==seed){
			show.setText("");//初始化文本框内容
			Webresource url = new Webresource(urlField.getText(), "utf-8");//获得输入的网址，创建Webresource类对象url
			String htmls =url.getPageSource();//调用url对象的getPageSource()函数，获取网页资源
			System.out.println(htmls);
			try{
				for(int i =0;i<arrayList.size();i++){
					filterInfo(arrayList.get(i).toString(),htmls);//调用filterInfo进行网页信息筛选
				}
				//调用compare函数，获得爬取的文本内容总长度
				compare();
				System.out.println(all.size());
				int flag =0;//通过设置标识位来判断当前元素是否访问过
				//循环访问每个字符，找到敏感词进行标红，其他文本内容标黑（通过坐标定位字符串）
				for(int i=0;i<all.size();i++){
					if(((weizhi)all.get(i)).getX()!=0 && flag==0){
						normal(htmls.substring(0, ((weizhi)all.get(i)).getX()));
						flag=1;
					}
					highLight(htmls.substring(((weizhi)all.get(i)).getX(),(((weizhi)all.get(i)).getX()+((weizhi)all.get(i)).getString().length())));
					normal(htmls.substring((((weizhi)all.get(i)).getX()+((weizhi)all.get(i)).getString().length()),((weizhi)all.get(i+1)).getX()));
				}
				if(all.size()==0){
					normal(htmls);
				}
			}catch (Exception E) {
			}
		}
		//如果按了"解析确定按钮"
		if(e.getSource()==but){
			Readfile();
			InitialUrl();
			getAll();
		}
	}

	//读取敏感词库
	public void InitialText(){
		File file = new File("/Users/liujie/Desktop/URL/敏感字词库.txt");
		StringBuffer contents = new StringBuffer();
		BufferedReader reader = null;//通过缓存流读取字符
		arrayList = new ArrayList<String>();
		try {
			reader = new BufferedReader(new FileReader(file));
			String text = null;
			// 重复读取，直到所有元素都被访问
			while ((text = reader.readLine()) != null) {
				if(!arrayList.contains(text)){
					arrayList.add(text);
				}
			}
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		catch (IOException e) {
			e.printStackTrace();
		}
		finally {
			try {
				if (reader != null) {
					reader.close();
				}
			}
			catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	//读取保存有其他网址的文件，并显示有这些网址
	public void Readfile(){
		int b;
		byte tom[]=new byte[25];
		try {File f=new File("/Users/liujie/Desktop/URL/其他网址.txt");
			FileInputStream in =new FileInputStream(f);
			while((b=in.read(tom,0,25))!=-1)
			{String s=new String (tom,0,b);
				System.out.print(s);
			}
			in.close();
		}
		catch(IOException e)
		{System.out.println("File read Error"+e);
		}
	}


	//读取文件里的网址，并逐条进行解析
	public void InitialUrl(){
		File file = new File("/Users/liujie/Desktop/URL/其他网址.txt");
		StringBuffer contents = new StringBuffer();
		BufferedReader reader = null;
		allUrl = new ArrayList<String>();
		try {
			reader = new BufferedReader(new FileReader(file));
			String text = null;
			//重复读取直到结束
			while ((text = reader.readLine()) != null) {
				if(!allUrl.contains(text)){
					allUrl.add(text);
				}
			}
		}
		catch (FileNotFoundException e) {//捕获异常
			e.printStackTrace();
		}
		catch (IOException e) {
			e.printStackTrace();
		}
		finally {
			try {
				if (reader != null) {
					reader.close();
				}
			}
			catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	//利用输出流将内容存入文件中
	public void writeFile(String name,String result){
		FileOutputStream fos = null;//输出流
		BufferedWriter bw = null;
		try {
			File file = new File(name);
			fos = new FileOutputStream(file);
			bw = new BufferedWriter(new OutputStreamWriter(fos));
			bw.write(result);
		}
		catch (FileNotFoundException fnfe) {
			fnfe.printStackTrace();
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
		finally {
			try {
				if (bw != null)
					bw.close();
				if (fos != null)
					fos.close();
			}
			catch (IOException ie) {
			}
		}
	}

	//对敏感词信息标红，实现敏感词高亮
	public void highLight(String str){
		try{

			this.show.getStyledDocument().insertString(this.show.getStyledDocument().getLength(), str, style2);
		}catch(Exception E){

		}
	}
	//对爬取的文本颜色设置为黑色
	public void normal(String str){
		try {
			this.show.getStyledDocument().insertString(this.show.getStyledDocument().getLength(), str, style);
		} catch (Exception e) {
		}
	}

   //通过匹配字符串的方式实现过滤信息，将符合正则标准的信息计入list
	public void filterInfo(String regEx,String str)
	{
		all = new ArrayList();//动态数组
		String copy = str;
		list = new ArrayList();
		Pattern pattern = Pattern.compile(regEx);
		int begin =0;
		Matcher matcher = pattern.matcher(str);// 一个Matcher对象是一个状态机器，依据pattern匹配模式对字符串展开匹配检查。
		boolean matches = matcher.matches();//布尔变量，true or false，即匹配是否正确
		while(matcher.find()){
			begin=matcher.start();
			weizhi p=new weizhi(begin, matcher.end(),regEx);
			list.add(p);
		}
		if(list.size()==0){
			System.out.println(regEx+"\n");//若无信息则换行
			return;
		}else{
			all.addAll(list);
			System.out.println("成功解析第"+k+"个网址！");
			k++;//通过全局变量K，实现网址的逐个解析
		}
	}

	//对于文件中网址的解析分别保存在不同想新生成的txt文档里
	public void getAll(){

		for(int i=0;i<allUrl.size();i++){
			Webresource url = new Webresource((String)allUrl.get(i), "UTF-8");
			urlField.setText("");
			String htmls =url.getPageSource();

			writeFile("/Users/liujie/Desktop/URL/htmls-"+i+".txt",htmls);
			try{

				for(int j =0;j<arrayList.size();j++){
					filterInfo(arrayList.get(j).toString(),htmls);
				}
				compare();

				String result ="";

				for(int k =0;k<all.size();k++){
					String newString =((weizhi)all.get(k)).getString();

					int count=1;
					for(int j=k+1;j<all.size();j++) {
						if (((weizhi) all.get(j)).getString().equals(newString)) {
							count++;
							all.remove(j);
							j = j - 1;
						}
					}
					int m=0;
					m=i+1;
					result += ("第"+m+"个网址的敏感词 '"+newString+"'出现了"+count+"次\n");
					all.remove(k);
				}
				writeFile("/Users/liujie/Desktop/URL/htmls-words"+i+".txt", result);
				JOptionPane.showMessageDialog(this, "result:"+result);
			}catch (Exception E) {

			}
		}

	}

	//对两个元素的位置进行对比
	public void compare() {
		Comparator<weizhi> comparator = new Comparator<weizhi>() {
			public int compare(weizhi o1, weizhi o2) {
				if (o1.getX() > o2.getX()) {
					return 1;
				} else if(o1.getX() < o2.getX()){
					return -1;
				}else{
					return 0;
				}
			}
		};
		Collections.sort(all,comparator);
	}
	public static void main(String []args){
		Progress myComponent = new Progress();
	}
}

//获得某个字符的位置，与该位置的字符串匹配（即定位某个字符串）
class weizhi{
	private int x;
	private int y;
	private String str;
	public weizhi(int a,int b,String st){
		x=a;
		y=b;
		str =st;
	}
	public int getX(){
		return x;
	}
	public String getString(){
		return str;
	}
}





