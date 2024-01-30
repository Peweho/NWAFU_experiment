package com.example.shixi2;

import static utils.Constants.CLEAR_STATE;
import static utils.Constants.ERROR_STATE;
import static utils.Constants.FIRST_NUM_STATE;
import static utils.Constants.SECOND_NUM_STATE;
import static utils.Constants.SHOW_RESULT_STATE;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import java.lang.ref.SoftReference;
import moudle.PutChar;
import utils.Constants.*;

public class MainActivity extends AppCompatActivity {
    PutChar putChar = new PutChar();
    String state = CLEAR_STATE;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE) {
            setContentView(R.layout.activity_mian_hor);
        } else if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
            setContentView(R.layout.activity_main);
        }
    }

    public void clickBUtton(View v){
        //获取界面元素
        TextView firstText = (TextView)findViewById(R.id.firstNum);
        TextView secondText = (TextView)findViewById(R.id.secondNum);
        TextView operationText = (TextView)findViewById(R.id.operationText);
        String btnText = (String) ((Button) v).getText();
        //判断输入后的下一次状态
        String nextState = putChar.nextState(state,btnText,operationText);

        //根据下次的状态执行相应的处理模型
        switch (nextState){
            case CLEAR_STATE: putChar.clearText(firstText,secondText,operationText);break;
            case FIRST_NUM_STATE: putChar.putNum(firstText,btnText);break;
            case SECOND_NUM_STATE:
                if (state.equals(SECOND_NUM_STATE)){
                    putChar.putNum(secondText,btnText);
                }break;
            case SHOW_RESULT_STATE: putChar.showResult(firstText,secondText,operationText);break;
            case ERROR_STATE: putChar.errorInformation(firstText,secondText,operationText);break;
        }
        state = nextState;
    }
}