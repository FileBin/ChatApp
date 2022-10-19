/*
 * file: client.cpp
 * author: filebin
 * date: 2022-10-19 14:22:52
 */

#include "client.hpp"
#include "Networking/protocol.hpp"
#include "src/logger.hpp"
#include <QtConcurrent/qtconcurrentrun.h>
#include <bits/chrono.h>
#include <chrono>
#include <qobject.h>
#include <qtcpsocket.h>
#include <qtmetamacros.h>
#include <thread>
NSP_CLIENT_BEGIN
Client::Client(QObject *parent, ptr<Logger> p_logger)
    : QObject(parent) {
    server.reset(new QTcpSocket(parent));
    logger = p_logger;
    connect(server.get(), &QTcpSocket::readyRead, this,
            &Client::slotReadyRead);
}

QFuture<bool> Client::connectTo(QString host, uint16_t port) {
    logger->info(
        QString("Connecting to %1:%2...").arg(host).arg(port));
    server->connectToHost(host, port);
    using namespace std::chrono;
    using namespace std::chrono_literals;
    using namespace std::this_thread;
    return QtConcurrent::run(
        [](Client *client) -> bool {
            auto logger = client->logger;
            auto start_time = steady_clock::now();
            if (!client->waitForState(QTcpSocket::ConnectedState)) {
                logger->critical("Connection is timed out!");
                client->server->disconnectFromHost();
                return false;
            }
            auto duration = duration_cast<milliseconds>(
                                steady_clock::now() - start_time)
                                .count();
            logger->info(QString("Connected in %1ms").arg(duration));
            return true;
        },
        this);
}

void Client::disconnectFrom() {
    server->disconnectFromHost();
    if (!waitForState(QTcpSocket::UnconnectedState)) {
        logger->critical("Error occured while disconnecting!");
        return;
    }
    logger->info("Disconnected succesfully");
}

void Client::sendMessage(QString msg) {
    Protocol p = server;
    p.sendMessage(msg);
}

void Client::slotReadyRead() {
    Protocol p = server;
    QString msg;
    p.recieveMessage(msg);
    emit messageRecieved(msg);
}

bool Client::waitForState(QTcpSocket::SocketState state) {
    using namespace std::chrono;
    using namespace std::chrono_literals;
    using namespace std::this_thread;
    auto start_time = steady_clock::now();
    while (server->state() != state) {
        if (steady_clock::now() - start_time > 5s) {
            return false;
        }
        sleep_for(1ms);
    }
    return true;
}
NSP_CLIENT_END
