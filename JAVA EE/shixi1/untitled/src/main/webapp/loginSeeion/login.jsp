<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/9/26
  Time: 15:41
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
<%
    //获取错误信息
    Object loginError = request.getAttribute("loginError");
    if (loginError != null){
        String info = (String) loginError;
        %>
            <script>alert("<%=info%>")</script>
        <%
    }

    //查询Cookie
    Cookie[] cookies = request.getCookies();
    String account = new String("");
    String pwd = new String("");
    for (Cookie cookie: cookies) {
        if(cookie.getName().equals("account")){
            account = cookie.getValue();
        } else if(cookie.getName().equals("pwd")){
            pwd = cookie.getValue();
        }
    }
        %>
    <form action="check.jsp" method="post">
        用户名：<input type="text" name="account" value="<%=account%>"><br>
        密码：<input type="password" name="pwd" value="<%=pwd%>"><br>
        <input type="checkbox" name="remember" value ="1">记住用户名和密码<br>
        <input type="submit" name="提交">
    </form>
</body>
</html>
