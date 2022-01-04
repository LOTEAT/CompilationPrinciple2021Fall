#include "grammar.h"

/**
 * @brief Grammar::Grammar non-arg constructor
 */
Grammar::Grammar()
{

}

/**
 * @brief Grammar::Grammar constructor
 * @param parser parser
 */
Grammar::Grammar(Parser parser)
{
    this->parser = parser;
}

/**
 * @brief Grammar::set_parser set parser
 * @param parser parser
 */
void Grammar::set_parser(Parser parser){
    this->parser = parser;
}

/**
 * @brief Grammar::parse_file parse input file
 * @param file_name file name
 */
void Grammar::parse_file(QString file_name){
    parser.set_file_name(file_name);
    parser.parse_file();
}

/**
 * @brief Grammar::parse_file parse input file
 */
void Grammar::parse_file(){
    parser.parse_file();
}

/**
 * @brief Grammar::parse_input parse gui input
 */
void Grammar::parse_input(){

}


/**
 * @brief Grammar::remove_direct_left_recursion remove direct left recursion
 * @param VN the left part of production
 */
void Grammar::remove_direct_left_recursion(QString VN){
    QString new_VN = VN + "\'";
    parser.VN.push_back(new_VN);
    QVector<QString> new_rights1;
    QVector<QString> new_rights2;
    for(auto it = parser.production[VN].begin(); it != parser.production[VN].end(); it++){
        if(it->startsWith(VN)){
            QString new_right = it->mid(VN.length() + 1) + " " + new_VN;
            new_rights1.push_back(new_right);
        }
        else{
            QString new_right = *it + " " + new_VN;
            new_rights2.push_back(new_right);
        }
    }
    // add epsilon
    new_rights1.push_back("@");
    parser.production[new_VN] = new_rights1;
    parser.production[VN] = new_rights2;
}



/**
 * @brief Grammar::remove_left_recursion remove left recursion
 */
QStringList Grammar::remove_left_recursion(){    
    for(auto vn: parser.VN){
        for(auto it = parser.production[vn].begin(); it != parser.production[vn].end(); it++){
            if(it->startsWith(vn)){
                remove_direct_left_recursion(vn);
                break;
            }
        }
    }
    remove_indirect_left_recursion();
    for(auto vn: parser.VN){
        for(auto it = parser.production[vn].begin(); it != parser.production[vn].end(); it++){
            if(it->startsWith(vn)){
                remove_direct_left_recursion(vn);
                break;
            }
        }
    }
    remove_useless_production();
    QStringList productions;
    for(auto vn: parser.VN){
        for(auto candidate: parser.production[vn]){
            QString production = vn + "->" + candidate + "\n";
            production.replace(" ", "");
            productions.push_back(production);
        }
    }
    return productions;
}

/**
 * @brief Grammar::indirect_left_recursion_check
 * @return check whether it is need to remove indirect left recursion
 */
bool Grammar::indirect_left_recursion_check(){
    QMap<QString, QVector<QString> > production_temp = parser.production;
    for(int i = 0; i < parser.VN.length(); i++){
        QString vn_i = parser.VN[i];
        for(int j = 0; j < i; j++){
            QVector<QString> new_rights;
            QString vn_j = parser.VN[j];
            for(auto it_i = production_temp[vn_i].begin(); it_i != production_temp[vn_i].end(); it_i++){
                if(it_i->startsWith(vn_j)){
                    for(auto it_j = production_temp[vn_j].begin(); it_j != production_temp[vn_j].end(); it_j++){
                        QStringList rights = it_j->split(" ");
                        new_rights.push_back(*it_j + it_i->mid(vn_j.length()));
                    }
                }
                else
                    new_rights.push_back(*it_i);
            }
            production_temp[vn_i] = new_rights;
        }
    }

    for(auto vn : parser.VN){
        QVector<QString> candidates = production_temp[vn];
        for(auto candidate: candidates){
            if(candidate.startsWith(vn))
                return true;
        }
    }
    return false;
}


/**
 * @brief Grammar::remove_indirect_left_recursion
 */
void Grammar::remove_indirect_left_recursion(){
    if(!indirect_left_recursion_check())
        return;
    for(int i = 0; i < parser.VN.length(); i++){
        QString vn_i = parser.VN[i];
        for(int j = 0; j < i; j++){
            QVector<QString> new_rights;
            QString vn_j = parser.VN[j];
            for(auto it_i = parser.production[vn_i].begin(); it_i != parser.production[vn_i].end(); it_i++){
                if(it_i->startsWith(vn_j)){
                    for(auto it_j = parser.production[vn_j].begin(); it_j != parser.production[vn_j].end(); it_j++){
                        QStringList rights = it_j->split(" ");
                        new_rights.push_back(*it_j + it_i->mid(vn_j.length()));
                    }
                }
                else
                    new_rights.push_back(*it_i);
            }
            parser.production[vn_i] = new_rights;
        }
    }

}


/****TODO*****/
void Grammar::remove_useless_production(){
    qDebug() << "remove";
}

/**
 * @brief Grammar::min_prefix extract minimum left factor
 * @param str1 string1
 * @param str2 string2
 * @return common prefix
 */
QString Grammar::min_prefix(QString str1, QString str2){
    QStringList str1_split = str1.split(" ");
    QStringList str2_split = str2.split(" ");
    if(str1_split[0] == str2_split[0])
        return str1_split[0];
    else
        return "";
}


void Grammar::left_common_for_one_production(QString vn){
    int number = 0;
    bool flag = true;
    while(flag){
        flag = false;
        for(int i = 0, s = parser.production[vn].length(); i < s; i++){
            for(int j = 0; j < s; j++){
                qDebug() << "";
            }
        }
    }
}

void Grammar::extract_left_common_factor(){
    for(auto vn: parser.VN){
        left_common_for_one_production(vn);
    }
}

/**
 * @brief Grammar::add_first_set add first set for one vn
 * @param left the left part of production
 * @param right the right part of production
 * @return whether the first set changed
 */
bool Grammar::add_first_set(QString left, QString right){
    QStringList right_split = right.split(" ");
    int old_size = first[left].size();
    for(int i = 0, s = right_split.length(); i < s; i++){
        QString right_split_part = right_split[i];
        // terminator, no need to go on
        if(parser.VT.contains(right_split_part)){
            first[left].insert(right_split_part);
            break;
        }
        // non-terminator
        else if(parser.VN.contains(right_split_part)){
            for(auto it = first[right_split_part].begin(); it != first[right_split_part].end(); it++){
                if(*it != "@")
                    first[left].insert(*it);
            }
            // epsilon
            if(first[left].contains("@")){
                if(i == s - 1)
                    first[left].insert("@");
            }
            else
                break;
        }
        else{
            // insert epsilon
            first[left].insert("@");
        }
    }
    int new_size = first[left].size();
    return !(old_size == new_size);
}

/**
 * @brief Grammar::extract_first_set get first set
 */
QStringList Grammar::extract_first_set(){
    // TODO
    // There is a question here.
    // the first set of G should contain "@"?
    first["@"].insert("@");

    // non-terminator
    for(auto vt: parser.VT)
        first[vt].insert(vt);
    bool flag = true;
    while(flag){
        flag = false;
        for(auto vn: parser.VN){
            for(auto it = parser.production[vn].begin(); it != parser.production[vn].end(); it++){
                flag = add_first_set(vn, *it) | flag;
            }
        }
    }

    QStringList first_set;
    for(auto vn: parser.VN){
        QString f = "First(" + vn + ")=";
        f = f + "{" + first[vn].values().join(',') + "}\n";
        f.replace(" ", "");
        first_set.push_back(f);
    }
    return first_set;
}

/**
 * @brief Grammar::extract_candidate_first_set
 */
QStringList Grammar::extract_candidate_first_set(){
    for(auto vn: parser.VN){
        for(auto it = parser.production[vn].begin(); it != parser.production[vn].end(); it++){
            if(*it == "@")
                continue;
            QStringList candidate_list = it->split(" ");
            for(int i = 0, s = candidate_list.length(); i < s; i++){
                first_candidate[*it].unite(first[candidate_list[i]]);
                if(!first[candidate_list[i]].contains("@")){
                    if(first_candidate[*it].contains("@"))
                        first_candidate[*it].remove("@");
                    break;
                }


            }
        }
    }


    QStringList first_candidate_set;
    for(auto vn: parser.VN){
        for(auto it = parser.production[vn].begin(); it != parser.production[vn].end(); it++){
            if(*it == "@")
                continue;
            QString f = "First(" + *it + ")=";
            f = f + "{" + first_candidate[*it].values().join(',') + "}\n";
            f.replace(" ", "");
            first_candidate_set.push_back(f);
        }
    }
    return first_candidate_set;
}


QSet<QString> Grammar::extract_first_set_parts(QStringList candidate_list, int start){
    QSet<QString> first_set_parts;
    for(int i = start, s = candidate_list.length(); i < s; i++){
        first_set_parts.unite(first[candidate_list[i]]);
        if(!first[candidate_list[i]].contains("@")){
            if(first_set_parts.contains("@"))
                first_candidate.remove("@");
            break;
        }
    }
    return first_set_parts;
}


/**
 * @brief Grammar::add_follow_set add follow set for vn
 * @param vn non-terminator
 * @return whether follow[vn] changed
 */
bool Grammar::add_follow_set(QString vn){
    int old_size = follow[vn].size();
    for(auto left: parser.VN){
        for(auto it = parser.production[left].begin(); it != parser.production[left].end(); it++){
            QStringList candidate_list = it->split(" ");
            for(int i = 0, s = candidate_list.length(); i < s; i++){
                // match
                if(candidate_list[i] == vn){
                    if(i == s - 1)
                       follow[vn].unite(follow[left]);
                    else{
                        QSet<QString> first_set_parts = extract_first_set_parts(candidate_list, i + 1);
                        follow[vn].unite(first_set_parts);
                        if(first_set_parts.contains("@"))
                            follow[vn].unite(follow[left]);
                    }
                }
            }
        }
    }
    if(follow[vn].contains("@"))
        follow[vn].remove("@");
    int new_size = follow[vn].size();
    return !(old_size == new_size);
}


/**
 * @brief Grammar::extract_follow_set extract follow set
 */
QStringList Grammar::extract_follow_set(){
    bool flag = true;
    while(flag){
        flag = false;
        for(auto vn: parser.VN){
            if(vn == parser.start)
                follow[vn].insert("#");
            flag = add_follow_set(vn) | flag;
        }
    }
    QStringList follow_set;
    qDebug() << follow;
    for(auto vn: parser.VN){
        QString f = "Follow(" + vn + ")=";
        f = f + "{" + follow[vn].values().join(',') + "}\n";
        f.replace(" ", "");
        follow_set.push_back(f);
    }
    return follow_set;
}






