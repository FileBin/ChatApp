#pragma once
#include "Networking/defines.hpp"
#include "src/client.hpp"
#include "src/logger.hpp"
#include "stdafx.hpp"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

NSP_CLIENT_BEGIN

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    uptr<Client> client;
    ptr<Logger> logger;
};

NSP_CLIENT_END
