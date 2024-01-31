package model;

import AOP.list;
import entity.User;
import jakarta.annotation.Resource;
import lombok.extern.java.Log;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

@Service
public class UserService {
    @Autowired
    DBBase dbBase;
    static String SELECTSQL = "select * from users";
    static String INSERTSQL = "insert into users(user_name,passwd) values(?,?)";
    static String DELETESQL = "delete from users where id=?";
    static String UPDATESQL = "update users set passwd = ? where id=?";

    public List<User> list() throws SQLException, ClassNotFoundException {
        ResultSet rs = dbBase.selectAll(SELECTSQL);
        List<User> users = new ArrayList<User>();
        while (rs.next()){
            User user = new User(rs.getInt("id"),rs.getString("user_name"),rs.getString("passwd"));
            users.add(user);
        }
        return users;
    }
    public void insertUser(User user) throws SQLException, ClassNotFoundException {
        dbBase.insertUser(user,INSERTSQL);
    }
    public void deleteUser(String id) throws SQLException, ClassNotFoundException {
        dbBase.deleteUser(id,DELETESQL);
    }
    public void updateUser(String id,String passwd) throws SQLException, ClassNotFoundException {
        dbBase.updateUser(id,passwd,UPDATESQL);
    }
}
