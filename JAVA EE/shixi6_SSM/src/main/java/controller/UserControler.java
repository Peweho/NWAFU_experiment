package controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import service.UserService;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;

import static Constants.Constants.*;

@Controller
public class UserControler {
    @Autowired
    UserService userService;

    @RequestMapping("/login")
    public String login(String account,String pwd,HttpServletRequest req) throws ServletException, IOException {
        return userService.login(account,pwd,req) ? REDICT.concat(CTRL_SHOW) : LOGIN;
    }

    @RequestMapping("/register")
    public String register(String account,String pwd,HttpServletRequest req){
        return userService.register(account,pwd,req);
    }
}
