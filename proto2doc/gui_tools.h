#ifndef GUI_TOOLS_H
#define GUI_TOOLS_H

#include <QObject>
#include "entry.h"

class gui_tools : public QObject
{
  Q_OBJECT
public:
  explicit gui_tools(QObject *parent = 0);
  static QStringList make_string_list(entry ref_entry);

private:

signals:

public slots:
};

#endif // GUI_TOOLS_H
