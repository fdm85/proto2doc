#ifndef DOCUMENT_WRITER_H
#define DOCUMENT_WRITER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QTreeWidget>
#include <QList>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>
#include "entry.h"


class document_writer : public QObject
{
  Q_OBJECT
public:
  explicit document_writer(QObject *parent = 0,
                           QString file_path = "");
  ~document_writer();
  void add_headline(QString headline = "");
  void add_content(entry *filter = NULL,
                   QTreeWidget *treeWidget = NULL,
                   entry::member_specifier = entry::_Titel);
  static entry* cast_row_change(QTreeWidgetItem *item);
  void dump_all(QTreeWidget *treeWidget = NULL);
  void add_timetable(QTableWidget *table = NULL);


private:
  QFile output_file;
  QTextStream *out;
  void write_entry(entry *entry_c);
  void write_table(QStringList table_content, int *max_width);
  bool open_file(QString file_path);
  static entry* cast_row(QTreeWidgetItem *item, bool change = false);
  void write_treeItem(QTreeWidgetItem *item);
signals:

public slots:
};

#endif // DOCUMENT_WRITER_H
