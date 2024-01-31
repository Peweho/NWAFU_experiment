package service;

import entity.book;

import java.sql.*;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.SimpleTimeZone;

import static Constants.Constants.*;

public class BookService {
    Connection con;
    public BookService(Connection con) {
        this.con = con;
    }
    public book findBookById(String id) throws SQLException {
        PreparedStatement pstat = con.prepareStatement(FIND_BOOK_BY_ID );
        pstat.setString(1,id);
        ResultSet res = pstat.executeQuery();
        if(res.next())
           return recToBook(res);
        return null;
    }
    public void insertBook(String bookName,String author,String press) throws SQLException {
        PreparedStatement pstat = con.prepareStatement(INSERT_BOOK);
        pstat.setString(1,bookName);
        pstat.setString(2,author);
        pstat.setString(3,press);
        pstat.setDate(4,Date.valueOf(LocalDate.now()));
        pstat.execute();
    }

    public void updatetBook(String id,String name,String author,String press) throws SQLException {
        PreparedStatement pstat = con.prepareStatement(UPDATE_BOOK);
        pstat.setString(1,name);
        pstat.setString(2,author);
        pstat.setString(3,press);
        pstat.setString(4,id);
        pstat.execute();
    }

    public void deleteBook(String id) throws SQLException {
        PreparedStatement pstat = con.prepareStatement(DELETE_BOOK);
        pstat.setString(1,id);
        pstat.execute();
    }

    public List<book> list() throws SQLException {
        PreparedStatement pstat = con.prepareStatement(FIND_BOOK_ALL);
        ResultSet res = pstat.executeQuery();
        List<book> books = new ArrayList<>();
        while (res.next()){
            books.add(recToBook(res));
        }
        return books;
    }
    private book recToBook(ResultSet res) throws SQLException {
        book b = new book();
        b.setName(res.getString(BOOK_NAME));
        b.setId(res.getString(BOOK_ID));
        b.setAuthor(res.getString(BOOK_AUTHOR));
        b.setPress(res.getString(BOOK_PRESS));
        b.setAddTime(res.getDate(BOOK_ADD_TIME));
        System.out.println();
        return b;
    }

}
