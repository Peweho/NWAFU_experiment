package moudle;

import static utils.Constants.ADD;
import static utils.Constants.CLEAR;
import static utils.Constants.CLEAR_STATE;
import static utils.Constants.DIV;
import static utils.Constants.EQUAL;
import static utils.Constants.ERROR;
import static utils.Constants.ERROR_STATE;
import static utils.Constants.FIRST_NUM_STATE;
import static utils.Constants.MUT;
import static utils.Constants.PER_CENT;
import static utils.Constants.POIMT;
import static utils.Constants.SECOND_NUM_STATE;
import static utils.Constants.SHOW_RESULT_STATE;
import static utils.Constants.SQRT;
import static utils.Constants.SUB;

import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import utils.Constants.*;
import com.example.shixi2.R;

public class PutChar {
    //判断下一个状态
    public String nextState(String state,String btnText,TextView operationText){
        switch (btnText) {
            case ADD:
            case SUB:
            case MUT:
            case DIV:
                //如果是双目运算符
                if (state.equals(FIRST_NUM_STATE)) {
                    operationText.setText(btnText);
                    return SECOND_NUM_STATE;
                } else {
                    return ERROR_STATE;
                }
            case SQRT:
            case PER_CENT:
                //如果是单目运算符
                if (state.equals(FIRST_NUM_STATE) || state.equals(SECOND_NUM_STATE)) {
                    operationText.setText(btnText);
                    return SHOW_RESULT_STATE;
                } else {
                    return ERROR_STATE;
                }
            case EQUAL:
                if (state.equals(SECOND_NUM_STATE)) {
                    return SHOW_RESULT_STATE;
                } else {
                    return ERROR_STATE;
                }
            case ERROR:
            case CLEAR:
                return CLEAR_STATE;
            default:
                if (state.equals(CLEAR_STATE))
                    return FIRST_NUM_STATE;
                else if (state.equals(SHOW_RESULT_STATE))
                    return CLEAR_STATE;
                else
                    return state;
        }
    }
    //执行清零状态
    public void clearText(TextView firstText,TextView secondText,TextView operationText) {
        firstText.setText("");
        secondText.setText("");
        operationText.setText("");
    }
    //添加数字
    public void putNum(TextView text,String btnText){
        String result = (String) text.getText();
        text.setText(result.concat(btnText));
    }
    //计算结果
    public void showResult(TextView firstText,TextView secondText,TextView operationText){
        String operation = (String)operationText.getText();
        double firstNum = Double.parseDouble(((String) firstText.getText()));
        double result = 0;

        if (operation.equals(PER_CENT) || operation.equals(SQRT)){
            switch (operation){
                case PER_CENT:result = firstNum * 0.01;break;
                case SQRT: result = Math.sqrt(firstNum);break;
            }
        }else{
            double secondNum = Double.parseDouble(((String) secondText.getText()));
            switch (operation){
                case ADD: result = firstNum + secondNum;break;
                case SUB: result = firstNum - secondNum;break;
                case MUT: result = firstNum * secondNum;break;
                case DIV: result = firstNum / secondNum;break;
            }
        }
        clearText(firstText,secondText,operationText);
        firstText.setText(String.valueOf(result));
    }
    //错误处理
    public void errorInformation(TextView firstText,TextView secondText,TextView operationText){
        clearText(firstText,secondText,operationText);
        firstText.setText(ERROR);
    }
}
