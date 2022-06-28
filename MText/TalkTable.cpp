﻿#include "TalkTable.h"

TalkTable::TalkTable(MYSQL* _mySql, string _talkTable,string _ID)
{
	mySql_ = _mySql;
	talkTable_ = _talkTable;
	ID_ = _ID;

	outputBox_ = new QListWidget(this);
	outputBox_->setGeometry(0, 0, 600, 300);
	outputBox_->setStyleSheet("background-color:rgb(204,204,204)");
	outputBox_->setFlow(QListView::TopToBottom);

	lineInputBox_ = new QTextEdit(this);
	lineInputBox_->setGeometry(0,300,600,100);
	lineInputBox_->setPlaceholderText("请输入...");
	lineInputBox_->setStyleSheet("background-color:rgb(204,204,204)");

	btnSend_ = new QPushButton("发送",this);
	btnSend_->move(510,370);
	btnClear_ = new QPushButton("清除", this);
	btnClear_->move(435,370);
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
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = nullptr;
	char sql[40];
	sprintf(sql, "SELECT * FROM `%s`;", talkTable_.c_str());
	mysql_real_query(mySql_, sql, strlen(sql));
	result = mysql_store_result(mySql_);
	//循环获取每一行数据数据

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		QListWidgetItem* Item = new QListWidgetItem();
		Item->setTextAlignment(Qt::AlignRight | Qt::AlignHCenter);
		char IDAddStr[30];
		sprintf(IDAddStr, "./image/Avatar/%s.png", "100003");

		Item->setSizeHint(QSize(280, 65));
		Item->setIcon(QIcon(IDAddStr));//QIcon("./image/Avatar/100001.png")
		Item->setText("Textaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		QWidget *widget={};
		widget->resize(QSize(100,100));

		widget->show();

		outputBox_->setItemWidget(Item,widget);
	}
}