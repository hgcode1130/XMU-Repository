package com.farsight.activitycommunication;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.view.View;

public class activity2 extends Activity 
{
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity2);
        Button btnReturn = (Button)findViewById(R.id.button1);

        btnReturn.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view){
                setResult(RESULT_CANCELED, null);
                finish();
            }
        });
    }
}
