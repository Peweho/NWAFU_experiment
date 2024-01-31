import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.ServletRequestEvent;
import javax.servlet.ServletRequestListener;
import javax.servlet.annotation.WebListener;
import javax.servlet.http.HttpSessionEvent;
import javax.servlet.http.HttpSessionListener;
import java.util.Date;

@WebListener()
public class EventListener implements ServletContextListener, ServletRequestListener, HttpSessionListener {

    //使用ServletContext统计启动时间
    @Override
    public void contextInitialized(ServletContextEvent sce) {
        sce.getServletContext().setAttribute("StartDate", new Date());
    }
    @Override
    public void contextDestroyed(ServletContextEvent sce) {
        sce.getServletContext().removeAttribute("StartDate");
    }

    //使用ServletRequest统计请求数
    @Override
    public synchronized void requestDestroyed(ServletRequestEvent sre) {
        int cnt = 0;
        Object reqcnt = sre.getServletContext().getAttribute("reqCnt");
        if(reqcnt != null){
            cnt = (Integer)reqcnt;
        }
        cnt--;
        sre.getServletContext().setAttribute("reqCnt", cnt);
    }
    @Override
    public synchronized void requestInitialized(ServletRequestEvent sre) {
        int cnt = 0;
        Object reqcnt = sre.getServletContext().getAttribute("reqCnt");
        if(reqcnt != null){
            cnt = (Integer)reqcnt;
        }
        cnt++;
        sre.getServletContext().setAttribute("reqCnt", cnt);
    }
    //使用HttpSession统计在线人数
    @Override
    public synchronized void sessionCreated(HttpSessionEvent se) {
        int cnt = 0;
        Object sessionCnt = se.getSession().getServletContext().getAttribute("sessionCnt");
        if(sessionCnt != null){
            cnt = (Integer)sessionCnt;
        }
        cnt++;
        se.getSession().getServletContext().setAttribute("sessionCnt", cnt);

    }
    @Override
    public synchronized void sessionDestroyed(HttpSessionEvent se) {
        int cnt = 0;
        Object sessionCnt = se.getSession().getServletContext().getAttribute("sessionCnt");
        if(sessionCnt != null){
            cnt = (Integer)sessionCnt;
        }
        cnt--;
        se.getSession().getServletContext().setAttribute("sessionCnt", cnt);
    }
}
