#ifndef UTILS_H
#define UTILS_H
#include<QString>

class Utils
{
public:
    Utils();
    // message box
    static void alert_message(QString title, QString content, QString type="null");
};

#endif // UTILS_H
