#include "AddAvatar.h"


AddAvatar::AddAvatar(MYSQL* addMysql,string f_ID, QWidget* parent) : QWidget(parent)
{
    ID = f_ID;
    //添加上传按钮，按下即可更改头像
    UpdataButton = new QPushButton("更新头像",this);
    UpdataButton->move(150,160);
    UpdataButton->setDisabled(true);
    QObject::connect(UpdataButton, SIGNAL(clicked(void)), this, SLOT(UpdataAvatar()));

    //添加头像预览图片，无图片时为+号
    UpdataLabel = new QLabel(this);
    UpdataLabel->setPixmap(QPixmap("./image/+.png"));
    UpdataLabel->setGeometry(150,50,100,100);
    UpdataLabel->setScaledContents(true);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mysql = addMysql;
    mainLayout->addStretch();
    resize(QSize(400,300));
    setFixedSize(width(), height());

    setWindowTitle("拖入图片作为头像");
    show();
    setWindowIcon(QIcon("./image/V_V.ico"));
    this->setAcceptDrops(true); //必须设置，不然无法接收拖放事件
}
AddAvatar::~AddAvatar()
{

}

void AddAvatar::dragEnterEvent(QDragEnterEvent* event) //拖动文件到窗口，触发
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction(); //事件数据中存在路径，方向事件
    }
    else
    {
        event->ignore();
    }
}

void AddAvatar::dragMoveEvent(QDragMoveEvent* event) //拖动文件到窗口移动文件，触发
{

}

void AddAvatar::dropEvent(QDropEvent* event) //拖动文件到窗口释放文件，触发
{
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QList<QUrl> urls = mimeData->urls();
        AvatarAdd = urls.at(0).toLocalFile();
        UpdataLabel->setPixmap(QPixmap(AvatarAdd));
        UpdataButton->setDisabled(false);
    }
}

void AddAvatar::UpdataAvatar()
{
    QFile file(AvatarAdd);
    file.open(QIODevice::ReadOnly);
    DWORD dwFileSize =file.size();//获取文件长度
    QByteArray array = file.readAll(); //读取文件数据
    file.close();

    BYTE* dataFrom = NULL;
    dataFrom = new BYTE[dwFileSize];
    ZeroMemory(dataFrom, dwFileSize);

    string AvatarAddStr = string((const char*)AvatarAdd.toLocal8Bit());//QString转String

    FILE* f = NULL;
    fopen_s(&f, AvatarAddStr.c_str(), "rb");
    if (f != NULL && dataFrom != NULL)
    {
        fread(dataFrom, dwFileSize, 1, f);
    }

    //为转换后的字符串申请内存
    BYTE* dataTo = new BYTE[dwFileSize * 2 + 1];
    DWORD dataToSize = mysql_real_escape_string(mysql, (char*)dataTo, (char*)dataFrom, dwFileSize);

    //为整个sql语句申请内存
    char* pSql = new char[dwFileSize * 2 + 256];
    char szSql[] = "UPDATE `mtest`.`usertable` SET `avatar` = '%s'WHERE `usertable`.`ID` = %s";
    sprintf(pSql, szSql, dataTo,ID.c_str());//拼接sql语句（pSql目的字符串，szSql拼接主体字符串，dataTo头像字符，ID编号字符)

    //插入操作
    mysql_real_query(mysql, pSql, strlen(pSql));


    if (f) fclose(f), f = NULL;
    if (dataFrom) delete[] dataFrom;
    if (dataTo) delete[] dataTo;
    if (pSql) delete pSql;
    close();
}