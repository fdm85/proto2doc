#include "document_reader.h"

document_reader::document_reader(QObject *parent,
                                 QTreeWidget *treeWidget_c,
                                 QList<QTreeWidgetItem *> *topicList_c,
                                 QStringList *responsibleList_c)
  : QObject(parent),
    treeWidget(treeWidget_c),
    topicList(topicList_c),
    responsibleList(responsibleList_c)
{

}

void document_reader::read_document(QString filename)
{
  if( !QFile(filename).exists()
      || treeWidget == NULL
      || topicList == NULL
      || responsibleList == NULL )
  {
    return;
  }

  QFile file(filename);

  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    return;
  }

  myDebug::dbg(QString("Importing DUMP\n"));
  QTextStream in(&file);
  while (!in.atEnd())
  {
    QString line = in.readLine();
    process_line(line);
  }
  myDebug::dbg(QString("Done DUMP\n"));
}

entry document_reader::cast_tmp_entry(document_reader::temp_entry_t tmp_entry_c)
{
  return entry(tmp_entry_c.titel,
                   tmp_entry_c.inhalt,
                   QDate::fromString(tmp_entry_c.datum, "dd_MM_yyyy"),
                   tmp_entry_c.verantwortlich,
                   entry::str2spec(tmp_entry_c.typ),
                   tmp_entry_c.topic,
                   -1);
}

void document_reader::process_line(QString line)
{
  int start, length;
  line.remove("\n").remove("\r").remove("\t");
  if(line.contains("Titel: "))
  {
    start = line.indexOf("<");
    length = line.indexOf(">");
    if(start != -1 && length != -1)
    {
      length = line.indexOf(">") - line.indexOf("<");
      tmp_entry.titel = line.mid(start + 1, length - 1);
    }
  }

  else if(line.contains("-Datum: "))
  {
    start = line.indexOf("<");
    length = line.indexOf(">");
    if(start != -1 && length != -1)
    {
      length = line.indexOf(">") - line.indexOf("<");
      tmp_entry.datum = line.mid(start + 1, length - 1);
    }
  }

  else if(line.contains("-Verantwortlich: "))
  {
    start = line.indexOf("<");
    length = line.indexOf(">");
    if(start != -1 && length != -1)
    {
      length = line.indexOf(">") - line.indexOf("<");
      tmp_entry.verantwortlich = line.mid(start + 1, length - 1);
    }
  }

  else if(line.contains("-Typ: "))
  {
    start = line.indexOf("<");
    length = line.indexOf(">");
    if(start != -1 && length != -1)
    {
      length = line.indexOf(">") - line.indexOf("<");
      tmp_entry.typ = line.mid(start + 1, length - 1);
    }
  }

  else if(line.contains("-Inhalt: "))
  {
    start = line.indexOf("<");
    length = line.indexOf(">");
    if(start != -1 && length != -1)
    {
      length = line.indexOf(">") - line.indexOf("<");
      tmp_entry.inhalt = line.mid(start + 1, length - 1);
    }
  }

  else if(line.contains("-Topic: "))
  {
    start = line.indexOf("<");
    length = line.indexOf(">");
    if(start != -1 && length != -1)
    {
      length = line.indexOf(">") - line.indexOf("<");
      tmp_entry.topic = line.mid(start + 1, length - 1);

      entry entry_c = cast_tmp_entry(tmp_entry);
      if(entry_c.o_specifier() == entry::_topic)
      {
        add_topic(entry_c);
        tmp_entry.datum.clear();
        tmp_entry.inhalt.clear();
        tmp_entry.titel.clear();
        tmp_entry.topic.clear();
        tmp_entry.typ.clear();
        tmp_entry.verantwortlich.clear();
      }
      else
      {
        add_sub(entry_c);
      }
    }
  }
}


void document_reader::add_topic(entry ref_entry)
{
  QStringList tmp_list;
  tmp_list << ref_entry.o_Titel() << ref_entry.o_Inhalt() << ref_entry.o_Verantwortlich()
           << ref_entry.o_Frist().toString("dd_MM_yyyy") << entry::spec2str(ref_entry.o_specifier());

  topicList->append(new QTreeWidgetItem(treeWidget, tmp_list));

  entry* tmp_entry = new entry( QString("undef"), QString("undef") ,
                                QDate(), ref_entry.o_Verantwortlich(),
                                entry::_undef, QString("undef"),
                                -1);

  if(!responsibleList->contains(ref_entry.o_Verantwortlich()))
  {
    responsibleList->append(ref_entry.o_Verantwortlich());
  }

  mark_dialog::copydebug(&ref_entry);
}

void document_reader::add_sub(entry ref_entry)
{
  QStringList tmp_list;
  tmp_list << ref_entry.o_Titel() << ref_entry.o_Inhalt() << ref_entry.o_Verantwortlich()
           << ref_entry.o_Frist().toString("dd_MM_yyyy") << entry::spec2str(ref_entry.o_specifier());

  QTreeWidgetItem *pobj_tree_item = new QTreeWidgetItem(topicList->last(), tmp_list);
  pobj_tree_item->setFlags(topicList->last()->flags() | Qt::ItemIsEditable);
  topicList->last()->addChild(pobj_tree_item);

  if(!responsibleList->contains(ref_entry.o_Verantwortlich()))
  {
    responsibleList->append(ref_entry.o_Verantwortlich());
  }
  mark_dialog::copydebug(&ref_entry);
}
