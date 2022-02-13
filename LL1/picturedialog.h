#ifndef PICTUREDIALOG_H
#define PICTUREDIALOG_H

#include <QDialog>
#include <QLabel>


class PictureDialog:QDialog
{
public:
    PictureDialog(QWidget *parent = nullptr);
    void showPic();
private:
    QLabel* pic;
};

#endif // PICTUREDIALOG_H
