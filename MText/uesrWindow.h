#pragma once
#include "Fwindow.h"
#include <fstream>
#include <sstream>
#include "TalkTable.h"
#include "AddFriend.h"

class uesrWindow :public Fwindow
{
    Q_OBJECT
public:
    uesrWindow(MYSQL* _mySql, string _ID);
    void fillingWindow();
    void addFriendList();
public slots:
    void reWindow();
    void createTalkTable(QListWidgetItem* item);
    void addFriend();
private:
    QListWidget* friendWidget_;
    QPushButton* btnAddFriend_;
    QPushButton* btnRefresh_;
};

