/*
 * file: server.cpp
 * author: name
 * date: 2022-10-19 12:31:28
 */

#include "Networking/defines.hpp"
#include "Networking/protocol.hpp"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <qabstractsocket.h>
#include <qdebug.h>
#include <qforeach.h>
#include <qhostaddress.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <src/server.hpp>
#include <stdexcept>
#include <utility>
NSP_SERVER_BEGIN
Server::Server() {
    if (listen(QHostAddress::Any, Protocol::DEFAULT_PORT)) {
        qInfo() << "Server started";
        qInfo() << "Listening at port" << Protocol::DEFAULT_PORT;
    } else {
        auto err = new std::runtime_error(
            "Server start error, could not open port");
        qInfo() << err->what();
        throw err;
    }
}
Server::~Server() {}

void Server::incomingConnection(qintptr socketDescriptor) {
    ptr<QTcpSocket> socket;
    socket.reset(new QTcpSocket);
    socket->setSocketDescriptor(socketDescriptor);
    ID id = getNextId();
    clients.insert(id, socket);
    connect(socket.get(), &QTcpSocket::readyRead, this,
            [this, socket]() { slotReadyRead(socket); });
    connect(socket.get(), &QTcpSocket::disconnected, this,
            [this, id]() { slotDisconnected(id); });

    qInfo() << "Client" << socket->localAddress().toString()
            << "connected.";
}

void Server::slotReadyRead(ptr<QTcpSocket> socket) {
    Protocol p = Protocol(socket);
    QString msg;
    auto result = p.recieveMessage(msg);
    if (result < 0) {
        qCritical() << "Message read error. (Code" << result << ","
                    << socket->localAddress().toString() << ")";
        return;
    }
    qInfo() << "Client" << socket->localAddress().toString() << ":"
            << msg;
    sendToClients(msg);
}

void Server::slotDisconnected(ID id) {
    auto o = clients[id];
    qInfo() << "Client" << o->localAddress().toString()
            << "disconnected.";
    clients.remove(id);
}

void Server::sendToClients(QString msg) {
    for (auto client : clients) {
        qDebug() << (client->state() ==
                     QAbstractSocket::ConnectedState);
        Protocol p = Protocol(client);
        p.sendMessage(msg);
    }
}

ID Server::getNextId() { return std::hash<uint64_t>()(nextId++); }
NSP_SERVER_END