<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/12/17
  Time: 15:19
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <form action="/register" method="post">
        账号：<input type="text" name="account"><br>
        密码：<input type="password" name="pwd"><br>
        <input type="submit">
    </form>
    <%
        Object error = request.getAttribute("error");
        if (error != null){
            String info = (String) error;
    %>
    <script>alert("<%=info%>")</script>
    <%
        }
    %>
</body>
</html>
