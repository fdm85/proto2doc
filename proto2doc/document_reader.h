#ifndef DOCUMENT_READER_H
#define DOCUMENT_READER_H

#include <QObject>
#include <QTreeWidget>
#include <QFile>
#include <QList>
#include <QStringList>
#include <QDate>
#include "entry.h"
#include "xml_dialog.h"
#include "gui_tools.h"

class document_reader : public QObject
{
  Q_OBJECT

  typedef struct temp_entry
  {
    QString titel;
    QString datum;
    QString verantwortlich;
    QString typ;
    QString inhalt;
    QString topic;
  } temp_entry_t;

public:
  explicit document_reader(QObject *parent = 0,
                           QTreeWidget *treeWidget_c = NULL,
                           QList<QTreeWidgetItem *> *topicList_c = NULL,
                           QStringList *responsibleList_c = NULL);

  void read_document(QString filename = QString(""));


  void ab(QString line, int length, int end, int start);
  
private:
  QTreeWidget *treeWidget;
  QList<QTreeWidgetItem *> *topicList;
  QStringList *responsibleList;
  temp_entry_t tmp_entry;
  entry cast_tmp_entry( temp_entry_t tmp_entry_c);

  /* line casting */
  int start, length, end;
  entry::member_specifier lastEntry;





  void process_line(QStringList);
  void add_topic(entry);
  void add_sub(entry);
  void read_content(QString line, int end, int length, int start);
  
  QString resolve_delimiters(QString line);
  
signals:

public slots:
};

#endif // DOCUMENT_READER_H
