/*
 * file: logger.cpp
 * author: filebin
 * date: 2022-10-19 14:46:37
 */

#include "logger.hpp"
#include <qdebug.h>

NSP_CLIENT_BEGIN
Logger::Logger(QObject *parent) : QObject(parent) {}

void Logger::info(QString line) {
    qInfo() << line;
    emit logged(Info, line);
}
void Logger::warning(QString line) {
    qWarning() << line;
    emit logged(Warning, line);
}
void Logger::critical(QString line) {
    qCritical() << line;
    emit logged(Critical, line);
}
NSP_CLIENT_END
