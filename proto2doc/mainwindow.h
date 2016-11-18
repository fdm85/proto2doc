#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "local_xml_content.h"
#include "xml_dialog.h"
#include "entry.h"
#include "select_dialog.h"
#include "document_writer.h"
#include "document_reader.h"
#include <QMainWindow>
#include <QTreeWidget>
#include <QDebug>
#include <qdom.h>
#include <QList>
#include <QStringList>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStandardPaths>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_add_Sub_clicked();
    void on_addTopic_clicked();
    void on_speichern_clicked();
    void entry_changed(QTreeWidgetItem *, int);
    void on_dump_clicked();
    void on_clear_clicked();
    void on_restore_clicked();
    void on_schichten_clicked();
    void on_notes_clicked();
    void on_colum_p_clicked();
    void on_colum_m_clicked();
    void on_row_m_clicked();

    void on_row_p_clicked();

private:
    void add_topic(entry);
    void add_sub(entry);
    void add_test_content();

    QList<QTreeWidgetItem *> topicList;
    QStringList responsibleList;
    QTreeWidget *topNode;
    Ui::MainWindow *ui;
    local_xml_content content;
    QString filename;

    QStringList make_string_list(entry ref_entry);
    void append_responsible(entry ref_entry);
};

#endif // MAINWINDOW_H
