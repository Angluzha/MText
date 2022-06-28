#include "MText.h"
#include <mysql.h>
#include <QtWidgets/QApplication>
#include "AddAvatar.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MYSQL mysql;	//数据库句柄
    //初始化数据库
    mysql_init(&mysql);
    //设置字符编码
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
    
    MText w;
    w.AddMySql(&mysql);
    w.setWindowTitle("V_V实验室");
    w.resize(QSize(400, 300));
    w.setFixedSize(w.width(), w.height());
    w.setWindowIcon(QIcon("./image/V_V.ico"));
    w.show();

    //关闭数据库
    mysql_close(&mysql);
    return a.exec();
}
