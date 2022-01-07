#include "treenode.h"
TreeNode t_node[1000];
int i=0;



void TreeNode::copyNode(TreeNode& treeNode){
    this->productionKey=treeNode.getProductionKey();
    this->node=treeNode.getNode();
    this->prefixNodes=treeNode.getPrefixNodes();
    this->getChildList()=treeNode.getChildList();
    this->getProductions()=treeNode.getProductions();
}

QString TreeNode::createNewNode(QString currentProductionLeft,int& newNodeCount){
    newNodeCount++;
    for(int index=0;index<newNodeCount;index++){
        currentProductionLeft=currentProductionLeft+"^";
    }
    return currentProductionLeft;
}



void TreeNode::addProductionToTreePath(Production production){
    TreeNode* parentNode=this;
    parentNode->productions.push_back(production);
    for(auto node:production.getRight()){

        TreeNode* temp_node = nullptr;
        for(auto childNode:parentNode->childList){
            if(childNode->getNode()==node){
                temp_node = childNode;
                break;
            }
        }
        if(temp_node == nullptr){
            temp_node = new TreeNode();
            QList<QString> prefixNodes=parentNode->prefixNodes;
            prefixNodes.push_back(node);
            temp_node->setProductionKey(productionKey);
            temp_node->setNode(node);
            temp_node->setPrefixNodes(prefixNodes);
            parentNode->childList.append(temp_node);


        }
        temp_node->productions.push_back(production);
        parentNode=temp_node;
        i++;
    }
}
/**
 * 通过递归的方式，获取提取左公因子后的产生式列表，包括新字符对应的产生式列表
 * 返回的 Production 表示处理过的路径对应产生式，即合并了多条子路径后的产生式
 * 因为我们使用递归的方式，所以用 newProductionList 来存储产生的新的字符串
 * @param newProductionList
 * @return
 */
Production TreeNode::extractLeftCommonFactor(QList<Production>& newProductionList,int& newNodeCount){
    /**
     * 如果 productions.size() == 1，表示从当前树节点往下的路径只有一个，没有分叉，
     * 那么它下面就不会有公共前缀的产生式，不用再向下递归了。
     */
    if(productions.size()==1){
        return productions[0];
    }
    /**
     * 表示当前树节点下面已经做过处理的产生式列表。
     * 因为如果当前树节点下面子路径有公共前缀，那么有公共前缀的多个产生式要合并成一个产生式返回
     */
    QList<Production> childHanledProductions;
    for (auto child:childList){
        Production handledProduction=child->extractLeftCommonFactor(newProductionList,newNodeCount);
        childHanledProductions.push_back(handledProduction);
    }
    /**
     * 处理过的产生式路径只有一条，那么也是直接返回它
     */

    if(node==""){
        for(auto i:childHanledProductions){
            newProductionList.push_back(i);
        }
        Production p;
        return p;
    }

    if(childHanledProductions.size()==1){
        return childHanledProductions[0];
    }
    /**
     * 需要合并路径，生成新的字符，例如 S' S'' S'''
     * 将新的字符指向分叉路径
     */
    QString newNode=createNewNode(productionKey,newNodeCount);

    for(auto production: childHanledProductions){
        QList<QString> newNodeNodeList;
        for(int index=prefixNodes.size();index<production.getRight().size();index++){
            newNodeNodeList.push_back(production.getRight()[index]);

        }
        Production newNodeProduction(newNode,newNodeNodeList);
        newProductionList.push_back(newNodeProduction);
    }


    QList<QString> newNodeList=prefixNodes;
    newNodeList.push_back(newNode);
    Production newProduction(productionKey,newNodeList);
    return newProduction;

}


