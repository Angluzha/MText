#pragma once
//UI控件组件
#include <QtWidgets/QMainWindow>
#include "QPushButton"
#include "qlineedit.h"
#include "qlabel.h"
#include "qstring.h"
#include <QMovie>
//字符串组件
#include <string>
#include <iostream>
//子类窗口组件
#include "fwindow.h"
#include "adminwindow.h"
#include "uesrWindow.h"
//数据库组件
#include <mysql.h>

using namespace std;

class MText : public QMainWindow
{
    Q_OBJECT

public:
    MText(QWidget *parent = Q_NULLPTR);
    void SqlLink(string ID,string Password);
    void AddMySql(MYSQL *addmysql);
public slots:
    void LoginCilck();
private:
    QPushButton *ButtonLogin;
    QPushButton* btnClose_;
    QLineEdit   *LineEditID;
    QLineEdit   *LineEditPassword;
    QLabel      *LabelPNG;
    Fwindow     *SonWindow;
    MYSQL       * mysql;
};
