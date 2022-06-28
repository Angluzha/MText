#pragma once
#include <qlistwidget.h>
#include <string>
using namespace std;

class FriendList :public QListWidgetItem
{
public:
	FriendList();
	void setCanSee();
	void setFriendClass(string _friendClass);
	void setTalkTable(string _talkTable);
	string getFriendClass();
	string getTalkTable();
public:
	bool canSee_;
private:
	string ID_;
	string friendClass_;
	string talkTable_;
};

