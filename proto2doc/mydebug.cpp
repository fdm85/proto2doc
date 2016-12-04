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
  QString path = QDir::homePath() + "/proto2doc";
  QFile file(path + myDebug::debug_filename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    return;

  QTextStream out(&file);
  out.setCodec("UTF-8");
  out << text;

  qDebug() << text;

  file.close();
}
