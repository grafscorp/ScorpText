#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QString>
#include <map>

class filemanager
{
public:
    filemanager();
    //Filename, Filepath
    std::map<QString, QString> openedFiles={};
    void clearOpenedFiles();
    void deleteOpenedFile(QString);
    size_t getSizeOpenedFiles();
    //Returned key
    QString getNameFileByIndex(int);
    //add file to vector(FileName, FilePath)
    void addFile(QString, QString);
    void addFileFromFilePath(QString);
    QString getFileNameFromDir(QString);
    QString getFilePathFromDir(QString);
    QString getDirFile(QString);
};

#endif // FILEMANAGER_H
