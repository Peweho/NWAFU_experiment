package entity;

import java.sql.Time;
import java.util.Date;

public class book {
    private String id;
    private String name;
    private String author;
    private String press;
    private Date addTime;

    public String getPress() {
        return press;
    }

    public void setPress(String press) {
        this.press = press;
    }

    public void setAddTime(Date addTime) {
        this.addTime = addTime;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public Date getAddTime() {
        return addTime;
    }

}
