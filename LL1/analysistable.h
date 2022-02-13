#ifndef ANALYSISTABLE_H
#define ANALYSISTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>

class AnalysisTable: public QWidget
{
    Q_OBJECT
public:
    AnalysisTable(QWidget* parent = nullptr);
    void setHidden(bool b) {setMaximumWidth(b ? 0 : QWIDGETSIZE_MAX);}
    void setControl(bool b) {controlWidget->setMaximumHeight(b ? QWIDGETSIZE_MAX : 0);}
    void setRow(QString row);
public slots:
    void addRow();
    void addCol();
    void subRow();
    void subCol();
    void clear() {table->clear();table->setRowCount(0);table->setColumnCount(0);}
private:
    QTableWidget* table;
    QWidget* controlWidget;
    QLabel* rowLabel;
    QLabel* colLabel;
    QPushButton* addRowBtn;
    QPushButton* subRowBtn;
    QPushButton* addColBtn;
    QPushButton* subColBtn;
};

#endif // ANALYSISTABLE_H
