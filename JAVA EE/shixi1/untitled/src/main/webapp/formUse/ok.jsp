<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/9/26
  Time: 14:49
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <%
        Integer age = Integer.parseInt(request.getParameter("age"));
        if (age < 16){
            %>
        <h1>Error</h1>
    <%
        }
        else{
            String name = request.getParameter("name");
            String sex = request.getParameter("sex");
            String[] hibbit = request.getParameterValues("hibbit");
            String info = name +" "+ sex + " ";
            for (String h:hibbit) {
                info += h + " ";
            }
            %>
    <h1><%=info%></h1>
    <%
        }
    %>

</body>
</html>
