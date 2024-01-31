import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

import static Constants.Constants.*;
import static Constants.Constants.LOGIN_PATH;

@WebFilter(urlPatterns = "/views/*")
public class LoginFilter implements javax.servlet.Filter{
    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        HttpServletRequest req = (HttpServletRequest) servletRequest;
        HttpServletResponse resp = (HttpServletResponse) servletResponse;

        Object isLogin = req.getSession().getAttribute(SESSION_LOGIN);
        if((isLogin == null || SESSION_NOT_LOGIN.equals((String) isLogin))){
            resp.sendRedirect(LOGIN_PATH);
        }else{
            filterChain.doFilter(servletRequest, servletResponse);
        }
    }
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {

    }

    @Override
    public void destroy() {

    }
}
