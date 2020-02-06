#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QPlainTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class Logger : public QObject
{
    Q_OBJECT
public:
    enum Level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };
    explicit Logger(QObject *parent= nullptr,
                    QString fileName = nullptr,
                    QTextEdit *editor = nullptr);
    ~Logger();
    void setShowDateTime(bool value);
    void setLevel(const Level &level);
    Level getLevel() const;

private:
    QFile *file;
    QTextEdit *m_editor;
    bool m_showDate;
    Level loggerLevel;
    QScrollBar *sb;


signals:

public slots:
    void write(const QString &value);
    void write(const Level &level, const QString &value);

};

#endif // LOGGER_H
