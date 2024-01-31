package shixi6_2;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("shixi6_2")
public class Info {
    @RequestMapping("/info")
    public String info() {
        return "shixi6_2_info";
    }
}
