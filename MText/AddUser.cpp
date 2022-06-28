#include "AddUser.h"

AddUser::AddUser(MYSQL* addMysql, QWidget* parent) : QWidget(parent)
{
    AvatarAdd = "./image/User.png";
    Ssort = "user";

    //添加上传按钮，按下即可更改头像
    UpdataButton = new QPushButton("创建用户", this);
    UpdataButton->move(150, 270);
    QObject::connect(UpdataButton, SIGNAL(clicked(void)), this, SLOT(insertUser()));

    Tcreate = new QLabel("此用户为：",this);
    Tcreate->move(150,210);
    Tcreate->show();
    ButtonChoeseSort = new QPushButton(Ssort, this);
    ButtonChoeseSort->move(200,200);
    QObject::connect(ButtonChoeseSort, SIGNAL(clicked(void)), this, SLOT(choeseSort()));

    //添加头像预览图片，无图片时为+号
    UpdataLabel = new QLabel(this);
    UpdataLabel->setPixmap(QPixmap(AvatarAdd));
    UpdataLabel->setGeometry(50, 50, 100, 100);
    UpdataLabel->setScaledContents(true);
    //创建ID输入框
    LineID  =new QLineEdit(this);
    LineID->setGeometry(200, 70, 170, 25);
    LineID->setPlaceholderText("请输入账号ID...");
    //创建昵称输入框
    LineName=new QLineEdit(this);
    LineName->setGeometry(200, 100, 170, 25);
    LineName->setPlaceholderText("请输入账号昵称...");
    //创建密码输入框
    LinePassword = new QLineEdit(this);
    LinePassword->setGeometry(200, 130, 170, 25);
    LinePassword->setPlaceholderText("请输入账号密码...");
    LinePassword->setEchoMode(QLineEdit::Password);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mysql = addMysql;
    mainLayout->addStretch();
    resize(QSize(400, 300));
    setFixedSize(width(), height());

    setWindowTitle("拖入图片作为头像");
    setWindowIcon(QIcon("./image/V_V.ico"));
    show();
    this->setAcceptDrops(true); //必须设置，不然无法接收拖放事件
}
AddUser::~AddUser()
{

}

void AddUser::dragEnterEvent(QDragEnterEvent* event) //拖动文件到窗口，触发
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction(); //事件数据中存在路径，方向事件
    }
    else
    {
        event->ignore();
    }
}

void AddUser::dragMoveEvent(QDragMoveEvent* event) //拖动文件到窗口移动文件，触发
{

}

void AddUser::dropEvent(QDropEvent* event) //拖动文件到窗口释放文件，触发
{
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QList<QUrl> urls = mimeData->urls();
        AvatarAdd = urls.at(0).toLocalFile();
        UpdataLabel->setPixmap(QPixmap(AvatarAdd));
    }
}

void AddUser::insertUser()
{
    if (lineJudge())//
    {
        if (Ssort == "admin") addUserAdmin();
        if (Ssort == "user")  addUserUser();
        
        //为整个sql语句申请内存
        char sqlStr[330];
        //创建好友表
        sprintf(sqlStr, "CREATE TABLE `mtest`.`%dFriend`  (`FriendID` int(11) NOT NULL COMMENT '好友ID',`FriendClass` varchar(20) NOT NULL COMMENT '好友所属分组',`News` int NULL COMMENT '待阅读信息',`talktable` varchar(20) NULL COMMENT '聊天所使用表',PRIMARY KEY(`FriendID`)); ", LineID->text().toInt());
        mysql_real_query(mysql, sqlStr, strlen(sqlStr));
        //授予好友表权限
        sprintf(sqlStr, "GRANT Delete, Insert, Select, Update ON TABLE `mtest`.`%dFriend` TO `%d`@``;", LineID->text().toInt(), LineID->text().toInt());
        mysql_real_query(mysql, sqlStr, strlen(sqlStr));
        //授予用户表查询修改权限
        sprintf(sqlStr, "GRANT Select, Update ON TABLE `mtest`.`usertable` TO `%d`@``;", LineID->text().toInt());
        mysql_real_query(mysql, sqlStr, strlen(sqlStr));

        QFile file(AvatarAdd);
        file.open(QIODevice::ReadOnly);
        DWORD dwFileSize = file.size();//获取文件长度
        QByteArray array = file.readAll(); //读取文件数据
        file.close();

        BYTE* dataFrom = NULL;
        dataFrom = new BYTE[dwFileSize];
        ZeroMemory(dataFrom, dwFileSize);

        string AvatarAddStr = string((const char*)AvatarAdd.toLocal8Bit());//QString转String

        FILE* f = NULL;
        fopen_s(&f, AvatarAddStr.c_str(), "rb");
        if (f != NULL && dataFrom != NULL)
        {
            fread(dataFrom, dwFileSize, 1, f);
        }

        //为转换后的字符串申请内存
        BYTE* dataTo = new BYTE[dwFileSize * 2 + 1];
        DWORD dataToSize = mysql_real_escape_string(mysql, (char*)dataTo, (char*)dataFrom, dwFileSize);

        //为整个sql语句申请内存
        char* pSql = new char[dwFileSize * 2 + 256 + 40];
        //拼接sql语句（pSql目的字符串，szSql拼接主体字符串，dataTo头像字符，ID编号字符)
        sprintf(pSql, "INSERT INTO `mtest`.`usertable` (`ID`, `name`, `sort`,`avatar`) VALUES ('%d', '%s', '%s','%s');",
            LineID->text().toInt(), LineName->text().toLatin1().data(), ButtonChoeseSort->text().toLatin1().data(), dataTo);

        //执行mysql插入操作
        mysql_real_query(mysql, pSql, strlen(pSql));


        if (f) fclose(f), f = NULL;
        if (dataFrom) delete[] dataFrom;
        if (dataTo) delete[] dataTo;
        if (pSql) delete pSql;
        close();
    }
    
}

void AddUser::choeseSort()
{
    if (Ssort == "user")
    {
        Ssort = "admin";
    }
    else
    {
        Ssort = "user";
    }

    ButtonChoeseSort->setText(Ssort);
}

bool AddUser::lineJudge()
{
    if (LineName->text() == "" || LineID->text() == "" || LinePassword->text() == "")
        return false;
    return true;
}

void AddUser::addUserAdmin()
{
    //为整个sql语句申请内存
    char sqlStr[250];

    //拼接sql语句 创建登录名为LineID，密码为LinePassword的数据库用户
    sprintf(sqlStr, "CREATE USER '%d'@'%%' IDENTIFIED BY '%s';" , LineID->text().toInt(), LinePassword->text().toLatin1().data());
    mysql_query(mysql, sqlStr);

    sprintf(sqlStr, "GRANT SELECT, INSERT, UPDATE, CREATE, INDEX, SHOW VIEW, CREATE USER ON * .*TO '%d'@'%%' IDENTIFIED BY '%s' REQUIRE NONE WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0; ", LineID->text().toInt(), LinePassword->text().toLatin1().data());
    mysql_query(mysql, sqlStr);
}

void AddUser::addUserUser()
{
    //为整个sql语句申请内存
    char sqlStr[230];

    sprintf(sqlStr, "CREATE USER '%d'@'%%' IDENTIFIED BY '%s';", LineID->text().toInt(), LinePassword->text().toLatin1().data());
    mysql_query(mysql, sqlStr);

    sprintf(sqlStr, "GRANT SELECT, INSERT, UPDATE, CREATE, DROP, INDEX ON *.* TO '%d'@'%%' IDENTIFIED BY '%s' REQUIRE NONE WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0;", LineID->text().toInt(), LinePassword->text().toLatin1().data());
    mysql_query(mysql, sqlStr);
}