#include <bits/stdc++.h>

std::unordered_map<std::string, std::vector<std::string>> cfg;

void create_cfg()
{
    cfg["program"] = {
        "stmt_list"};

    cfg["stmt_list"] = {
        "loop",
        "loop stmt_list",
        "definition",
        "definition stmt_list",
        "stmt",
        "stmt stmt_list"};

    cfg["loop"] = {
        "for ( expression ; expression ; expression ) { stmt_list }",
        "for ( expression ; expression ; expression ) stmt"};

    cfg["definition"] = {
        "function_definiton",
        "derived_data_type_definition ;"};

    cfg["stmt"] = {
        "expression ;"};

    cfg["expression"] = {
        "declaration",
        "assignment",
        "operation",
        "id",
        "val",
        "function_call"};

    cfg["function_definition"] = {
        "basic_type id ( parameter_list ) { stmt_list }",
        "basic_type id ( ) { stmt_list }",
        "struct id id ( parameter_list ) { stmt_list }",
        "struct id id ( ) { stmt_list }",
        "union id id ( parameter_list ) { stmt_list }",
        "union id id ( ) { stmt_list }",
        "enum id id ( ) { stmt_list }",
        "enum id id ( parameter_list ) { stmt_list }"};

    cfg["derived_data_type_definition"] = {
        "struct id { field_list }",
        "enum id { field_list }",
        "union id { field_list }"};

    cfg["declaration"] = {"basic_declaration", "user_defined_declaration"};

    cfg["assignment"] = {
        "id = expression",
        ". id = expression"};

    cfg["operation"] = {
        "expression bin_op expression",
        "val bin_op expression",
        "id unary_op expression",
        "id postfix_op",
        "val postfix_op",
        "prefix_op id",
        "prefix_op val"};

    cfg["function_call"] = {
        "id ( argument_list )",
        "id ( )"};

    cfg["basic_type"] = {
        "int",
        "float",
        "char",
        "void",
        "basic_type *"};

    cfg["parameter_list"] = {
        "parameter",
        "parameter , parameter_list"};

    cfg["field_list"] = {
        "field",
        "field ; field_list"};

    cfg["basic_declaration"] = {
        "basic_type id = expression"};

    cfg["user_defined_declaration"] = {
        "struct id id = { assignment_list } ",
        "union id id = { assignment }",
        "enum id id = id"};

    cfg["bin_op"] = {
        "+", "-", "*", "/",
        "<", ">", "<=", ">=",
        "==", "!=", "&&", "||",
        "&", "^", "|"};

    cfg["unary_op"] = {
        "+=",
        "-=",
        "*=",
        "/=",
        "&=",
        "^=",
        "|=",
    };

    cfg["postfix_op"] = {
        "++", "--"};

    cfg["prefix_op"] = {
        "++", "--", "!"};

    cfg["assignment_list"] = {
        "assignment",
        "assignment , assignment_list"};

    cfg["argument_list"] = {
        "argument",
        "argument , argument_list"};

    cfg["parameter"] = {
        "basic_type id",
        "basic_type id arr_ptr",
        "struct id id",
        "struct id id arr_ptr",
        "union id id",
        "union id id arr_ptr",
        "enum id id",
        "enum id id arr_ptr"};

    cfg["field"] = {
        "basic_type id",
        "basic_type id_list",
        "basic_type id arr_ptr",
        "struct id id",
        "struct id id_list",
        "struct id id arr_ptr",
        "union id id",
        "union id id_list",
        "union id id arr_ptr",
        "enum id id",
        "enum id id_list",
        "enum id id arr_ptr"};

    cfg["argument"] = {
        "expression"};

    cfg["id_list"] = {
        "id",
        "id , id_list"};

    cfg["arr_ptr"] = {
        "*", "[ ]",
        "* arr_ptr", "arr_ptr [ ]"};
}

// extern void print_cfg()
// {
//     for (auto it = cfg.begin(); it != cfg.end(); it++)
//     {
//         std::cout << it->first << " ";
//     }
// }