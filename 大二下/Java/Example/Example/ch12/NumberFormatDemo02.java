package ch12;
import java.text.* ;  
class FormatDemo{  
    public void format1(String pattern,double value){   // �˷���ר������������ֵĸ�ʽ����ʾ  
        DecimalFormat df = null ;           // ����һ��DecimalFormat��Ķ���  
        df = new DecimalFormat(pattern) ;   // ʵ�������󣬴���ģ��  
        String str = df.format(value) ;     // ��ʽ������  
        System.out.println("ʹ��" + pattern  
            + "��ʽ������" + value + "��" + str) ;  
    }  
};  public class NumberFormatDemo02{  
    public static void main(String args[]){  
        FormatDemo demo = new FormatDemo() ;    // ��ʽ���������  
        demo.format1("###,###.###",111222.34567) ;  
        demo.format1("000,000.000",11222.34567) ;  
        demo.format1("��###,###.###",11222.34567) ;  
        demo.format1("��000,000.000",11222.34567) ;  
        demo.format1("##.###%",0.345678) ;  
        demo.format1("00.###%",0.0345678) ;  
        demo.format1("###.###\u2030",0.345678) ;  
    }  
}; 