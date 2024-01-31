package shixi6_1;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class controller {
    @RequestMapping("/getParam")
    public ModelAndView getParam(String param1,Double param2){
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.addObject("param1",param1);
        modelAndView.addObject("param2",param2);
        modelAndView.setViewName("shixi6_1_show");
        return modelAndView;
    }
}
