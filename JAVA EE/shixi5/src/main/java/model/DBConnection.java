package model;

import lombok.Data;
import org.springframework.beans.factory.annotation.Autowired;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

@Data
public class DBConnection {
    private String driver;
    private String url;
    private String user;
    private String passwd;

    static Connection con;
    public Connection getCon() throws ClassNotFoundException, SQLException {
        if(con == null){
            Class.forName(driver);
            con = DriverManager.getConnection(url,user,passwd);
        }
        return con;
    }

}
