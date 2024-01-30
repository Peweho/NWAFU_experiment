package com.example.shixi6.entity;

import android.database.Cursor;

import androidx.annotation.NonNull;

public class Student {
    Integer id;
    String name;
    String classes;
    String sid;

    public Student(Integer id,String name, String classes, String sid) {
        this.id = id;
        this.name = name;
        this.classes = classes;
        this.sid = sid;
    }

    public Student(String name, String classes, String sid) {
        this.name = name;
        this.classes = classes;
        this.sid = sid;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getClasses() {
        return classes;
    }

    public void setClasses(String classes) {
        this.classes = classes;
    }

    public String getSid() {
        return sid;
    }

    public void setSid(String sid) {
        this.sid = sid;
    }

    @NonNull
    @Override
    public String toString() {
        return "id=" + id +
                ", name='" + name + '\'' +
                ", classes='" + classes + '\'' +
                ", sid='" + sid ;
    }
}
