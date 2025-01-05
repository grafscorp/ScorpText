#ifndef OPENEDFILESMANGER_H
#define OPENEDFILESMANGER_H

#include <QString>
#include <QMap>
#include <QList>
#include <openedfile.h>
class FManager
{
public:
    FManager();
    QList<OpenedFile> openedFilesList;

    void clearOpenedFiles();
    //Returned index of element with this disaplyname, return -1 if that element didnt found
    void deleteElement(int);
    //name,disaplay name , path
    void addElement(QString, QString,QString);
    //add name, path
    void addElement(QString,QString);
    QString setUniqFileDisplayName(QString, int = 1);

    size_t countOpenedFiles();

    QString getDisplatNameOfIndex(int);
    QString getPathOfIndex(int);
    QString getPathOfDisplayName(QString);
    QString getDirOfIndex(int);
    QString getDirOfDisplayName(QString);
    int getIndexOfDisplayName(QString);

    QString getAllFilesPath();
};

#endif // OPENEDFILESMANGER_H
