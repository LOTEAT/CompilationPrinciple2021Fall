#ifndef TREENODE_H
#define TREENODE_H
#include <QMap>
#include <QString>
#include "production.h"
#include <QDebug>
class TreeNode{
private:
    QString productionKey;
    QString node;
    QList<QString> prefixNodes;
    QList<TreeNode*> childList;
    QList<Production> productions;


    QString createNewNode(QString currentProductionLeft,int& newNodeCount);

public:

    TreeNode(QString productionKey){
        this->productionKey=productionKey;
    }

    TreeNode(const TreeNode& treeNode){
        this->productionKey=treeNode.productionKey;
        this->node=treeNode.node;
        this->prefixNodes=treeNode.prefixNodes;
        this->getChildList()=treeNode.childList;
        this->getProductions()=treeNode.productions;

    }

    TreeNode(){};

    QString getNode(){ return node;}
    QString getProductionKey(){return productionKey;}
    QList<QString> getPrefixNodes(){return prefixNodes;}
    QList<TreeNode*> getChildList(){return childList;}
    QList<Production> getProductions(){return productions;}
    void setProductionKey(QString productionKey){this->productionKey=productionKey;}
    void setNode(QString node){this->node=node;}
    void setPrefixNodes(QList<QString> prefixNodes){this->prefixNodes=prefixNodes;}
    void copyNode(TreeNode& treeNode);

    void addProductionToTreePath(Production production);

    Production extractLeftCommonFactor(QList<Production>& newProductionList,int& newNodeCount);



};

#endif // TREENODE_H
