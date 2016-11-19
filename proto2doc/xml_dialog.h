// xml_dialog.h
#ifndef XML_DIALOG
#define XML_DIALOG

#include "mydebug.h"
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
#include <QObject>

/*
class QLineEdit;
class QSpinBox;
class QComboBox;
class QPushButton;
*/
class mark_dialog : public QDialog
{
  Q_OBJECT
  //typedef struct

public:
  mark_dialog( QWidget *parent = NULL,
               QList<QTreeWidgetItem *> *topicList = NULL,
               QStringList *responibles = NULL,
               bool topic_b = true,
               int index = -1);
  entry getEntry() const;
  static void copydebug(entry *entry);

private:
  QLineEdit *o_Titel;
  QTextEdit *o_Inhalt;
  QComboBox *o_Verantwortlich;
  QComboBox *o_specifier, *o_Topic_i;
  QSpinBox *o_Frist_day, *o_Frist_month, *o_Frist_year;
  QCheckBox *o_date_acitve;
  QPushButton *m_confirmButton, *m_cancelButton;
  QTreeWidgetItem *topic;
  QList<QTreeWidgetItem *> *o_topicList;

private slots:
  void edit_responsible(int);




};

#endif // XML_DIALOG
