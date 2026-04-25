/**
 * @file messages.cpp
 * @author d_bootleg
 * @brief Checkers Server Message Functions
 * @date 2026-04-15
 */

#include "message.h"

ErrorNum parse_ai_name_msg(char *msg, char *ai_name)
{
    string msg_str = msg;
    vector<string> tokens = separate_string(msg_str);
    if (tokens.size() <= 2 || tokens[0] != "id" || tokens[1] != "name")
        return BAD_HELLO_MSG;
    string names;
    for (size_t i = 2; i < tokens.size(); ++i)
    {
        if (i > 2)
            names += " ";
        names += tokens[i];
    }
    strncpy(ai_name, names.c_str(), MAX_NAME_SIZE - 1);
    ai_name[MAX_NAME_SIZE - 1] = '\0';
    return NO_ERR;
}

ErrorNum parse_author_names_msg(char *msg, char *author_names)
{
    string msg_str = msg;
    vector<string> tokens = separate_string(msg_str);
    if (tokens.size() <= 2 || tokens[0] != "id" || tokens[1] != "author")
        return BAD_HELLO_MSG;
    string names;
    for (size_t i = 2; i < tokens.size(); ++i)
    {
        if (i > 2)
            names += " ";
        names += tokens[i];
    }
    strncpy(author_names, names.c_str(), MAX_NAME_SIZE - 1);
    author_names[MAX_NAME_SIZE - 1] = '\0';
    return NO_ERR;
}

vector<string> separate_string(const string &str)
{
    istringstream iss(str);
    vector<string> words;
    string word;

    while (iss >> word)
    {
        words.push_back(word);
    }

    return words;
}