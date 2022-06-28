#pragma once
#include <qwidget.h>
#include <mysql.h>
#include <string>
#include <qlineedit.h>
#include <QTextEdit.h>
#include <QListWidget.h>
#include <qpushbutton.h>
using namespace std;

class TalkTable :
    public QWidget
{
public:
    TalkTable(MYSQL* _mySql,string _talkTable,string _ID);
    void fillingWindow();
    void getMessage();
private:
    MYSQL* mySql_;
    QTextEdit* lineInputBox_;
    QListWidget* outputBox_;
    QPushButton* btnSend_;
    QPushButton* btnClear_;
    string talkTable_;
    string ID_;
};

