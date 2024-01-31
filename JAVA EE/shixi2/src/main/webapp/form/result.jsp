<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/10/10
  Time: 15:26
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <%
        Object info = request.getAttribute("info");
        if (info != null){
            %>
        <h1><%=info%></h1>
    <%
        }
    %>

</body>
</html>
