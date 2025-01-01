#include "filemanager.h"

filemanager::filemanager() {
    openedFiles = {
                   {QString("untitled*"),QString("")}
        };
}

void filemanager::clearOpenedFiles()
{
    openedFiles.clear();
    openedFiles.insert(std::pair<QString,QString>("untitled*",""));
}

void filemanager::deleteOpenedFile(QString nameFile)
{
    const auto findNameFile = openedFiles.find(nameFile);
    if (findNameFile != openedFiles.end())
    openedFiles.erase(nameFile);


}

size_t filemanager::getSizeOpenedFiles()
{
    return openedFiles.size();
}

QString filemanager::getNameFileByIndex(int index)
{
    auto it = openedFiles.begin();
    std::advance(it,index);
    return it->first;
}

void filemanager::addFile(QString newFileName, QString newFilePath)
{
    openedFiles.insert(std::pair<QString,QString>(newFileName,newFilePath));
}

void filemanager::addFileFromFilePath(QString fileDir)
{
    openedFiles.insert(std::pair<QString,QString>(getFileNameFromDir(fileDir),getFilePathFromDir(fileDir)));
}

QString filemanager::getFilePathFromDir(QString fileDir)
{
    return fileDir.left(fileDir.lastIndexOf('/'));
}

QString filemanager::getDirFile(QString fileName)
{
    return openedFiles.at(fileName) +"/"+fileName;
}

QList<QString> filemanager::getAllFilesFroomDir(QString path)
{
    QList<QString> files;
    QDir dir(path);
    foreach (QFileInfo item, dir.entryInfoList() )
    {
        if(item.isFile())
        {
            files.append(item.fileName());
        }
    }
    return files;
}



QString filemanager::getFileNameFromDir(QString fileDir)
{
    QString filePath = fileDir.left(fileDir.lastIndexOf('/'));
    QString fileName = fileDir.remove(0, filePath.size()+1);
    return fileName;

}
