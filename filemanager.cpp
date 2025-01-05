#include "filemanager.h"

filemanager::filemanager() {

}


QString filemanager::getFilePathFromDir(QString fileDir)
{
    return fileDir.left(fileDir.lastIndexOf('/'));
}



QList<QString> filemanager::getAllFilesFroomDir(QString path)
{
    QList<QString> files;
    QDir dir(path);
    foreach (QFileInfo item, dir.entryInfoList() )
    {
        // if(item.isFile())
        // {
        //     files.append(item.fileName());
        // }
        files.append(item.fileName());
    }
    return files;
}

bool filemanager::isFile(QString dir)
{
    QFileInfo checkFile(dir);
    if(checkFile.exists() && checkFile.isFile()) return true;
    return false;
}



QString filemanager::getFileNameFromDir(QString fileDir)
{
    QString filePath = fileDir.left(fileDir.lastIndexOf('/'));
    QString fileName = fileDir.remove(0, filePath.size()+1);
    return fileName;

}
