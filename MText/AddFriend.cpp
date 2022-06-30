#include "AddFriend.h"

AddFriend::AddFriend(MYSQL *_mySql,string _ID)
{
	mySql_ = _mySql;
	ID_ = _ID;

	lineAddID_ = new QLineEdit(this);
	lineAddID_->move(150,20);


	btnAddYes_ = new QPushButton("添加好友", this);
	btnAddYes_->move(100,160);
	QObject::connect(btnAddYes_, SIGNAL(clicked(void)), this, SLOT(btnYes()));

	show();
	resize(QSize(300,200));
}

void AddFriend::btnYes()
{
	string sqlW = "SELECT * FROM `usertable` WHERE `ID` ="+ lineAddID_->text().toStdString();
	
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = nullptr;
	mysql_query(mySql_,sqlW.c_str());
	result = mysql_store_result(mySql_);
	row = mysql_fetch_row(result);

	if (row == NULL)
	{
		lineAddID_->clear();
		lineAddID_->setText("该用户不存在");
	}
	else
	{
		string talkTableName;
		if (atoi(ID_.c_str()) > atoi(lineAddID_->text().toLatin1()))
		{
			talkTableName = lineAddID_->text().toStdString();
			talkTableName += "talk";
			talkTableName += ID_;
		}
		else
		{
			talkTableName = ID_;
			talkTableName += "talk";
			talkTableName += lineAddID_->text().toStdString();
		}
		//
		char sqlC[200];
		//添加好友到自身Frieng表
		sprintf(sqlC,"INSERT INTO `mtest`.`%sFriend` (`FriendID`, `FriendClass`, `News`, `talktable`) VALUES ('%s', '好友', '0', '%s');",ID_.c_str(), lineAddID_->text().toLatin1().data(), talkTableName.c_str());
		mysql_query(mySql_, sqlC);
		//添加自身到好友Friend表
		sprintf(sqlC, "INSERT INTO `mtest`.`%sFriend` (`FriendID`, `FriendClass`, `News`, `talktable`) VALUES ('%s', '好友', '0', '%s');", lineAddID_->text().toLatin1().data(), ID_.c_str(), talkTableName.c_str());
		mysql_query(mySql_, sqlC);

		//创建好友表
		sprintf(sqlC, "CREATE TABLE `mtest`.`%s` ( `ID` INT(10) NOT NULL COMMENT '发言人ID' , `Text` TEXT NOT NULL COMMENT '发言内容' , `Date` DATETIME NOT NULL COMMENT '发言日期' ) ENGINE = InnoDB; ", talkTableName.c_str());
		mysql_query(mySql_, sqlC);

		//授予好友表权限
		sprintf(sqlC, "GRANT Delete, Insert, Select, Update ON TABLE `mtest`.`%s` TO `%s`@``;", talkTableName.c_str(), ID_.c_str());
		mysql_query(mySql_, sqlC);
		//授予好友表权限
		sprintf(sqlC, "GRANT Delete, Insert, Select, Update ON TABLE `mtest`.`%s` TO `%s`@``;", talkTableName.c_str(), lineAddID_->text().toLatin1().data());
		mysql_query(mySql_, sqlC);

		close();
	}
}