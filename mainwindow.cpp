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

    //ui->tabWidget->clear();
    updateTabWidget();

}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    size_t tabsCount = fManager.getSizeOpenedFiles();
    for(size_t i =0; i < tabsCount; i++)
    {
        ui->tabWidget->addTab(new tabTextEdit, fManager.getNameFileByIndex(i));
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
    ui->treeWidget->headerItem()->setText(0,fileDir);
    QList<QString> files = fManager.getAllFilesFroomDir(fileDir);
    for (auto fileName : files)
    {
        QTreeWidgetItem* newFileItem = new QTreeWidgetItem(ui->treeWidget);
        newFileItem->setText(0, fileName);
        ui->treeWidget->addTopLevelItem(newFileItem);
    }

}

void MainWindow::openNewFile()
{
    ui->tabWidget->addTab(new tabTextEdit,QString("untitled*"));
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
    ui->tabWidget->addTab(new tabTextEdit(dataFile), fManager.getFileNameFromDir(file_dir));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    fManager.addFileFromFilePath(file_dir);
    openTreeWidget(fManager.getFilePathFromDir(file_dir));
    file.close();
}

void MainWindow::saveFile()
{
    auto file_dir = fManager.getDirFile(ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    QFile file(file_dir);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Error","File not open");
        return;
    }

    QTextStream out(&file);

    out << getTextFromTab();
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
    QString newFileName = fManager.getFileNameFromDir(file_dir);
    QString newFilePath = fManager.getFilePathFromDir(file_dir);
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), newFileName);
    fManager.addFile(newFileName,newFilePath);
    openTreeWidget(newFilePath);
    file.flush();
    file.close();
}






void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    fManager.deleteOpenedFile(ui->tabWidget->tabText(index));
    ui->tabWidget->removeTab(index);
}


void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //qInfo()<< item->treeWidget()->headerItem()->text(column);
    //qInfo()<< item->text(column);
     QString file_dir = item->treeWidget()->headerItem()->text(column)  + "/"+ item->text(column);
     //qInfo()<< file_dir;
    openFile(file_dir);
}

