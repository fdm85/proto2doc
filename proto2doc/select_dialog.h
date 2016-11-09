#ifndef SELECT_DIALOG_H
#define SELECT_DIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include "entry.h"

namespace Ui {
  class select_dialog;
}

class select_dialog : public QDialog
{
  Q_OBJECT

public:
  explicit select_dialog(QWidget *parent = 0,
                         QStringList *responsibles = NULL,
                         QList<QTreeWidgetItem *> *topicList = NULL );

  QList<entry *> *get_filters_resp();
  QList<entry *> *get_filters_topics();
  ~select_dialog();

private:
  Ui::select_dialog *ui;
  QWidget container_resp;
  QVBoxLayout* containerLayout_resp;
  QWidget container_topic;
  QVBoxLayout* containerLayout_topic;

};

#endif // SELECT_DIALOG_H
