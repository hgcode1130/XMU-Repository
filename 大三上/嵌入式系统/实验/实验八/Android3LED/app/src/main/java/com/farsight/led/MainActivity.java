package com.farsight.led;

import androidx.appcompat.app.AppCompatActivity; // 导入AppCompatActivity
import android.os.Bundle; // 导入Bundle类
import android.view.View; // 导入View类
import android.widget.ImageButton; // 导入ImageButton类
import com.farsight.led.databinding.ActivityMainBinding; // 数据绑定类

public class MainActivity extends AppCompatActivity { // 主活动类
    LED led = new LED(); // 创建LED类实例，用于控制LED硬件
    boolean IsLight_1_On = false; // 标记LED 1的状态
    boolean IsLight_2_On = false; // 标记LED 2的状态
    boolean IsLight_3_On = false; // 标记LED 3的状态
    private ImageButton LedButton_1; // LED 1的按钮
    private ImageButton LedButton_2; // LED 2的按钮
    private ImageButton LedButton_3; // LED 3的按钮

    @Override
    protected void onCreate(Bundle savedInstanceState) { // onCreate生命周期方法
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main); // 设置布局

        // 初始化LED按钮并设置点击事件
        LedButton_1 = (ImageButton)findViewById(R.id.buttonOne);
        LedButton_1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 切换LED 1的状态并更新按钮图标
                if (IsLight_1_On) {
                    ((ImageButton)view).setBackground(getDrawable(R.drawable.pic_bulboff));
                    led.open(); // 打开LED设备
                    led.LedOff1(); // 关闭LED 1
                    led.close(); // 关闭LED设备
                } else {
                    ((ImageButton)view).setBackground(getDrawable(R.drawable.pic_bulbon));
                    led.open(); // 打开LED设备
                    led.LedOn1(); // 打开LED 1
                    led.close(); // 关闭LED设备
                }
                IsLight_1_On = !IsLight_1_On; // 切换状态
            }
        });

        // 初始化LED 2按钮并设置点击事件
        LedButton_2 = (ImageButton)findViewById(R.id.buttonTow); // 疑似有误，应为buttonTwo
        LedButton_2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 切换LED 2的状态并更新按钮图标
                if (IsLight_2_On) {
                    ((ImageButton)view).setBackground(getDrawable(R.drawable.pic_bulboff));
                    led.open(); // 打开LED设备
                    led.LedOff2(); // 关闭LED 2
                    led.close(); // 关闭LED设备
                } else {
                    ((ImageButton)view).setBackground(getDrawable(R.drawable.pic_bulbon));
                    led.open(); // 打开LED设备
                    led.LedOn2(); // 打开LED 2
                    led.close(); // 关闭LED设备
                }
                IsLight_2_On = !IsLight_2_On; // 切换状态
            }
        });

        // 初始化LED 3按钮并设置点击事件
        LedButton_3 = (ImageButton)findViewById(R.id.buttonThree);
        LedButton_3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 切换LED 3的状态并更新按钮图标
                if (IsLight_3_On) {
                    ((ImageButton)view).setBackground(getDrawable(R.drawable.pic_bulboff));
                    led.open(); // 打开LED设备
                    led.LedOff3(); // 关闭LED 3
                    led.close(); // 关闭LED设备
                } else {
                    ((ImageButton)view).setBackground(getDrawable(R.drawable.pic_bulbon));
                    led.open(); // 打开LED设备
                    led.LedOn3(); // 打开LED 3
                    led.close(); // 关闭LED设备
                }
                IsLight_3_On = !IsLight_3_On; // 切换状态
            }
        });
    }
}