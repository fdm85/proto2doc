#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  myDebug::debug_filename = QDateTime::currentDateTime().toString("hh-mm_-_dd-MM-yyyy").append(".txt");

  qDebug()<< myDebug::debug_filename;
  ui->setupUi(this);
  topicList.clear();

  ui->treeWidget->setColumnCount(5);
  QStringList headers;
  headers << "Titel" << "Inhalt" << "Verantwortlich" << "Datum/Frist" << "Typ";
  ui->treeWidget->setHeaderLabels(headers);
  add_test_content();
}



MainWindow::~MainWindow()
{
  delete ui;
}



void MainWindow::on_add_point_clicked()
{
  entry ref_entry;
  mark_dialog xml_dialog(this, &topicList);
  if(xml_dialog.exec() == QDialog::Accepted)
  {
    ref_entry = xml_dialog.getEntry();
  }
  else
  {
    return;
  }

  add_sub(ref_entry);

}

void MainWindow::on_pushButton_clicked()
{
  mark_dialog xml_dialog(this);
  entry ref_entry;
  if(xml_dialog.exec() == QDialog::Accepted)
  {
    ref_entry = xml_dialog.getEntry();
  }
  else
  {
    return;
  }

  add_topic(ref_entry);

}

void MainWindow::add_topic(entry ref_entry)
{
  QStringList tmp_list;
  tmp_list << ref_entry.o_Titel() << ref_entry.o_Inhalt() << ref_entry.o_Verantwortlich() << ref_entry.o_Frist().toString("dd_MM_yyyy") << entry::spec2str(ref_entry.o_specifier());

  topicList.append(new QTreeWidgetItem( ui->treeWidget, tmp_list));
  mark_dialog::copydebug(ref_entry);
}

void MainWindow::add_sub(entry ref_entry)
{
  QStringList tmp_list;
  tmp_list << ref_entry.o_Titel() << ref_entry.o_Inhalt() << ref_entry.o_Verantwortlich() << ref_entry.o_Frist().toString("dd_MM_yyyy") << entry::spec2str(ref_entry.o_specifier());

  QTreeWidgetItem *pobj_tree_item = new QTreeWidgetItem(topicList.at(ref_entry.o_topicIndex()), tmp_list);
  pobj_tree_item->setFlags(topicList.at(ref_entry.o_topicIndex())->flags() | Qt::ItemIsEditable);
  topicList.at(ref_entry.o_topicIndex())->addChild(pobj_tree_item);
  mark_dialog::copydebug(ref_entry);
}

void MainWindow::add_test_content()
{
  QDate date;
  date.setDate(2016, 9, 18);
  entry new_topic("1_titel", "nva", date, "me", entry::_topic );
  entry new_topic2("2_titel", "tbd", date.addDays(5), "you", entry::_topic );
  add_topic(new_topic);
  add_topic(new_topic2);

  entry new_sub("pick up", "narf", date.addDays(20), "", entry::_todo, 0);
  entry new_sub2("2_titel", "tbd", date.addDays(35), "you", entry::_comment, 1);
  add_sub(new_sub);
  add_sub(new_sub2);

}
