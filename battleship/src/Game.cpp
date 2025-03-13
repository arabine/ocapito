
#include <thread>
#include <chrono>

#include "Game.h"


// void Game::LookMyBoard(ITileVisitor &v)
// {
//     mPlayer.LookMyBoard(v);
// }

void Game::RunSoloGameVersusAI()
{
    Player computer;

    Fleet fleet_human;
    Fleet fleet_computer;

    // ------------------- BOUCLE D'INIT DU JOUEUR -------------------

    for (auto &b : fleet_human.boats)
    {
        // on place le bateau du joueur humain (version interactive)
//        human.PrintMyBoard();
//        while(!human.AskForPosition(b));

        // Version automatique
        do {

            b.GenerateRandomPosition(10, 10);
        } while(!mPlayer.PlaceBoat(b));
    }

    // ------------------- BOUCLE D'INIT DU ROBOT -------------------
    for (auto &b : fleet_computer.boats)
    {
        // on place le bateau ennemi
        do {
            b.GenerateRandomPosition(10, 10);
        } while(!computer.PlaceBoat(b));
    }

    mPlayer.PrintMyBoard();
    computer.PrintMyBoard();

    // ------------------- BOUCLE DE JEU  -------------------

    bool victory = false;
    Point p;
    do
    {
        p = mPlayer.Play();
        std::cout << p;
        computer.EnemyFire(p);

        victory = fleet_human.IsDestroyed();

        if (!victory)
        {
            p = computer.PlayRandom();
            mPlayer.EnemyFire(p);

            victory = fleet_computer.IsDestroyed();

            mPlayer.PrintMyBoard();
            computer.PrintMyBoard();
        }
    }
    while (!victory);

    if (fleet_human.IsDestroyed())
    {
        std::cout << "===============================================\n";
        std::cout << "            VOUS AVEZ PERDU!                   \n";
        std::cout << "===============================================\n" << std::endl;
    }
    else
    {
        std::cout << "===============================================\n";
        std::cout << "            VOUS AVEZ GAGNÉ!                   \n";
        std::cout << "===============================================\n" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "[BATTLE] Stopped" << std::endl;
}
