#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  myDebug::debug_filename = QDateTime::currentDateTime().toString("hh-mm_-_dd-MM-yyyy").append(".log");

  filename = "/" + myDebug::debug_filename;

  qDebug()<< myDebug::debug_filename;
  ui->setupUi(this);
  topicList.clear();
  responsibleList.clear();

  ui->treeWidget->setColumnCount(5);
  QStringList headers;
  headers << "Titel" << "Inhalt" << "Verantwortlich" << "Datum/Frist" << "Typ";
  ui->treeWidget->setHeaderLabels(headers);
//  add_test_content();
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
  tmp_list << ref_entry.o_Titel() << ref_entry.o_Inhalt() << ref_entry.o_Verantwortlich()
           << ref_entry.o_Frist().toString("dd_MM_yyyy") << entry::spec2str(ref_entry.o_specifier());

  topicList.append(new QTreeWidgetItem( ui->treeWidget, tmp_list));

  entry* tmp_entry = new entry( QString("undef"), QString("undef") ,
                                QDate(), ref_entry.o_Verantwortlich(),
                                entry::_undef, QString("undef"),
                                -1);

  if(!responsibleList.contains(ref_entry.o_Verantwortlich()))
  {
    responsibleList.append(ref_entry.o_Verantwortlich());
  }

  mark_dialog::copydebug(&ref_entry);
}

void MainWindow::add_sub(entry ref_entry)
{
  QStringList tmp_list;
  tmp_list << ref_entry.o_Titel() << ref_entry.o_Inhalt() << ref_entry.o_Verantwortlich()
           << ref_entry.o_Frist().toString("dd_MM_yyyy") << entry::spec2str(ref_entry.o_specifier());

  QTreeWidgetItem *pobj_tree_item = new QTreeWidgetItem(topicList.at(ref_entry.o_topicIndex()), tmp_list);
  pobj_tree_item->setFlags(topicList.at(ref_entry.o_topicIndex())->flags() | Qt::ItemIsEditable);
  topicList.at(ref_entry.o_topicIndex())->addChild(pobj_tree_item);

  if(!responsibleList.contains(ref_entry.o_Verantwortlich()))
  {
    responsibleList.append(ref_entry.o_Verantwortlich());
  }
  mark_dialog::copydebug(&ref_entry);
}

void MainWindow::add_test_content()
{
  QDate date;
  date.setDate(2016, 9, 18);
  entry new_topic("Funktion", "A bisl a gschwetz hald", date, "me", entry::_topic , QString());
  entry new_topic2("Fiktion", "Laber deinen Dönerspieß daher!", date.addDays(5), "you", entry::_topic , QString());
  add_topic(new_topic);
  add_topic(new_topic2);

  entry new_sub("pick up", "Anlage abholen", date.addDays(20), "Timo", entry::_todo, "Funktion", 0);
  entry new_sub2("TimoNutella", "Timo ein Nutella Brot schmieren", date.addDays(20), "Timo", entry::_todo, "Funktion", 0);
  entry new_sub4("Bella", "In die Apotheke gehen", date.addDays(20), "Chucky", entry::_todo, "Funktion", 0);
  entry new_sub3("2_titel", "tbd", date.addDays(35), "you", entry::_comment, "Fiktion",  1);
  add_sub(new_sub);
  add_sub(new_sub2);
  add_sub(new_sub3);
  add_sub(new_sub4);
}

void MainWindow::on_speichern_clicked()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  QStandardPaths::displayName(QStandardPaths::DesktopLocation) + filename,
                                                  tr("Text (*.txt)"));


  select_dialog sele_diag(this, &responsibleList, &topicList);

  if(!(sele_diag.exec() == QDialog::Accepted))
  {
    return;
  }
  QList<entry *> *filters_resp = sele_diag.get_filters_resp();
  QList<entry *> *filters_topic = sele_diag.get_filters_topics();

  document_writer doc_writer(this, fileName);

  if(!filters_resp->isEmpty())
  {
    doc_writer.add_headline(QString("Verantwortliche(r)"));
    for(int i = 0; i < filters_resp->size(); ++i)
      doc_writer.add_content(filters_resp->at(i), ui->treeWidget, entry::_Verantwortlich);
  }

  if(!filters_topic->isEmpty())
  {
    doc_writer.add_headline(QString("Themen(r)"));
    for(int i = 0; i < filters_topic->size(); ++i)
      doc_writer.add_content(filters_topic->at(i), ui->treeWidget, entry::_Titel);
  }

}

void MainWindow::entry_changed(QTreeWidgetItem *item, int column)
{
  if(entry::_Verantwortlich == column)
  {
    if(!responsibleList.contains(item->data(entry::_Verantwortlich, Qt::DisplayRole).toString()))
      responsibleList.append(item->data(entry::_Verantwortlich, Qt::DisplayRole).toString());
  }

  mark_dialog::copydebug(document_writer::cast_row_change(item));
}

void MainWindow::on_dump_clicked()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  QStandardPaths::displayName(QStandardPaths::DesktopLocation) + "/dump.dmp",
                                                  tr("Dump (*.dmp)"));

  qDebug()<< fileName;

  if(fileName.isEmpty())
  {
    return;
  }
  if(QFile(fileName).exists())
  {
    QFile(fileName).remove();
  }

  document_writer dump(this, fileName);
  dump.dump_all(ui->treeWidget);
}

void MainWindow::on_clear_clicked()
{
  ui->treeWidget->clear();
  responsibleList.clear();
  topicList.clear();
}

void MainWindow::on_restore_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  QStandardPaths::displayName(QStandardPaths::DesktopLocation),
                                                  tr("Dump (*.dmp)"));
  if(fileName.isEmpty())
  {
    return;
  }

  ui->treeWidget->clear();
  responsibleList.clear();
  topicList.clear();

  document_reader reader(NULL,
                         ui->treeWidget,
                         &topicList,
                         &responsibleList);

  reader.read_document(fileName);
}

void MainWindow::on_schichten_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_notes_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_colum_m_clicked()
{
  ui->tableWidget->setColumnCount(ui->tableWidget->columnCount() - 1);
}

void MainWindow::on_colum_p_clicked()
{
  ui->tableWidget->setColumnCount(ui->tableWidget->columnCount() + 1);
}

void MainWindow::on_row_m_clicked()
{
  ui->tableWidget->setRowCount(ui->tableWidget->rowCount() - 1);
}

void MainWindow::on_row_p_clicked()
{
  ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
}
