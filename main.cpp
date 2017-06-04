#include <QCoreApplication>
#include "sqlitedatabase.h"
#include "server.h"

static void AutoRunWithSystem(bool bAutoRun)
{
    //HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                   QSettings::NativeFormat);

    if (bAutoRun)
    {
         QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
        //strAppPath.replace(QChar('/'),QChar('\\'),Qt::CaseInsensitive);
        reg->setValue("WeinberyServer", strAppPath);
    }
    else
    {
        reg->setValue("WeinberyServer", "");
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /// 开机自启动
    AutoRunWithSystem(true);
    /// 创建数据库连接
    if (!createConnection())
    {
        return -1;
    }
    /// 服务器启动
    Server server;
    server.startServer();

    return a.exec();
}
