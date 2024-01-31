package shixi6_2;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.servlet.http.HttpServletRequest;

@Controller
public class Login {
    @RequestMapping("/login")
    public String login(HttpServletRequest req){
        if (req.getParameter("account").equals("pwh") && req.getParameter("passwd").equals("123")){
            req.getSession().setAttribute("login",true);
            return "shixi6_2_info";
        } else{
            return "shixi6_2_login";
        }
    }
}

