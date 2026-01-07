package com.farsight.temperature;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.os.Handler;
import android.os.Message;

public class MainActivity extends AppCompatActivity {
    TextView val; // 用于显示ADC值的TextView
    Button start_btn; // 启动按钮
    Button close_btn; // 关闭按钮
    Boolean sensorflag = false; // 用于判断传感器是否已打开
    int data = 0; // ADC数据
    adc adcDevice = new adc(); // adc类实例，用于与本地驱动交互

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 初始化界面元素
        val = findViewById(R.id.text);
        start_btn = findViewById(R.id.start_btn);
        close_btn = findViewById(R.id.close_btn);

        // 启动按钮点击事件
        start_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 如果传感器没有打开，则启动
                if (!sensorflag) {
                    sensorflag = true;
                    adcDevice.open(); // 打开ADC设备
                    new TimeThread().start(); // 启动定时线程
                }
            }
        });

        // 关闭按钮点击事件
        close_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 如果传感器已经打开，则关闭
                if (sensorflag) {
                    adcDevice.close(); // 关闭ADC设备
                    sensorflag = false; // 更新标志位
                }
            }
        });
    }

    // 定时读取ADC数据的线程
    public class TimeThread extends Thread {
        @Override
        public void run() {
            super.run();
            do {
                if (sensorflag) {
                    try {
                        Thread.sleep(200); // 每200毫秒读取一次
                        Message msg = new Message();
                        msg.what = 1; // 读取成功标志
                        handler.sendMessage(msg); // 发送消息更新UI
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } else {
                    try {
                        Thread.sleep(200); // 每200毫秒循环
                        Message msg = new Message();
                        msg.what = 2; // ADC设备未打开标志
                        handler.sendMessage(msg); // 发送消息提示
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            } while (true);
        }
    }

    // 处理线程发送的消息，更新UI
    private Handler handler = new Handler(new Handler.Callback() {
        @Override
        public boolean handleMessage(Message msg) {
            switch (msg.what) {
                case 1:
                    // 更新ADC值显示
                    data = adcDevice.read(); // 读取ADC数据
                    val.setText(String.format("ADC Value: %d", data));
                    break;
                case 2:
                    // 提示ADC设备未打开
                    val.setText("ADC设备未打开");
                    break;
            }
            return false;
        }
    });
}
