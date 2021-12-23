#include <QMessageBox>
#include <QStringList>
#include <QRegExp>
#include <algorithm>
#include "parser.h"
#include "utils.h"

/**
 * @brief Parser::parse_file parse file
 * @return whether parse successfully
 */

bool Parser::parse_file(){
    QFile ll1_file(file_name);

    /***********TODO*************/
    // These may be better.
    if(!ll1_file.exists()){
        Utils::alert_message("upload", "error!");
        return false;
    }
    Utils::alert_message("upload", "ok!");
    /***********TODO*************/


    // open file
    if (ll1_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!ll1_file.atEnd())
        {
            QString line = ll1_file.readLine();
            // remove '\n'
            line = line.trimmed();
            parse_line(line);
        }
        ll1_file.close();
    }
    add_VT();
    // remove duplicate vt
    std::sort(VN.begin(), VN.end());
    VN.erase(std::unique(VN.begin(), VN.end()), VN.end());
    return true;
}

/**
 * @brief Parser::set_file_name set file name
 * @param input_file_name input file
 */
void Parser::set_file_name(QString input_file_name){
    file_name = input_file_name;
}

/**
 * @brief Parser::parse_line parse file line
 * @param line file line
 * @return whether parse sucessfully
 */
bool Parser::parse_line(QString line){

    /*****************TODO************************/
    // This should be judged.
    /*****************TODO************************/
    QStringList left_right = line.split("->");
    // remove ""
    QString left = left_right[0];
    QString right = left_right[1];
    // add non terminator
    VN.push_back(left);
    add_production(left, right);
    return true;
}

/**
 * @brief Parser::add_production add a production
 * @param left the left part of the production
 * @param right the right part of the production
 */
void Parser::add_production(QString left, QString right){
    QString part_right = "";
    for(QChar c: right){
        if(c != '|')
            part_right.push_back(c);
        else{
            // add production
            production[left].push_back(part_right);
            part_right = "";
        }
    }
    production[left].push_back(part_right);
}

/**
 * @brief Parser::add_VT add vt vector
 */
void Parser::add_VT(){
    QRegExp seq = QRegExp("\\|| ");
    for(QString vn: VN){
        for(QString right: production[vn]){
            QStringList right_list = right.split(seq);
            QList<QString>::Iterator it = right_list.begin(), end = right_list.end();
            for(; it != end; it++){
                if(!VN.contains(*it))
                    VT.push_back(*it);
            }
        }
    }
    // remove duplicate vt
    std::sort(VT.begin(), VT.end());
    VT.erase(std::unique(VT.begin(), VT.end()), VT.end());
}


