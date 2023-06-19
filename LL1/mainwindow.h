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
#include "picturedialog.h"


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
    void clickPictureBtn();
private:
    QString file_name = "";
    QLabel* title;
    QLabel* author;
    QLabel* experimentTitle;
    QLabel* inputString;
    QLabel* begin;
    QLabel* pattern;
    QPushButton* importBtn;
    QPushButton* confirmBtn;
    QPushButton* pictureBtn;
    QLineEdit* beginEdit;
    QLineEdit* patternEdit;
    QFrame* horizontalLine;
    QComboBox* experimentSelect;
    Display* display;
    PictureDialog* picture;
};
#endif // MAINWINDOW_H
