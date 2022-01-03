#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
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
    void showOutput(int id);
private:
    QLabel* inputTitle;
    QLabel* tableTitle;
    QLabel* outputTitle;
    Parser* parser;
    Grammar* grammar;
    LL1* ll1;
    InputList* inputList;
    QListWidget* outputList;
    AnalysisTable* analysisTable;
};

#endif // DISPLAY_H
