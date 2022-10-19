/*
 * file: logger.hpp
 * author: filebin
 * date: 2022-10-19 14:38:58
 */

#include "stdafx.hpp"
#include <qobject.h>
#include <qtmetamacros.h>

NSP_CLIENT_BEGIN
class Logger;
NSP_CLIENT_END

#pragma once

NSP_CLIENT_BEGIN

class Logger : public QObject {
    Q_OBJECT
  public:
    enum Level { Info, Critical, Warning };
    Logger(QObject *parent);
    void info(QString line);
    void critical(QString line);
    void warning(QString line);
  signals:
    void logged(Level lvl, QString line);

  private:
};

NSP_CLIENT_END