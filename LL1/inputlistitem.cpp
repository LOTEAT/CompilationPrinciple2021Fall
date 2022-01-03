#include "inputlistitem.h"
#include "inputlist.h"

InputListItem::InputListItem(int id, QWidget *parent):QWidget(parent)
{
    this->id = id;

    arrow = new QLabel();
    QImage *img=new QImage;
    img->load(":/pic/arrow.png");
    arrow->setPixmap(QPixmap::fromImage(*img));
    arrow->setScaledContents(true);

    leftText = new QLineEdit();
    leftText->setAlignment(Qt::AlignHCenter);
    rightText = new QLineEdit();
    rightText->setAlignment(Qt::AlignHCenter);

    deleteBtn = new QPushButton();
    deleteBtn->setFlat(true);
    deleteBtn->setFixedSize(20, 20);
    deleteBtn->setIcon(QIcon(":/pic/delete.png"));
    deleteBtn->setStyleSheet("QPushButton{border:none;} "
                          "QPushButton:hover{background-color: rgb(224,224,224);}");
    connect(deleteBtn, &QPushButton::clicked, this, &InputListItem::clickDeleteBtn);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(leftText);
    layout->addWidget(arrow);
    layout->addWidget(rightText);
    layout->addStretch();
    layout->addWidget(deleteBtn);
    setLayout(layout);
}

void InputListItem::setItem(QString left, QString right){
    leftText->setText(left);
    rightText->setText(right);
}

void InputListItem::clickDeleteBtn()
{
    static_cast<InputList*>(parent()->parent())->deleteById(id);
}


