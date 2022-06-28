#pragma once
#include <qwidget.h>
#include <mysql.h>
#include <string>
#include <qlineedit.h>
#include <QTextEdit.h>
using namespace std;

class TalkTable :
    public QWidget
{
public:
    TalkTable(MYSQL* _mySql,string _talkTable);
private:
    MYSQL* mySql_;
    QTextEdit* lineInputBox_;
};

