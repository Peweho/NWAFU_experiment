<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/11/1
  Time: 16:04
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>错误页面</title>
</head>
<body>
    <c:if test="${error != null}">
        <%
            String error = (String) request.getAttribute("error");
        %>
        <h1><%=error%></h1>
    </c:if>
</body>
</html>
