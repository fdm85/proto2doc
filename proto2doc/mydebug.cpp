#include <QFile>
#include <QStandardPaths>
#include "QDebug"
#include "mydebug.h"

myDebug::myDebug(QObject *parent, QString filename_c) :
  QObject(parent)
{

}

QString myDebug::debug_filename;

myDebug::~myDebug()
{
  debug_file.close();
}

void myDebug::dbg(QString text)
{
  QString path = QStandardPaths::displayName(QStandardPaths::DesktopLocation);
  QFile file(myDebug::debug_filename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);
  out << text;

  file.close();
}
