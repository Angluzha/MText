#pragma once
#include <qwidget.h>
#include <string>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <mysql.h>
using namespace std;

class AddFriend :
    public QWidget
{
    Q_OBJECT
public:
    AddFriend(MYSQL *_mySql,string _ID);
public slots:
    void btnYes();
private:
    QLineEdit *lineAddID_;
    QPushButton *btnAddYes_;
    string ID_;
    MYSQL* mySql_;
};

