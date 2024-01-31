<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/11/1
  Time: 22:05
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <%
        session.setAttribute("postType","addBook");
    %>
    <form action="/ctrl?action=add" method="post" onsubmit="return validateForm()">
        书籍名称：<input type="text" name="bookName" id="bookName"><br>
        作者：<input type="text" name="author" id="author"><br>
        出版社：<input type="text" name="press" id="press"><br>
        <input type="submit">
    </form>

    <script>
        function validateForm() {
            var bookName = document.getElementById("bookName").value;
            var author = document.getElementById("author").value;
            var press = document.getElementById("press").value;

            if (bookName === "" || author === "" || press === "") {
                alert("请填写所有字段！");
                return false;
            }
        }
    </script>
</body>
</html>
