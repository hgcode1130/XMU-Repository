package com.farsight.activitycommunication;

import android.app.Activity;
import android.widget.EditText;
import android.os.Bundle;
import android.widget.Button;
import android.view.View;
import android.net.Uri;
import android.content.Intent;

public class activity1 extends Activity 
{
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity1);
        final EditText editText = (EditText)findViewById(R.id.text1);
        Button btnOK = (Button)findViewById(R.id.button1);
        Button btnCancel = (Button)findViewById(R.id.button2);

        btnOK.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view){
                String uriString = editText.getText().toString();
                Uri data = Uri.parse(uriString);
                Intent result = new Intent(null, data);
                setResult(RESULT_OK, result);
                finish();
            }
        });

        btnCancel.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view){
                setResult(RESULT_CANCELED, null);
                finish();
            }
        });
    }
}
