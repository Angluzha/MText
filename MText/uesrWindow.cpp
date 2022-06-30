#include "uesrWindow.h"
void bolbCPNG(char* m_row, unsigned long length, string avatarAddStr);

uesrWindow::uesrWindow(MYSQL* _mySql, string _ID)
{
	mysql = _mySql;
	ID = _ID;

	friendWidget_ = new QListWidget(this);
	friendWidget_->setViewMode(QListWidget::ListMode);//显示模式
	friendWidget_->setIconSize(QSize(50, 50));//设置图片大小
	friendWidget_->setResizeMode(QListView::Adjust);//适应布局调整
	friendWidget_->setMovement(QListView::Static);//不能移动
	friendWidget_->setGeometry(0, 130, 300, 470);
	//QObject::connect(friendWidget_, &QListWidget::itemClicked, this, &uesrWindow::createTalkTable);//

	LabelID = new QLabel(this);
	LabelID->setText(("ID：" + ID).c_str());
	LabelID->move(110, 60);
	LabelID->setStyleSheet("QLabel{font:15px;color:black;background-color:rgb(f9,f9,f9);}");

	LabelName = new QLabel(this);
	LabelName->setGeometry(110, 20, 180, 40);
	LabelName->setStyleSheet("QLabel{font:30px;color:black;background-color:rgb(f9,f9,f9);}");

	LabelPNG = new QLabel(this);
	LabelPNG->setGeometry(20, 10, 75, 75);//设置文本框大小
	LabelPNG->setScaledContents(true);//图片自适应大小
	LabelPNG->show();

	ButtonUpataAvatar = new QPushButton("修改头像", this);
	ButtonUpataAvatar->setGeometry(0, 90, 60, 40);
	ButtonUpataAvatar->setStyleSheet("QPushButton{font:10px;}");
	QObject::connect(ButtonUpataAvatar, SIGNAL(clicked(void)), this, SLOT(CreateAddAvatar()));

	btnRepair_ = new QPushButton("修改昵称", this);
	btnRepair_->setGeometry(60, 90, 60, 40);
	btnRepair_->setStyleSheet("QPushButton{font:10px;}");
	QObject::connect(btnRepair_, SIGNAL(clicked(void)), this, SLOT(repairUserName()));

	btnAddFriend_ = new QPushButton("添加好友", this);
	btnAddFriend_->setGeometry(120, 90, 60, 40);
	btnAddFriend_->setStyleSheet("QPushButton{font:10px;}");
	QObject::connect(btnAddFriend_, SIGNAL(clicked(void)), this, SLOT(addFriend()));

	btnRefresh_ = new QPushButton("刷新界面", this);
	btnRefresh_->setGeometry(180, 90, 60, 40);
	btnRefresh_->setStyleSheet("QPushButton{font:10px;}");
	QObject::connect(btnRefresh_, SIGNAL(clicked(void)), this, SLOT(reWindow()));

	fillingWindow();
	setWindowTitle("V_V网络");

	resize(QSize(300, 600));
	setFixedSize(this->width(), this->height());//禁止修改窗口大小
}

void uesrWindow::fillingWindow()
{
	char IDAddStr[30];//地址最大长度为35位
	sprintf(IDAddStr, "./image/Avatar/%s.png", ID.c_str());

	//获取结果集
	MYSQL_RES* result = NULL;
	//执行查询
	char sql[70];
	sprintf(sql, "SELECT avatar,name FROM `usertable` WHERE ID =  %s", ID.c_str());
	mysql_real_query(mysql, sql, strlen(sql));
	result = mysql_store_result(mysql);

	//循环获取每一行数据数据
	MYSQL_ROW row = nullptr;
	row = mysql_fetch_row(result);
	unsigned long length = mysql_fetch_lengths(result)[0];
	bolbCPNG(row[0], length, IDAddStr);

	LabelName->setText(row[1]);
	LabelPNG->setPixmap(QPixmap(IDAddStr));//

	addFriendList();

	//释放资源-结果集
	if (result)mysql_free_result(result), result = nullptr;
}
void uesrWindow::addFriendList()
{
	friendWidget_->clear();
	//获取结果集
	MYSQL_RES* resultID = NULL;
	MYSQL_ROW rowFriend = nullptr;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = nullptr;

	//执行查询
	char sql[80];//char sql[] = "SELECT ID, name  ,avatar FROM `usertable`";
	sprintf(sql, "SELECT  FriendID ,news,FriendClass,talktable FROM `%sFriend`;", ID.c_str());
	mysql_real_query(mysql, sql, strlen(sql));
	resultID = mysql_store_result(mysql);
	//循环获取每一行数据数据
	while ((rowFriend = mysql_fetch_row(resultID)) != NULL)
	{
		sprintf(sql, "SELECT name  ,avatar FROM `usertable` WHERE ID = %s", rowFriend[0]);// rowFriend[0]

		mysql_real_query(mysql, sql, strlen(sql));
		result = mysql_store_result(mysql);
		row = mysql_fetch_row(result);

		sprintf(sql, "昵称：%s \nID：%s                            %s条新信息", row[0], rowFriend[0], rowFriend[1]);

		QListWidgetItem* Item = new QListWidgetItem();
		Item->setStatusTip(rowFriend[3]);//找个容器存下talk表值

		//将Blob类型数据转换为png类型并保存到./image/Avatar/%s.png下以供使用
		char IDAddStr[30];
		sprintf(IDAddStr, "./image/Avatar/%s.png", rowFriend[0]);
		unsigned long length = mysql_fetch_lengths(result)[1];
		bolbCPNG(row[1], length, IDAddStr);

		Item->setSizeHint(QSize(280, 65));
		Item->setIcon(QIcon(IDAddStr));//QIcon("./image/Avatar/100001.png")
		Item->setText(sql);
		Item->setBackground(QPixmap("./image/远山B.png"));

		friendWidget_->addItem(Item);
		if (result)mysql_free_result(result), result = nullptr;
	}

	//释放资源-结果集
	if (resultID)mysql_free_result(resultID), resultID = nullptr;
}

void uesrWindow::reWindow()
{
	fillingWindow();
}

void uesrWindow::createTalkTable(QListWidgetItem* item)//
{
	string str = item->statusTip().toStdString();;
	new TalkTable(mysql, str, ID);
}

void bolbCPNG(char* m_row, unsigned long length, string avatarAddStr)
{
	char* buffer = new char[length + 1];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, m_row, length);

	stringstream pic_name;
	pic_name << avatarAddStr;
	ofstream outfile(pic_name.str(), ios::binary);
	outfile.write(buffer, length);

	if (buffer) delete[] buffer;
	cout << endl;
}

void uesrWindow::addFriend()
{
	new AddFriend(mysql,ID);
}