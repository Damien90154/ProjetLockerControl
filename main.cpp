#include <QApplication>
#include <QTextCodec>
#include "consolewindows.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    ConsoleWindows w;
   // w.setWindowState(w.windowState() ^ Qt::WindowFullScreen);
    w.show();
    
    return a.exec();
}
