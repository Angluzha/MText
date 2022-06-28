#include "DeleteUser.h"
DeleteUser::DeleteUser(MYSQL* _mySql)
{
	lineUserName_ = new QLineEdit("请输入待删除用户ID号....", this);
	lineUserName_->setGeometry(0, 20, 200, 25);

	btnYes_ = new QPushButton("确定删除", this);
	btnYes_->move(60, 70);
	QObject::connect(btnYes_, SIGNAL(clicked(void)), this, SLOT(yesDelete()));
	mySql_ = _mySql;

	resize(QSize(200, 100));
	setFixedSize(this->width(), this->height());//禁止修改窗口大小
	show();
	setWindowIcon(QIcon("./image/V_V.ico"));
	setWindowTitle(" ");
}

void DeleteUser::yesDelete()
{

	close();
}