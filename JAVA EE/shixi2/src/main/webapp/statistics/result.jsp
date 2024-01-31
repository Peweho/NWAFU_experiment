<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/10/26
  Time: 14:42
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>生命周期事件</title>
</head>
<body>
<%
    Object reqCnt = application.getAttribute("reqCnt");
    int cnt = (int)reqCnt - 1;
%>
    <p>当前应用启动时间：<%=application.getAttribute("StartDate") %></p>
    <p>当前在线人数：<%=application.getAttribute("sessionCnt") %></p>
    <p>处理请求数：<%=cnt %></p>
</body>
</html>
