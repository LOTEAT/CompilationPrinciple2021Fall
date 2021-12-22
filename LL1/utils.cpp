#include "utils.h"
#include <QMessageBox>
Utils::Utils()
{

}

void Utils::alert_message(QString title, QString content, QString type){
    QMessageBox messagebox;
    messagebox.setWindowTitle(title);
    messagebox.setText(content);
    messagebox.exec();
}
