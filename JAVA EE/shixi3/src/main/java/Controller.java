import Common.DBConnection;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

import entity.book;
import service.BookService;
import service.UserService;

import static Constants.Constants.*;

@WebServlet(name = "Controller", value = "ctrl")
public class Controller extends HttpServlet {
    private Connection con;
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("utf-8");
        //获取请求参数
        Object action = req.getParameter(ACTION);
        System.out.println("action = " + action);
        if (action == null){
            req.setAttribute(ERROR,ERROR_MISSING_PARAMETER);
            req.getRequestDispatcher(ERROR_PATH).forward(req,resp);
            return;
        }
        String actionString = (String) action;

        //定义服务层
        BookService bookService = new BookService(con);
        UserService userService = new UserService(con);

        try {
            if (actionString.equals(ACTION_SHOW)){
                List<book> books = bookService.list();
                req.setAttribute(REQUEST_BOOK_LIST,books);
                req.getRequestDispatcher(BOOKLIST_PATH).forward(req,resp);
            }
            else if(action.equals(ACTION_SAVE)){
                Object id = req.getParameter(BOOK_ID);
                if (id == null){
                    throw new Exception(ERROR_MISSING_PARAMETER);
                }
                String name = req.getParameter(BOOK_NAME);
                String author = req.getParameter(BOOK_AUTHOR);
                String press = req.getParameter(BOOK_PRESS);

                bookService.updatetBook((String) id, name,author,press);
                resp.sendRedirect(CTRL_ACTION_SHOW);
            }
            else if(actionString.equals(ACTION_EDIT)){
                Object id = req.getParameter(BOOK_ID);
                if (id == null){
                    throw new Exception(ERROR_MISSING_PARAMETER);
                }
                book editBook = bookService.findBookById((String) id);
                req.setAttribute(REQUEST_EDIT_BOOK,editBook);
                req.getRequestDispatcher(EDIT_PATH).forward(req,resp);
            }
            else if(actionString.equals(ACTION_LOHIN)){
                userService.login(req,resp);
            }
            else if(actionString.equals(ACTION_ADD)){
                String bookName = req.getParameter(ADD_BOOK_NAME);
                String bookAuthor = req.getParameter(ADD_BOOK_AUTHOR);
                String bookPress = req.getParameter(ADD_BOOK_PRESS);

                bookService.insertBook(bookName,bookAuthor,bookPress);
                resp.sendRedirect(CTRL_ACTION_SHOW);
            }
            else if(actionString.equals(ACTION_DELETE)){
                Object id = req.getParameter(BOOK_ID);
                if (id == null){
                    throw new Exception(ERROR_MISSING_PARAMETER);
                }
                bookService.deleteBook((String) id);
                resp.sendRedirect(CTRL_ACTION_SHOW);
            }
            else {
                throw new Exception("非法请求！！");
            }
        } catch (Exception e) {
            req.setAttribute(ERROR,e.getLocalizedMessage());
            req.getRequestDispatcher(ERROR_PATH).forward(req,resp);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }

    @Override
    public void init() throws ServletException {
        try {
            DBConnection conn = new DBConnection();
            con = conn.getCon();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }
}
