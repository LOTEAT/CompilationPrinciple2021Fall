#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include "inputlist.h"
#include "analysistable.h"
#include "parser.h"
#include "grammar.h"
#include "ll1.h"

class Display: public QWidget
{
    Q_OBJECT
public:
    Display(QWidget* parent = nullptr);
    void setText(const QString& input, const QString& table, const QString& output);
    void addInputItem(QString left, QString right);
    void removeLeftRecursion(QString start);
    void extractLeftCommonFactor();
    void extractFirstSet();
    void extractFollowSet(QString start);
    void recursiveDescent(QString sentence, QString start);
    void showOutput(int id, QString sentence, QString start);
    void showAnalysisTable();
    void ll1_parse(QString sentence, QString start);
    void clearInput() {inputList->clearList();}
    void clearTable() {analysisTable->clear();}
    Parser initParser();
    Parser initParser(QString start);
private:
    QLabel* inputTitle;
    QLabel* tableTitle;
    QLabel* outputTitle;
    InputList* inputList;
    QPlainTextEdit* outputList;
    AnalysisTable* analysisTable;
};

#endif // DISPLAY_H
