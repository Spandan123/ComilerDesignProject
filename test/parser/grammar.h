#pragma once
#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> cfg;
vector<pair<string, string>> annotated_cfg;

void create_cfg()
{
    cfg["program"] = {
        " stmt_list "};

    cfg["stmt_list"] = {
        " loop ",
        " loop stmt_list ",
        " definition ",
        " definition stmt_list ",
        " stmt ",
        " stmt stmt_list "};

    cfg["expression"] = {
        " declaration ",
        " assignment ",
        " operation ",
        " id ",
        " val ",
        " function_call "};

    cfg["operation"] = {
        " expression bin_op expression ",
        " val bin_op expression ",
        " id unary_op expression ",
        " id postfix_op ",
        " val postfix_op ",
        " prefix_op id ",
        " prefix_op val "};

    cfg["bin_op"] = {
        " + ", " - ", " * ", " / ",
        " < ", " > ", " <= ", " >= ",
        " == ", " != ", " && ", " || ",
        " & ", " ^ ", " | "};

    cfg["unary_op"] = {
        " += ",
        " -= ",
        " *= ",
        " /= ",
        " &= ",
        " ^= ",
        " |= ",
    };

    cfg["postfix_op"] = {
        " ++ ", " -- "};

    cfg["prefix_op"] = {
        " ++ ", " -- ", " ! "};

    cfg["declaration"] = {" basic_declaration ", " user_defined_declaration "};

    cfg["basic_declaration"] = {
        " basic_type id = expression "};

    cfg["basic_type"] = {
        " int ",
        " float ",
        " char ",
        " void ",
        " basic_type * "};

    cfg["user_defined_declaration"] = {
        " struct id id = { assignment_list } ",
        " union id id = { assignment } ",
        " enum id id = id "};

    cfg["assignment"] = {
        " id = expression "};

    cfg["assignment_list"] = {
        " assignment ",
        " assignment , assignment_list "};

    cfg["function_call"] = {
        " id ( argument_list ) ",
        " id ( ) "};

    cfg["argument_list"] = {
        " argument ",
        " argument , argument_list "};

    cfg["argument"] = {
        " expression "};

    cfg["stmt"] = {
        " preprocessor_directive ",
        " expression ; "};

    cfg["preprocessor_directive"] = {
        " #define id val ",
        " #include val ",
        " #pragma id "};

    cfg["loop"] = {
        " for ( expression ; expression ; expression ) { stmt_list } "};

    cfg["definition"] = {
        " function_definition ",
        " derived_data_type_definition ; "};

    cfg["derived_data_type_definition"] = {
        " struct id { field_list } ",
        " enum id { field_list } ",
        " union id { field_list } "};

    cfg["field_list"] = {
        " field ",
        " field ; field_list "};

    cfg["field"] = {
        " basic_type id ",
        " basic_type id_list ",
        " basic_type id arr_ptr ",
        " struct id id ",
        " struct id id_list ",
        " struct id id arr_ptr ",
        " union id id ",
        " union id id_list ",
        " union id id arr_ptr ",
        " enum id id ",
        " enum id id_list ",
        " enum id id arr_ptr ",
    };

    cfg["id_list"] = {
        "  id ",
        "  id , id_list "};

    cfg["function_definition"] = {
        " basic_type id ( parameter_list ) { stmt_list }  ",
        " basic_type id ( ) { stmt_list }  ",
        " struct id id ( parameter_list ) { stmt_list }  ",
        " struct id id ( ) { stmt_list } ",
        " union id id ( parameter_list ) { stmt_list } ",
        " union id id ( ) { stmt_list } ",
        " enum id id ( ) { stmt_list } ",
        " enum id id ( parameter_list ) { stmt_list } "};

    cfg["parameter_list"] = {
        " parameter ",
        " parameter , parameter_list "};

    cfg["parameter"] = {
        " basic_type id ",
        " basic_type id arr_ptr ",
        " struct id id ",
        " struct id id arr_ptr ",
        " union id id ",
        " union id id arr_ptr ",
        " enum id id ",
        " enum id id arr_ptr "};

    cfg["arr_ptr"] = {
        " * ", " [ ] ",
        " * arr_ptr ", " arr_ptr [ ] "};
}

void print_cfg()
{
    for (auto it : cfg)
    {
        cout << it.first << " : \n";
        for (auto it1 : it.second)
        {
            cout << "   " << it1 << "\n";
        }
        cout << endl;
    }
}

void create_annotated_cfg()
{
    int num = 0;
    for (auto it : cfg)
    {
        for (auto itt : it.second)
        {
            annotated_cfg.push_back(make_pair(it.first, itt));
        }
    }
}

void print_annotated_cfg()
{
    for (int i = 0; i < annotated_cfg.size(); i++)
    {
        cout << i + 1 << ") " << annotated_cfg[i].first << " -> " << annotated_cfg[i].second << endl;
    }
}

int get_position(const string &lhs, const string &rhs)
{
    for (int i = 0; i < annotated_cfg.size(); i++)
    {
        if (annotated_cfg[i].first == lhs && rhs == annotated_cfg[i].second)
        {

            return i;
        }
    }
    return -1;
}

pair<string, string> get_prod(int index)
{
    return make_pair(annotated_cfg[index].first, annotated_cfg[index].second);
}