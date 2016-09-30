#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "local_xml_content.h"
#include "xml_dialog.h"
#include "entry.h"
#include <QMainWindow>
#include <QTreeWidget>
#include <QDebug>
#include <qdom.h>
#include <QList>
#include <QStringList>

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
    void on_add_point_clicked();
    void on_pushButton_clicked();

private:
    void add_topic(entry);
    void add_sub(entry);
    void add_test_content();

    QList<QTreeWidgetItem *> topicList;
    QTreeWidget *topNode;
    Ui::MainWindow *ui;
    local_xml_content content;

};

#endif // MAINWINDOW_H
