#pragma once
#include "Fwindow.h"
#include <string>
#include <fstream>
#include <sstream>
#include "AddUser.h"
#include "DeleteUser.h"

class adminwindow :
    public Fwindow
{
    Q_OBJECT
public:
    adminwindow();
    ~adminwindow();
    void fixwindow(string ID);
    void fillingWindow();
public slots:
    void addUser();
    void choeseUser(QListWidgetItem* item);
    void deleteUserBtn();
    void refreshWindow();
private:
    QListWidget *BoxUser;
    QWidget     *WidgetUser;
    QWidget     *WidgetUserAdjustment;
    QPushButton *ButtonAddUser;
    QPushButton *btnDeleteUser_;
};

