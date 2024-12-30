#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QList>
#include <tabtextedit.h>
#include "filemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;
    filemanager fManager;
    void clearTabWidget();
    void updateTabWidget();

    QString getTextFromTab(int);

    //File actions
    void openNewFile();
    void openFile();
    void saveFile();
    void saveFileAs();


};
#endif // MAINWINDOW_H
