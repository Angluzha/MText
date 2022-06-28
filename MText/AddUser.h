#pragma once

#include <QWidget>
#include <QDebug>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <qpushbutton.h>
#include <QMimeData>
#include <qlineedit.h>
#include <qfile.h>
#include <qlabel.h>
#include <QVBoxLayout>
#include <mysql.h>
#include <string.h>

using namespace std;

class AddUser :
    public QWidget
{
    Q_OBJECT
public:
    explicit AddUser(MYSQL*addMysql,QWidget* parent = nullptr);
    ~AddUser();
public:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent* event);
    bool lineJudge();
    void addUserAdmin();
    void addUserUser();
public slots:
    void insertUser();
    void choeseSort();
private:
    QString AvatarAdd;//头像的本机地址
    QString   Ssort; //权限文本
    QLabel* UpdataLabel;//头像文本框
    QLabel* TextLabel;
    QLabel *Tcreate;
    QPushButton* UpdataButton;//插入按钮
    QPushButton*ButtonChoeseSort;//权限改变
    QLineEdit   *LineID;
    QLineEdit   *LineName;
    QLineEdit* LinePassword; 

    MYSQL* mysql;
};

