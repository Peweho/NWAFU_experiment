<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/11/1
  Time: 16:14
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>登录页面</title>
</head>
<body>
<%
    session.setAttribute("postType","login");
%>
    <form action="/login" method="post">
        账号：<input type="text" name="account"><br>
        密码：<input type="password" name="pwd"><br>
        <input type="submit">
    </form>
        <input type="button" onclick='location.href=("/register.jsp")' value="注册"/>
    <%
        Object error = request.getAttribute("error");
        if (error != null){
            String info = (String) error;
    %>
    <script>alert("<%=info%>")</script>
    <%
        }
    %>
            <script>

            </script>
</body>
</html>
