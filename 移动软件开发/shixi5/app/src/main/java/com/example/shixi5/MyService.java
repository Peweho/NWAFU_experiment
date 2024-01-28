package com.example.shixi5;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.Nullable;

public class MyService extends Service {

    Thread threadDate;
    private int min;
    private int second;
    private int ms;
    private final IBinder binder = new LocalBinder();
    public class LocalBinder extends Binder{
        public MyService getService(){
            return MyService.this;
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        return binder;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Log.d("ServiceOnCreate","start");
        Runnable date = new Runnable(){
            @Override
            public void run() {
                try {
                    Thread.sleep(1000);
                    while(true){
                        ms += 1;
                        if (ms >= 60){
                            ms = 0;
                            second += 1;
                            if (second >= 60){
                                second = 0;
                                min += 1;
                            }
                        }
                        MainActivity.updateGui(min,second,ms);
                        Thread.sleep(1000);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        this.threadDate  = new Thread(null, date, "thread1");
        Log.d("ServiceOnCreate","end");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d("ServiceOnStartCommand","start");
        if (!threadDate.isAlive()){
            Bundle extras = intent.getExtras();
            this.min = extras.getInt("min");
            this.second = extras.getInt("second");
            this.ms = extras.getInt("ms");
            threadDate.start();
        }
        Log.d("ServiceOnStartCommand","end");
        return START_STICKY;
        //        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.d("ServiceOnDestroy","start");
        threadDate.interrupt();
        Log.d("ServiceOnDestroy","end");
    }
}