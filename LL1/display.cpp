#include "display.h"
#include "utils.h"
Display::Display(QWidget *parent):QWidget(parent)
{
    inputTitle = new QLabel(QString::fromLocal8Bit("输入"));
    tableTitle = new QLabel("");
    outputTitle = new QLabel(QString::fromLocal8Bit("输出"));

    inputList = new InputList();
    outputList = new QPlainTextEdit();
    outputList->setReadOnly(true);
    outputList->setStyleSheet("border:1px solid #DCDFE6; border-radius: 6px; background-color: #F8F8F8;");

    analysisTable = new AnalysisTable();
    analysisTable->setMaximumWidth(0);

    QVBoxLayout* inputLayout = new QVBoxLayout();
    inputLayout->addWidget(inputTitle, 0, Qt::AlignHCenter);
    inputLayout->addWidget(inputList);

    QVBoxLayout* tableLayout = new QVBoxLayout();
    tableLayout->addWidget(tableTitle, 0, Qt::AlignHCenter);
    tableLayout->addWidget(analysisTable);

    QVBoxLayout* outputLayout = new QVBoxLayout();
    outputLayout->addWidget(outputTitle, 0, Qt::AlignHCenter);
    outputLayout->addWidget(outputList);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addLayout(inputLayout);
    layout->addLayout(tableLayout);
    layout->addLayout(outputLayout);
    setLayout(layout);
}

void Display::setText(const QString& input, const QString& table, const QString& output)
{
    inputTitle->setText(input);
    tableTitle->setText(table);
    outputTitle->setText(output);
    inputList->setHidden(!input.length());
    analysisTable->setHidden(!table.length());
    analysisTable->setControl(!input.length() && table.length());
    outputList->setMaximumWidth(output.length() ? QWIDGETSIZE_MAX : 0);
    outputList->clear();
}


void Display::addInputItem(QString left, QString right){
    inputList->addInputItem(left, right);
}


Parser Display::initParser(){
    QStringList input_list = inputList->getInput();
    QString str=QString(input_list[0][0]);  //默认第一个字符为起始符
    Parser parser;
    parser.parse_input(input_list,str);
    return parser;
}

void Display::removeLeftRecursion(){
    Grammar grammar;
    grammar.set_parser(initParser());
    QStringList productions = grammar.remove_left_recursion();
    for(auto production: productions){
        outputList->insertPlainText(production);
    }
}


void Display::extractLeftCommonFactor(){
    Grammar grammar;
    grammar.set_parser(initParser());
    QStringList productions = grammar.extract_left_common_factor();
    for(auto production: productions){
        outputList->insertPlainText(production);
    }

}

void Display::extractFirstSet(){
    Grammar grammar;
    grammar.set_parser(initParser());
    QStringList first_set = grammar.extract_first_set();
    for(auto first: first_set){
        outputList->insertPlainText(first);
    }
    QStringList first_candidate_set = grammar.extract_candidate_first_set();
    for(auto first_candidate: first_candidate_set){
        outputList->insertPlainText(first_candidate);
    }
}


void Display::extractFollowSet(){
    Grammar grammar;
    grammar.set_parser(initParser());
    grammar.extract_first_set();
    grammar.extract_candidate_first_set();
    QStringList follow_set = grammar.extract_follow_set();
    for(auto follow: follow_set){
        outputList->insertPlainText(follow);
    }
}


void Display::recursiveDescent(QString sentence){
    if(sentence == ""){
        Utils::alert_message("input cannot be null", "error");
        return;
    }
    Grammar grammar;
    grammar.set_parser(initParser());
    grammar.extract_first_set();
    grammar.extract_candidate_first_set();
    grammar.extract_follow_set();
    LL1 ll1;
    ll1.set_grammar(grammar);
    ll1.recursive_descent(sentence);
    if(!ll1.recursive_descent(sentence)){
        Utils::alert_message("parse", "error");
        return;
    }
    QStringList productions = ll1.get_recursive_descent_productions();
    for(auto p: productions){
        outputList->insertPlainText(p);
    }
    ll1.generate_grammar_tree("recursive_descent");
}


void Display::showAnalysisTable(){
    Grammar grammar;
    grammar.set_parser(initParser());
    grammar.extract_first_set();
    grammar.extract_candidate_first_set();
    grammar.extract_follow_set();
    LL1 ll1;
    ll1.set_grammar(grammar);
    ll1.generate_ll1_analysis_table();
    QStringList tables = ll1.get_ll1_table();
    for(auto table_row : tables){
        analysisTable->setRow(table_row);
    }
}


void Display::ll1_parse(QString sentence){
    if(sentence == ""){
        Utils::alert_message("input cannot be null", "error");
        return;
    }
    Grammar grammar;
    grammar.set_parser(initParser());
    grammar.remove_left_recursion();
    grammar.extract_left_common_factor();
    grammar.extract_first_set();
    grammar.extract_candidate_first_set();
    grammar.extract_follow_set();
    LL1 ll1;
    ll1.set_grammar(grammar);
    ll1.generate_ll1_analysis_table();
    if(ll1.parse(sentence)){
        Utils::alert_message("parse", "error");
        return;
    }
    QStringList ll1_productions = ll1.get_ll1_productions();
    for(auto p: ll1_productions){
        outputList->insertPlainText(p);
    }
    QStringList tables = ll1.get_ll1_table();
    for(auto table_row : tables){
        analysisTable->setRow(table_row);
    }
    ll1.generate_grammar_tree("ll1");
}

void Display::showOutput(int id, QString sentence){
    qDebug() << id;
    outputList->clear();
    switch (id) {
    case 0:
        removeLeftRecursion();
        break;
    case 1:
        extractLeftCommonFactor();
        break;
    case 2:
        extractFirstSet();
        break;
    case 3:
        extractFollowSet();
        break;
    case 4:
        recursiveDescent(sentence);
        break;
    case 5:
        showAnalysisTable();
        break;
    case 6:
        break;
    case 7:
        ll1_parse(sentence);
        break;
    }
}
