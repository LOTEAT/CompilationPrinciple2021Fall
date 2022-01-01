#include "ll1.h"

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
            qDebug() << left << "->" << "@";
            current_node->next_node.push_back(new GrammarTree("@"));
        }
        else
            is_parse_success = false;
        return;
    }
    if(grammar.parser.VT.contains(left) && left == input_list[parse_index]){
        parse_index++;
        return;
    }
    bool flag = true;
    for(auto candidate: grammar.parser.production[left]){
        if(grammar.first_candidate[candidate].contains(input_list[parse_index])){
            flag = false;
            qDebug() << left << "->" << candidate;
            QStringList right_list = candidate.split(" ");
            for(auto right_part: right_list){
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
    if(grammar.first[left].contains("@") && (parse_index == input_list.length() || grammar.follow[left].contains(input_list[parse_index])) && flag){
        qDebug() << left << "->" << "@";
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
    print_left_first(recursive_descent_tree);
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


void LL1::parse(QString input){

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
    if(flag)
        qDebug() << "error";
    print_right_first(ll1_tree);
}

void LL1::print_right_first(GrammarTree* current_node){
    qDebug() << current_node->node;
    if(current_node->next_node.empty())
        return;
    for(int i = current_node->next_node.length() - 1; i >= 0; i--){
        print_right_first(current_node->next_node[i]);
    }
}


void LL1::print_left_first(GrammarTree* current_node){
    qDebug() << current_node->node;
    if(current_node->next_node.empty())
        return;
    for(int i = 0; i < current_node->next_node.length(); i++){
        print_left_first(current_node->next_node[i]);
    }
}
