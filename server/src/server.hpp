/*
 * file: server.hpp
 * author: filebin
 * date: 2022-10-19 12:19:23
 */

#include "stdafx.hpp"
#include <cstddef>
#include <cstdint>
#include <qglobal.h>
#include <qtmetamacros.h>
#include <sys/types.h>

NSP_SERVER_BEGIN
class Server;
NSP_SERVER_END

#pragma once

#include <qmap.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>

NSP_SERVER_BEGIN

using ID = uint64_t;

class Server : public QTcpServer {
    Q_OBJECT
  public:
    Server();
    ~Server();

  public slots:
    void incomingConnection(qintptr socketDescriptor) override;
    void slotReadyRead(ptr<QTcpSocket> socket);
    void slotDisconnected(ID id);

  private:
    uint64_t nextId = 0;
    void sendToClients(QString msg);
    ID getNextId();

    QMap<uint64_t, ptr<QTcpSocket>> clients;
};

NSP_SERVER_END