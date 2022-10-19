#include "mainwindow.hpp"

#include <QMessageBox>
#include <QString>
#include <cstdint>
#include <qlabel.h>
#include <qpushbutton.h>

#include "./ui_mainwindow.h"
#include "Networking/protocol.hpp"
#include "src/client.hpp"
#include "src/logger.hpp"

#include <QtConcurrent/QtConcurrent>

NSP_CLIENT_BEGIN

void errMsg(QWidget *parent, QString msg) {
    QMessageBox::critical(parent, "Error", msg);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    logger.reset(new Logger(this));
    client.reset(new Client(this, logger));
    connect(ui->connectButton, &QPushButton::clicked, this, [this]() {
        auto text = ui->hostAddressEdit->text();
        QStringList list = text.split(':');
        QString host = list.front();
        uint16_t port = Protocol::DEFAULT_PORT;
        list.pop_front();
        bool ok = true;
        if (!list.empty()) {
            port = list.front().toInt(&ok);
        }
        ok &= list.empty();
        if (!ok) {
            logger->warning("Incorrect host address format! (right "
                            "is host:port)");
        }
        client->connectTo(host, port);
    });

    connect(ui->send, &QPushButton::clicked, this, [this]() {
        client->sendMessage(ui->textEdit->toPlainText());
    });
    connect(client.get(), &Client::messageRecieved, this,
            [this](QString msg) { ui->chatWidget->addItem(msg); });
    connect(logger.get(), &Logger::logged, this,
            [this](Logger::Level level, QString msg) {
                ui->logWidget->addItem(msg);
            });

    connect(ui->disconnect, &QPushButton::clicked, client.get(),
            &Client::disconnectFrom);
}

MainWindow::~MainWindow() { delete ui; }
NSP_CLIENT_END