#ifndef PRODUCTION_H
#define PRODUCTION_H
class Production{
private:
    QString left;
    QList<QString> right;
public:
    Production(){}
    Production(QString left,QList<QString> right){
        this->left=left;
        this->right=right;
    }

    QString getLeft(){
        return left;
    }

    QList<QString> getRight(){
        return right;
    }
};
#endif // PRODUCTION_H
