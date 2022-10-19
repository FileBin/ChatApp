#include <QCoreApplication>

#include "server.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Server::Server s;
    return a.exec();
}
