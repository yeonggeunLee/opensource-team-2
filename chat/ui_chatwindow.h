/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *Address_label;
    QTextEdit *Address_textedit;
    QLabel *Name_label;
    QTextEdit *Name_textedit;
    QPushButton *Connect_button;
    QPlainTextEdit *Chat_plaintextedit;
    QTextEdit *ChatSend_textedit;
    QPushButton *ChatSend_button;
    QPushButton *FileSend_button;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(575, 422);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Address_label = new QLabel(centralwidget);
        Address_label->setObjectName(QString::fromUtf8("Address_label"));
        Address_label->setGeometry(QRect(10, 20, 51, 31));
        Address_textedit = new QTextEdit(centralwidget);
        Address_textedit->setObjectName(QString::fromUtf8("Address_textedit"));
        Address_textedit->setGeometry(QRect(60, 20, 171, 31));
        Address_textedit->setTextInteractionFlags(Qt::TextEditorInteraction);
        Name_label = new QLabel(centralwidget);
        Name_label->setObjectName(QString::fromUtf8("Name_label"));
        Name_label->setGeometry(QRect(250, 20, 51, 31));
        Name_textedit = new QTextEdit(centralwidget);
        Name_textedit->setObjectName(QString::fromUtf8("Name_textedit"));
        Name_textedit->setGeometry(QRect(290, 20, 171, 31));
        Name_textedit->setTextInteractionFlags(Qt::TextEditorInteraction);
        Connect_button = new QPushButton(centralwidget);
        Connect_button->setObjectName(QString::fromUtf8("Connect_button"));
        Connect_button->setGeometry(QRect(480, 20, 91, 31));
        Chat_plaintextedit = new QPlainTextEdit(centralwidget);
        Chat_plaintextedit->setObjectName(QString::fromUtf8("Chat_plaintextedit"));
        Chat_plaintextedit->setGeometry(QRect(10, 60, 561, 241));
        Chat_plaintextedit->setMouseTracking(false);
        Chat_plaintextedit->setReadOnly(true);
        ChatSend_textedit = new QTextEdit(centralwidget);
        ChatSend_textedit->setObjectName(QString::fromUtf8("ChatSend_textedit"));
        ChatSend_textedit->setGeometry(QRect(10, 320, 451, 31));
        ChatSend_button = new QPushButton(centralwidget);
        ChatSend_button->setObjectName(QString::fromUtf8("ChatSend_button"));
        ChatSend_button->setGeometry(QRect(470, 320, 91, 31));
        FileSend_button = new QPushButton(centralwidget);
        FileSend_button->setObjectName(QString::fromUtf8("FileSend_button"));
        FileSend_button->setGeometry(QRect(470, 360, 91, 31));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Address_label->setText(QCoreApplication::translate("MainWindow", " \354\243\274\354\206\214 : ", nullptr));
        Address_textedit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">127.0.0.1</p></body></html>", nullptr));
        Address_textedit->setPlaceholderText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        Name_label->setText(QCoreApplication::translate("MainWindow", "\354\235\264\353\246\204 : ", nullptr));
        Connect_button->setText(QCoreApplication::translate("MainWindow", "\354\240\221\354\206\215", nullptr));
        ChatSend_button->setText(QCoreApplication::translate("MainWindow", "\354\240\204\354\206\241", nullptr));
        FileSend_button->setText(QCoreApplication::translate("MainWindow", "\355\214\214\354\235\274 \354\240\204\354\206\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
