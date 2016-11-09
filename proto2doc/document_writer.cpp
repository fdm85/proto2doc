#include "document_writer.h"

document_writer::document_writer(QObject *parent,
                                 QString file_path)
  : QObject(parent)
{


  if(open_file(file_path) == false)
  {
    QMessageBox::warning(NULL, tr("Textdatei speichern"),
                         tr("Fehler beim Erstellen der Datei.\n"
                            "OOoopps"),
                         QMessageBox::Ok );
  }
}


document_writer::~document_writer()
{
  out->flush();
  out->~QTextStream();
  output_file.close();
}

void document_writer::add_headline(QString headline)
{
  *out << "----------------" + headline + "----------------\n" ;
  out->flush();
}

void document_writer::add_content(entry *filter,
                                  QTreeWidget *treeWidget,
                                  entry::member_specifier spec)
{
  if(filter == NULL || treeWidget == NULL)
  {
    return;
  }

  int colum = spec;

  if(spec == entry::_Titel)
  {
    *out << "**********___" + filter->o_Titel() + "___**********\n" ;
    out->flush();
    for(int i = 0; i < treeWidget->topLevelItemCount(); ++i)
    {

      if( treeWidget->topLevelItem(i)->data(colum, Qt::DisplayRole).toString()
          == filter->o_Titel() )
      {
        write_treeItem(treeWidget->topLevelItem(i));
        for(int j = 0; j < treeWidget->topLevelItem(i)->childCount(); ++j )
        {
          write_treeItem(treeWidget->topLevelItem(i)->child(j));
        }
      }
    }
  }

  if(spec == entry::_Verantwortlich)
  {
    *out << "**********___" + filter->o_Verantwortlich() + "___**********\n" ;
    out->flush();
    for(int i = 0; i < treeWidget->topLevelItemCount(); ++i)
    {
      for(int j = 0; j < treeWidget->topLevelItem(i)->childCount(); ++j )
      {
        if(treeWidget->topLevelItem(i)->child(j)->data(colum, Qt::DisplayRole).toString()
           == filter->o_Verantwortlich())
        {
          write_treeItem(treeWidget->topLevelItem(i)->child(j));
        }
      }
    }
  }
}

entry* document_writer::cast_row_change(QTreeWidgetItem *item)
{
  return cast_row(item, true);
}

void document_writer::dump_all(QTreeWidget *treeWidget)
{

  if(treeWidget == NULL)
  {
    return;
  }

  for(int i = 0; i < treeWidget->topLevelItemCount(); ++i)
  {
    write_treeItem(treeWidget->topLevelItem(i));
    for(int j = 0; j < treeWidget->topLevelItem(i)->childCount(); ++j )
    {
      write_treeItem(treeWidget->topLevelItem(i)->child(j));
    }
  }

  out->flush();
}

void document_writer::add_timetable(QTableWidget *table)
{
  QStringList row;
  int cell_width[table->columnCount()];

  for(int j = 0; j < table->rowCount(); ++j)
  {
    for(int i = 0; i < table->columnCount(); ++i)
    {
      table->setCurrentCell(j,i);

      if(table->currentItem()->data(Qt::DisplayRole).toString().length() > cell_width[i])
      {
        cell_width[i] = table->currentItem()->data(Qt::DisplayRole).toString().length();
      }
    }
  }

  for(int j = 0; j < table->rowCount(); ++j)
  {
    for(int i = 0; i < table->columnCount(); ++i)
    {
      table->setCurrentCell(j,i);
      row.append(table->currentItem()->data(Qt::DisplayRole).toString());
    }
    write_table(row, &cell_width[0]);
  }

}


void document_writer::write_entry(entry *entry_c)
{
  QString text;
  QString datum;

  text.clear();
  if(entry_c->o_Frist().isValid())
  {
    datum = entry_c->o_Frist().toString("dd_MM_yyyy");
  }
  else
  {
    datum = "N/V";
  }

  text.append("# Titel: ").append("<").append(entry_c->o_Titel()).append(">").append("\n");
  text.append("\t").append("-Datum: ").append("<").append(datum).append(">").append("\n");
  text.append("\t").append("-Verantwortlich: ").append("<").append(entry_c->o_Verantwortlich()).append(">").append("\n");
  text.append("\t").append("-Typ: ").append("<").append(entry::spec2str(entry_c->o_specifier())).append(">").append("\n");
  text.append("\t").append("-Inhalt: ").append("<").append(entry_c->o_Inhalt()).append(">").append("\n");
  text.append("\t").append("-Topic: ").append("<").append(entry_c->o_Topic()).append(">").append("\n\n");


  *out << text;
  out->flush();
}

void document_writer::write_table(QStringList table_content, int *max_width)
{

}

bool document_writer::open_file(QString file_path)
{
  bool result = false;
  if(output_file.isOpen())
  {
    QMessageBox::warning(NULL, tr("Textdatei speichern"),
                         tr("Eine Datei ist bereits geöffnet.\n"
                            "OOoopps"),
                         QMessageBox::Ok);
  }
  else
  {
    output_file.setFileName(file_path);
    result = output_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    out = new QTextStream(&output_file);
  }
  return result;
}

entry* document_writer::cast_row(QTreeWidgetItem *item, bool change)
{
  entry::type_t type_c = entry::str2spec(item->data(entry::_Specifier, Qt::DisplayRole).toString());

  entry* result = new entry(item->data(0,Qt::DisplayRole).toString(),
                            item->data(1,Qt::DisplayRole).toString(),
                            QDate::fromString(item->data(3,Qt::DisplayRole).toString(), "dd_MM_yyyy"),
                            item->data(2,Qt::DisplayRole).toString(),
                            change ? entry::_change : type_c,
                            (item->parent()!=NULL) ? item->parent()->data(entry::_Titel,  Qt::DisplayRole).toString() : item->data(0,Qt::DisplayRole).toString(),
                            -1);
  return result;
}

void document_writer::write_treeItem(QTreeWidgetItem *item)
{
  entry *tmp_entry = cast_row(item);
  write_entry(tmp_entry);
  delete tmp_entry;
}


