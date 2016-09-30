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
        _undef

    } type_t;

public:
  entry( const QString& o_Titel = "undef", const QString& o_Inhalt = "undef",
         const QDate& o_Frist = QDate(), const QString& o_Verantwortlich = "undef",
         const type_t& o_specifier = _undef,
         const int o_topicIndex = -1)
    : Titel( o_Titel ),
      Inhalt( o_Inhalt ),
      Verantwortlich( o_Verantwortlich ),
      Frist( o_Frist ),
      Specifier( o_specifier ),
      topic_index( o_topicIndex ){ }
  const QString& o_Titel() { return Titel; }
  const QString& o_Inhalt() { return Inhalt; }
  const QDate& o_Frist() { return Frist; }
  const QString& o_Verantwortlich() { return Verantwortlich; }
  const type_t& o_specifier() { return Specifier; }
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

private:
  QString Titel, Inhalt, Verantwortlich;
  QDate Frist;
  type_t Specifier;
  int topic_index;
};

#endif // ENTRY
