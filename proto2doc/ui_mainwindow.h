/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_0;
    QTreeWidget *treeWidget;
    QWidget *page_1;
    QTableWidget *tableWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *add_point;
    QPushButton *notes;
    QPushButton *schichten;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *colum_p;
    QPushButton *colum_m;
    QPushButton *row_p;
    QPushButton *row_m;
    QSpacerItem *verticalSpacer;
    QPushButton *speichern;
    QPushButton *dump;
    QPushButton *restore;
    QPushButton *clear;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1275, 634);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(1135, 0));
        centralWidget->setMaximumSize(QSize(16777215, 581));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 1041, 571));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        stackedWidget = new QStackedWidget(verticalLayoutWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page_0 = new QWidget();
        page_0->setObjectName(QStringLiteral("page_0"));
        treeWidget = new QTreeWidget(page_0);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(3, QStringLiteral("4"));
        __qtreewidgetitem->setText(2, QStringLiteral("3"));
        __qtreewidgetitem->setText(1, QStringLiteral("2"));
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(0, 0, 1041, 571));
        treeWidget->setMinimumSize(QSize(831, 100));
        treeWidget->setAutoFillBackground(false);
        treeWidget->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        treeWidget->setColumnCount(5);
        stackedWidget->addWidget(page_0);
        page_1 = new QWidget();
        page_1->setObjectName(QStringLiteral("page_1"));
        tableWidget = new QTableWidget(page_1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 1041, 571));
        stackedWidget->addWidget(page_1);

        horizontalLayout->addWidget(stackedWidget);


        verticalLayout->addLayout(horizontalLayout);

        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(1060, 10, 82, 571));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(80, 16777215));

        verticalLayout_2->addWidget(pushButton);

        add_point = new QPushButton(layoutWidget);
        add_point->setObjectName(QStringLiteral("add_point"));
        add_point->setMaximumSize(QSize(80, 16777215));

        verticalLayout_2->addWidget(add_point);

        notes = new QPushButton(layoutWidget);
        notes->setObjectName(QStringLiteral("notes"));
        notes->setMaximumSize(QSize(80, 16777215));

        verticalLayout_2->addWidget(notes);

        schichten = new QPushButton(layoutWidget);
        schichten->setObjectName(QStringLiteral("schichten"));
        schichten->setMinimumSize(QSize(80, 0));

        verticalLayout_2->addWidget(schichten);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        colum_p = new QPushButton(layoutWidget);
        colum_p->setObjectName(QStringLiteral("colum_p"));
        colum_p->setMaximumSize(QSize(30, 20));

        horizontalLayout_3->addWidget(colum_p);

        colum_m = new QPushButton(layoutWidget);
        colum_m->setObjectName(QStringLiteral("colum_m"));
        colum_m->setMaximumSize(QSize(30, 20));

        horizontalLayout_3->addWidget(colum_m);


        verticalLayout_2->addLayout(horizontalLayout_3);

        row_p = new QPushButton(layoutWidget);
        row_p->setObjectName(QStringLiteral("row_p"));
        row_p->setMinimumSize(QSize(80, 0));

        verticalLayout_2->addWidget(row_p);

        row_m = new QPushButton(layoutWidget);
        row_m->setObjectName(QStringLiteral("row_m"));
        row_m->setMinimumSize(QSize(80, 0));

        verticalLayout_2->addWidget(row_m);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        speichern = new QPushButton(layoutWidget);
        speichern->setObjectName(QStringLiteral("speichern"));

        verticalLayout_2->addWidget(speichern);

        dump = new QPushButton(layoutWidget);
        dump->setObjectName(QStringLiteral("dump"));

        verticalLayout_2->addWidget(dump);

        restore = new QPushButton(layoutWidget);
        restore->setObjectName(QStringLiteral("restore"));

        verticalLayout_2->addWidget(restore);

        clear = new QPushButton(layoutWidget);
        clear->setObjectName(QStringLiteral("clear"));

        verticalLayout_2->addWidget(clear);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1275, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("MainWindow", "5", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Topic", 0));
        add_point->setText(QApplication::translate("MainWindow", "Sub", 0));
        notes->setText(QApplication::translate("MainWindow", "Notes", 0));
        schichten->setText(QApplication::translate("MainWindow", "Schichten", 0));
        colum_p->setText(QApplication::translate("MainWindow", "+", 0));
        colum_m->setText(QApplication::translate("MainWindow", "-", 0));
        row_p->setText(QApplication::translate("MainWindow", "+", 0));
        row_m->setText(QApplication::translate("MainWindow", "-", 0));
        speichern->setText(QApplication::translate("MainWindow", "save", 0));
        dump->setText(QApplication::translate("MainWindow", "dump", 0));
        restore->setText(QApplication::translate("MainWindow", "restore", 0));
        clear->setText(QApplication::translate("MainWindow", "clear", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
