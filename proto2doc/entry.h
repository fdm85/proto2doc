// Person.h
#ifndef ENTRY
#define ENTRY

#include <QString>
#include <QDate>
#include <QTreeWidgetItem>

class entry
{
public:
  typedef enum
  {
    _topic,
    _todo,
    _comment,
    _undef,
    _change

  } type_t;

  typedef enum
  {
    _Titel = 0,
    _Inhalt = 1,
    _Verantwortlich = 2,
    _Frist = 3,
    _Specifier = 4,
    _Topic,
    _Topic_Index
  } member_specifier;

public:



  entry( const QString& o_Titel = "undef", const QString& o_Inhalt = "undef",
         const QDate& o_Frist = QDate(), const QString& o_Verantwortlich = "undef",
         const type_t& o_specifier = _undef,
         const QString& o_topic = "undef" ,
         const int o_topicIndex = -1 )
    : Titel( o_Titel ),
      Inhalt( o_Inhalt ),
      Frist( o_Frist ),
      Verantwortlich( o_Verantwortlich ),
      Specifier( o_specifier ),
      Topic( o_topic),
      topic_index( o_topicIndex ) {}
  const QString& o_Titel() { return Titel; }
  const QString& o_Inhalt() { return Inhalt; }
  const QDate& o_Frist() { return Frist; }
  const QString& o_Verantwortlich() { return Verantwortlich; }
  const type_t& o_specifier() { return Specifier; }
  const QString& o_Topic() { return Topic; }
  int o_topicIndex() { return topic_index; }

  static QString spec2str(type_t t)
  {
    switch(t)
    {
      case _topic:
      return "topic";
      case _todo:
      return "toDo";
      case _comment:
      return "comment";
      default:
      return "undef";
    }
  }

  static type_t str2spec(QString string)
  {

     if(string.contains("topic"))
        return _topic;
     if(string.contains("toDo"))
        return _todo;
     if(string.contains("comment"))
        return _comment;
     else
        return _undef;
  }

  bool operator ==(entry const&);




private:
  QString Titel;
  QString Inhalt;
  QDate Frist;
  QString Verantwortlich;
  type_t Specifier;
  QString Topic;
  int topic_index;
};


#endif // ENTRY
