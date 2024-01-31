package model;

import entity.User;
import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.Signature;
import org.aspectj.lang.annotation.*;
import org.aspectj.lang.reflect.MethodSignature;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.lang.annotation.Annotation;
import java.lang.reflect.Method;
import java.sql.PreparedStatement;
import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.List;

@Aspect
@Component
public class LogAOP {

    @Autowired
    DBConnection connection;

    @Pointcut(value = "execution(* model.UserService.insertUser(*))")
    public void insert(){}
    @Pointcut(value = "execution(* model.UserService.list())")
    public void select(){}
    @Pointcut(value = "execution(* model.UserService.deleteUser(*))")
    public void delete(){}
    @Pointcut(value = "execution(* model.UserService.updateUser(*,*))")
    public void update(){}


    @After("insert()")
    public void insertLog(JoinPoint point) throws Throwable {
        connection.getCon();
        List<Object> list = Arrays.asList(point.getArgs());
        User use = (User) list.get(0);
        PreparedStatement pstat = DBConnection.con.prepareStatement("insert into logs(date,detail) values(?,?)");
        pstat.setString(1, LocalDateTime.now().toString());
        pstat.setString(2,"加入用户" + use.getUserName());
        pstat.execute();
    }

    @After("delete()")
    public void deleteLog(JoinPoint point) throws Throwable {
        Object[] args = point.getArgs();
        connection.getCon();
        PreparedStatement pstat = DBConnection.con.prepareStatement("insert into logs(date,detail) values(?,?)");
        pstat.setString(1, LocalDateTime.now().toString());
        pstat.setString(2,"删除用户,id=" + args[0].toString());
        pstat.execute();
    }

    @After("update()")
    public void updateLog(JoinPoint point) throws Throwable {
        Object[] args = point.getArgs();
        connection.getCon();
        PreparedStatement pstat = DBConnection.con.prepareStatement("insert into logs(date,detail) values(?,?)");
        pstat.setString(1, LocalDateTime.now().toString());
        pstat.setString(2,"用户id= " + args[0].toString() + " 修改密码");
        pstat.execute();
    }

    @After("select()")
    public void selectLog(JoinPoint point) throws Throwable {
        connection.getCon();
        PreparedStatement pstat = DBConnection.con.prepareStatement("insert into logs(date,detail) values(?,?)");
        pstat.setString(1, LocalDateTime.now().toString());
        pstat.setString(2,"查询所有用户");
        pstat.execute();
    }
}
