#include "openedfile.h"

OpenedFile::OpenedFile() {}

QString OpenedFile::getDir()
{
    return path + "/" + name;
}

void OpenedFile::setName(QString name)
{
    this->name = name;
}

void OpenedFile::setDisplayName(QString dName){
    displayName = dName;
}
void OpenedFile::setPath(QString path){
    this->path = path;
}
QString OpenedFile::getName() {
    return name;
}

QString OpenedFile::getPath(){
    return path;
}
QString OpenedFile::getDisplayName(){
    return displayName;
}
