package com.example.shixi5;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private static final Handler handler = new Handler();
    Intent intent;
    MyService mService;
    boolean mBound = false;
    static TextView minute;
    static TextView sec;
    static TextView msTv;
    static String minText;
    static String secondText;
    static String msText;
    private final ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName className, IBinder service) {
            Log.d("MianOnServiceConnected","start");
            MyService.LocalBinder binder = (MyService.LocalBinder) service;
            mService = binder.getService();
            Log.d("MianOnServiceConnected","end");
        }
        @Override
        public void onServiceDisconnected(ComponentName arg0) {
            mBound = false;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d("MianOnCreate","start");
        setContentView(R.layout.activity_main);
        intent = new Intent(MainActivity.this, MyService.class);
        minute = (TextView) findViewById(R.id.minute);
        sec = (TextView) findViewById(R.id.second);
        msTv = (TextView) findViewById(R.id.last);

        minText = new String("");
        secondText = new String("");
        msText = new String("");
        Log.d("MianOnCreate","end");
    }

//    @Override
//    protected void onStart() {
//        super.onStart();
//        Log.d("MianOnStart","start");
//
//        bindService(intent, connection, Context.BIND_AUTO_CREATE);
//        Log.d("MianOnStart","end");
//    }
//
//    @Override
//    protected void onStop() {
//        super.onStop();
//        Log.d("MianOnStop","start");
//        unbindService(connection);
//        mBound = false;
//        Log.d("MianOnStop","end");
//    }

    public static void updateGui(int min, int second, int ms){
        minText = dealDate(min);
        secondText = dealDate(second);
        msText = dealDate(ms);

        handler.post(new Runnable(){
            @Override
            public void run() {
                minute.setText(minText);
                sec.setText(secondText);
                msTv.setText(msText);
                minText = "";
                secondText = "";
                msText = "";
            }
        });
    }
    public static String dealDate(int text) {
        if (text < 10){
            return "0".concat(String.valueOf(text));
        } else {
            return String.valueOf(text);
        }
    }

    public void clickClear(View view) {
        Log.d("MianClickClear","start");
        if (mBound){
            mBound = false;
            unbindService(connection);
            stopService(intent);
        }
        minute.setText("00");
        sec.setText("00");
        msTv.setText("00");
        Log.d("MianClickClear","end");
    }

    public void clickPause(View view) {
        if (mBound){
            Log.d("MianClickPause","start");
            mBound = false;
            unbindService(connection);
            stopService(intent);
        }
        Log.d("MianClickPause","end");
    }

    public void clickStart(View view) {

        if (!mBound) {
            Log.d("MianClickStart","start");
            mBound = true;
            addBunle();
            bindService(intent, connection, Context.BIND_AUTO_CREATE);
            startService(intent);
        }
        Log.d("MianClickStart","end");
    }

    public void addBunle(){
        int min = Integer.parseInt(minute.getText().toString());
        int second = Integer.parseInt(sec.getText().toString());
        int ms = Integer.parseInt(msTv.getText().toString());

        Bundle bundle = new Bundle();
        bundle.putInt("min",min);
        bundle.putInt("second",second);
        bundle.putInt("ms",ms);

        intent.putExtras(bundle);
    }
}
