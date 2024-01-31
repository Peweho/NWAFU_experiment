import entity.Books;
import entity.SelectBook;
import mapper.BookWebMapper;
import mapper.BooksMapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

public class test {
    public static void main(String[] args) throws IOException {
        InputStream inputStream = Resources.getResourceAsStream("config.xml");
        SqlSessionFactory ssf = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = ssf.openSession();

        SelectBook selectBook = new SelectBook("%数学%",null,null,null,null,null,null);
        BookWebMapper mapper = sqlSession.getMapper(BookWebMapper.class);
        List<Books> books = mapper.selectBooks(selectBook);
        sqlSession.commit();
        sqlSession.close();
//        List<Books> books = sqlSession.selectList("mapper.BooksSql.getAllBooks");
//        System.out.println("books = " + books);
    }
}
