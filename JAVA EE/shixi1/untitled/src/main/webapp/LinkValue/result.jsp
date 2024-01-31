<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/9/26
  Time: 15:24
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <%
        String num = request.getParameter("link");
        String order = "";
        switch (num){
            case "1":order = "一";break;
            case "2":order = "二";break;
            case "3":order = "三";break;
        }

    %>
    <h4>你点击了第”<%=order%>“链接…</h4>
</body>
</html>
