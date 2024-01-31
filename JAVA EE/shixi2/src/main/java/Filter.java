import org.jetbrains.annotations.NotNull;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebFilter("/loginSeeion/admin.jsp")
public class Filter implements javax.servlet.Filter {
    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse,
                         FilterChain filterChain) throws IOException, ServletException {
        System.out.println("成功拦截发送admin.jsp的请求");
        HttpServletRequest request = (HttpServletRequest) servletRequest;
        HttpServletResponse response = (HttpServletResponse) servletResponse;
        HttpSession session = request.getSession();

        //判断是否登录过
        Object login = session.getAttribute("login");
        if (login != null && "1".equals((String) login)){
            request.getRequestDispatcher("/loginSeeion/login.jsp").forward(request, response);
        }else
        {
            //从数据库获取到的账号密码
            String dateAccount = "pwh";
            String datePwd = "123";
            //获取表单元素
            String account = request.getParameter("account");
            String pwd = request.getParameter("pwd");
            //获取session元素
            Object sessionAccount = session.getAttribute("account");
            Object sessionPwd = session.getAttribute("pwd");

            if (sessionAccount == null && sessionPwd == null) {
                //没有session从数据库获取数据
                if (account.equals(dateAccount) && pwd.equals(datePwd)) {
                    session.setAttribute("account", dateAccount);
                    session.setAttribute("pwd", datePwd);
                    session.setAttribute("login", 1);
                } else
                {
                    //错误处理
                    loginError(account, dateAccount, request);
                    request.getRequestDispatcher("/loginSeeion/login.jsp").forward(request, response);
                }
            } else if (sessionAccount != null && sessionPwd != null) {
                if (account.equals((String) sessionAccount) && pwd.equals((String) sessionPwd)) {
                    session.setAttribute("login", 1);
                } else
                {
                    //错误处理
                    loginError(account, (String) sessionAccount, request);
                    request.getRequestDispatcher("/loginSeeion/login.jsp").forward(request, response);
                }
            }
            //登录成功，完成记住密码功能
            if (session.getAttribute("login") != null) {
                String[] remembers = request.getParameterValues("remember");
                if (remembers != null && remembers[0].equals("1")) {
                    addCookie(account, pwd, response);
                }
                filterChain.doFilter(servletRequest, servletResponse);
            }
        }
    }

    //判断账号错误还是密码错误
    private void loginError(@NotNull String formAccount, String account, @NotNull HttpServletRequest request){
        if(!formAccount.equals((String) account))
            request.setAttribute("loginError","账号错误");
        else
            request.setAttribute("loginError","密码错误");
    }

    //完成记住密码功能
    private void addCookie(String account, String pwd, @NotNull HttpServletResponse response){
        //账号加入Cookie
        Cookie cookieAccount = new Cookie("account", account);
        cookieAccount.setMaxAge(100);
        response.addCookie(cookieAccount);
        //密码加入Cookie
        Cookie cookiePwd = new Cookie("pwd", pwd);
        cookiePwd.setMaxAge(100);
        response.addCookie(cookiePwd);
    }

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
        javax.servlet.Filter.super.init(filterConfig);
    }

    @Override
    public void destroy() {
        javax.servlet.Filter.super.destroy();
    }
}
