#include "logger.h"
#include <QScrollBar>

QString debugHTML = "<font color=\"gray\">";
QString infoHTML = "<font color=\"black\">";
QString warningHTML = "<font color=\"yellow\">";
QString errorHTML = "<font color=\"orange\">";
QString criticalHTML = "<font color=\"red\">";
QString endHTML = "</font><br>";

Logger::Logger(QObject *parent,
               QString fileName,
               QTextEdit *editor) : QObject(parent)
{
    m_editor = editor;
    m_showDate = true;
    loggerLevel = Level::INFO;
    sb = m_editor->verticalScrollBar();
    if (!fileName.isEmpty()) {
        file = new QFile;
        file->setFileName(fileName);
        file->open(QIODevice::Truncate | QIODevice::Append | QIODevice::Text);
    }
}

void Logger::write(const QString &value) {

    QString text = value;

    if (m_showDate) {
        text = QDateTime::currentDateTime()
                /*.toString("dd.MM.yyyy hh:mm:ss ") + text;*/
                .toString("hh:mm:ss:  ") + text;
    }
    QTextStream out(file);
    out.setCodec("UTF-8");

    if (file != 0) {
        out << text + "\n";
    } else {
        //TODO: add QMessageBox here with error
    }

    //Adds HTML color/formatting
    switch(loggerLevel)
    {
        case DEBUG: text = debugHTML + text; break;
        case INFO: text = infoHTML + text; break;
        case WARNING: text = warningHTML + text; break;
        case ERROR: text = errorHTML + text; break;
        case CRITICAL: text = criticalHTML + text; break;
        default: text = infoHTML + text; break;
    }
    text = text + endHTML;

    if (m_editor != 0) {
        m_editor->insertHtml(text);
        sb->setValue(sb->maximum());
    } else {
        //TODO: add QMessageBox here with error
    }
}

void Logger::write(const Level &level, const QString &value) {
    Level prevLoggerLevel = Logger::getLevel();
    Logger::setLevel(level);
    write(value);
    Logger::setLevel(prevLoggerLevel);
}

//--------Setters--------
void Logger::setLevel(const Level &level) {
    loggerLevel = level;
}

//-------Getters--------
Logger::Level Logger::getLevel() const {
    return loggerLevel;
}

void Logger::setShowDateTime(bool value) {
    m_showDate = value;
}


Logger::~Logger() {
    if (file != 0) {
        file->close();
    }
}
