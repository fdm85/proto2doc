/****************************************************************************/
/*!
@file xmlRelevant.cpp

Company
<br><br> (c) Mackware GmbH

@author C. Grünberger (cg@mackware.de)
@brief All xml relevant parts of PgS

XML Class for HBM4 Program Suite

@version  R0001  08.03.2016  C. Grünberger
*****************************************************************************/

#include "xmlRelevant.h"

xmlRelevant::xmlRelevant(QObject *parent) :
    QObject(parent)
{
}


/*****************************************************************************
Function: xml_tree()
*****************************************************************************/
/*!
@brief Parse a xml file and show content in a QTreeWidget

This Funktion will do all checks neccesary before parsing the specified xml file.
One can specify a tag name for a container entry, that can contain other containers
or elements.
One can also specify a element tag name. Use these two guidelines if the file
will follow a strict naming convention, where each single node will have an
attribute called name.
If the node name does not match the guideline, the nodename itself will be used
as a naming source. In general it is possible to use this function to parse and
visualize any given but well defined(dome node) xml file in a tree widget.

@param[in] str_xml_file_path Full path to xml file
@param[in] obj_tree pointer to tree widget where the xml shall be visualized
@param[in] str_container_tag_name guideline for container name
@param[in] str_element_tag_name guideline for entry name
@param[in] str_header_name guideline for top level entry name,
           leave empty if no guideline is needed.
@return None
*****************************************************************************/
void xmlRelevant::xml_tree(QString str_xml_file_path, QDomDocument *obj_file_content, QTreeWidget * obj_tree,
                           QString str_container_tag_name, QString str_element_tag_name,
                           QString str_header_name)
{
    QFile obj_xml_file(str_xml_file_path);
    QDomDocument obj_dom_doc;
    QDomElement obj_dom_element;
    QTreeWidgetItem *obj_father_element;

    QString str_prs_error;
    int i_prs_err_line, i_prs_err_col;

    qDebug()<< "xml_tree called" << str_container_tag_name << str_element_tag_name;
    if(!str_xml_file_path.isEmpty())//only read from file if provided
    {
        if(!obj_xml_file.exists())
        {
            qDebug()<<"specified file does not exist"<< str_xml_file_path;
            return;
        }

        if(!obj_xml_file.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug()<<"file open error"<< str_xml_file_path;
            return;
        }

        if(!obj_dom_doc.setContent(obj_xml_file.readAll(),
                                   &str_prs_error, &i_prs_err_line, &i_prs_err_col))
        {
            qDebug()<<"error parsing xml file" << str_prs_error << i_prs_err_line << i_prs_err_col;
            return;
        }

        /* get root entity (top level only one is allowed) */
        obj_dom_element = obj_dom_doc.documentElement();

        qDebug()<< "xml_tree called with xml document"  << str_container_tag_name << str_element_tag_name;
    } else {
        obj_dom_element = obj_file_content->documentElement();
    }

    /* check for top level entry tag name if a guideline is supplied */
    if(!str_header_name.isEmpty())
    {
        if(obj_dom_element.attribute("name") != str_header_name)
        {
            qDebug()<<"xml root tag does not match guideline" <<obj_dom_element.attribute("name") << "!=" <<str_header_name;
            return;
        }
    }


    obj_father_element = new QTreeWidgetItem(obj_tree);

    /* is root a headline, e.g. date, file info, etc...
        so get tag name for naming */
    if((obj_dom_element.tagName() != str_container_tag_name) &&
       (obj_dom_element.tagName() != str_element_tag_name) )
    {
        obj_father_element->setText(0, obj_dom_element.tagName());
        /* get first child if there is one */
    }
    /* is root a container, so use name attribute for naming */
    else
    {
        obj_father_element->setText(0, obj_dom_element.attribute("name", "not found"));
    }
    /* add top level to tree view and save a reference to it */
    obj_tree->addTopLevelItem(obj_father_element);

    obj_dom_element = obj_dom_element.firstChildElement();

    while(!obj_dom_element.isNull())
    {
        xml_tree_element(&obj_dom_element, str_container_tag_name, str_element_tag_name, obj_father_element);
        obj_dom_element = obj_dom_element.nextSiblingElement();
    }

    obj_tree->expandItem(obj_father_element);
}


/*****************************************************************************
Function: xml_tree_element()
*****************************************************************************/
/*!
@brief

@param[in] pobj_element
@param[in] pobj_parent_item

@return None
*****************************************************************************/
void xmlRelevant::xml_tree_element( const QDomElement *pobj_element, QString str_container_tag_name,
                                        QString str_element_tag_name, QTreeWidgetItem *pobj_parent_item)
{
    //qDebug()<< "xml_tree_element called" << pobj_element->tagName() << pobj_element->attribute("name", "none given");
    /* for each container found a entry in the tree is generated */
    QTreeWidgetItem *pobj_tree_item = new QTreeWidgetItem(pobj_parent_item);
    pobj_tree_item->setFlags( pobj_tree_item->flags());
    pobj_parent_item->addChild(pobj_tree_item);


    /* if tag name is container or element, use name atribute for naming, else use tag name */
    if( (pobj_element->tagName() == str_container_tag_name) ||
        (pobj_element->tagName() == str_element_tag_name))
    {
        pobj_tree_item->setText(0, pobj_element->attribute("name", "not found"));
        pobj_tree_item->setText(1, pobj_element->attribute("value", ""));
        pobj_tree_item->setText(2, pobj_element->attribute("description", ""));
    }
    else
    {
        pobj_tree_item->setText(0, pobj_element->tagName());
        if(!pobj_element->hasChildNodes())
        {
            QDomNamedNodeMap obj_attribute_list = pobj_element->attributes();

            for(int i = 0; i < (int)obj_attribute_list.length(); ++i)
            {
                QTreeWidgetItem *pobj_new_item = new QTreeWidgetItem(pobj_tree_item);
                pobj_new_item->setText(0,obj_attribute_list.item(i).nodeName());
                pobj_new_item->setText(1,obj_attribute_list.item(i).nodeValue());
                pobj_tree_item->addChild(pobj_new_item);
            }
        }
    }



    QDomElement obj_child = pobj_element->firstChildElement();

    while(!obj_child.isNull())
    {
        if((pobj_element->tagName() == str_container_tag_name) ||
           (pobj_element->hasChildNodes()))
        {
            xml_tree_element(&obj_child, str_container_tag_name, str_element_tag_name, pobj_tree_item);
        }
        else
        {
            QTreeWidgetItem *pobj_item_child = new QTreeWidgetItem(pobj_tree_item);
            pobj_item_child->setFlags( pobj_tree_item->flags());
            pobj_item_child->setText(0, obj_child.attribute("name", "not found"));
            pobj_item_child->setText(1, obj_child.attribute("value", ""));
            pobj_item_child->setText(2, obj_child.attribute("description", ""));
            pobj_tree_item->addChild(pobj_item_child);

        }
        obj_child = obj_child.nextSiblingElement();
    }

}



