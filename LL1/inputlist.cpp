#include "inputlist.h"
#include <QDebug>
InputList::InputList(QWidget *parent):QListWidget(parent)
{
    initAddItem();
    setSelectionMode(QAbstractItemView::NoSelection);
    setStyleSheet("QListWidget{border:1px solid #DCDFE6; border-radius: 6px; background-color: #F8F8F8;}");
}

void InputList::initAddItem()
{
    addBtn = new QPushButton();
    addBtn->setFlat(true);
    addBtn->setIcon(QIcon(":/pic/add.png"));
    addBtn->setStyleSheet("QPushButton{border:none;} "
                          "QPushButton:hover{background-color: rgb(224,224,224);}");
    connect(addBtn, &QPushButton::clicked, this, &InputList::clickAddItem);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(addBtn);
    QWidget* w = new QWidget(this);
    w->setLayout(layout);
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 40));
    addItem(item);
    setItemWidget(item, w);
}

void InputList::clickAddItem()
{
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 40));
    insertItem(count() - 1, item);
    item->setWhatsThis(QString::number(curId));
    InputListItem* w = new InputListItem(curId++);
    productions.push_back(w);
    setItemWidget(item, w);
}

void InputList::deleteById(int id)
{
    QString idString = QString::number(id);
    for(int i = 0; i < count(); ++i)
        if(item(i)->whatsThis() == idString)
        {
            takeItem(i);
            productions.erase(productions.begin() + i);
            break;
        }
}

void InputList::addInputItem(QString left, QString right)
{
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 40));
    insertItem(count() - 1, item);
    item->setWhatsThis(QString::number(curId));
    InputListItem* w = new InputListItem(curId++);
    w->setItem(left, right);
    setItemWidget(item, w);
    productions.push_back(w);
}

QStringList InputList::getInput(){
    QStringList production_list;
    for(auto production : productions){
        production_list.push_back(production->getItem());
    }
    return production_list;
}
