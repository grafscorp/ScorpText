#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QString>
#include <QList>
#include <QFileInfo>
#include <QDir>
#include <QMap>

class filemanager
{
public:
    filemanager();

    QString getFileNameFromDir(QString);
    QString getFilePathFromDir(QString);

    QList<QString> getAllFilesFroomDir(QString);
    //Check directory, if is file return true
    bool isFile(QString dir);
};

#endif // FILEMANAGER_H
