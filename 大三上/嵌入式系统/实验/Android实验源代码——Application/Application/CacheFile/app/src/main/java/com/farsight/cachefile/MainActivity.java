package com.farsight.cachefile;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import java.io.File;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity 
{
    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        File f = this.getCacheDir();
        String path = f.getParent() + java.io.File.separator + f.getName();
        TextView tv = (TextView) findViewById(R.id.textView1);
        tv.setText(path);
    }
}