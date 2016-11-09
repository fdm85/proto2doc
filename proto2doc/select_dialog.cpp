#include "select_dialog.h"
#include "ui_select_dialog.h"

select_dialog::select_dialog(QWidget *parent, QStringList *responsibles, QList<QTreeWidgetItem *> *topicList) :
  QDialog(parent),
  ui(new Ui::select_dialog)
{
  ui->setupUi(this);

  if(responsibles == NULL || topicList == NULL)
  {
    return;
  }

  containerLayout_resp = new QVBoxLayout();
  containerLayout_topic = new QVBoxLayout();
  container_resp.setLayout(containerLayout_resp);
  ui->scrollArea_resp->setWidget(&container_resp);

  for(int i = 0; i < responsibles->size(); ++i)
  {
    QCheckBox *checkbox = new QCheckBox(QString(responsibles->at(i)));
    containerLayout_resp->addWidget(checkbox);
  }

  container_topic.setLayout(containerLayout_topic);
  ui->scrollArea_topic->setWidget(&container_topic);

  for(int i = 0; i < topicList->size(); ++i)
  {
    QCheckBox *checkbox = new QCheckBox(QString(topicList->at(i)->text(0)));
    containerLayout_topic->addWidget(checkbox);
  }

}

QList<entry *> *select_dialog::get_filters_topics()
{
  QList<entry *> *result = new QList<entry *>;
  QList<QCheckBox*> list = ui->scrollArea_resp->findChildren<QCheckBox *>();

  list.clear();
  list = ui->scrollArea_topic->findChildren<QCheckBox *>();
  foreach(QCheckBox *w, list)
  {

    if(w->isChecked())
    {
      entry* filter = new entry( w->text(), QString("undef") ,
                                 QDate(), QString(""), entry::_undef, QString(""), -1 );
      result->append(filter);
    }
  }

  return result;
}

QList<entry *> *select_dialog::get_filters_resp()
{
  QList<entry *> *result = new QList<entry *>;
  QList<QCheckBox*> list = ui->scrollArea_resp->findChildren<QCheckBox *>();
  foreach(QCheckBox *w, list)
  {
    if(w->isChecked())
    {
      entry* filter = new entry( QString("undef"), QString("undef") ,
                                 QDate(), w->text(), entry::_undef, QString(""), -1 );
      result->append(filter);
    }
  }

  return result;
}



select_dialog::~select_dialog()
{
  delete ui;
}
