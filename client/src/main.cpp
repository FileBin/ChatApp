
#include <QApplication>
#include <QIcon>

#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Client::MainWindow w;
    w.setWindowIcon(QIcon("res/icon.ico"));
    w.show();
    return a.exec();
}