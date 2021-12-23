#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <QSet>
#include <QMap>
#include "parser.h"
class Grammar
{
private:
    Parser parser;
    QMap<QString, QSet<QString> > first;
    QMap<QString, QSet<QString> > first_candidate;
    QMap<QString, QSet<QString> > follow;
    // remove direct left recursion
    void remove_direct_left_recursion(QString left);
    // remove indirect left recursion
    void remove_indirect_left_recursion();
    // match min prefix
    QString min_prefix(QString str1, QString str2);
    // extract the left common factor for one vn
    void left_common_for_one_production(QString vn);
    // add first set
    bool add_first_set(QString left, QString right);
    // add follow set
    bool add_follow_set(QString vn);
    // extract first set of candidate parts
    QSet<QString> extract_first_set_parts(QStringList candidate_list, int start);

public:
    Grammar();
    Grammar(Parser parser);
    void set_parser(Parser parser);
    // parse file
    void parse_file(QString file_name);
    // parse file
    void parse_file();
    // parse input
    void parse_input();
    // remove left recursion
    void remove_left_recursion();
    // remove useless production
    void remove_useless_production();
    // extract the left common factor
    void extract_left_common_factor();
    // extract the first set
    void extract_first_set();
    // extract the right part first set
    void extract_candidate_first_set();
    // extract the follow set
    void extract_follow_set();

    friend class LL1;
};

#endif // GRAMMAR_H
