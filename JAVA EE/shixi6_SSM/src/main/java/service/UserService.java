package service;

import mapper.UserMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import static Constants.Constants.*;
import static Constants.Constants.LOGIN_PATH;

@Service
public class UserService {
    @Autowired
    UserMapper userMapper;
    public String findUserByAccount(String account) throws SQLException {
        String pwd = userMapper.findUserByAccount(account);
        return  pwd == null ? "" : pwd;
    }
    public Boolean login(String formAccount,String formPwd,HttpServletRequest req){

        if (formAccount == null || formPwd == null){
            req.setAttribute(ERROR,ERROR_ACCOUNT);
            return false;
        }else if (formAccount.equals("")){
            req.setAttribute(ERROR,ERROR_ACCOUNT);
            return false;
        } else if(formPwd.equals("")){
            req.setAttribute(ERROR,ERROR_PWD);
            return false;
        }

        HttpSession session = req.getSession();
        Object sessionAccount = session.getAttribute(SESSION_ACCOUNT);
        Object sessionPwd= session.getAttribute(SESSION_PWD);

        if (sessionAccount != null && sessionPwd != null &&
                formAccount.equals((String)sessionAccount) && formPwd.equals((String)sessionPwd)){
            session.setAttribute(SESSION_LOGIN,SESSION_LOGIN_SUCCESS);
            return true;
        }else{
            //查找数据库
            try {
                String dataBasePwd = findUserByAccount((String) formAccount);
                if (dataBasePwd.equals(formPwd)){
                    session.setAttribute(SESSION_ACCOUNT,formAccount);
                    session.setAttribute(SESSION_PWD,formPwd);
                    session.setAttribute(SESSION_LOGIN,SESSION_LOGIN_SUCCESS);
                    return true;
                }else{
                    session.setAttribute(SESSION_LOGIN,SESSION_NOT_LOGIN);
                    req.setAttribute(ERROR,ERROR_ACCOUNT_AND_PWD);
                    return false;
                }
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }

    public String register(String formAccount,String formPwd,HttpServletRequest req){
        String usePwd = userMapper.findUserByAccount(formAccount);

        if (usePwd == null) {
            userMapper.register(formAccount, formPwd);
            req.setAttribute(ERROR, "注册成功");
            return LOGIN;
        }
        else {
            req.setAttribute(ERROR,ERROR_ACCOUNT_REPEAT);
            return "register";
        }
    }
}
