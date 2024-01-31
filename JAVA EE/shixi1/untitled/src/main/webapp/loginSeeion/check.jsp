<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/9/26
  Time: 15:44
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>

    <%
        //从数据库获取到的账号密码
        String dateAccount = "pwh";
        String datePwd = "123";
        //获取表单元素
        String account = request.getParameter("account");
        String pwd = request.getParameter("pwd");
        //获取session元素
        Object sessionAccount = session.getAttribute("account");
        Object sessionPwd = session.getAttribute("pwd");

        if (sessionAccount == null && sessionPwd == null){
            //没有session从数据库获取数据
            if(account.equals(dateAccount) && pwd.equals(datePwd)) {
                session.setAttribute("account", "pwh");
                session.setAttribute("pwd", "123");
                session.setAttribute("login","1");//"1"表示登录成功
            }else{
                if(!account.equals(dateAccount))
                    request.setAttribute("loginError","账号错误");
                else
                    request.setAttribute("loginError","密码错误");
                session.setAttribute("login","0");//"0"表示登录失败
                request.getRequestDispatcher("login.jsp").forward(request, response);

            }
        } else if (sessionAccount != null && sessionPwd != null){
            if (account.equals((String) sessionAccount) && pwd.equals((String) sessionPwd )){
                session.setAttribute("login","1");//"1"表示登录成功
            }else{
                if(!account.equals((String) sessionAccount))
                    request.setAttribute("loginError","账号错误");
                else
                    request.setAttribute("loginError","密码错误");
                session.setAttribute("login","0");//"0"表示登录失败
                request.getRequestDispatcher("login.jsp").forward(request, response);
            }
        }

        //登录成功，完成记住密码功能
        if (session.getAttribute("login") != null && "1".equals((String) session.getAttribute("login"))) {
            String[] remembers = request.getParameterValues("remember");
            if (remembers != null && remembers[0].equals("1")) {
                //账号加入Cookie
                Cookie cookieAccount = new Cookie("account", account);
                cookieAccount.setMaxAge(100);
                response.addCookie(cookieAccount);
                //密码加入Cookie
                Cookie cookiePwd = new Cookie("pwd", pwd);
                cookiePwd.setMaxAge(100);
                response.addCookie(cookiePwd);
            }
            response.sendRedirect("admin.jsp");
        }
    %>
</body>
</html>
