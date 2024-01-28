package com.example.shixi6;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListAdapter;
import android.widget.ListView;

import com.example.shixi6.DB.DBAdapter;
import com.example.shixi6.entity.Student;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private String name;
    private String classes;
    private String sid;
    private String ID;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getText();//获取输入信息
        DBAdapter db = new DBAdapter(MainActivity.this);
        db.open();

        ArrayList<Student> stus = new ArrayList<>();//数据库中对象集合
        ArrayList<String> students = new ArrayList<>();//listView数据集

        ArrayAdapter<String> listViewAdapter = new ArrayAdapter<>(MainActivity.this, android.R.layout.simple_list_item_1,students);
        ListView listView = (ListView)findViewById(R.id.listView);
        listView.setAdapter(listViewAdapter);

        //button的监听事件
        findViewById(R.id.btn_show_all).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                students.clear();
                stus.clear();
                ArrayList<Student> data = db.selectAll();
                if (data == null)
                    return;;
                stus.addAll(data);

                for (Student student : stus) {
                    students.add(student.toString());
                }
                listViewAdapter.notifyDataSetChanged();
            }
        });

        findViewById(R.id.btn_add_data).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                getText();
                if (!db.insertStudent(new Student(name,classes,sid)))
                    return;
                students.clear();
                stus.clear();
                stus.addAll(db.selectAll());

                for (Student student : stus) {
                    students.add(student.toString());
                }
                listViewAdapter.notifyDataSetChanged();
            }
        });

        findViewById(R.id.btn_clear_all).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                students.clear();
                stus.clear();
                listViewAdapter.notifyDataSetChanged();
            }
        });

        findViewById(R.id.btn_del_all).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(!db.deleteAll())
                    return;
                students.clear();
                stus.clear();
                listViewAdapter.notifyDataSetChanged();
            }
        });

        findViewById(R.id.btn_del_by_id).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                getText();
                if( !db.deleteById(ID) )
                    return;

                students.clear();
                stus.clear();
                ArrayList<Student> data = db.selectAll();
                if (data == null)
                    return;;
                stus.addAll(data);

                for (Student student : stus) {
                    students.add(student.toString());
                }
                listViewAdapter.notifyDataSetChanged();
            }
        });

        findViewById(R.id.btn_update_id).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                getText();
                Student newStu = new Student(Integer.parseInt(ID),name, classes, sid);
                if (!db.updateById(ID,newStu))
                    return;

                for (int i=0;i<stus.size();++i) {
                    if (stus.get(i).getId().toString().equals(ID)){
                        stus.set(i,newStu);
                        students.set(i,newStu.toString());
                        break;
                    }
                }
                listViewAdapter.notifyDataSetChanged();
            }
        });

        findViewById(R.id.btn_select_id).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                getText();
                stus.clear();
                students.clear();
                ArrayList<Student> data = db.selectById(ID);
                if (data == null)
                    return;;
                stus.addAll(data);

                for (Student student : stus) {
                    students.add(student.toString());
                }

                listViewAdapter.notifyDataSetChanged();
            }
        });
    }

    private void getText(){
        this.name = ((EditText) findViewById(R.id.editText3)).getText().toString();
        this.classes = ((EditText) findViewById(R.id.editText2)).getText().toString();
        this.sid = ((EditText) findViewById(R.id.editText1)).getText().toString();
        this.ID= ((EditText) findViewById(R.id.editText4)).getText().toString();
    }
}