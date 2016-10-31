// PersonDialog.cpp
#include "xml_dialog.h"




mark_dialog::mark_dialog( QWidget *parent, QList<QTreeWidgetItem *> *topicList )
  : QDialog( parent ),
    o_Titel( new QLineEdit() ),
    o_Inhalt( new QTextEdit() ),
    o_Verantwortlich( new QLineEdit() ),
    o_specifier( new QComboBox() ),
    o_Topic( new QComboBox() ),
    o_Frist_day(new QSpinBox() ),
    o_Frist_month(new QSpinBox() ),
    o_Frist_year(new QSpinBox() ),
    o_date_acitve(new QCheckBox() ),
    m_confirmButton( new QPushButton( "Confirm" ) ),
    m_cancelButton( new QPushButton( "Cancel") )
{
  o_Frist_day->setRange( 1, 31 );
  o_Frist_month->setRange( 1, 12);
  o_Frist_year->setRange( 2016, 2020);
  o_specifier->addItem( "_topic" );
  o_specifier->addItem( "_todo" );
  o_specifier->addItem( "_comment" );
  o_specifier->addItem( "_undef" );


  if(topicList != NULL) for(int i=0; i<topicList->length();++i)
  {
    o_Topic->addItem(topicList->at(i)->text(0));
  }

  connect( m_confirmButton, SIGNAL( clicked() ),
           this, SLOT( accept() ) );
  connect( m_cancelButton, SIGNAL(clicked(bool)),
           this, SLOT( reject() ) );

  QVBoxLayout *vLayout = new QVBoxLayout( this );
  QFormLayout *fLayout = new QFormLayout();
  QHBoxLayout *date = new QHBoxLayout();
  date->addWidget(o_date_acitve);
  date->addWidget(o_Frist_year);
  date->addWidget(o_Frist_month);
  date->addWidget(o_Frist_day);
  fLayout->addRow( "Topic", o_Topic);
  fLayout->addRow( "Titel:", o_Titel );
  fLayout->addRow( "Inhalt:", o_Inhalt );
  fLayout->addRow( "Frist/Datum:", date);
  fLayout->addRow( "Specifier:", o_specifier );
  vLayout->addLayout( fLayout );
  QHBoxLayout *hLayout = new QHBoxLayout();
  hLayout->addStretch();
  hLayout->addWidget( m_confirmButton );
  hLayout->addWidget( m_cancelButton );
  vLayout->addLayout( hLayout );

  if(topicList != NULL)
  {
    o_topicList = topicList;
  }
}


entry mark_dialog::getEntry() const
{

  myDebug::dbg( o_Titel->text());
  entry::type_t typespec = entry::_undef;
  if(o_specifier->currentText().contains("_topic"))
    typespec = entry::_topic;
  else if(o_specifier->currentText().contains("_todo"))
    typespec = entry::_todo;
  else if(o_specifier->currentText().contains("_comment"))
    typespec = entry::_todo;

  const entry::type_t r_typespec = typespec;
  return entry(o_Titel->text(),
               o_Inhalt->toPlainText(),
               o_date_acitve->isChecked() ? QDate(o_Frist_year->text().toInt(),o_Frist_month->text().toInt(), o_Frist_day->text().toInt() ) : QDate(),
               o_Verantwortlich->text(),
               r_typespec,
               o_Topic->currentIndex() );

}


void mark_dialog::copydebug(entry entry_c)
{
  QString debug_text;
  QString datum;

  debug_text.clear();
  if(entry_c.o_Frist().isValid())
  {
    datum = entry_c.o_Frist().toString("dd_MM_yyyy");
  }
  else
  {
    datum = "N/V";
  }

  debug_text.append("# Titel: ").append(entry_c.o_Titel()).append("\r\n");
  debug_text.append("\t").append("-Datum: ").append(datum).append("\r\n");
  debug_text.append("\t").append("-Verantwortlich: ").append(entry_c.o_Verantwortlich()).append("\r\n");
  debug_text.append("\t").append("Typ: ").append(entry::spec2str(entry_c.o_specifier()));
  debug_text.append("\t").append("-Inhalt: ").append(entry_c.o_Inhalt()).append("\r\n");


  myDebug::dbg(debug_text);

}
