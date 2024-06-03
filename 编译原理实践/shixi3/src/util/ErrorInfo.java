package util;

import java.util.ArrayList;

public class ErrorInfo {
    String info;
    int line;
    int column;

    String variable;

    public static ArrayList<String> error = new ArrayList<>();

    public static final String variable_duplicate_declaration = " duplicate declaration";
    public static final String variable_not_define = " not define";
    public static final String dont_shoule_appear = " don`t shoule appear this";

    public ErrorInfo(String info, int line, int column,String variable) {
        this.info = info;
        this.line = line;
        this.column = column;
        this.variable = variable;
        error.add("in " + line + " line,in " + column + " column," + "the variable " + variable + info);
    }

    public static void printErrorInfo(){
        for (String e:error) {
            System.out.println(e);
        }
    }
}
