package mapper;

import entity.Books;
import entity.SelectBook;
import org.apache.ibatis.annotations.Select;

import java.util.List;

public interface BookWebMapper {
   List<Books> selectBooks(SelectBook selectBook);

//    @Select("select * from books")
//    List<Books> selectBook();
}
