#ifndef OPENEDFILE_H
#define OPENEDFILE_H

#include <QString>

class OpenedFile
{
public:
    OpenedFile();
    OpenedFile(QString name, QString displayName, QString path)
        : name(std::move(name)), displayName(std::move(displayName)),
        path(std::move(path)) {}

    QString getDir();
    void setName(QString);
    void setDisplayName(QString);
    void setPath(QString);
    QString getName();
    QString getPath();
    QString getDisplayName();
private:
        QString name, displayName, path;
};

#endif // OPENEDFILE_H
