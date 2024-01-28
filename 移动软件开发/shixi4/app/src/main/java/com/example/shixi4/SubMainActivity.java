package com.example.shixi4;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class SubMainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sub);
        Button btnBack= (Button) findViewById(R.id.btn_back);
        btnBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent();
                Bundle bundle = new Bundle();

                EditText editText = (EditText)findViewById(R.id.edit2);
                String s = editText.getText().toString();
                System.out.println("editText = " + s);
                bundle.putString("user",s);

                intent.putExtras(bundle);
                setResult(MainActivity.RESULT_OK,intent);
                finish();
            }
        });
    }
}
