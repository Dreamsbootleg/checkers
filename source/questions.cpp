/**
 * @file questions.cpp
 * @authors dreamsbootleg
 * @brief gets settings for checkers compitition
 * @date 3/29/26
 */

#include <iostream>
#include <string>

using namespace std;

int get_run_type()
{
    string input = "";
    printf("\nWhat would you like to run? \n");
    printf("Run contest[0]\n");
    printf("Test AI (default)[1]\n:");

    getline(cin, input);
    if (input == "0")
        return 0;
    else
        return 1;
}

string get_game_type()
{
    string input = "";
    printf("\nAmerican or International Checkers? \n");
    printf("American[0] (default)\n");
    printf("International[1]\n:");

    getline(cin, input);
    if (input == "1")
        return "international_checkers";
    else
        return "american_checkers";
}