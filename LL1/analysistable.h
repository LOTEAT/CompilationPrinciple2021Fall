#ifndef ANALYSISTABLE_H
#define ANALYSISTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class AnalysisTable: public QWidget
{
    Q_OBJECT
public:
    AnalysisTable(QWidget* parent = nullptr);
    void setHidden(bool b) {setMaximumWidth(b ? 0 : QWIDGETSIZE_MAX);}
    void setControl(bool b) {controlWidget->setMaximumHeight(b ? QWIDGETSIZE_MAX : 0);}
public slots:
    void addRow();
    void addCol();
    void subRow();
    void subCol();
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
