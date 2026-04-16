/**
 * @file questions.h
 * @authors dreamsbootleg
 * @brief gets settings for checkers compitition
 * @date 3/29/26
 */
#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <algorithm>
#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "defines.h"
#include "conio.h"

#define EXEC_DIR "/AI_Files/"
#define PROTECT_DIR "protected/"

using namespace conio;

int get_run_type();

void exit_abruptly();

std::string get_match_type();

std::vector<std::tuple<std::string, std::string>> get_all_players(const std::string &system_dir);
void get_protected_players(const string &exec_dir, vector<tuple<string, string>> &execs);
bool sort_players_by_name(const tuple<string, string> &a, const tuple<string, string> &b);

void check_ai_list(vector<tuple<string, string>> &execs);
bool is_int(string str);

void ask_which_player(vector<tuple<string, string>> &execs, const char *word, string &ai_exec);

#endif