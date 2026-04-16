/**
 * @file questions.cpp
 * @authors dreamsbootleg
 * @brief gets settings for checkers compitition
 * @date 3/29/26
 */

#include <iostream>
#include <string>

#include "questions.h"
#define EXEC_DIR "/AI_Files/"
#define PROTECT_DIR "protected/"

int get_run_type()
{
    std::string input = "";
    std::cout << "What would you like to run?\n";
    std::cout << "   [0]\tTest AI (default)\n"
              << "   [1]\tRun Contest\n"
              << "   [2]\tReplay Logs\n";
    std::cout << "Please enter your choice [(0)-2]\n"
              << std::flush;

    getline(std::cin, input);
    if (input == "1")
        return 1;
    else if (input == "2")
        return 2;
    else
        return 0;
}

std::string get_match_type()
{
    std::string input = "";
    std::cout << "What kind of game would you like to play?\n";
    std::cout << "   [0]\tAmerican Checkers (default)\n"
              << "   [1]\tInternational Checkers\n";
    std::cout << "Please enter your choice [(0)-1]\n"
              << std::flush;

    getline(std::cin, input);
    if (input == "1")
        return "international_checkers";
    else
        return "american_checkers";
}

void exit_abruptly()
{
    std::cout << "\nExiting.\n"
              << std::flush;
    exit(1);
}

std::vector<std::tuple<std::string, std::string>> get_all_players(const std::string &system_dir)
{
    DIR *dir;
    dirent *dp;
    std::vector<std::tuple<std::string, std::string>> execs;

    string exec_dir = system_dir + EXEC_DIR;

    get_protected_players(exec_dir, execs);
    // make sure the directory can be opened
    if ((dir = opendir(exec_dir.c_str())) == NULL)
    {
        print_error("Cannot open AI_Files/ directory!", __FILE__, __LINE__);
        fprintf(stderr, "Directory path: %s\n", exec_dir.c_str());
        exit(16); // exit_abruptly();
    }

    struct stat sb;
    while ((dp = readdir(dir)) != NULL)
    {
        string file_name = exec_dir + dp->d_name;
        // if it is both a regular file, and an executable, add it.
        if (stat(file_name.c_str(), &sb) == 0 && sb.st_mode & S_IXUSR && sb.st_mode & S_IFREG)
        {
            execs.push_back(make_tuple(dp->d_name, exec_dir));
        }
    }

    // sort the players in alphabetical order
    sort(execs.begin(), execs.end(), sort_players_by_name);

    return execs;
}

void get_protected_players(const std::string &exec_dir, std::vector<std::tuple<std::string, std::string>> &execs)
{
    DIR *dir;
    dirent *dp;
    std::string protect_dir = exec_dir + PROTECT_DIR;

    // make sure the directory can be opened.
    if ((dir = opendir(protect_dir.c_str())) == NULL)
    {
        print_error("Cannot open AI_Files/protected/ directory!", __FILE__, __LINE__);
        fprintf(stderr, "Directory path: %s\n", protect_dir.c_str());
        exit(15); // exit_abruptly();
    }

    struct stat sb;
    // for each file in the directory
    while ((dp = readdir(dir)) != NULL)
    {
        string file_name = protect_dir + dp->d_name;
        // if it is both a regular file, and an executable, add it.
        if (stat(file_name.c_str(), &sb) == 0 && sb.st_mode & S_IXUSR && sb.st_mode & S_IFREG)
        {
            execs.push_back(make_tuple(dp->d_name, protect_dir));
        }
    }
    return;
}

void check_ai_list(vector<tuple<string, string>> &execs)
{
    string input = "";

    // make sure there are AI to play the contest.
    int choice, num_execs = execs.size();
    if (num_execs < 1)
    {
        cout << "\nNo AI to play a contest.\n";
        exit_abruptly();
    }

    do
    {
        cout << "\nThis is the list of AIs entered in the contest:\n"
             << flush;

        // display all AI in the contest
        for (int i = 0; i < num_execs; i++)
        {
            cout << "   [" << i << "]\t" << get<0>(execs.at(i)) << "\n"
                 << flush;
        }

        // ask for any AI to remove from the contest
        cout << "Would you like to remove any from the contest? [Enter for no, AI # if so] " << flush;
        getline(cin, input);

        if (input == "")
            break; // no AI to remove, continue
        if (!is_int(input))
            exit_abruptly(); // if they input non-int

        choice = stoi(input);
        if (choice < 0 || choice >= num_execs)
            exit_abruptly(); // input not in range

        execs.erase(execs.begin() + choice);
        num_execs = execs.size();

    } while (input != "" && num_execs - 1 >= 2);
    return;
}

bool is_int(string str)
{
    int len = str.length();
    if (len == 0)
        return false;
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

bool is_float(string str)
{
    int len = str.length();
    if (len == 0)
        return false;
    int period = 0;
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(str[i]))
        {
            if (str[i] == '.' && period == 0)
            {
                // all is good, as long as there is only one period.
                period = 1;
            }
            else
                return false;
        }
    }
    return true;
}

bool sort_players_by_name(const tuple<string, string> &a, const tuple<string, string> &b)
{
    return get<0>(a) < get<0>(b);
}

void ask_game_questions(int &board_size, int &num_games)
{
    string input = "";
    cout << "\nHow many games should the AI play? (500) " << flush;
    getline(cin, input);
    if (input != "")
    {
        if (!is_int(input))
            exit_abruptly();
        num_games = stoi(input);
        if (num_games < 0 || num_games >= INT16_MAX)
            exit_abruptly();
    }
    cout << "\nWhat size of the board would you like? [3-(10)] " << flush;
    getline(cin, input);
    if (input != "")
    { // don't take the default, convert it
        if (!is_int(input))
            exit_abruptly();
        board_size = stoi(input);
        if (board_size < 3 || board_size > 10)
            exit_abruptly();
    }
    return;
}
void ask_delay_question(int &delay)
{
    float f_delay;
    string input = "";
    cout << "\nHow long should the delay between actions be? [(0.3), 0.5, 1, etc.] " << flush;
    getline(cin, input);
    if (input != "")
    { // don't take the default, convert it
        if (!is_float(input))
            exit_abruptly();
        f_delay = stof(input);
        if (f_delay < 0.0)
            exit_abruptly();
        delay = static_cast<int>(f_delay * 1000000);
    }
    return;
}
/* ────────────────────────── *
 * CONTEST QUESTION FUNCTIONS *
 * ────────────────────────── */

void ask_contest_display_questions(DisplayType &contest_display, int &delay)
{
    string input = "";
    cout << "\nHow would you like to display the contest games?\n";
    cout << "   [0]\tDisplay games after contest finishes (default)\n"
         << "   [1]\tDisplay games while running\n"
         << "   [2]\tLog only, don't display\n";
    cout << "Please enter your choice [(0)-2] " << flush;
    getline(cin, input);

    if (input == "" || input == "0")
        contest_display = AFTER;
    else if (input == "1")
        contest_display = DURING;
    else if (input == "2")
        contest_display = NONE;
    else
        exit_abruptly();

    if (contest_display != NONE)
        ask_delay_question(delay);
    return;
}

void ask_which_player(vector<tuple<string, string>> &execs, const char *word, string &ai_exec)
{
    string input = "";
    int choice, num_execs;

    // make sure there are AI to play the match.
    num_execs = execs.size();
    if (num_execs < 1)
    {
        cout << "\nNo AI to play a match.\n";
        exit_abruptly();
    }

    // word is either "first" or "second"
    printf("\nChoose the %s AI to battle from the following:\n", word);

    // display all AI options
    for (int i = 0; i < num_execs; i++)
    {
        printf("   [%d]\t%s\n", i, get<0>(execs.at(i)).c_str());
    }

    // ask for AI option input
    printf("Please enter your choice [0-%d] ", num_execs - 1);
    getline(cin, input);

    if (input == "")
        exit_abruptly(); // if they input empty string
    if (!is_int(input))
        exit_abruptly(); // if they input non-int

    choice = stoi(input);
    if (choice < 0 || choice >= num_execs)
        exit_abruptly(); // if input is not in range

    ai_exec = get<1>(execs.at(choice)) + get<0>(execs.at(choice)); // else, store the executable with path <1> and file name <0>
    return;
}