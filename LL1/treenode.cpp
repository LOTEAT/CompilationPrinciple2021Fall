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
 * ͨ���ݹ�ķ�ʽ����ȡ��ȡ�����Ӻ�Ĳ���ʽ�б��������ַ���Ӧ�Ĳ���ʽ�б�
 * ���ص� Production ��ʾ�������·����Ӧ����ʽ�����ϲ��˶�����·����Ĳ���ʽ
 * ��Ϊ����ʹ�õݹ�ķ�ʽ�������� newProductionList ���洢�������µ��ַ���
 * @param newProductionList
 * @return
 */
Production TreeNode::extractLeftCommonFactor(QList<Production>& newProductionList,int& newNodeCount){
    /**
     * ��� productions.size() == 1����ʾ�ӵ�ǰ���ڵ����µ�·��ֻ��һ����û�зֲ棬
     * ��ô������Ͳ����й���ǰ׺�Ĳ���ʽ�����������µݹ��ˡ�
     */
    if(productions.size()==1){
        return productions[0];
    }
    /**
     * ��ʾ��ǰ���ڵ������Ѿ���������Ĳ���ʽ�б�
     * ��Ϊ�����ǰ���ڵ�������·���й���ǰ׺����ô�й���ǰ׺�Ķ������ʽҪ�ϲ���һ������ʽ����
     */
    QList<Production> childHanledProductions;
    for (auto child:childList){
        Production handledProduction=child->extractLeftCommonFactor(newProductionList,newNodeCount);
        childHanledProductions.push_back(handledProduction);
    }
    /**
     * ������Ĳ���ʽ·��ֻ��һ������ôҲ��ֱ�ӷ�����
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
     * ��Ҫ�ϲ�·���������µ��ַ������� S' S'' S'''
     * ���µ��ַ�ָ��ֲ�·��
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


