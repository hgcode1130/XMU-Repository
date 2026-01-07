package com.farsight.actionbardemo;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.ActionBar;

public class ActionBarDemo extends AppCompatActivity 
{
    //    private final String TAG = ActionBarDemo.class.getSimpleName();
    private int count = 10;
    private ActionBarHideAndShow actionBarHideAndShow;
    private final int HIDE = 1;
    private final int SHOW = 2;
    private int old = HIDE;
    private ActionBar actionBar;
    private boolean threadOn = false;

    @SuppressLint("HandlerLeak")
    private Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch (msg.what) {
                case HIDE:
                    if (actionBar != null) {
                        actionBar.hide();
                    }
                    break;
                case SHOW:
                    if (actionBar != null) {
                        actionBar.show();
                    }
                    break;
                default:
                    break;
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //正常情况下使用AppcompatActivity。
        //导入android.support.v7.app.ActionBar。
        //并使用getSupportActionBar()来获取actionBar实例。
        actionBar = getSupportActionBar();

        if (actionBar != null) {
            actionBar.setTitle("华清远见");
            actionBar.hide();
        }
        actionBarHideAndShow = new ActionBarHideAndShow();
        threadOn = true;
        actionBarHideAndShow.start();
    }

    @Override
    protected void onDestroy() 
    {
        super.onDestroy();
        threadOn = false;
        actionBarHideAndShow = null;
    }

    //循环显示和隐藏ActionBar
    private class ActionBarHideAndShow extends Thread 
    {
        @Override
        public void run() {
            super.run();
            while (threadOn) {
                try {
                    sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                count--;
                if (count == 0) {
                    count = 10;
                    old = old == HIDE ? SHOW : HIDE;
                    handler.sendEmptyMessage(old);
                }
            }
        }
    }
}