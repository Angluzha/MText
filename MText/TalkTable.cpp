#include "TalkTable.h"

string Time2Str()
{
	time_t tm;
	time(&tm); //获取time_t类型的当前时间
	char tmp[64];

	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&tm));
	return tmp;
}

TalkTable::TalkTable(MYSQL* _mySql, string _talkTable,string _ID)
{
	mySql_ = _mySql;
	talkTable_ = _talkTable;
	ID_ = _ID;

	if (ID_ == talkTable_.substr(0, 6))
	{
		friendID_ = talkTable_.substr(10, 15);
	}
	else
	{
		friendID_ = talkTable_.substr(0, 6);
	}

	MYSQL_RES* resultName = NULL;
	MYSQL_ROW rowName = nullptr;

	string sqlW="SELECT name FROM `usertable` WHERE `ID` = "+friendID_;
	mysql_query(mySql_, sqlW.c_str());
	resultName = mysql_store_result(mySql_);
	rowName = mysql_fetch_row(resultName);

	setWindowTitle(rowName[0]);

	outputBox_ = new QListWidget(this);
	outputBox_->setGeometry(0, 0, 600, 300);
	outputBox_->setStyleSheet("background-color:rgb(204,204,204)");
	outputBox_->setFlow(QListView::TopToBottom);
	outputBox_->setIconSize(QSize(50, 50));
	outputBox_->setWordWrap(true);

	lineInputBox_ = new QTextEdit(this);
	lineInputBox_->setGeometry(0,300,600,100);
	lineInputBox_->setPlaceholderText("请输入...");
	lineInputBox_->setStyleSheet("background-color:rgb(204,204,204)");

	btnSend_ = new QPushButton("发送",this);
	btnSend_->move(510,370);
	QObject::connect(btnSend_, SIGNAL(clicked(void)), this, SLOT(sendMessage()));

	btnClear_ = new QPushButton("清除", this);
	btnClear_->move(435,370);
	QObject::connect(btnClear_, SIGNAL(clicked(void)), this, SLOT(clearText()));

	resize(QSize(600, 400));
	setFixedSize(this->width(), this->height());//禁止修改窗口大小
	show();

	fillingWindow();
}
void TalkTable::fillingWindow()
{
	getMessage();
}
void TalkTable::getMessage()
{
	outputBox_->clear();
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = nullptr;
	char sql[100];
	sprintf(sql, "SELECT * FROM `%s`;", talkTable_.c_str());
	mysql_real_query(mySql_, sql, strlen(sql));
	result = mysql_store_result(mySql_);
	//循环获取每一行数据数据
	if(result!=NULL)
	{
		while ((row = mysql_fetch_row(result)) != NULL)
		{
			QListWidgetItem* Item = new QListWidgetItem();
			Item->setTextAlignment(Qt::AlignLeft | Qt::AlignLeft);

			char IDAddStr[30];
			sprintf(IDAddStr, "./image/Avatar/%s.png",row[0]);

			Item->setSizeHint(QSize(280, 65));
			Item->setIcon(QIcon(IDAddStr));//QIcon("./image/Avatar/100001.png")
			
			//char testStr[500];
			//sprintf(testStr, "%s\n%s", row[2],row[1]);//"%s       %s\n%s",row[0], row[3],row[1]
			string testStr = row[2];
			testStr += "\n";
			testStr += row[1];
			Item->setText(QString::fromStdString(testStr));

			outputBox_->addItem(Item);
		}
	}
	//修改自身列表News为0
	sprintf(sql, "UPDATE `mtest`.`%sFriend` SET `News` = '0' WHERE `%sFriend`.`FriendID` = %s;", ID_.c_str(),ID_.c_str(),friendID_.c_str());
	mysql_query(mySql_,sql);
}

void TalkTable::sendMessage()
{
	string message;//INSERT INTO `mtest`.`100001talk100004` (`ID`, `Text`, `Date`) VALUES ('100004', 'hello hello', '2022-06-29 12:32:45');
	message = "INSERT INTO `mtest`.`";
	message += talkTable_;
	message += "` (`ID`, `Text`, `Date`) VALUES ('";
	message += ID_;
	message += "', '";
	message += lineInputBox_->toPlainText().toStdString();
	message += "', '";
	message += Time2Str();
	message += "');";

	mysql_query(mySql_, message.c_str());
	lineInputBox_->clear();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = nullptr;
	char sql[100];
	sprintf(sql, "SELECT News FROM `%sFriend` WHERE `FriendID` = %s;", friendID_.c_str(), ID_.c_str());
	mysql_query(mySql_, sql);
	result = mysql_store_result(mySql_);
	row = mysql_fetch_row(result);
	int News = atoi(row[0]);
	News++;
	sprintf(sql, "UPDATE `mtest`.`%sFriend` SET `News` = '%d' WHERE `%sFriend`.`FriendID` = %s;", friendID_.c_str(),News, friendID_.c_str(), ID_.c_str() );
	mysql_query(mySql_, sql);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	fillingWindow();
	outputBox_->setCurrentRow(outputBox_->count() - 1);

}

void TalkTable::clearText()
{
	lineInputBox_->clear();
	fillingWindow();
	outputBox_->setCurrentRow(outputBox_->count() - 1);
}