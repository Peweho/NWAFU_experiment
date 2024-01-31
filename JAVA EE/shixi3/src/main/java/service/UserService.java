package service;

import entity.user;

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

public class UserService {
    Connection con;
    public UserService(Connection con){
        this.con = con;
    }
    public String findUserByAccount(String account) throws SQLException {
        PreparedStatement pstat = con.prepareStatement(FIND_USER_BY_ACCOUNT);
        pstat.setString(1,account);
        ResultSet res = pstat.executeQuery();
        String pwd = "";
        if(res.next())
            pwd = res.getString(USER_PASSWORD);
        return pwd;
    }
    public void login(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        Object formAccount = req.getParameter(LOGIN_ACCOUNT);
        Object formPwd = req.getParameter(LOGIN_PWD);

        if (formAccount == null || formPwd == null){
            req.setAttribute(ERROR,ERROR_ACCOUNT);
            req.getRequestDispatcher(LOGIN_PATH).forward(req,resp);
        }else if (formAccount.equals("")){
            req.setAttribute(ERROR,ERROR_ACCOUNT);
            req.getRequestDispatcher(LOGIN_PATH).forward(req,resp);
            return;
        } else if(formPwd.equals("")){
            req.setAttribute(ERROR,ERROR_PWD);
            req.getRequestDispatcher(LOGIN_PATH ).forward(req,resp);
            return;
        }

        HttpSession session = req.getSession();
        Object sessionAccount = session.getAttribute(SESSION_ACCOUNT);
        Object sessionPwd= session.getAttribute(SESSION_PWD);

        if (sessionAccount != null && sessionPwd != null &&
                formAccount.equals((String)sessionAccount) && formPwd.equals((String)sessionPwd)){
            session.setAttribute(SESSION_LOGIN,SESSION_LOGIN_SUCCESS);
            resp.sendRedirect(CTRL_ACTION_SHOW);
            System.out.println("session_login");
        }else{
            //查找数据库
            try {
                String dataBasePwd = findUserByAccount((String) formAccount);
                if (dataBasePwd.equals(formPwd)){
                    session.setAttribute(SESSION_ACCOUNT,formAccount);
                    session.setAttribute(SESSION_PWD,formPwd);
                    session.setAttribute(SESSION_LOGIN,SESSION_LOGIN_SUCCESS);
                    resp.sendRedirect(CTRL_ACTION_SHOW);
                }else{
                    session.setAttribute(SESSION_LOGIN,SESSION_NOT_LOGIN);
                    req.setAttribute(ERROR,ERROR_ACCOUNT_AND_PWD);
                    req.getRequestDispatcher(LOGIN_PATH ).forward(req,resp);
                }
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
