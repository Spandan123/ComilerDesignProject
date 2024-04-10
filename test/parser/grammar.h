#include <bits/stdc++.h>

extern std::unordered_map<std::string, std::vector<std::string>> cfg;

extern void create_cfg()
{
    cfg["expression"] = {
        "declaration",
        "assignment",
        "conditional"};

    cfg["declaration"] = {
        "basic_declaration",
        "user_defined_declaration"};

    cfg["basic_declaration"] = {
        "basic_type id = expression"};

    cfg["basic_type"] = {
        "int",
        "float",
        "char",
        "void",
        "type *"};

    cfg["user_defined_declaration"] = {
        "struct id id = { assignment_list } ",
        "union id id = { assignment }",
        "enum id id = id"};

    cfg["assignment_list"] = {
        "assignment",
        "assignment , assignment_list"};

    cfg["assignment"] = {
        "identifier = expression",
        ".identifier = expression"};

    cfg["expression"] = {
        "id",
        "val",
        "function_call",
        "expression operator expression",
    };

    cfg["function_call"] = {
        "id ( argument_list )",
        "id ( )"};

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
        "function_definiton",
        "derived_data_type_definition ;"};

    cfg["derived_data_type_definition"] = {
        "struct id { field_list }",
        "enum id { field_list }",
        "union id { field_list }"};

    cfg["field_list"] = {
        "field",
        "field ; field_list"};

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
        "enum id id arr_ptr",
    };

    cfg["id_list"] = {
        "id",
        "id , id_list"};

    cfg["function_definition"] = {
        "basic_type id ( parameter_list ) { stmt_list }",
        "basic_type id ( ) { stmt_list }",
        "struct id id ( parameter_list ) { stmt_list }",
        "struct id id ( ) { stmt_list }",
        "union id id ( parameter_list ) { stmt_list }",
        "union id id ( ) { stmt_list }",
        "enum id id ( ) { stmt_list }",
        "enum id id ( parameter_list ) { stmt_list }"};

    cfg["parameter_list"] = {
        "parameter",
        "parameter , parameter_list"};

    cfg["parameter"] = {
        "basic_type id",
        "basic_type id arr_ptr",
        "struct id id",
        "struct id id arr_ptr",
        "union id id",
        "union id id arr_ptr",
        "enum id id",
        "enum id id arr_ptr"};

    cfg["arr_ptr"] = {
        "*", "[ ]",
        "* arr_ptr", "arr_ptr [ ]"};
}
