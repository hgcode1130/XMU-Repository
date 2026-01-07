package com.farsight.animatorlistenerdemo;

import android.animation.Animator;
import android.animation.ValueAnimator;
import android.annotation.SuppressLint;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

@SuppressLint("NewApi")

public class MainActivity extends AppCompatActivity implements
        Animator.AnimatorListener, ValueAnimator.AnimatorUpdateListener,
        View.OnClickListener, Animator.AnimatorPauseListener
{
    private ValueAnimator animator;
    private final String TAG = "ANIMATOR";
    private TextView txv;

    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        txv = (TextView) findViewById(R.id.txv);
        animator = ValueAnimator.ofFloat(0f, 10f);
        animator.setDuration(10000);
        //更新事件监听
        animator.addUpdateListener(this);
        //暂停事件监听
        animator.addPauseListener(this);
        //继承自Animator的动画监听
        animator.addListener(this);
        findViewById(R.id.btn_cancel).setOnClickListener(this);
        findViewById(R.id.btn_resume).setOnClickListener(this);
        findViewById(R.id.btn_pause).setOnClickListener(this);
        findViewById(R.id.btn_stop).setOnClickListener(this);
        findViewById(R.id.btn_start).setOnClickListener(this);
    }

    @Override
    protected void onStop() 
    {
        super.onStop();
        if (animator != null)
        {
            animator.end();
            animator = null;
        }
    }

    @Override
    public void onAnimationStart(Animator animation) 
    {
        if (animation == this.animator)
        {
            Log.d(TAG, "onAnimationStart");
        }
    }

    @Override
    public void onAnimationEnd(Animator animation) 
    {
        if (animation == this.animator) 
        {
            Log.d(TAG, "onAnimationEnd");
        }
    }

    @Override
    public void onAnimationCancel(Animator animation) 
    {
        if (animation == this.animator) 
        {
            Log.d(TAG, "onAnimationCancel");
        }
    }

    @Override
    public void onAnimationRepeat(Animator animation) 
    {
        if (animation == this.animator) 
        {
            Log.d(TAG, "onAnimationRepeat");
        }
    }

    @Override
    public void onAnimationUpdate(ValueAnimator animation) 
    {
        Log.d(TAG, "onAnimationUpdate: " + animation.getAnimatedValue());
        if (animation == this.animator) 
        {
            Log.d(TAG, "onAnimationUpdate: " + animation.getAnimatedValue());
        }
    }

    @Override
    public void onClick(View v) 
    {
        switch (v.getId())
        {
            case R.id.btn_cancel:
                animator.cancel();
                break;
            case R.id.btn_pause:
                if (animator.isRunning())
                {
                    animator.pause();
                    findViewById(R.id.btn_resume).setClickable(true);
                    findViewById(R.id.btn_pause).setClickable(false);
                }
                break;
            case R.id.btn_resume:
                if (animator.isPaused())
                {
                    animator.resume();
                    findViewById(R.id.btn_resume).setClickable(false);
                    findViewById(R.id.btn_pause).setClickable(true);
                }
                break;
            case R.id.btn_start:
                animator.start();
                break;
            case R.id.btn_stop:
                if (animator.isRunning() || animator.isPaused() || animator.isStarted())
                    animator.end();
                break;
        }
    }

    @Override
    public void onAnimationPause(Animator animation) 
    {
        Log.d(TAG, "onAnimationPause");
    }

    @Override
    public void onAnimationResume(Animator animation) 
    {
        Log.d(TAG, "onAnimationResume");
    }
}
