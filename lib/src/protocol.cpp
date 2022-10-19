/*
 * file: protocol.cpp
 * author: filebin
 * date: 2022-10-19 11:16:56
 */

#include "Networking/defines.hpp"
#include "pch.h"

#include <Networking/protocol.hpp>
#include <cstdint>
#include <qtcpsocket.h>

NSP_NET_BEGIN

Protocol::Protocol(ptr<QTcpSocket> soc) : socket(soc) {}
Protocol::~Protocol() {}

void Protocol::sendMessage(QString msg) {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_3);
    // write packet size (empty) and actual data
    stream << packet_size_t() << msg;
    // return stream to start
    stream.device()->seek(0);
    // write packet size
    stream << packet_size_t(data.size() - sizeof(packet_size_t));
    // send data to socket
    socket->write(data);
}

Result Protocol::recieveMessage(QString &msg) {
    QDataStream stream(socket.get());
    stream.setVersion(QDataStream::Qt_6_3);
    packet_size_t block_size;
    if (socket->bytesAvailable() < sizeof(packet_size_t))
        return SmallPacket;
    stream >> block_size;
    if (socket->bytesAvailable() < block_size)
        return DataNotFull;
    stream >> msg;
    return Success;
}

NSP_NET_END