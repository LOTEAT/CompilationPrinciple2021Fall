#ifndef LL1_H
#define LL1_H

#include "grammar.h"
#include <QStack>
class LL1
{
private:
    Grammar grammar;
    QVector<QString> production_in_derive;
    QMap<QPair<QString, QString>, QString> ll1_table;
    QStack<QString> analysis;
    int parse_index;
    bool is_parse_success;
public:
    // non-arg constructor
    LL1():parse_index(0){}
    // constructor with grammar arg
    LL1(Grammar grammar): grammar(grammar),parse_index(0){}
    // set grammar
    void set_grammar(Grammar grammar);
    // sub program
    void sub_program(QString vn, QStringList input_list);
    // recursive descent algorithm
    bool recursive_descent(QString str);
    // generate ll1 analysis table
    void generate_ll1_analysis_table();
    // LL1 parser
    void parse(QString input);

};

#endif // LL1_H
