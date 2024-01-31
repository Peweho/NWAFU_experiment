package form;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "fromserverlet",urlPatterns = "/formResult")
public class formServerlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        System.out.println("请求发送到了servlet");
        //设置编码
        resp.setCharacterEncoding("UTF-8");
        resp.setContentType("text/html;charset=utf-8");
        req.setCharacterEncoding("UTF-8");
        //获取年龄
        int age = Integer.parseInt(req.getParameter("age"));
        if (age > 16) {
            //获取表单元素
            String name = req.getParameter("name");
            String sex = req.getParameter("sex");
            String[] hibbits = req.getParameterValues("hibbit");
            String info = name +" "+ sex + " " + age + " ";
            for (String h:hibbits) {
                info = info.concat(h+" ");
            }
            //存储信息并转发
            req.setAttribute("info",info);
            req.getRequestDispatcher("/form/result.jsp").forward(req,resp);
        } else {
            //显示错误信息
            resp.getWriter().println("Error:年龄小于16");
        }
    }
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        super.doGet(req, resp);
    }
}
