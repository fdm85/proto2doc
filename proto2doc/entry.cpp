#include "entry.h"

bool entry::operator ==(entry const& other)
{
  if(other.Titel != "undef" )
    return (Titel == other.Titel);
  else if(other.Inhalt != "undef")
    return (Inhalt == other.Inhalt);
  else if(other.Verantwortlich != "undef")
    return (Verantwortlich == other.Verantwortlich);
  else if(!other.Frist.isNull())
    return (Frist == other.Frist);
  else if(other.Specifier != _undef)
    return (Specifier == other.Specifier);
  else if(other.topic_index != -1)
    return (topic_index == other.topic_index);
  else
    return false;
}

void entry::setTopic_index(int value)
{
    topic_index = value;
}


