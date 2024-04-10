#include <bits/stdc++.h>

std::unordered_map<std::string, std::vector<std::string>> cfg;

std::unordered_map<std::string, std::vector<std::string>> create_cfg()
{

    cfg["expression"] = {
        "identifier",
        "constant",
        "function_call",
        "expression operator expression",
        "declaration",
        "assignment",
        "conditional"};

    cfg["declaration"] = {
        "basic_declaration",
        "user_defined_declaration"};

    cfg["basic_declaration"] = {
        "keyword identifier = expression"};

    cfg["user_defined_declaration"] = {
        "keyword identifier identifier"};

    cfg["assignment"] = {
        "identifier = expression"};

    cfg["conditional"] = {
        "expression operator expression"};

    cfg["function_call"] = {
        "identifier ( argument_list )"};

    cfg["argument_list"] = {
        "argument",
        "argument , argument_list"};

    cfg["argument"] = {
        "expression"};

    cfg["stmt_list"] = {
        "loop",
        "loop stmt_list",
        "definition",
        "definition stmt_list",
        "stmt",
        "stmt stmt_list"};

    cfg["stmt"] = {
        "expression ;"};

    cfg["loop"] = {
        "for ( expression ; expression ; expression ) { stmt_list }"};

    cfg["program"] = {
        "stmt_list"};

    cfg["definition"] = {
        "function_definition",
        "keyword identifier { stmt_list } ;"};

    cfg["function_definition"] = {
        "keyword identifier ( parameter_list ) { stmt_list }"};

    cfg["parameter_list"] = {
        "parameter",
        "parameter , parameter_list"};

    cfg["parameter"] = {
        "keyword identifier"};
    return cfg;
}

extern void print_cfg()
{
    for (auto it = cfg.begin(); it != cfg.end(); it++)
    {
        std::cout << it->first << " ";
    }
}