/**
 * @file messages.cpp
 * @author d_bootleg
 * @brief Checkers Server Message Functions
 * @date 2026-04-15
 */

#include "message.h"

ErrorNum parse_ai_name_msg(char *msg, char *ai_name)
{
    if (strlen(msg) == 0)
        return BAD_HELLO_MSG;
    if (strlen(msg) > MAX_NAME_SIZE)
        strncpy(ai_name, msg, MAX_NAME_SIZE - 1);
    else
        strncpy(ai_name, msg, strlen(msg));
    return NO_ERR;
}

ErrorNum parse_author_names_msg(char *msg, char *author_names)
{
    if (strlen(msg) == 0)
        return BAD_HELLO_MSG;
    if (strlen(msg) > MAX_NAME_SIZE)
        strncpy(author_names, msg, MAX_NAME_SIZE - 1);
    else
        strncpy(author_names, msg, strlen(msg));
    return NO_ERR;
}
