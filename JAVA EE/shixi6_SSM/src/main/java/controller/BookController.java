package controller;

import entity.book;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import service.BookService;
import service.UserService;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.List;

import static Constants.Constants.*;

@Controller
@RequestMapping("/ctrl")
public class BookController {
    @Autowired
    BookService bookService;

    @RequestMapping("/show")
    public String show(HttpServletRequest req) throws SQLException {
        List<book> books = bookService.list();
        req.setAttribute(REQUEST_BOOK_LIST,books);
        return BOOKLIST;
    }

    @RequestMapping("/insert")
    public String show(book newBook) throws SQLException {
        bookService.insertBook(newBook);
        return REDICT.concat(CTRL_SHOW);
    }

    @RequestMapping("/add")
    public String add() {
        return ADDBOOK;
    }

    @GetMapping("/update")
    public String update(book newBook,HttpServletRequest req) throws SQLException {
        bookService.updatetBook(req,newBook);
        return EDITBOOK_PATH;
    }

    @PostMapping("/save")
    public String save(book newBook) throws SQLException {
        System.out.println("newBook = " + newBook);
        bookService.saveBook(newBook);
        return REDICT.concat(CTRL_SHOW);
    }

    @RequestMapping("/delete")
    public String delete(String id) throws SQLException {
        bookService.deleteBook(id);
        return REDICT.concat(CTRL_SHOW);
    }
}
