/****************************************************************************/
/*!
@file xmlRelevant.h


*****************************************************************************/

#ifndef XMLRELEVANT_H
#define XMLRELEVANT_H

#include <QObject>
#include <QDebug>
#include <QTreeWidget>
#include <qdom.h>
#include <QFile>

class xmlRelevant : public QObject
{
    Q_OBJECT
public:
    explicit xmlRelevant(QObject *parent = 0);


    void xml_tree(QString str_xml_file_path = " ", QDomDocument *obj_file_content = new QDomDocument("blank"), QTreeWidget * obj_tree = new QTreeWidget(),QString str_container_tag_name = "", QString str_element_tag_name = "", QString str_header_name = "");
    void xml_tree_element(const QDomElement *pobj_element, QString str_container_tag_name = "", QString str_element_tag_name = "", QTreeWidgetItem *pobj_parent_item = 0);

signals:
    
public slots:
    
};

#endif // XMLRELEVANT_H
