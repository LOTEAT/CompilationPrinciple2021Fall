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
void LL1::sub_program(QString left, QStringList input_list){
    if(parse_index == input_list.length()){
        if(grammar.first[left].contains("@"))
            qDebug() << left << "->" << "@";
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
                if(grammar.parser.VT.contains(right_part) && right_part == input_list[parse_index])
                    parse_index++;
                else if(grammar.parser.VN.contains(right_part)){
                    sub_program(right_part, input_list);
                }
            }
            break;
        }
    }
    if(grammar.first[left].contains("@") && (parse_index == input_list.length() || grammar.follow[left].contains(input_list[parse_index])) && flag)
        qDebug() << left << "->" << "@";
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
    sub_program(grammar.parser.start, input_list);
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
                ll1_table[qMakePair(vn, vt)] = "null";
        }
    }

    for(auto it=ll1_table.begin(); it!=ll1_table.end(); it++)
        qDebug() << it.key() << " " << it.value();
}
