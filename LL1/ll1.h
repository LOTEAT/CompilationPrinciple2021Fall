#ifndef LL1_H
#define LL1_H

#include "grammar.h"
#include <QStack>
struct GrammarTree{
    QString node = "";
    QVector<GrammarTree*> next_node;
    GrammarTree(QString node_val): node(node_val){}
    GrammarTree(){}
};

class LL1
{
private:
    Grammar grammar;
    GrammarTree* recursive_descent_tree = new GrammarTree;
    GrammarTree* ll1_tree = new GrammarTree;
    QStringList recursive_descent_productions;
    QStringList ll1_productions;
    QMap<QPair<QString, QString>, QString> ll1_table;
    QStack<QString> analysis;
    void tranverse_right_first(GrammarTree* current_node);
    void tranverse_left_first(GrammarTree* current_node);
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
    void sub_program(QString vn, QStringList input_list, GrammarTree* current_node);
    // recursive descent algorithm
    bool recursive_descent(QString str);
    // generate ll1 analysis table
    void generate_ll1_analysis_table();
    // get ll1 table
    QStringList get_ll1_table();
    // LL1 parser
    bool parse(QString input);
    // get productions in recursive decent
    QStringList get_recursive_descent_productions(){
        return recursive_descent_productions;
    }
    // get productions in ll1
    QStringList get_ll1_productions(){
        return ll1_productions;
    }
    // generage grammar tree
    void generate_grammar_tree(QString type);

};

#endif // LL1_H
