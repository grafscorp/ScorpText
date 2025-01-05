#ifndef TABTEXTEDIT_H
#define TABTEXTEDIT_H

#include <QWidget>

namespace Ui {
class tabTextEdit;
}

class tabTextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit tabTextEdit(QWidget *parent = nullptr);
    tabTextEdit(QString text,QWidget *parent = nullptr);
    ~tabTextEdit();

private:
    Ui::tabTextEdit *ui;
};

#endif // TABTEXTEDIT_H
