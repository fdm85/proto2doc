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

/* public function to import a file */
void document_reader::read_document(QString filename)
{
  /* check if file exists and paramtere valid check */
  if( !QFile(filename).exists()
      || treeWidget == NULL
      || topicList == NULL
      || responsibleList == NULL )
  {
    /* something is invalid */
    return;
  }

  QFile file(filename);

  /* try to pen file */
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    return;
  }

  /* set up temporary stuff */
  myDebug::dbg(QString("Importing DUMP\n"));
  QTextStream in(&file);

  /* proccess content line by line */
  while (!in.atEnd())
  {
    start = -1;
    end = -1;
    length = 0;
    /* read lines from file for a complete set of < ... > */
    QString lineFromFile;
    QStringList linesContentOnly;
    bool found_content = false;

    /* as long as at least one delimiter is not found
     * file is not at the end */
    while(  ((start < 0) || (end < 0))
            && !in.atEnd() )
    {
      /* clear vars */
      lineFromFile.clear();
      lineFromFile = in.readLine();

      if( lineFromFile.contains("# Titel: ") )
      {
        linesContentOnly.append("# Titel: ");
        found_content = true;
      }

      else if(lineFromFile.contains("-Datum: "))
      {
        linesContentOnly.append("-Datum: ");
        found_content = true;
      }

      else if(lineFromFile.contains("-Verantwortlich: "))
      {
        linesContentOnly.append("-Verantwortlich: ");
        found_content = true;
      }

      else if(lineFromFile.contains("-Typ: "))
      {
        linesContentOnly.append("-Typ: ");
        found_content = true;
      }

      else if(lineFromFile.contains("-Inhalt: "))
      {
        linesContentOnly.append("-Inhalt: ");
        found_content = true;
      }

      else if(lineFromFile.contains("-Topic: "))
      {
        linesContentOnly.append("-Topic: ");
        found_content = true;
      }
      if(found_content == true)
      {
        /* if line is not empty refresh delimiters and get content text*/
        linesContentOnly.append(resolve_delimiters(lineFromFile));
      }
    }
    /* cast text into something this programm can interpret */
    process_line(linesContentOnly);
    found_content = false;
    linesContentOnly.clear();
  }
  /* collect some meta data for later debbuging */
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

QString document_reader::resolve_delimiters(QString line)
{
  /* try to find the start */
  if(start == -1)
  {
    start = line.indexOf("<");
  }
  /* try to find the end and remove > */
  if( (end == -1) && (line.indexOf(">") != -1) )
  {
    end = line.indexOf(">") -1;
  }

  /* only found the < beginning or multiline */
  if(end == -1)
  {
    /* get the whole line */
    length = line.length() -1;
  }
  /* found either < ... > or last of a multiline ending with > */
  else
  {
    /* get the line excluding the delimiter */
    length = (end - start);
  }

  return line.mid(start + 1, length );
}

void document_reader::process_line(QStringList lines)
{

  if(lines.contains("# Titel: "))
  {
    lines.removeFirst();
    tmp_entry.titel = lines.join("|");
  }

  else if(lines.contains("-Datum: "))
  {
    lines.removeFirst();
    tmp_entry.datum = lines.join("");
  }

  else if(lines.contains("-Verantwortlich: "))
  {
    lines.removeFirst();
    tmp_entry.verantwortlich = lines.join("|");
  }

  else if(lines.contains("-Typ: "))
  {
    /* TODO einrückung mit einbeziehen */
    lines.removeFirst();
    tmp_entry.typ = lines.join("|");
  }

  else if(lines.contains("-Inhalt: "))
  {
    lines.removeFirst();
    tmp_entry.inhalt = lines.join("\r\n");
  }

  else if(lines.contains("-Topic: "))
  {
    lines.removeFirst();
    tmp_entry.topic = lines.join("|");

    /* TODO check for existing entry first and if it is a duplicate,
     * add to separate list called duplicates or so.... */

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


void document_reader::add_topic(entry ref_entry)
{
  /* cast the content from ref_entry to something the gui can process
   * a list of cell contents */
  QStringList tmp_list = gui_tools::make_string_list(ref_entry);

  /* on import we need to refresh/rebuild the meta-data collection
   * of topics */
  topicList->append(new QTreeWidgetItem(treeWidget, tmp_list));

  /* TODO clarify what tmp_entry is needed for */
  /* simulate topic import just like a regular user would cause */
  entry* tmp_entry = new entry( QString("undef"), QString("undef") ,
                                QDate(), ref_entry.o_Verantwortlich(),
                                entry::_undef, QString("undef"),
                                topicList->length() - 1);


  if(!responsibleList->contains(ref_entry.o_Verantwortlich()))
  {
    responsibleList->append(ref_entry.o_Verantwortlich());
  }

  mark_dialog::copydebug(&ref_entry);
}

void document_reader::add_sub(entry ref_entry)
{
  /* cast the content from ref_entry to something the gui can process
   * a list of cell contents */
  QStringList tmp_list = gui_tools::make_string_list(ref_entry);
  bool index_found = false;
  /* get corresponding parent node */
  for(int i = 0; i < topicList->length(); ++i)
  {
    if( topicList->at(i)->data(0,0).toString() == ref_entry.o_Topic())
    {
      ref_entry.setTopic_index(i);
      index_found = true;
    }
  }

  /* no parent node found */
  if(index_found == false)
  {
    /* no parent node? lets cast our imaginary friend into the real */
    add_topic(entry( ref_entry.o_Topic())); // unspecified details get a default value automatically
    ref_entry.setTopic_index(topicList->length() - 1);
  }

  /* TODO implement a else case when no corresponding topic is found */

  QTreeWidgetItem *pobj_tree_item = new QTreeWidgetItem(topicList->at(ref_entry.o_topicIndex()),
                                                        tmp_list);
  pobj_tree_item->setFlags(topicList->last()->flags() | Qt::ItemIsEditable);
  topicList->last()->addChild(pobj_tree_item);

  if(!responsibleList->contains(ref_entry.o_Verantwortlich()))
  {
    responsibleList->append(ref_entry.o_Verantwortlich());
  }
  mark_dialog::copydebug(&ref_entry);
}
