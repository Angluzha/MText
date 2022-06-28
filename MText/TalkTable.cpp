#include "TalkTable.h"

TalkTable::TalkTable(MYSQL* _mySql, string _talkTable)
{
	mySql_ = _mySql;

	lineInputBox_ = new QTextEdit(this);
	lineInputBox_->setGeometry(0,400,800,200);
	lineInputBox_->setPlaceholderText("请输入...");

	resize(QSize(800, 600));
	setFixedSize(this->width(), this->height());//禁止修改窗口大小
	show();
}