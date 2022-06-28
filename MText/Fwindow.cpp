#include "fwindow.h"


Fwindow::Fwindow()
{
    setWindowIcon(QIcon("./image/V_V.ico"));
    this->installEventFilter(this);
	//show();所有组件加载完之后再show
}

void Fwindow::addmysql(MYSQL* addmysql)
{
	mysql = addmysql;
}

void Fwindow::fixwindow(string f_ID)
{}

void Fwindow::CreateAddAvatar()
{
	new AddAvatar(mysql,ID);
}

void Fwindow::repairUserName()
{
    new RepairUserName(mysql,ID);
}

bool Fwindow::eventFilter(QObject* obj, QEvent* ev)
{
    /*判断发生事件的是否为主窗口*/
    if (obj == this) {
        /*判断事件的类型是否为关闭事件*/
        if (ev->type() == QEvent::Close) {
            qApp->quit();//主窗口关闭事件,程序退出,其他窗口将被关闭
            return true; //返回true代表事件已被处理不需要向下传递，返回false代表事件未被处理需要向下传递由别的组件处理
        }
    }
    /*不是我们关心的事件，交由QMainWindow的事件过滤器处理*/
    return QMainWindow::eventFilter(obj, ev);
}
