package com.example.shixi6.DB;

import android.annotation.SuppressLint;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import com.example.shixi6.entity.Student;

import java.util.ArrayList;
import java.util.List;

public class DBAdapter {
    private static final String DB_NAME = "student.db";
    private static final String DB_TABLE = "studentinfo";
    private static final String DB_TABLE_SEQ = "sqlite_sequence";
    private static final int DB_VERSION = 1;
    public static final String KEY_ID = "id";
    public static final String KEY_NAME = "name";
    public static final String KEY_SID = "sid";
    public static final String KEY_CLASS = "classes";
    private SQLiteDatabase db;

    private final Context ctx;
    private DBOpenHelper dbOpenHelper;

    private static class DBOpenHelper extends SQLiteOpenHelper {
        public DBOpenHelper(Context ctx, String dbName, SQLiteDatabase.CursorFactory o, int dbVersion) {
            super(ctx, dbName, o, dbVersion);
        }
        private static final String DB_CREATE = "create table IF NOT EXISTS " + DB_TABLE +
                "( " + KEY_ID + " integer primary key autoincrement," +
                KEY_NAME + " text not null," +
                KEY_CLASS + " text," +
                KEY_SID +" text);";
        @Override
        public void onCreate(SQLiteDatabase db) {
            Log.i("db","onCreate");
            db.execSQL(DB_CREATE);
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            Log.i("db","onUpgrade");
//            db.execSQL("DROP TABLE IF EXISTS " + DB_TABLE);
            onCreate(db);
        }
    }

    public DBAdapter(Context ctx) {
        this.ctx = ctx;
    }

    public void open() throws SQLiteException {
        Log.i("db","open");
        dbOpenHelper = new DBOpenHelper(ctx,DB_NAME,null,DB_VERSION);

        try {
            db = dbOpenHelper.getWritableDatabase();
        }catch (SQLiteException e){
            db = dbOpenHelper.getReadableDatabase();
        }
    }

    public void close(){
        if(db != null){
            db.close();
            db = null;
        }
    }
    @SuppressLint("Range")
    public Student toStudent(Cursor cursor){
        return new Student(cursor.getInt(0),
                cursor.getString(cursor.getColumnIndex(KEY_NAME)),
                cursor.getString(cursor.getColumnIndex(KEY_CLASS)),
                cursor.getString(cursor.getColumnIndex(KEY_SID)));
    }
    public ArrayList<Student> selectAll(){
        Cursor cursor = db.query(DB_TABLE, new String[]{KEY_ID, KEY_NAME, KEY_CLASS, KEY_SID}, null, null, null, null, null);
        int resultCounts = cursor.getCount();
        if (resultCounts == 0 || !cursor.moveToFirst()){
            return null;
        }
        ArrayList<Student> stus = new ArrayList<>();
        for (int i = 0 ; i<resultCounts; i++){
            stus.add(toStudent(cursor));
            cursor.moveToNext();
        }
        return stus;
    }
    public ArrayList<Student> selectById(String id){
        Cursor cursor = db.query(DB_TABLE, new String[]{KEY_ID, KEY_NAME, KEY_CLASS, KEY_SID}, KEY_ID + "=" + id, null, null, null, null);
        int resultCounts = cursor.getCount();
        if (resultCounts == 0 || !cursor.moveToFirst()){
            return null;
        }

        ArrayList<Student> stus = new ArrayList<>();
        for (int i = 0 ; i<resultCounts; i++){
            stus.add(toStudent(cursor));
            cursor.moveToNext();
        }
        return stus;
    }
    public Boolean deleteById(String id){
        int seq = getSeq();
        setSeq(String.valueOf(seq-1));
        int res = db.delete(DB_TABLE,KEY_ID + "=" + id ,null);
        if (res==0)
            return false;

        int start = Integer.parseInt(id);

        for (int i=0 ; i<seq - start ; ++i ){
            ContentValues cv=new ContentValues();
            cv.put(KEY_ID,start + i);
            db.update(DB_TABLE,cv,KEY_ID+"=?",new String[]{String.valueOf(start+i+1)});
        }
        return true;
    }
    public Boolean updateById(String id,Student stu){
        ContentValues cv=new ContentValues();
        cv.put("name",stu.getName());
        cv.put("classes",stu.getClasses());
        cv.put("sid",stu.getSid());

        return db.update(DB_TABLE, cv, "id=?", new String[]{id}) != 0;
    }
    public Boolean insertStudent(Student stu){
        ContentValues cv = new ContentValues();
        cv.put("name",stu.getName());
        cv.put("classes",stu.getClasses());
        cv.put("sid",stu.getSid());
        return db.insert(DBAdapter.DB_TABLE,"name,classes,sid",cv)!=0;
    }
    public Boolean deleteAll(){
        setSeq("0");
        return db.delete(DB_TABLE,null,null)!=0;
    }
    @SuppressLint("Range")
    private int getSeq(){
        Cursor query = db.query(DB_TABLE_SEQ, new String[]{"seq"}, "name=?", new String[]{DB_TABLE}, null, null, null);
        query.moveToFirst();
        return query.getInt(query.getColumnIndex("seq"));
    }
    private void setSeq(String value){
        ContentValues cv=new ContentValues();
        cv.put("seq",value);
        db.update(DB_TABLE_SEQ,cv,"name=?",new String[]{DB_TABLE});
    }
}
