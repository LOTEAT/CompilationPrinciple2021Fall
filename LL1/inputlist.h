#ifndef INPUTLIST_H
#define INPUTLIST_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAbstractItemView>
#include "inputlistitem.h"


class InputList:public QListWidget
{
    Q_OBJECT
public:
    InputList(QWidget* parent = nullptr);
    void setHidden(bool b) {setMaximumWidth(b ? 0 : QWIDGETSIZE_MAX);}
    void deleteById(int id);
    void addInputItem(QString left, QString right);
    void getInput();
public slots:
    void clickAddItem();
private:
    void initAddItem();
    int curId = 0;
    QPushButton* addBtn;
};

#endif // INPUTLIST_H
