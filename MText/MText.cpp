#include "MText.h"


MText::MText(QWidget *parent)
    : QMainWindow(parent)
{
    //添加右侧图片
    LabelPNG = new QLabel(this);
    LabelPNG->show();
    LabelPNG->setPixmap(QPixmap("./image/远山A.png"));
    LabelPNG->setGeometry(0, 0, 800, 450);//320,0,480,450

    //初始化账号密码输入框与登录按钮
    ButtonLogin = new QPushButton("登录", this);
    LineEditID = new QLineEdit(this);
    LineEditPassword = new QLineEdit(this);

    //将登录按钮移动到合适位置
    ButtonLogin->setGeometry(120, 230, 160, 30);
    ButtonLogin->setStyleSheet("QPushButton{font:18px;}");

    //将账号密码输入框移动到合社位置
    LineEditID->setGeometry(100, 150, 200, 25);//move(150, 150);
    LineEditPassword->setGeometry(100, 200, 200, 25);

    //添加账号密码输入框提示文字
    LineEditID->setPlaceholderText("请输入账号...");
    LineEditPassword->setPlaceholderText("请输入密码...");

    //账号密码输入框添加一键清除按钮
    LineEditID->setClearButtonEnabled(true);
    LineEditPassword->setClearButtonEnabled(true);

    //指定密码框文本显示方式
    LineEditPassword->setEchoMode(QLineEdit::Password);

    //点击登录按钮跳转到LoginClick()
    QObject::connect(ButtonLogin, SIGNAL(clicked(void)), this, SLOT(LoginCilck()));

}


//将账号密码输入框中的字符传入SqlLink登录函数中
void MText::LoginCilck()
{
    std::string IDText = string((const char*)LineEditID->text().toLocal8Bit());
    std::string PasswordText = string((const char*)LineEditPassword->text().toLocal8Bit());
    cout << IDText << endl;;
    SqlLink(IDText,PasswordText);

}

void MText::AddMySql(MYSQL *addmysql)
{
    mysql = addmysql;
}

void MText::SqlLink(string ID, string Password)

{
    MYSQL_RES* res; //查询结果集
    MYSQL_ROW row;  //记录结构体

    //连接数据库
    if (mysql_real_connect(mysql, "112.74.38.94", ID.c_str(), Password.c_str(), "mtest", 3306, NULL, 0) == NULL)//
        //localhost为服务器"112.74.38.94" ，ID.c_str为用户名和密码，mtest为数据库名，3306为端口
    {
        setWindowTitle("账号密码错误");
    }
    else
    {
        setWindowTitle("登录中。。。。。。。。。。。");

        string SelLogin= "SELECT sort FROM usertable WHERE ID ="+ID+";";//查询ID类别 0为管理员 1为普通用户
        mysql_query(mysql, SelLogin.c_str());//
        res = mysql_store_result(mysql);

        row = mysql_fetch_row(res); //获取mysql结果集
        
        QMovie* movie = new QMovie("./image/PUI.gif");//路径要用双斜杠
        LabelPNG->setMovie(movie);
        LabelPNG->setScaledContents(true);//用来自适应label大小，图片填充label空间
        movie->start();

        //row[0]进入管理员界面 row[1]进入用户界面 
        string login = row[0];
        if (login == "admin")
        {
            setWindowTitle("登录成功");
            LineEditID->hide();
            LineEditPassword->hide();
            ButtonLogin->hide();

           /* SonWindow = new adminwindow;
            SonWindow->addmysql(mysql);
            SonWindow->fixwindow(ID);
            SonWindow->setWindowTitle("管理员界面");
            SonWindow->show();*/

           

        }
        if(login  == "user")
        {
           setWindowTitle("登录成功");
           LineEditID->hide();
           LineEditPassword->hide();
           ButtonLogin->hide();

           /*SonWindow = new UserWindow(mysql,ID);
           SonWindow->show();*/
        }
        //close();

        //释放结果集
        mysql_free_result(res);
    }
}