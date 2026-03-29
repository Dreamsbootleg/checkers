#include <string>
#include <stdexcept>

#include "referee.cpp"
#include "questions.cpp"
#include "define.h"

bool check_game_types(string game_type)
{
    for (int i = 0; i <= game_type_size; i++)
    {
        if (game_type == game_types[i])
            return true;
    }
    return false;
}

int main()
{
    string run_type;
    string game_type;

    run_type = get_run_type();
    game_type = get_game_type();
    if (check_game_types(game_type))
    {
        throw new invalid_argument("no game type %s on file!\n");
    }
    run_referee(game_type);
}