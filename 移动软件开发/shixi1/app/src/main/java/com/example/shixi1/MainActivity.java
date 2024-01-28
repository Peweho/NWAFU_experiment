package com.example.shixi1;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i("Create","CreateUse");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i("Destroy","DestroyUse");
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
        Log.i("SaveInstanceState","SaveInstanceStateUse");
    }

    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        Log.i("RestoreInstanceState","RestoreInstanceStateUse");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.i("Restart","RestartUse");
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.i("Start","StartUse");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.i("Stop","StopUse");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.i("Pause","PauseUse");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.i("Resume","ResumeUse");
    }
}