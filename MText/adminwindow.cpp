#include "adminwindow.h"

void bolbToPNG(char* m_row, unsigned long length, string avatarAddStr);//查询图片结果 图片长度 图片本地存储地址

void addUserList(MYSQL* mysql, QListWidget* BoxParet)
{
	BoxParet->clear();
	//获取结果集
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = nullptr;

	//执行查询
	char sql[] = "SELECT ID, name  ,avatar FROM `usertable`";
	mysql_real_query(mysql, sql, strlen(sql));
	result = mysql_store_result(mysql);
	//循环获取每一行数据数据

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		char nameID[40];
		sprintf(nameID, "昵称：%s\nID：%s", row[1], row[0]);
		QListWidgetItem* Item = new QListWidgetItem();

		//将row[i+2]中的Blob类型数据转换为png类型并保存到./image/Avatar/%s.png下以供使用
		char IDAddStr[30];
		sprintf(IDAddStr, "./image/Avatar/%s.png", row[0]);
		unsigned long length = mysql_fetch_lengths(result)[2];
		bolbToPNG(row[2], length, IDAddStr);

		Item->setSizeHint(QSize(300, 65));
		Item->setIcon(QIcon(IDAddStr));//QIcon("./image/Avatar/100001.png")
		Item->setText(nameID);

		BoxParet->addItem(Item);
	}
}

adminwindow::adminwindow()
{
	WidgetUser = new QWidget(this);
	WidgetUser->setGeometry(0, 130, 400, 480);

	BoxUser = new QListWidget(WidgetUser);
	BoxUser->setViewMode(QListWidget::ListMode);//显示模式
	BoxUser->setIconSize(QSize(50, 50));//设置图片大小
	BoxUser->setResizeMode(QListView::Adjust);//适应布局调整
	BoxUser->setMovement(QListView::Static);//不能移动
	BoxUser->resize(400, 480);
	QObject::connect(BoxUser, &QListWidget::itemClicked, this, &adminwindow::choeseUser);

	WidgetUser->show();
	resize(QSize(300, 600));
	setFixedSize(this->width(), this->height());//禁止修改窗口大小
}
adminwindow::~adminwindow()
{
	setWindowTitle("111111111111111");
	exit(0);
}

void adminwindow::fixwindow(string f_ID)
{
	ID = f_ID;

	LabelID = new QLabel(this);
	LabelID->setText(("ID：" + ID).c_str());
	LabelID->move(110, 60);
	LabelID->setStyleSheet("QLabel{font:15px;color:black;background-color:rgb(f9,f9,f9);}");

	LabelName = new QLabel(this);
	LabelName->setGeometry(110, 20,180,40);
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

	ButtonAddUser = new QPushButton("添加用户", this);
	ButtonAddUser->setGeometry(120, 90, 60, 40);
	ButtonAddUser->setStyleSheet("QPushButton{font:10px;}");
	QObject::connect(ButtonAddUser, SIGNAL(clicked(void)), this, SLOT(addUser()));

	btnDeleteUser_ = new QPushButton("删除用户", this);
	btnDeleteUser_->setGeometry(180, 90, 60, 40);
	btnDeleteUser_->setStyleSheet("QPushButton{font:10px;}");
	QObject::connect(btnDeleteUser_, SIGNAL(clicked(void)), this, SLOT(deleteUserBtn()));

	btnRefresh_= new QPushButton("刷新界面", this);
	btnRefresh_->setGeometry(240, 90, 60, 40);
	btnRefresh_->setStyleSheet("QPushButton{font:10px;}");
	QObject::connect(btnRefresh_, SIGNAL(clicked(void)), this, SLOT(refreshWindow()));

	fillingWindow();
}

void bolbToPNG(char* m_row, unsigned long length, string avatarAddStr)
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

void adminwindow::choeseUser(QListWidgetItem* item)
{

}

void adminwindow::addUser()
{
	new AddUser(mysql);
}
void adminwindow::deleteUserBtn()
{
	new DeleteUser(mysql);
}

void adminwindow::fillingWindow()
{

	addUserList(mysql, BoxUser);
	
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
	bolbToPNG(row[0], length, IDAddStr);

	LabelName->setText(row[1]);
	LabelPNG->setPixmap(QPixmap(IDAddStr));//

	//释放资源-结果集
	if (result)mysql_free_result(result), result = nullptr;

}
void adminwindow::refreshWindow()
{
	fillingWindow();
}