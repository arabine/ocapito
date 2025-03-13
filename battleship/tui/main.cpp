#include <iostream>

#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "NetGame.h"

#define GAME_TCP_PORT1   12345
#define GAME_TCP_PORT2   12346


int main(int argc, char **argv)
{
	std::cout << "[BATTLE] Starting" << std::endl;

    bool solo = true;
    bool start = false;

    if (argc > 3) {
        solo = false;
        if (std::string(argv[3]) == "start")
        {
            start = true;
        }
    }

    if (solo)
    {
        Game::RunSoloGameVersusAI();
    }
    else
    {
        int port1 = start ? GAME_TCP_PORT1 : GAME_TCP_PORT2;
        int port2 = start ? GAME_TCP_PORT2 : GAME_TCP_PORT1;
        Game::State state = start ? Game::MY_TURN : Game::HIS_TURN;

        NetGame game(port1, port2, state);
        game.Start(argv[1], argv[2]);
    }


	return 0;
}
