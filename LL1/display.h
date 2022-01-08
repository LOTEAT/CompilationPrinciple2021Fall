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
    void removeLeftRecursion();
    void extractLeftCommonFactor();
    void extractFirstSet();
    void extractFollowSet();
    void recursiveDescent(QString sentence);
    void showOutput(int id, QString sentence);
    void showAnalysisTable();
    void ll1_parse(QString sentence);
    Parser initParser();
private:
    QLabel* inputTitle;
    QLabel* tableTitle;
    QLabel* outputTitle;
    InputList* inputList;
    QPlainTextEdit* outputList;
    AnalysisTable* analysisTable;
};

#endif // DISPLAY_H
