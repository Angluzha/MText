#pragma once
#include "Fwindow.h"
#include <fstream>
#include <sstream>
#include "TalkTable.h"
#include "AddFriend.h"

class UserWindow :
    public Fwindow
{
public:
    UserWindow(MYSQL *_mySql,string _ID);
    void fillingWindow();
    void addFriendList();
public slots:
    void btnRefresh();
    void reWindow();
    void createTalkTable(QListWidgetItem* item);
    void addFriend();
private:
    QListWidget *friendWidget_;
    QPushButton* btnAddFriend_;

};

