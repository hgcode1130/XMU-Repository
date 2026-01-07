package com.farsight.buzzer;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener 
{
    Buzzer buzzer = new Buzzer();
    private Button start;
    private Button stop;

    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        start = (Button) findViewById(R.id.button1);
        stop = (Button) findViewById(R.id.button2);
        start.setOnClickListener(this);
        stop.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) 
    {
        switch (view.getId()) 
        {
            case R.id.button1:
                if(buzzer.open() == -1)
                {
                    Toast.makeText(this, "设备打开失败！", Toast.LENGTH_SHORT).show();
                    return;
                }
                buzzer.BuzzerOn();
                buzzer.close();
                break;

            case R.id.button2:
                if(buzzer.open() == -1)
                {
                    Toast.makeText(this, "设备打开失败！", Toast.LENGTH_SHORT).show();
                    return;
                }
                buzzer.BuzzerOff();
                buzzer.close();
                break;
        }
    }
}

