#ifndef PARSER_H
#define PARSER_H
#include <QDebug>
#include <QString>
#include <vector>
#include <QFile>
#include <QVector>
#include <QMessageBox>
#include <QMap>
class Parser{
private:
    QString start;
    QString file_name;
    // Terminator
    QVector<QString> VT;
    // Non-Terminator
    QVector<QString> VN;
    // production
    QMap<QString, QVector<QString> > production;


    // parse line
    bool parse_line(QString line);
    // add production
    void add_production(QString left, QString right);
    // add VT
    void add_VT();


public:
    Parser(QString input_file): file_name(input_file){}
    Parser(){file_name = "";}

    // parse
    bool parse_file();
    void parse_input(){}

    // set file name
    void set_file_name(QString file_name);

    // TODO
    // Is it the best way to share data?
    // define friend class
    friend class Grammar;
    friend class LL1;

};



#endif // PARSER_H
