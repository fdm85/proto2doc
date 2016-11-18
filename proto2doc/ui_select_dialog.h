/********************************************************************************
** Form generated from reading UI file 'select_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_DIALOG_H
#define UI_SELECT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_select_dialog
{
public:
    QDialogButtonBox *buttonBox;
    QScrollArea *scrollArea_resp;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *scrollArea_topic;
    QWidget *scrollAreaWidgetContents_2;

    void setupUi(QDialog *select_dialog)
    {
        if (select_dialog->objectName().isEmpty())
            select_dialog->setObjectName(QStringLiteral("select_dialog"));
        select_dialog->resize(408, 289);
        buttonBox = new QDialogButtonBox(select_dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        scrollArea_resp = new QScrollArea(select_dialog);
        scrollArea_resp->setObjectName(QStringLiteral("scrollArea_resp"));
        scrollArea_resp->setGeometry(QRect(10, 10, 381, 111));
        scrollArea_resp->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 379, 109));
        scrollArea_resp->setWidget(scrollAreaWidgetContents);
        scrollArea_topic = new QScrollArea(select_dialog);
        scrollArea_topic->setObjectName(QStringLiteral("scrollArea_topic"));
        scrollArea_topic->setGeometry(QRect(10, 130, 381, 101));
        scrollArea_topic->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 379, 99));
        scrollArea_topic->setWidget(scrollAreaWidgetContents_2);

        retranslateUi(select_dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), select_dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), select_dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(select_dialog);
    } // setupUi

    void retranslateUi(QDialog *select_dialog)
    {
        select_dialog->setWindowTitle(QApplication::translate("select_dialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class select_dialog: public Ui_select_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_DIALOG_H
