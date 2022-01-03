#ifndef INPUTLISTITEM_H
#define INPUTLISTITEM_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class InputListItem: public QWidget
{
public:
    InputListItem(int id, QWidget* parent = nullptr);
    void setItem(QString left, QString right);
public slots:
    void clickDeleteBtn();
private:
    int id;
    QLabel* arrow;
    QLineEdit* leftText;
    QLineEdit* rightText;
    QPushButton* deleteBtn;
};

#endif // INPUTLISTITEM_H
