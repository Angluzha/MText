#pragma once
#ifndef DRAGFILE_H
#define DRAGFILE_H

#include <QWidget>
#include <QDebug>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <qpushbutton.h>
#include <QMimeData>
#include <qfile.h>
#include <qlabel.h>
#include <QVBoxLayout>
#include <mysql.h>
#include <string.h>

using namespace std;

class AddAvatar :
    public QWidget
{
    Q_OBJECT
public:
    explicit AddAvatar(MYSQL *addMysql,string f_ID,QWidget* parent = nullptr);
    ~AddAvatar();
public:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent* event);
public slots:
    void UpdataAvatar();
private:
    QString AvatarAdd;
    QLabel *UpdataLabel;
    QLabel *TextLabel;
    QPushButton *UpdataButton;
    MYSQL* mysql;
    string ID;
};

#endif