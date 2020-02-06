#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class ConfigHandler : public QObject
{
    Q_OBJECT
public:
    explicit ConfigHandler(QObject *parent = nullptr);

private:
    QString fileName;
    QFile *file;


signals:

public slots:
    QString getData() const;
    void setData(const QString text);

};

#endif // CONFIGHANDLER_H
