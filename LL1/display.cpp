#include "display.h"

Display::Display(QWidget *parent):QWidget(parent)
{
    inputTitle = new QLabel(QString::fromLocal8Bit("输入"));
    tableTitle = new QLabel("");
    outputTitle = new QLabel(QString::fromLocal8Bit("输出"));

    inputList = new InputList();
    outputList = new QListWidget();
    outputList->setStyleSheet("border:1px solid #DCDFE6; border-radius: 6px; background-color: #F8F8F8;");

    analysisTable = new AnalysisTable();
    analysisTable->setMaximumWidth(0);

    QVBoxLayout* inputLayout = new QVBoxLayout();
    inputLayout->addWidget(inputTitle, 0, Qt::AlignHCenter);
    inputLayout->addWidget(inputList);

    QVBoxLayout* tableLayout = new QVBoxLayout();
    tableLayout->addWidget(tableTitle, 0, Qt::AlignHCenter);
    tableLayout->addWidget(analysisTable);

    QVBoxLayout* outputLayout = new QVBoxLayout();
    outputLayout->addWidget(outputTitle, 0, Qt::AlignHCenter);
    outputLayout->addWidget(outputList);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addLayout(inputLayout);
    layout->addLayout(tableLayout);
    layout->addLayout(outputLayout);
    setLayout(layout);
    parser = new Parser();
    grammar = new Grammar();
    ll1 = new LL1();
}

void Display::setText(const QString& input, const QString& table, const QString& output)
{
    inputTitle->setText(input);
    tableTitle->setText(table);
    outputTitle->setText(output);
    inputList->setHidden(!input.length());
    analysisTable->setHidden(!table.length());
    analysisTable->setControl(!input.length() && table.length());
    outputList->setMaximumWidth(output.length() ? QWIDGETSIZE_MAX : 0);
    outputList->clear();
}


void Display::addInputItem(QString left, QString right){
    inputList->addInputItem(left, right);
}


void Display::removeLeftRecursion(){
    inputList->getInput();

}

void Display::showOutput(int id){
    switch (id) {
    case 0:
        removeLeftRecursion();
    }
}
