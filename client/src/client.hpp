/*
 * file: client.hpp
 * author: filebin
 * date: 2022-10-19 14:12:46
 */

#include "stdafx.hpp"

NSP_CLIENT_BEGIN
class Client;
NSP_CLIENT_END

#pragma once

#include "Networking/protocol.hpp"
#include "src/logger.hpp"
#include <qfuture.h>
#include <qobject.h>
#include <qtcpsocket.h>
#include <qtmetamacros.h>

NSP_CLIENT_BEGIN

class Client : public QObject {
    Q_OBJECT
  public:
    Client(QObject *parent, ptr<Logger> logger);

  private:
    bool waitForState(QTcpSocket::SocketState state);

  public slots:
    QFuture<bool> connectTo(QString host,
                            uint16_t port = Protocol::DEFAULT_PORT);
    void disconnectFrom();
    void sendMessage(QString msg);
  private slots:
    void slotReadyRead();
  signals:
    void messageRecieved(QString msg);

  private:
    ptr<QTcpSocket> server;
    ptr<Logger> logger;
};

NSP_CLIENT_END