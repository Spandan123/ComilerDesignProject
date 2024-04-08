#include <bits/stdc++.h>

extern std::unordered_map<std::string, std::vector<std::string>> cfg;

extern void intialize_grammar_cfg()
{
    cfg["program"] = {"declaration_list", "function_list"};
    cfg["declaration_list"] = {"declaration", "declaration_list"};
    cfg["declaration"] = {"basic_declaration", "user_defined_declaration"};
    cfg["basic_declaration"] = {"basic_data_type", "identifier", "=", "literal"};
    cfg["basic_data_type"] = {"int", "float"};
    cfg["literal"] = {"integer_literal", "float_literal"};
    cfg["integer_literal"] = {"digit_list"};
    cfg["float_literal"] = {"digit_list", ".", "digit_list"};
    cfg["digit"] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    cfg["user_defined_declaration"] = {"struct_declaration", "union_declaration", "enum_declaration"};
    cfg["struct_declaration"] = {"struct", "identifier", "{", "struct_members", "}"};
    cfg["struct_members"] = {"declaration", "struct_members"};
    cfg["union_declaration"] = {"union", "identifier", "{", "union_members", "}"};
    cfg["union_members"] = {"declaration", "union_members"};
    cfg["enum_declaration"] = {"enum", "identifier", "{", "enum_constants", "}"};
    cfg["enum_constants"] = {"identifier", ",", "enum_constants"};
    cfg["function_list"] = {"function", "function_list"};
    cfg["function"] = {"return_type", "identifier", "(", "parameters", ")", "{", "body", "}"};
    cfg["return_type"] = {"basic_data_type", "void"};
    cfg["parameters"] = {"parameter_list", "void"};
    cfg["parameter_list"] = {"parameter", "parameter_list"};
    cfg["parameter"] = {"basic_data_type", "identifier"};
    cfg["body"] = {"statement_list"};
    cfg["statement_list"] = {"statement", "statement_list"};
    cfg["statement"] = {"declaration", "assignment", "loop", "function_call"};
    cfg["assignment"] = {"identifier", "=", "expression"};
    cfg["loop"] = {"for", "(", "assignment", ";", "condition", ";", "assignment", ")", "{", "body", "}"};
    cfg["condition"] = {"expression", "<", "expression"};
    cfg["relational_operator"] = {">", "<"};
    cfg["expression"] = {"term", "expression"};
    cfg["term"] = {"factor", "term"};
    cfg["factor"] = {"identifier", "literal"};
    cfg["add_operator"] = {"+", "-"};
    cfg["function_call"] = {"identifier", "(", "arguments", ")"};
    cfg["arguments"] = {"argument_list", "ε"};
    cfg["argument_list"] = {"expression", "argument_list"};
}