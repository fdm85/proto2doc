#ifndef LOCAL_XML_CONTENT_H
#define LOCAL_XML_CONTENT_H

#include <QObject>
#include <qdom.h>

class local_xml_content : public QObject
{
    Q_OBJECT
public:
    explicit local_xml_content(QObject *parent = 0);

signals:

public slots:

    void new_entry(/*gui pointer*/);

private:
    QDomDocument xml_data;
};

#endif // LOCAL_XML_CONTENT_H
