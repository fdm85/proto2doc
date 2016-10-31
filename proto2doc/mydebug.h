#ifndef MYDEBUG_H
#define MYDEBUG_H

#include <QObject>
#include <QFile>
#include <QTextStream>


class myDebug : public QObject
{
    Q_OBJECT
public:
    explicit myDebug(QObject *parent = 0, QString filename_c = "none.txt");
    ~myDebug();

    static void dbg(QString text);
  static QString debug_filename;

private:
    QFile debug_file;
    QTextStream out;


signals:

public slots:
};

#endif // MYDEBUG_H
