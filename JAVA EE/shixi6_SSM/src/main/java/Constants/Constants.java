package Constants;

public class Constants {
    //request属性
    public static final String REQUEST_BOOK_LIST = "bookList";
    public static final String REQUEST_EDIT_BOOK = "editBook";

    //session的属性或值
    public static final String SESSION_LOGIN = "login";
    public static final String SESSION_LOGIN_SUCCESS = "1";
    public static final String SESSION_NOT_LOGIN = "0";
    public static final String SESSION_ACCOUNT = "BookSystemAccount";
    public static final String SESSION_PWD= "BookSystemPwd";
    public static final String ERROR = "error";
    //错误信息
    public static final String ERROR_ACCOUNT_AND_PWD = "账号或密码错误";
    public static final String ERROR_ACCOUNT = "请输入账号";
    public static final String ERROR_ACCOUNT_REPEAT = "账号已存在";
    public static final String ERROR_PWD = "请输入密码";
    public static final String ERROR_NORMAL = "错误";
    public static final String ERROR_NOT_LOGIN = "请登录";
    public static final String ERROR_MISSING_PARAMETER ="缺少参数";
    //文件路径
    public static final String EDITBOOK_PATH = "WEB-INF/views/edit";
    public static final String LOGIN_PATH = "login.jsp";

    public static final String ERROR_PATH = "error.jsp";
    //请求路径
    public static final String REDICT = "redirect:";
    public static final String CTRL_SHOW="/ctrl/show";
    public static final String LOGIN ="login";
    public static final String BOOKLIST ="WEB-INF/views/bookList";
    public static final String ADDBOOK ="WEB-INF/views/addBook";
}
