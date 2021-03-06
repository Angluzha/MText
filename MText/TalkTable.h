#pragma once
#include <qwidget.h>
#include <mysql.h>
#include <string>
#include <qlineedit.h>
#include <QTextEdit.h>
#include <QListWidget.h>
#include <qpushbutton.h>
#include <time.h>
using namespace std;

class TalkTable :
    public QWidget
{
    Q_OBJECT
public:
    TalkTable(MYSQL* _mySql,string _talkTable,string _ID);
    void fillingWindow();
    void getMessage();
public slots:
    void sendMessage();
    void clearText();
private:
    MYSQL* mySql_;
    QTextEdit* lineInputBox_;
    QListWidget* outputBox_;
    QPushButton* btnSend_;
    QPushButton* btnClear_;
    string talkTable_;
    string ID_;
    string friendID_;
};

