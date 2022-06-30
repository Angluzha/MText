#include "RepairUserName.h"
RepairUserName::RepairUserName(MYSQL* _mySql,string _ID)
{
	ID_ = _ID;
	lineUserName_ = new QLineEdit("请输入名称....",this);
	lineUserName_->setGeometry(0,20,200,25);

	btnYes_ = new QPushButton("确定",this);
	btnYes_->move(60,70);
	QObject::connect(btnYes_, SIGNAL(clicked(void)), this, SLOT(yes()));
	mySql_ = _mySql;

	resize(QSize(200, 100));
	setFixedSize(this->width(), this->height());//禁止修改窗口大小
	show();
	setWindowIcon(QIcon("./image/V_V.ico"));
	setWindowTitle(" ");
}
void RepairUserName::yes()
{
	//获取结果集
	//char sqlW[100];
	//sprintf(sqlW,"UPDATE `mtest`.`usertable` SET `name` = '%s' WHERE `usertable`.`ID` = %s", lineUserName_->text().toLatin1().data(),ID_.c_str());
	string sqlW ="UPDATE `mtest`.`usertable` SET `name` = '";
	sqlW += lineUserName_->text().toStdString();
	sqlW += "' WHERE `usertable`.`ID` = ";
	sqlW += ID_;
	sqlW += ";";

	mysql_query(mySql_, sqlW.c_str());

	close();
}