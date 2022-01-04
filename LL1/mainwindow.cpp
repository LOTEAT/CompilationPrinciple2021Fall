#include "mainwindow.h"
#include "utils.h"
#include <QFileDialog>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QFont titleFont;
    titleFont.setPointSize(35);
    title = new QLabel(QString::fromLocal8Bit("自上而下语法分析"));
    title->setFont(titleFont);
    author = new QLabel(QString::fromLocal8Bit("1950055 余文迪\t1952218 许王子路\t1952230 朱增乐"));
    QFont subTitleFont;
    subTitleFont.setPointSize(15);
    experimentTitle = new QLabel(QString::fromLocal8Bit("消除左递归算法"));
    experimentTitle->setFont(subTitleFont);
    inputString = new QLabel(QString::fromLocal8Bit("输入串"));

    horizontalLine = new QFrame(this);
    horizontalLine->setFrameShape(QFrame::HLine);
    horizontalLine->setFrameShadow(QFrame::Plain);

    experimentSelect = new QComboBox(this);
    QStringList experimentSelectNames = {QString::fromLocal8Bit("算法 2.1："), QString::fromLocal8Bit("算法 2.2："),
                                         QString::fromLocal8Bit("算法 2.3："), QString::fromLocal8Bit("算法 2.4："),
                                         QString::fromLocal8Bit("算法 2.5："), QString::fromLocal8Bit("算法 2.6："),
                                         QString::fromLocal8Bit("算法 2.7："), QString::fromLocal8Bit("综合实验")};


    experimentSelect->addItems(experimentSelectNames);
    connect(experimentSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(experimentChanged(int)));

    importBtn = new QPushButton();
    importBtn->setFixedSize(20,20);
    importBtn->setFlat(true);
    importBtn->setIcon(QIcon(":/pic/import.png"));
    importBtn->setStyleSheet("QPushButton{border:none;} "
                              "QPushButton:hover{background-color: rgb(224,224,224);}");
    connect(importBtn, SIGNAL(clicked()), this, SLOT(clickImportBtn()));

    confirmBtn = new QPushButton();
    confirmBtn->setFixedSize(20,20);
    confirmBtn->setFlat(true);
    confirmBtn->setIcon(QIcon(":/pic/refresh.png"));
    confirmBtn->setStyleSheet("QPushButton{border:none;} "
                              "QPushButton:hover{background-color: rgb(224,224,224);}");
    connect(confirmBtn, SIGNAL(clicked()), this, SLOT(clickConfirmBtn()));


    pictureBtn = new QPushButton();
    pictureBtn->setFixedSize(20,20);
    pictureBtn->setFlat(true);
    pictureBtn->setIcon(QIcon(":/pic/picture.png"));
    pictureBtn->setStyleSheet("QPushButton{border:none;} "
                              "QPushButton:hover{background-color: rgb(224,224,224);}");
    pictureBtn->setEnabled(false);

    inputStringEdit = new QLineEdit();
    inputStringEdit->setMaximumWidth(0);

    display = new Display();

    QHBoxLayout* subTitleLayout = new QHBoxLayout();
    subTitleLayout->addWidget(experimentSelect);
    subTitleLayout->addStretch();
    subTitleLayout->addWidget(experimentTitle);
    subTitleLayout->addStretch();

    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->addWidget(importBtn);
    controlLayout->addStretch();
    controlLayout->addWidget(inputStringEdit);
    controlLayout->addWidget(confirmBtn);
    controlLayout->addStretch();
    controlLayout->addWidget(pictureBtn);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(title, 0, Qt::AlignHCenter);
    layout->addWidget(author, 0, Qt::AlignRight);
    layout->addWidget(horizontalLine);
    layout->addLayout(subTitleLayout);
    layout->addLayout(controlLayout);
    layout->addWidget(display);

    QWidget* widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);
    setStyleSheet(".MainWindow{background-color: white}");
}

MainWindow::~MainWindow()
{
}

void MainWindow::experimentChanged(int index)
{
    QString experimentNames[] = {QString::fromLocal8Bit("消除左递归算法"),QString::fromLocal8Bit("提取公共左因子法"),
                                 QString::fromLocal8Bit("FIRST 集合构造算法"),QString::fromLocal8Bit("FOLLOW 集合构造算法"),
                                QString::fromLocal8Bit("递归下降分析程序构造算法"),QString::fromLocal8Bit("LL(1)分析表生成算法"),
                                 QString::fromLocal8Bit("预测分析程序构造算法"),
                                 QString::fromLocal8Bit("基于 LL(1)预测分析法的语法分析程序生成器")};
    experimentTitle->setText(experimentNames[index]);
    inputStringEdit->clear();
    inputStringEdit->setMaximumWidth(0);
    importBtn->setEnabled(true);
    pictureBtn->setEnabled(false);

    switch (index) {
    case 0:
        display->setText(QString::fromLocal8Bit("文法产生式"), "", QString::fromLocal8Bit("消除左递归后的等价文法产生式"));
        break;
    case 1:
        display->setText(QString::fromLocal8Bit("文法产生式"), "", QString::fromLocal8Bit("消除左递归后的等价文法产生式"));
        break;
    case 2:
        display->setText(QString::fromLocal8Bit("文法产生式"), "", QString::fromLocal8Bit("所有候选式的FIRST集合"));
        break;
    case 3:
        display->setText(QString::fromLocal8Bit("文法产生式"), "", QString::fromLocal8Bit("所有非终结符的FOLLOW集合"));
        break;
    case 4:
        display->setText(QString::fromLocal8Bit("LL(1)文法产生式"), "", QString::fromLocal8Bit("推导过程所用产生式"));
        inputStringEdit->setMaximumWidth(QWIDGETSIZE_MAX);
        pictureBtn->setEnabled(true);
        break;
    case 5:
        display->setText(QString::fromLocal8Bit("LL(1)文法产生式"), QString::fromLocal8Bit("LL(1)分析表"), "");
        break;
    case 6:
        display->setText("", QString::fromLocal8Bit("LL(1)分析表"), QString::fromLocal8Bit("推导过程所用产生式"));
        inputStringEdit->setMaximumWidth(QWIDGETSIZE_MAX);
        importBtn->setEnabled(false);
        pictureBtn->setEnabled(true);
        break;
    case 7:
        display->setText(QString::fromLocal8Bit("上下文无关文法"), QString::fromLocal8Bit("LL(1)分析表"), QString::fromLocal8Bit("推导过程所用产生式"));
        inputStringEdit->setMaximumWidth(QWIDGETSIZE_MAX);
        pictureBtn->setEnabled(true);
        break;
    }
}

void MainWindow::clickImportBtn(){
    this->file_name = QFileDialog::getOpenFileName(this, "Open file","G:/programs/QT/compile/LL1/test","Text files (*.txt)");
    QFile ll1_file(file_name);

    /***********TODO*************/
    // These may be better.
    if(!ll1_file.exists()){
        Utils::alert_message("upload", "error!");
    }
    Utils::alert_message("upload", "ok!");
    /***********TODO*************/
    bool flag = false;
    // open file
    if (ll1_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!ll1_file.atEnd())
        {
            QString line = ll1_file.readLine();
            // remove '\n'
            line = line.trimmed();
            QStringList line_split = line.split("->");
            display->addInputItem(line_split[0], line_split[1]);
        }
        ll1_file.close();
    }
}

void MainWindow::clickConfirmBtn(){
    int id = experimentSelect->currentIndex();
    display->showOutput(id, inputStringEdit->text());
}

