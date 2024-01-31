package mapper;

import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.springframework.dao.DataAccessException;

public interface UserMapper {
    @Select("select password from user where account = #{account}")
    String findUserByAccount(String account) throws DataAccessException;

    @Insert("insert into user(account,password) values(#{account},#{passwd})")
    void register(@Param("account") String account, @Param("passwd")String passwd);
}
