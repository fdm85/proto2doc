#include "gui_tools.h"

gui_tools::gui_tools(QObject *parent) : QObject(parent)
{

}

QStringList gui_tools::make_string_list(entry ref_entry)
{
  QStringList tmp_list;
  tmp_list << ref_entry.o_Titel() << ref_entry.o_Verantwortlich()
           << ref_entry.o_Frist().toString("dd_MM_yyyy")
           << entry::spec2str(ref_entry.o_specifier())
           << ref_entry.o_Inhalt();

  return tmp_list;
}

