<%--
  Created by IntelliJ IDEA.
  User: PWH
  Date: 2023/11/1
  Time: 16:03
  To change this template use File | Settings | File Templates.
--%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>展示页面</title>
    <style>
        table{
            border-collapse: collapse;
        }
        td,th{
            padding: 5px;
        }
    </style>
</head>
<body>
<%
    String login = (String) session.getAttribute("login");
    if (!"1".equals(login))
        response.sendRedirect("/views/login.jsp");
%>
    <table border="1" align="center" width="600">
        <caption>
            图书信息列表
            <p>    <button onclick="redirectToPage()">添加</button></p>
        </caption>
        <thead>
        <tr>
            <th>序号</th>
            <th>书名</th>
            <th>作者</th>
            <th>出版社</th>
            <th>加入时间</th>
        </tr>
        </thead>
        <tbody>
        <c:forEach items="${bookList}" var="book" varStatus="stat">
            <tr>
                <td>${stat.count}</td>
                <td>${book.name}</td>
                <td>${book.author}</td>
                <td>${book.press}</td>
                <td>${book.addTime}</td>
                <td>
                    <a href="/ctrl?action=edit&id=${book.id}">编辑</a>
                    <a href="/ctrl?action=delete&id=${book.id}">删除</a>
                </td>
            </tr>
        </c:forEach>
        </tbody>
        <tfoot>
        <tr>

        </tr>
        </tfoot>
    </table>
</body>
<script>
    function redirectToPage() {
        window.location.href = "/views/addBook.jsp";
    }
</script>
</html>
