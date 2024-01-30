package com.example.shixi3;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.PopupMenu;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_linerlayout_main);
        String sep = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
        EditText et1 = (EditText)findViewById(R.id.editText1);
        EditText et2 = (EditText)findViewById(R.id.editText2);
        EditText et3 = (EditText)findViewById(R.id.editText3);
        Button bt1 = (Button)findViewById(R.id.button);
        //设置数据list
        ArrayList<String> data = new ArrayList<>();
        ArrayAdapter<String> listViewAdapter = new ArrayAdapter<>(MainActivity.this, android.R.layout.simple_list_item_1, data);
        View listView = findViewById(R.id.listView);
        setListView((ListView) listView,sep,listViewAdapter,data);
        //添加数据
        bt1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                data.add(et1.getText().toString()+sep+et2.getText().toString()+sep+et3.getText().toString());
                listViewAdapter.notifyDataSetChanged();
            }
        });
    }

    //设置listview
    private void setListView(ListView listView,String sep,ArrayAdapter<String> listViewAdapter,ArrayList<String> data){
        data.add("班级"+sep+"学号"+sep+"姓名");
        listView.setAdapter(listViewAdapter);
        listView.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, View view, int i, long l) {
                //设置弹出菜单
                PopupMenu popupMenu = new PopupMenu(MainActivity.this, view);
                MenuInflater menuInflater = popupMenu.getMenuInflater();
                menuInflater.inflate(R.menu.menu,popupMenu.getMenu());
                popupMenu.show();

                popupMenu.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
                    @Override
                    public boolean onMenuItemClick(MenuItem menuItem) {
                        if (menuItem.getItemId() == R.id.it2){
                            data.remove(i);
                            listViewAdapter.notifyDataSetChanged();
                        }
                        return false;
                    }
                });
                return false;
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater menuInflater = getMenuInflater();
        menuInflater.inflate(R.menu.menu,menu);
        return true;
    }
}