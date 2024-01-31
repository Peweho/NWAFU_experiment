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
        <form action="/ctrl" method="post">
            书名：<input type="text" name="bookName"><br>
            作者：<input type="text" name="author"><br>
            出版社：<input type="text" name="press"><br>
            价格：<input type="number" name="priceLower">
            ~<input type="number" name="priceLimit"><br>
            出版日期 <input type="date" name="pressDateLower">
            ~<input type="date" name="pressDateLimit"><br>
            <input type="submit" value="确定">
        </form>

<table border="1" align="center" width="600">
    <caption>
        图书信息列表
    </caption>
    <thead>
    <tr>
        <th>序号</th>
        <th>书名</th>
        <th>作者</th>
        <th>出版社</th>
        <th>价格</th>
        <th>出版时间</th>
    </tr>
    </thead>
    <tbody>
    <c:forEach items="${bookList}" var="book" varStatus="stat">
        <tr>
            <td>${stat.count}</td>
            <td>${book.bookName}</td>
            <td>${book.author}</td>
            <td>${book.press}</td>
            <td>${book.price}</td>
            <td>${book.pressDate}</td>
        </tr>
    </c:forEach>
    </tbody>
    <tfoot>
    <tr>

    </tr>
    </tfoot>
</table>
</body>
</html>
