#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include "display.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void experimentChanged(int index);
    void clickImportBtn();
    void clickConfirmBtn();
private:
    QString file_name = "";
    QLabel* title;
    QLabel* author;
    QLabel* experimentTitle;
    QLabel* inputString;
    QPushButton* importBtn;
    QPushButton* confirmBtn;
    QPushButton* pictureBtn;
    QLineEdit* inputStringEdit;
    QFrame* horizontalLine;
    QComboBox* experimentSelect;
    Display* display;

};
#endif // MAINWINDOW_H
