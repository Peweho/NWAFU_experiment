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
    <title>编辑页面</title>
</head>
<body>
    <div style="margin: 20px auto;width: 200px">
        <form action="ctrl?action=save&id=${editBook.id}" method="post" onsubmit="return validateForm()">
            名称：<input name="name" value="${editBook.name}" id="name"> <br />
            作者：<input name="author" value="${editBook.author}" id="author"> <br />
            出版社：<input name="press"  value="${editBook.press}" id="press"> <br />
            <button type="submit">保存</button>
        </form>
    </div>
    <script>
        function validateForm() {
            var bookName = document.getElementById("name").value;
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
