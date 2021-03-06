#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm");
  myDebug::debug_filename = filename.prepend("/inputLog_").append(".log");

  filename.append(".txt");

  qDebug()<< myDebug::debug_filename;
  ui->setupUi(this);
  topicList.clear();
  responsibleList.clear();

  ui->treeWidget->setColumnCount(5);
  QStringList headers;
  headers << "Titel" << "Verantwortlich" << "Datum/Frist" << "Typ"  << "Inhalt";
  ui->treeWidget->setHeaderLabels(headers);
//  add_test_content();

  qDebug()<< QDir::homePath();

  if(!QDir(QDir::homePath() + "/proto2doc").exists())
  {
    QDir().mkdir(QDir::homePath() + "/proto2doc");
  }
  QDesktopServices::openUrl(QDir::homePath() + "/proto2doc");
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_add_Sub_clicked()
{
  entry ref_entry;

  /* get selected items from gui */
  QList<QTreeWidgetItem *> selected = ui->treeWidget->selectedItems();
  int index;

  /* check if at least one is selected */
  if(selected.length() > 0)
  {
    for(int i = 0; i < selected.length();++i)
    {
      /* we need to different between nodes and its children */
      /* is this particular reference known in topic list */
      if(topicList.contains(selected.at(i)))
      {
        index = topicList.indexOf(selected.at(i));
      }
      /* is a regular child */
      else
      {
        index = topicList.indexOf(selected.at(i)->parent());
      }
    }
  }


  mark_dialog xml_dialog(this,
                         &topicList,
                         &responsibleList,
                         false,
                         index);

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

void MainWindow::on_addTopic_clicked()
{
  mark_dialog xml_dialog(this,
                         NULL,
                         &responsibleList,
                         true);
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

void MainWindow::append_responsible(entry ref_entry)
{
  if(!responsibleList.contains(ref_entry.o_Verantwortlich()))
  {
    responsibleList.append(ref_entry.o_Verantwortlich());
  }
}

void MainWindow::add_topic(entry ref_entry)
{
  QStringList tmp_list = gui_tools::make_string_list(ref_entry);

  QTreeWidgetItem *pobj_tree_node = new QTreeWidgetItem( ui->treeWidget, tmp_list);
  pobj_tree_node->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled
                           | Qt::ItemIsSelectable);

  ui->treeWidget->addTopLevelItem(pobj_tree_node);

  topicList.append(pobj_tree_node);

  append_responsible(ref_entry);
  mark_dialog::copydebug(&ref_entry);
}

void MainWindow::add_sub(entry ref_entry)
{
  QStringList tmp_list = gui_tools::make_string_list(ref_entry);

  QTreeWidgetItem *pobj_tree_item = new QTreeWidgetItem(topicList.at(ref_entry.o_topicIndex()), tmp_list);
  pobj_tree_item->setFlags(topicList.at(ref_entry.o_topicIndex())->flags());
  topicList.at(ref_entry.o_topicIndex())->addChild(pobj_tree_item);

  append_responsible(ref_entry);
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

void MainWindow::remove(QList<QTreeWidgetItem *> *topicList_c,
                        QTreeWidget *tree)
{
  /* get selected items from gui */
  QList<QTreeWidgetItem *> selected = tree->selectedItems();

  /* check if at least one is selected */
  if(selected.length() > 0)
  {
    for(int i = 0; i < selected.length();++i)
    {
      /* we need to different between nodes and its children */
      /* is this particular reference known in topic list */
      if(topicList_c->contains(selected.at(i)))
      {
        /* find corresponding gui entry */
        for(int j = 0; j < tree->topLevelItemCount();++j)
        {
          /* found the corresponding top level item */
          if(tree->topLevelItem(j) == selected.at(i))
          {
            /* remove from gui */
            delete tree->takeTopLevelItem(j);
          }
        }
        /* remove from list */
        topicList_c->removeOne(selected.at(i));
      }
      /* is a regular child */
      else
      {
        selected.at(i)->parent()->removeChild(selected.at(i));
        delete selected.at(i);
      }
    }
  }
}

void MainWindow::on_speichern_clicked()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  QDir::homePath() + "/proto2doc/" + filename,
                                                  tr("Text (*.txt)"));
  if(fileName.isEmpty())
  {
    return;
  }
  else if(QFile(filename).exists())
  {
    QFile(fileName).remove();
  }

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
                                                  QDir::homePath() + "/proto2doc" + "/dump.dmp",
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
  /* save last used file path */
  static QString path;
  QString fileName;

  /* no load path set yet */
  if(path.isEmpty())
  {
    path = QDir::homePath() + "/proto2doc";
  }

  /* do file dialog */
  fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                          path + filename,

                                          tr("dump (*.dmp);;Text (*.txt)"));
  /* was dialog aborted? */
  if(fileName.isEmpty())
  {
    return;
  }

  /* get metadata */
  QFileInfo file(fileName);
  filename = file.fileName();
  path = file.filePath();

  /* clear current content */
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

void MainWindow::on_delete_content_clicked()
{
  remove(&topicList,
         ui->treeWidget);
}

/* load parts */
void MainWindow::on_load_clicked()
{
  /* save last used file path */
  static QString path;
  QString fileName;

  /* no load path set yet */
  if(path.isEmpty())
  {
    path = QDir::homePath() + "/proto2doc";
  }

  /* do file dialog */
  fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                          path,

                                          tr("Textdatei (*.txt)"));
  /* was dialog aborted? */
  if(fileName.isEmpty())
  {
    return;
  }

  /* get metadata */
  QFileInfo file(fileName);
  filename = file.fileName().prepend("/");
  path = file.absolutePath();

  document_reader reader(NULL,
                         ui->treeWidget,
                         &topicList,
                         &responsibleList);

  reader.read_document(fileName);
}
