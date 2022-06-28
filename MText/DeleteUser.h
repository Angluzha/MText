#pragma once
#include <qwidget.h>
#include <mysql.h>
#include "QPushButton"
#include "qlineedit.h"

class DeleteUser :public QWidget
{
    Q_OBJECT
public:
    DeleteUser(MYSQL* _mySql);
private slots:
    void yesDelete();
private:
    QPushButton* btnYes_;
    QLineEdit* lineUserName_;
    MYSQL* mySql_;
};

