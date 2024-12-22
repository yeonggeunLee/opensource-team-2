#include "chatwindow.h"
#include "./ui_chatwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFileInfo>

ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      socket(new QTcpSocket(this)) {
    ui->setupUi(this);

    connect(ui->Connect_button, &QPushButton::clicked, this, &ChatWindow::connectToServer);
    connect(ui->ChatSend_button, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->FileSend_button, &QPushButton::clicked, this, &ChatWindow::sendFile);
    connect(socket, &QTcpSocket::readyRead, this, &ChatWindow::receiveMessage);
}

ChatWindow::~ChatWindow() {
    delete ui;
}

void ChatWindow::connectToServer() {
    QString address = ui->Address_textedit->toPlainText();
    QString username = ui->Name_textedit->toPlainText();

    if (address.isEmpty() || username.isEmpty()) {
        QMessageBox::warning(this, "오류", "주소와 이름을 입력하세요.");
        return;
    }

    socket->connectToHost(address, 12345);
    if (socket->waitForConnected(3000)) {
        QMessageBox::information(this, "연결 성공", "서버에 연결되었습니다.");
        socket->write(username.toUtf8());
    } else {
        QMessageBox::critical(this, "연결 실패", "서버에 연결할 수 없습니다.");
    }
}

void ChatWindow::sendMessage() {
    QString message = ui->ChatSend_textedit->toPlainText();
    QString username = ui->Name_textedit->toPlainText();

    if (message.isEmpty()) {
        QMessageBox::warning(this, "오류", "메시지를 입력하세요.");
        return;
    }

    ui->Chat_plaintextedit->appendPlainText(username + " : " + message);
    
    QString finalMessage = username + " : " + message;
    socket->write(finalMessage.toUtf8());
    ui->ChatSend_textedit->clear();
}

void ChatWindow::receiveMessage() {
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    
    QString username = ui->Name_textedit->toPlainText();
    
    ui->Chat_plaintextedit->appendPlainText(message);
}

void ChatWindow::sendFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "파일 선택");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "오류", "파일을 열 수 없습니다.");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QString fileHeader = QString("%1\n").arg(QFileInfo(file).fileName());
    socket->write("파일명 : " + fileHeader.toUtf8());
    socket->write(fileData);

    QMessageBox::information(this, "파일 전송 완료", "파일이 서버로 정상적으로 전송되었습니다.");
}

