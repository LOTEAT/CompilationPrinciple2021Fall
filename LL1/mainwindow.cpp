#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <qDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_upload_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open file","G:/programs/QT/compile/LL1","Text files (*.txt)");
    grammar.parse_file(file_name);
    //grammar.remove_left_recursion();
    grammar.extract_first_set();
    grammar.extract_candidate_first_set();
    qDebug() << "-----------";
    grammar.extract_follow_set();
    ll1.set_grammar(grammar);
    ll1.generate_ll1_analysis_table();
}
