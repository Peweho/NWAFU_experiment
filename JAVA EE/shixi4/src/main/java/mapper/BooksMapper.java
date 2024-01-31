package mapper;

import entity.Books;
import org.apache.ibatis.annotations.*;

import java.util.List;

public interface BooksMapper {
//    List<Books> getBookById(Integer id);
//    boolean deleteBookById(Integer id);
//    boolean addBook(Books book);
//    boolean editBook(Books book);
    //List<Books> getAllBooks();


    @Select("select * from books")
    List<Books> selectAll();

    @Select("select * from books where id=#{id}")
    Books selecBookById(@Param("id") Integer id);

    @Insert("insert into books(book_name,author,price,press) " +
            "values (#{book.bookName},#{book.author},#{book.price},#{book.press})")
    void insertBook(@Param("book") Books book);

    @Delete("delete from books where id = #{id}")
    void deleteBook(Integer id);

    @Update("update books" +
            "        set book_name = #{book.bookName}," +
            "            author = #{book.author}," +
            "            price = #{book.price}," +
            "            press = #{book.press}" +
            "        where id = #{book.id};")
    void updateBookById(@Param("book") Books book);

}
