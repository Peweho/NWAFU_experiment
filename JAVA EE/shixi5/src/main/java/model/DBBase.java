package model;

import entity.User;
import jakarta.annotation.Resource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.sql.*;

@Component
public class DBBase {
    @Autowired
    DBConnection connection;

    public ResultSet selectAll(String sql) throws ClassNotFoundException, SQLException {
        Connection con = connection.getCon();
        Statement stat = con.createStatement();
        ResultSet res = stat.executeQuery(sql);
        return res;
    }
    public void insertUser(User user,String sql) throws SQLException, ClassNotFoundException {
        Connection con = connection.getCon();
        PreparedStatement pstat = DBConnection.con.prepareStatement(sql);
        pstat.setString(1,user.getUserName());
        pstat.setString(2,user.getPasswd());
        pstat.execute();
    }
    public void deleteUser(String id,String sql) throws SQLException, ClassNotFoundException {
        Connection con = connection.getCon();
        PreparedStatement pstat = DBConnection.con.prepareStatement(sql);
        pstat.setString(1,id);
        pstat.execute();
    }
    public void updateUser(String id,String passwd,String sql) throws SQLException, ClassNotFoundException {
        Connection con = connection.getCon();
        PreparedStatement pstat = DBConnection.con.prepareStatement(sql);
        pstat.setString(1,passwd);
        pstat.setString(2,id);
        pstat.execute();
    }
}