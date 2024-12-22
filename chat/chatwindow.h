#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ChatWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void connectToServer();
    void sendMessage();
    void receiveMessage();
    void sendFile();
    //void receiveFile();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};

#endif

