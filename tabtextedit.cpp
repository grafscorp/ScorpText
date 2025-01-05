#include "tabtextedit.h"
#include "ui_tabtextedit.h"

tabTextEdit::tabTextEdit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tabTextEdit)
{
    ui->setupUi(this);
}

tabTextEdit::tabTextEdit(QString text, QWidget *parent)    : QWidget(parent)
    , ui(new Ui::tabTextEdit)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}


tabTextEdit::~tabTextEdit()
{
    delete ui;
}
