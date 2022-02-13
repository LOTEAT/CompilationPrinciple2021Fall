#include "picturedialog.h"
#include "QCoreApplication"

PictureDialog::PictureDialog(QWidget *parent):QDialog(parent)
{
    pic = new QLabel(this);
}

void PictureDialog::showPic(){
    QString fileName = QCoreApplication::applicationDirPath() + "/dot/result.png";
    pic->setPixmap(QPixmap(fileName));
    pic->show();
    show();
}
