#ifndef GLOBAL_H
#define GLOBAL_H

static void AutoRunWithSystem(bool bAutoRun)
{
    //HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
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
/*
static void AutoRunWithSystem(bool IsAutoRun, QString AppName)
{
    QString AppPath = QApplication::applicationFilePath();
    AppPath = AppPath.replace("/","\\");

    QSettings *reg=new QSettings(
                "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                QSettings::NativeFormat);

    if (IsAutoRun){reg->setValue(AppName,AppPath);}
    else{reg->setValue(AppName,"");}
}
*/
#endif // GLOBAL_H
