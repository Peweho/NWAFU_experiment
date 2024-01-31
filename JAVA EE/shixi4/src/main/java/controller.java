import entity.Books;
import entity.SelectBook;
import lombok.val;
import mapper.BookWebMapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

@WebServlet(name = "Controller", value = "ctrl")
public class controller extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("utf-8");
        //数据处理
        String bookName = dealString(req.getParameter("bookName"),true);
        String author = dealString(req.getParameter("author"),true);
        String press = dealString(req.getParameter("press"),true);
        Double priceLower = dealDouble(req.getParameter("priceLower"));
        Double priceLimit =dealDouble(req.getParameter("priceLimit"));;
        String pressDateLower = dealString(req.getParameter("pressDateLower"),false);
        String pressDateLimit = dealString(req.getParameter("pressDateLimit"),false);
        //构建查询对象
        SelectBook selectBook = new SelectBook(
                bookName, author, press, priceLower, priceLimit, pressDateLower, pressDateLimit);

        InputStream inputStream = Resources.getResourceAsStream("config.xml");
        SqlSessionFactory ssf = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = ssf.openSession();

        //调用查询的动态sql
        BookWebMapper mapper = sqlSession.getMapper(BookWebMapper.class);
        List<Books> books = mapper.selectBooks(selectBook);

        req.setAttribute("bookList",books);
        req.getRequestDispatcher("/index.jsp").forward(req,resp);
    }

    public String dealString(String str ,Boolean isVague){
        if (str.equals(""))
            return null;
        if (isVague){
            String res = "%";
            str = str.concat("%");
            return res.concat(str);
        }
        return str;
    }
    public Double dealDouble(String str){
        if (str.equals(""))
            return null;
        return Double.parseDouble(str);
    }
}
