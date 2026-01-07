package com.farsight.activitycommunication;

import androidx.appcompat.app.AppCompatActivity;
import android.widget.TextView;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.content.Intent;
import android.net.Uri;

public class MainActivity extends AppCompatActivity 
{
    private static final int SUBACTIVITY1 = 1;
    private static final int SUBACTIVITY2 = 2;
    TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = (TextView)findViewById(R.id.textshow);
        Button button1 = (Button) findViewById(R.id.button1);
        Button button2 = (Button) findViewById(R.id.button2);

        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, activity1.class);
                startActivityForResult(intent, SUBACTIVITY1);
            }
        });
    
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this,activity2.class);
                startActivityForResult(intent,SUBACTIVITY2);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) 
    {
        super.onActivityResult(requestCode, resultCode, data);

        switch(requestCode){
            case SUBACTIVITY1:
                if (resultCode == RESULT_OK){
                    Uri uriData = data.getData();
                    textView.setText(uriData.toString());
                }
                break;
            case SUBACTIVITY2:
                break;
        }
    }
}