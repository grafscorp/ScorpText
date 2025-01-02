#include "openedFilesManger.h"

FManager::FManager() {
    clearOpenedFiles();
}

void FManager::clearOpenedFiles()
{
    openedFilesList.clear();
    openedFilesList.append(OpenedFile("untitled","untitled",""));
}

// int FManager::findIndexByDisplayName(QString dName)
// {
//     for (int i = 0; i < openedFilesList.size(); i ++)
//     {
//         if (openedFilesList[i].getDisplayName() == dName) return i;
//     }
//     return -1;
// }

void FManager::deleteElement(int index)
{
    if (index == -1) return;
    openedFilesList.removeAt(index);
}

void FManager::addElement(QString name, QString dname, QString path)
{
    auto newFile = OpenedFile(name,setUniqFileDisplayName(dname),path);
    openedFilesList.append(newFile);
}

void FManager::addElement(QString name , QString path)
{
    auto newFile = OpenedFile(name,setUniqFileDisplayName(name),path);
    openedFilesList.append(newFile);
}


QString FManager::setUniqFileDisplayName(QString dName, int index )
{
    if (getIndexOfDisplayName(dName) == -1)
    {
        // if (index == 1) return dName;
        // else return dName +"("+ QString::number(index) + ")";
        return dName;
    }
    dName = dName + "("+ QString::number(index) + ")";
    return setUniqFileDisplayName(dName, index+1);
}

size_t FManager::countOpenedFiles()
{
    return openedFilesList.size();
}

QString FManager::getDisplatNameOfIndex(int index )
{
    if (index == -1) return "None";
    return openedFilesList[index].getDisplayName();
}

QString FManager::getPathOfIndex(int index)
{
    if (index == -1) return "None";
    return openedFilesList[index].getPath();
}

QString FManager::getPathOfDisplayName(QString dName)
{
    if (dName == "") return "None";
    for (int i = 0;i < openedFilesList.size();i++)
    {
        if (openedFilesList[i].getDisplayName() == dName)
        {
            return openedFilesList[i].getPath();
        }
    }
    return "None";
}

QString FManager::getDirOfIndex(int index)
{
    if (index == -1) return "None";
return openedFilesList[index].getDir();
}

QString FManager::getDirOfDisplayName(QString dName)
{
    for (int i = 0; i < openedFilesList.size(); i++)
    {
        if (openedFilesList[i].getDisplayName() == dName) return openedFilesList[i].getDir();
    }
    return "None";
}

int FManager::getIndexOfDisplayName(QString dName)
{
    for (int i =0;i < openedFilesList.size();i++)
    {
        if (openedFilesList[i].getDisplayName() == dName)
        {
            return i;
        }
    }
    return -1;
}

QString FManager::getAllFilesPath()
{
    QString allFilesPath ="";
    for (int i = 0; i < openedFilesList.size();i++)
    {
        allFilesPath += openedFilesList[i].getDir() + " ";
    }
    return allFilesPath;
}

