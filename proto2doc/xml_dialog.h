// xml_dialog.h
#ifndef XML_DIALOG
#define XML_DIALOG

#include "entry.h"
#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDebug>
#include <QLabel>
#include <QTextEdit>
#include <QCheckBox>
#include <QTreeWidgetItem>

/*
class QLineEdit;
class QSpinBox;
class QComboBox;
class QPushButton;
*/
class mark_dialog : public QDialog
{

  //typedef struct

public:
  mark_dialog( QWidget *parent = NULL, QList<QTreeWidgetItem *> *topicList = NULL );
  entry getEntry() const;

private:
  QLineEdit *o_Titel;
  QTextEdit *o_Inhalt;
  QLineEdit *o_Verantwortlich;
  QComboBox *o_specifier, *o_Topic;
  QSpinBox *o_Frist_day, *o_Frist_month, *o_Frist_year;
  QCheckBox *o_date_acitve;
  QPushButton *m_confirmButton, *m_cancelButton;
  QTreeWidgetItem *topic;
  QList<QTreeWidgetItem *> *o_topicList;

private slots:
  void mark_topic(int);



};

#endif // XML_DIALOG