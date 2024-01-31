package mapper;

import entity.book;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Select;
import java.util.List;


public interface BookMapper {
    @Select("select * from book")
    List<book> list();

    @Select("select * from book where id = #{id}")
    book findBookById(String id);

    @Delete("delete from book where id = #{id}")
    void deleteBook(String id);

    void insertBook(book insertBook);
    void updatetBook(book updateBook);
}
