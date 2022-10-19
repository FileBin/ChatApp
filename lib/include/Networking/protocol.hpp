/*
 * file: protocol.hpp
 * author: filebin
 * date: 2022-10-19 10:56:47
 */

#include "stdafx.hpp"

NSP_NET_BEGIN
class Protocol;
NSP_NET_END

#pragma once

#include "result.hpp"
#include <QTcpSocket>

NSP_NET_BEGIN

class Protocol {
  public:
    static constexpr uint16_t DEFAULT_PORT = 2323;

    typedef uint16_t packet_size_t;
    Protocol(ptr<QTcpSocket> socket);
    ~Protocol();

    void sendMessage(QString msg);
    Result recieveMessage(QString &msg);

  private:
    ptr<QTcpSocket> socket;
};

NSP_NET_END