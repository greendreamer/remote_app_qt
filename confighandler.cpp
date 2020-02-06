#include "confighandler.h"



ConfigHandler::ConfigHandler(QObject *parent) : QObject(parent)
{
    fileName = "./config.txt";
    file = new QFile;
    file->setFileName(fileName);
}

QString ConfigHandler::getData() const
{
    if (QFile::exists(fileName)) {
        file->open(QIODevice::ReadWrite | QIODevice::Text);
        QString data = file->readAll();
        file->close();
        return data;
    } else {
        return "";
    }
}

//Will create a file if there is none
//If there is a file, it will clear the text and write the new text
void ConfigHandler::setData(const QString text)
{
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    file->resize(0);
    QTextStream out(file);
    out.setCodec("UTF-8");
    out << text;
    file->close();
}
