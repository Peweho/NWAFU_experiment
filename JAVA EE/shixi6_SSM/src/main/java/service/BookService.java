package service;

import entity.book;
import mapper.BookMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.servlet.http.HttpServletRequest;
import java.sql.*;
import java.time.LocalDate;
import java.util.Date;
import java.util.List;

import static Constants.Constants.*;
@Service
public class BookService {

    @Autowired
    BookMapper bookMapper;

    public book findBookById(String id) throws SQLException {
        return bookMapper.findBookById(id);
    }

    public void insertBook(book newBook) throws SQLException {
        newBook.setAddTime(java.sql.Date.valueOf(LocalDate.now()));
        bookMapper.insertBook(newBook);
    }

    public void saveBook(book newBook) throws SQLException {
        bookMapper.updatetBook(newBook);
    }

    public void updatetBook(HttpServletRequest req, book updateBook) throws SQLException {
        req.setAttribute(REQUEST_EDIT_BOOK, updateBook);
    }
    public void deleteBook(String id) throws SQLException {
        bookMapper.deleteBook(id);
    }

    public List<book> list() throws SQLException {
        return bookMapper.list();
    }


}
