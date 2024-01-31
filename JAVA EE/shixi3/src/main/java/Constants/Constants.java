package Constants;

public class Constants {
    //SQL语句
    public static final String FIND_USER_BY_ACCOUNT = "select password from user where account = ?";
    public static final String FIND_BOOK_ALL = "select * from book";
    public static final String FIND_BOOK_BY_ID = "select * from book where id = ?";
    public static final String INSERT_BOOK = "insert into book(name,author,press,addTime) values(?,?,?,?)";
    public static final String UPDATE_BOOK = "update book set name = ?,author = ?, press = ? where id = ?";
    public static final String DELETE_BOOK = "delete from book where id = ?";
    //request属性
    public static final String REQUEST_BOOK_LIST = "bookList";
    public static final String REQUEST_EDIT_BOOK = "editBook";

    //session的属性或值
    public static final String SESSION_LOGIN = "login";
    public static final String SESSION_LOGIN_SUCCESS = "1";
    public static final String SESSION_NOT_LOGIN = "0";
    public static final String SESSION_ACCOUNT = "BookSystemAccount";
    public static final String SESSION_PWD= "BookSystemPwd";
    public static final String SESSION_POST_TYPE = "postType";
    public static final String SESSION_POST_TYPE_LOGIN = "login";
    public static final String SESSION_POST_TYPE_ADD_BOOK = "addBook";
    public static final String ERROR = "error";
    //错误信息
    public static final String ERROR_ACCOUNT_AND_PWD = "账号或密码错误";
    public static final String ERROR_ACCOUNT = "请输入账号";
    public static final String ERROR_PWD = "请输入密码";
    public static final String ERROR_NORMAL = "错误";
    public static final String ERROR_NOT_LOGIN = "请登录";
    public static final String ERROR_MISSING_PARAMETER ="缺少参数";
    //user表字段
    public static final String USER_PASSWORD = "password";
    //book表字段
    public static final String BOOK_ID = "id";
    public static final String BOOK_NAME = "name";
    public static final String BOOK_PRESS = "press";
    public static final String BOOK_ADD_TIME = "addTime";
    public static final String BOOK_AUTHOR = "author";
    //文件路径
    public static final String BOOKLIST_PATH = "/views/bookList.jsp";
    public static final String LOGIN_PATH = "/login.jsp";
    public static final String EDIT_PATH = "/views/edit.jsp";
    public static final String ERROR_PATH = "/error.jsp";
    //请求路径
    public static final String CTRL_ACTION_SHOW = "/ctrl?action=show";
    //路径参数
    public static final String ACTION = "action";
    public static final String ACTION_SHOW = "show";
    public static final String ACTION_SAVE = "save";
    public static final String ACTION_EDIT = "edit";
    public static final String ACTION_ADD = "add";
    public static final String ACTION_DELETE = "delete";
    public static final String ACTION_LOHIN = "login";
    //表单参数
    public static final String LOGIN_ACCOUNT = "account";
    public static final String LOGIN_PWD = "pwd";
    public static final String ADD_BOOK_NAME = "bookName";
    public static final String ADD_BOOK_AUTHOR = "author";
    public static final String ADD_BOOK_PRESS = "press";
}
