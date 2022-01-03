#include "analysistable.h"

AnalysisTable::AnalysisTable(QWidget *parent):QWidget(parent)
{
    table = new QTableWidget();
    rowLabel = new QLabel(QString::fromUtf8("行:"));
    colLabel = new QLabel("列:");
    addRowBtn = new QPushButton();
    addRowBtn->setFlat(true);
    addRowBtn->setIcon(QIcon(":/pic/add.png"));
    addRowBtn->setStyleSheet("QPushButton{border:none;} "
                             "QPushButton:hover{background-color: rgb(224,224,224);}");
    addColBtn = new QPushButton();
    addColBtn->setFlat(true);
    addColBtn->setIcon(QIcon(":/pic/add.png"));
    addColBtn->setStyleSheet("QPushButton{border:none;} "
                             "QPushButton:hover{background-color: rgb(224,224,224);}");
    subRowBtn = new QPushButton();
    subRowBtn->setFlat(true);
    subRowBtn->setIcon(QIcon(":/pic/sub.png"));
    subRowBtn->setStyleSheet("QPushButton{border:none;} "
                             "QPushButton:hover{background-color: rgb(224,224,224);}");
    subColBtn = new QPushButton();
    subColBtn->setFlat(true);
    subColBtn->setIcon(QIcon(":/pic/sub.png"));
    subColBtn->setStyleSheet("QPushButton{border:none;} "
                             "QPushButton:hover{background-color: rgb(224,224,224);}");
    connect(addRowBtn, &QPushButton::clicked, this, &AnalysisTable::addRow);
    connect(addColBtn, &QPushButton::clicked, this, &AnalysisTable::addCol);
    connect(subRowBtn, &QPushButton::clicked, this, &AnalysisTable::subRow);
    connect(subColBtn, &QPushButton::clicked, this, &AnalysisTable::subCol);

    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->addStretch();
    controlLayout->addWidget(rowLabel);
    controlLayout->addWidget(addRowBtn);
    controlLayout->addWidget(subRowBtn);
    controlLayout->addStretch();
    controlLayout->addWidget(colLabel);
    controlLayout->addWidget(addColBtn);
    controlLayout->addWidget(subColBtn);
    controlLayout->addStretch();

    controlWidget = new QWidget();
    controlWidget->setLayout(controlLayout);
    setControl(false);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(table);
    layout->addWidget(controlWidget);

    setLayout(layout);
}

void AnalysisTable::addRow()
{
    table->insertRow(table->rowCount());
}

void AnalysisTable::addCol()
{
    table->insertColumn(table->columnCount());
}

void AnalysisTable::subRow()
{
    if(table->rowCount())
        table->removeRow(table->rowCount() - 1);
}

void AnalysisTable::subCol()
{
    if(table->columnCount())
        table->removeColumn(table->columnCount() - 1);
}
