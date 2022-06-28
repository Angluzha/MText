#pragma once
#include <qwidget.h>
#include <mysql.h>
#include "QPushButton"
#include "qlineedit.h"
#include <string>
using namespace std;

class RepairUserName :public QWidget
{
    Q_OBJECT
public:
    RepairUserName(MYSQL* _mySql,string _ID);
private slots:
    void yes();
private:
    QPushButton* btnYes_;
    QLineEdit* lineUserName_;
    string ID_;
    MYSQL* mySql_;
};

