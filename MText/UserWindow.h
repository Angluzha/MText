#pragma once
#include "Fwindow.h"
#include <fstream>
#include <sstream>
#include "FriendList.h"

class UserWindow :
    public Fwindow
{
public:
    UserWindow(MYSQL *_mySql,string _ID);
    void fillingWindow();
    void addFriendList();
public slots:
    void btnRefresh();
    void refreshWindow();
    void createTalkTable(FriendList* Item);
private:
    QListWidget *friendWidget_;

};

