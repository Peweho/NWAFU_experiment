<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/9/26
  Time: 15:54
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <%
        Object login = session.getAttribute("login");
//        判断是否登录，”1“表示登录成功
        if (login == null || !"1".equals((String) login))
            response.sendRedirect("login.jsp");
    %>
    <h1>登录成功</h1>
</body>
</html>
