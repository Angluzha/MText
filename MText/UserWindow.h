#pragma once
#include "Fwindow.h"
#include <fstream>
#include <sstream>

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
    void createTalkTable(QListWidgetItem* item);
private:
    QListWidget *friendWidget_;

};

