package ch15;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import javax.swing.filechooser.FileFilter;
import java.util.*;
import java.util.zip.*;
public class ZipTest1 {
    public static void main(String[]args){
    ZipTestFrame  myframe=new ZipTestFrame();
    myframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    myframe.show();
    }
}
class ZipTestFrame extends JFrame{
    private static final int DEFAULT_WIDTH=300;
    private static final int DEFAULT_HEIGHT=400;
    private String zipname;
    private JComboBox fileCombo;
    private JTextArea   fileText;
    public ZipTestFrame(){
        setTitle("zip-test-phenix");
        setSize(this.DEFAULT_WIDTH,this.DEFAULT_HEIGHT);
        //添加菜单
        JMenuBar  menubar=new JMenuBar();
        JMenu   menu=new JMenu("File");
        
        
        JMenuItem openItem=new JMenuItem("open");
        menu.add(openItem);
        openItem.addActionListener(new OpenAction());
        
        JMenuItem  exitItem=new JMenuItem("Exit");
        menu.add(exitItem);
        exitItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent  event){
                System.exit(0);
            }
        });
        menubar.add(menu);
        setJMenuBar(menubar);
        
        //添加文本区和组合框
        fileText=new JTextArea();
        fileCombo=new JComboBox();
        fileCombo.addActionListener(new 
        ActionListener(){
            public void actionPerformed(ActionEvent event){
                loadZipFile((String)fileCombo.getSelectedItem());
                System.out.println("***********输出****************");
                System.out.println((String)fileCombo.getSelectedItem());
                System.out.println("***********************     ***********");
            }
        }       
        );
        Container contentPane =getContentPane();
        contentPane.add(fileCombo,BorderLayout.SOUTH);
        contentPane.add(fileText,BorderLayout.CENTER);
        
    }
//最重要的是这个函数，看他是如何读取压缩文件当中的数据

    public void loadZipFile(String name){
        try{ 
            ZipInputStream  zin=new ZipInputStream(new FileInputStream(zipname));
            ZipEntry  entry;
            fileText.setText("");
            
            while((entry=zin.getNextEntry())!=null){
                if(entry.getName().equals(name)){
                    BufferedReader  in=new BufferedReader(new InputStreamReader(zin));
                    String line;
                    while((line=in.readLine())!=null){
                        fileText.append(line);
                        fileText.append("\n");
                    }
                }
                zin.closeEntry();
            }
            zin.close();
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }
    private class OpenAction implements ActionListener{
        public void actionPerformed(ActionEvent event){
            JFileChooser chooser=new JFileChooser();
            chooser.setCurrentDirectory(new File("."));
            ExtensionFileFilter filter=new ExtensionFileFilter();
            filter.addExtension(".zip");
            filter.addExtension(".rar");
            filter.addExtension(".jar");
            filter.setDescription("zip archives");
            chooser.setFileFilter(filter);
            int r=chooser.showOpenDialog(ZipTestFrame.this);
            if(r==JFileChooser.APPROVE_OPTION){
                zipname=chooser.getSelectedFile().getPath();
                System.out.println(zipname);
                scanZipFile();
            }
        }
    }
    public void scanZipFile(){
        fileCombo.removeAllItems();
        try{
            ZipInputStream zin=new ZipInputStream(new FileInputStream(zipname)); 
            ZipEntry  entry;
            System.out.println("**********************************");
            while((entry=zin.getNextEntry())!=null){
                fileCombo.addItem(entry.getName());
                zin.closeEntry();
                System.out.println(entry.getName());
            }
            System.out.println("**********************************");
            zin.close();
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }
}
class ExtensionFileFilter extends FileFilter{
    private String description;
    private ArrayList extensions=new ArrayList();
    public void addExtension(String extension){
        if(!extension.startsWith(".")){
            extension="."+extension;
        }
        extensions.add(extension.toLowerCase());
    }
    public void setDescription(String aDescription){
        this.description=aDescription;
        }
    public String getDescription(){
        return description;
    }
    public boolean accept(File f){
        if(f.isDirectory()){return true;}
        String name=f.getName().toLowerCase();
        for(int i=0;i<this.extensions.size();i++){
            if(name.endsWith((String)extensions.get(i)))
                    {
                    return true;
            }
        }
        return false;
    }
}
//仅支持jar文件和zip文件，不能支持rar文件