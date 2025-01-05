#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen, &QAction::triggered,[this](bool){openFile("");});
    connect(ui->actionSave, &QAction::triggered,[this](bool){saveFile();});
    connect(ui->actionSave_as, &QAction::triggered,[this](bool){saveFileAs();});
    connect(ui->actionNew, &QAction::triggered,[this](bool){openNewFile();});
    connect(ui->actionOpen_Folder,&QAction::triggered, [this](bool){openFolder();});

    //ui->tabWidget->clear();
    updateTabWidget();

}

MainWindow::~MainWindow()
{
    delete ui;
}
//Tab Widget
void MainWindow::clearTabWidget()
{
    for (int i = 0; i <= ui->tabWidget->count();i++)
    {
        ui->tabWidget->removeTab(0);

    }
    clearTreeWidget();

}

void MainWindow::updateTabWidget()
{
    clearTabWidget();
    size_t tabsCount = openFilesManager.countOpenedFiles();
    for(size_t i =0; i < tabsCount; i++)
    {
        ui->tabWidget->addTab(new tabTextEdit, openFilesManager.getDisplatNameOfIndex(i));
        // ui->tabWidget.s
    }
}

QString MainWindow::getTextFromTab(int i = 0)
{
    QTextEdit* pTextEdit = NULL;
    QWidget* pWidget = ui->tabWidget->widget(ui->tabWidget->currentIndex());
    if(pWidget->metaObject()->className() == "QTextEdit")
    {
        pTextEdit = (QTextEdit*)pWidget;
    }else{
        QList<QTextEdit*> allTextEdit = pWidget->findChildren<QTextEdit*>();
        if (allTextEdit.count() < 1)
        {
            qWarning()<<"Cant find text editor in tab";
            return "";
        }
        pTextEdit = allTextEdit[0];
    }
    return pTextEdit->toPlainText();
}
//TreeWidget
void MainWindow::clearTreeWidget()
{
    ui->treeWidget->headerItem()->setText(0,"");
    ui->treeWidget->topLevelItemCount();
    int itemCount = ui->treeWidget->topLevelItemCount();
    for(int i = 0 ; i < itemCount; i++)
    {
        ui->treeWidget->takeTopLevelItem(0)->text(0);
        //ui->treeWidget->removeItemWidget(ui->treeWidget->takeTopLevelItem(1),0);
    }
}

void MainWindow::openTreeWidget(QString fileDir)
{
    clearTreeWidget();
    if(fileDir == "") return;
    ui->treeWidget->headerItem()->setText(0,fileDir);
    QList<QString> files = fileManager.getAllFilesFroomDir(fileDir);
    for (auto fileName : files)
    {
        QTreeWidgetItem* newFileItem = new QTreeWidgetItem(ui->treeWidget);
        newFileItem->setText(0, fileName);
        QIcon icon = fileManager.isFile(fileDir + "/"+fileName)?QIcon(":/icons/docs.png"):QIcon(":/icons/folder.png");
        newFileItem->setIcon(0, icon);
        ui->treeWidget->addTopLevelItem(newFileItem);
    }
}

//Actions
void MainWindow::openNewFile()
{
    openFilesManager.addElement("untitled","");
    ui->tabWidget->addTab(new tabTextEdit,openFilesManager.getDisplatNameOfIndex(openFilesManager.countOpenedFiles()-1));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

void MainWindow::openFile(QString file_dir ="")
{
    if (file_dir == "") file_dir = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_dir);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Error","File not open");
        return;
    }
    QTextStream in(&file);
    QString dataFile = in.readAll();

    if (openFilesManager.getIndexOfDisplayName(fileManager.getFileNameFromDir(file_dir))!=-1) return;
    openFilesManager.addElement(fileManager.getFileNameFromDir(file_dir), fileManager.getFilePathFromDir(file_dir));
    //qInfo() << openFilesManager.openedFilesList.last().getDisplayName();
    ui->tabWidget->addTab(new tabTextEdit(dataFile), openFilesManager.getDisplatNameOfIndex(openFilesManager.countOpenedFiles()-1));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    // openFilesManager.addFileFromFilePath(file_dir);
    // openTreeWidget(openFilesManager.getFilePathFromDir(file_dir));
    file.close();
}

void MainWindow::saveFile()
{
    QString filePath = openFilesManager.getPathOfDisplayName(ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    if (filePath == "" || filePath =="None")
    {
        saveFileAs();
    }


    auto file_dir = openFilesManager.getDirOfDisplayName(ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    QFile file(file_dir);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Error","File not open");
        return;
    }

    QTextStream out(&file);

    out << getTextFromTab();
    //openTreeWidget(filePath);
    file.flush();
    file.close();
}

void MainWindow::saveFileAs()
{
    QString file_dir = QFileDialog::getSaveFileName(this,"Save file");
    QFile file(file_dir);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Error","File not open");
        return;
    }
    QTextStream out(&file);
    out << getTextFromTab();
    QString newFileName = fileManager.getFileNameFromDir(file_dir);
    QString newFilePath = fileManager.getFilePathFromDir(file_dir);
    openFilesManager.deleteElement(openFilesManager.getIndexOfDisplayName(ui->tabWidget->tabText(ui->tabWidget->currentIndex())));
    openFilesManager.addElement(newFileName, newFilePath);

    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), openFilesManager.getDisplatNameOfIndex(openFilesManager.countOpenedFiles()-1));
    // openTreeWidget(newFilePath);
    qInfo() << newFilePath;
    openTreeWidget(newFilePath);
    file.flush();
    file.close();
}

void MainWindow::openFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this,"Open Folder");
    openTreeWidget(dir);
}





//Signals
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QString dName = ui->tabWidget->tabText(index);
    int indexOfFile = openFilesManager.getIndexOfDisplayName(dName);
    openFilesManager.deleteElement(indexOfFile);
    // openFilesManager.getAllFilesPath();
    // openFilesManager.deleteOpenedFile(ui->tabWidget->tabText(index));
    ui->tabWidget->removeTab(index);
}


void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{

     QString file_dir = item->treeWidget()->headerItem()->text(column)  + "/"+ item->text(column);
    fileManager.isFile(file_dir)?openFile(file_dir):openTreeWidget(file_dir);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == -1) {
        clearTreeWidget();
        return;
    }
    int currentFileIndex = openFilesManager.getIndexOfDisplayName(ui->tabWidget->tabText(index));
    QString filePath = openFilesManager.getPathOfIndex(currentFileIndex);
    openTreeWidget(filePath);
}

