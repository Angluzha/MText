#pragma once
#include <QtWidgets/QMainWindow>
#include "QPushButton"
#include <qboxlayout.h>
#include <QListWidget>
#include "qlineedit.h"
#include "qlabel.h"
#include "qstring.h"
#include <string>
#include <iostream>
#include "AddAvatar.h"
#include <mysql.h>
#include <QApplication>
#include "RepairUserName.h"

using namespace std;

class Fwindow : public QMainWindow
{
    Q_OBJECT

public:
    Fwindow();
    virtual void fixwindow(string ID);
    void addmysql(MYSQL *addmysql);
    bool eventFilter(QObject* obj, QEvent* ev);//窗口关闭时，终止程序
public slots:
    void CreateAddAvatar();
    void repairUserName();
public:
    QPushButton* ButtonUpataAvatar;
    QPushButton* btnRepair_;
    QLabel* LabelPNG;
    QLabel *LabelID;
    QLabel* LabelName;
    MYSQL* mysql;
    string ID;
};
 