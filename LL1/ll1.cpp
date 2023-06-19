#include "ll1.h"
#include <QFile>
#include <QQueue>
#include <QDir>
/**
 * @brief LL1::set_grammar set grammar
 * @param grammar grammar
 */
void LL1::set_grammar(Grammar grammar){
    this->grammar = grammar;
}

/**
 * @brief LL1::vn_sub_program sub program
 * @param vn vn
 * @param input_list input list
 * @return whether it can be parsed
 */
void LL1::sub_program(QString left, QStringList input_list, GrammarTree* current_node){
    if(parse_index == input_list.length()){
        if(grammar.first[left].contains("@")){
            // make grammar tree
            recursive_descent_productions.push_back(left + "->@\n");
            current_node->next_node.push_back(new GrammarTree("@"));
        }
        else
            is_parse_success = false;
        return;
    }
    // advance
    if(grammar.parser.VT.contains(left) && left == input_list[parse_index]){
        parse_index++;
        return;
    }
    bool flag = true;
    for(auto candidate: grammar.parser.production[left]){
        if(grammar.first_candidate[candidate].contains(input_list[parse_index])){
            flag = false;
            QString p = left + "->" + candidate + "\n";
            recursive_descent_productions.push_back(p.replace(" ", ""));
            QStringList right_list = candidate.split(" ");
            for(auto right_part: right_list){
                // advance
                if(grammar.parser.VT.contains(right_part) && right_part == input_list[parse_index]){
                    current_node->next_node.push_back(new GrammarTree(right_part));
                    parse_index++;
                }
                else if(grammar.parser.VN.contains(right_part)){
                    GrammarTree* new_child = new GrammarTree(right_part);
                    current_node->next_node.push_back(new_child);
                    sub_program(right_part, input_list, new_child);
                }
            }
            break;
        }
    }
    if(grammar.first[left].contains("@") && (parse_index == input_list.length() ||
       grammar.follow[left].contains(input_list[parse_index])) && flag){
        recursive_descent_productions.push_back(left + "->@\n");
        // make grammar tree
        current_node->next_node.push_back(new GrammarTree("@"));
    }
}

/**
 * @brief LL1::recursive_descent recursive descent algorithm
 * @param str input string
 * TODO The algorithm I implement can only read input splited by space.
 * TODO Should we implement one that user can input freely?
 */
bool LL1::recursive_descent(QString str){
    QStringList input_list = str.split(" ");
    is_parse_success = true;
    recursive_descent_tree->node = grammar.parser.start;
    sub_program(grammar.parser.start, input_list, recursive_descent_tree);
    // print_left_first(recursive_descent_tree);
    return is_parse_success && parse_index == input_list.length();
}




/**
 * @brief LL1::generate_ll1_analysis_table generate_ll1_analysis_table
 */
void LL1::generate_ll1_analysis_table(){
    for(auto vn: grammar.parser.VN){
        for(auto candidate: grammar.parser.production[vn]){
            for(auto candidate_first : grammar.first_candidate[candidate]){
                if(grammar.parser.VT.contains(candidate_first))
                    ll1_table[qMakePair(vn, candidate_first)] = vn + "->" + candidate;
            }
        }
        if(grammar.first[vn].contains("@")){
            for(auto follow_vn: grammar.follow[vn]){
                if(grammar.parser.VT.contains(follow_vn))
                   ll1_table[qMakePair(vn, follow_vn)] = vn + "->" + "@";
            }
        }
        for(auto vt: grammar.parser.VT){
            if(ll1_table.find(qMakePair(vn, vt)) == ll1_table.end())
                ll1_table[qMakePair(vn, vt)] = "error";
        }
    }

}



QStringList LL1::get_ll1_table(){
    QStringList table;
    QString vt_row = "vn/vt," + grammar.parser.VT.toList().join(",");
    table.push_back(vt_row);
    for(auto vn: grammar.parser.VN){
        QString vn_row = vn;
        for(auto vt: grammar.parser.VT){
            vn_row += "," + ll1_table[qMakePair(vn, vt)];
        }
        table.push_back(vn_row);
    }
    return table;
}


bool LL1::parse(QString input){

    // analysis stack
    analysis.push("#");
    analysis.push(grammar.parser.start);
    // grammar tree stack
    QStack<GrammarTree*> tree;
    ll1_tree->node = grammar.parser.start;
    tree.push(ll1_tree);

    if(!input.contains('#'))
        input.push_back(" #");
    QStringList input_list = input.split(" ");
    int cur = 0;
    bool flag = false;
    while(analysis.top() != "#"){
        // pop
        QString top = analysis.pop();
        GrammarTree* current_node = tree.pop();
        qDebug() << top;
        if(grammar.parser.VT.contains(top)){
            cur++;
            continue;
        }
        auto table_ij = qMakePair(top, input_list[cur]);
        QString production = ll1_table[table_ij];
        if(production == "error"){
            flag = true;
            break;
        }
        QString p = production;
        ll1_productions.push_back(p.replace(" ", "") + "\n");
        if(production.contains("@")){
            current_node->next_node.push_back(new GrammarTree("@"));
            continue;
        }
        QStringList left_right = production.split("->");
        QStringList right = left_right[1].split(" ");
        for(int i = right.length() - 1; i >= 0; i--){
            analysis.push(right[i]);
            GrammarTree* new_child = new GrammarTree(right[i]);
            current_node->next_node.push_back(new_child);
            tree.push(new_child);
        }
    }
    return flag;
}

void LL1::tranverse_right_first(GrammarTree* current_node){
    qDebug() << current_node->node;
    if(current_node->next_node.empty())
        return;
    for(int i = current_node->next_node.length() - 1; i >= 0; i--){
        tranverse_right_first(current_node->next_node[i]);
    }
}


void LL1::tranverse_left_first(GrammarTree* current_node){
    qDebug() << current_node->node;
    if(current_node->next_node.empty())
        return;
    for(int i = 0; i < current_node->next_node.length(); i++){
        tranverse_left_first(current_node->next_node[i]);
    }
}


void LL1::generate_grammar_tree(QString type){
    QQueue<GrammarTree*> tree;
    QString tree_dot = "graph{\n";
    QMap<QString, int> tree_map;
    int num = 1;
    if(type == "ll1"){
        tree.push_back(ll1_tree);
        while(!tree.empty()){
            auto top = tree.front();
            tree.pop_front();
            if(tree_map[top->node] == 0){
                tree_dot += QString::number(num) + "[label=\"" + top->node + "\"];\n";
                tree_map[top->node] = num++;
            }
            for(int i = top->next_node.length() - 1; i >= 0; i--){
                tree.push_back(top->next_node[i]);
                tree_dot += QString::number(num) + "[label=\"" + top->next_node[i]->node + "\"];\n";
                tree_dot += QString::number(tree_map[top->node]) + "--" + QString::number(num) + ";\n";
                tree_map[top->next_node[i]->node] = num++;
            }
        }
    }
    else{
        qDebug() << 666;
        tree.push_back(recursive_descent_tree);
        while(!tree.empty()){
            auto top = tree.front();
            tree.pop_front();
            if(tree_map[top->node] == 0){
                tree_dot += QString::number(num) + "[label=\"" + top->node + "\"];\n";
                tree_map[top->node] = num++;
            }
            for(int i = 0; i < top->next_node.length(); i++){
                tree.push_back(top->next_node[i]);
                tree_dot += QString::number(num) + "[label=\"" + top->next_node[i]->node + "\"];\n";
                tree_dot += QString::number(tree_map[top->node]) + "--" + QString::number(num) + ";\n";
                tree_map[top->next_node[i]->node] = num++;
            }
        }
    }
    tree_dot += "}";
    qDebug() << QDir::currentPath();
    QFile file("./dot/result.dot");
    if(file.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug() << 666;
        QTextStream out(&file);  //创建写入流
        out << tree_dot;
    }
    file.close();
    system(".\\Graphviz\\dot.exe -Tpng .\\dot\\result.dot -o .\\dot\\result.png");
}


