
#include "Player.h"
#include <iostream>
#include <thread>
#include <iomanip>
#include "Random.h"

Player::Player()
{

}

void Player::PrintMyBoard()
{
    mMyBoard.Print();
}


void Player::Print()
{
    PrintMyBoard();
	std::cout << "---------- MES TIRS ----------" << std::endl;
	mMyShots.Print();
}

bool Player::PlaceBoat(Boat &b)
{
    return mMyBoard.AddBoat(b);
}

void Player::EnemyFire(const Point &p)
{
    mMyBoard.Fire(p);
}

Point Player::PlayRandom()
{
    Random rng(0, 9);

    // simule une réflexion
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * rng.get()));
    Random rng2(0, 9);
    Point p(rng.get(), rng2.get());
    return p;
}

Point Player::Play()
{
    bool valid = false;
    Point p;

    do {
        std::cout << "Entrez les coordonnées du tir (ex: B4): ";
        std::string coord;
        std::cin >> coord;

        if (p.FromString(coord))
        {
            if ((p.GetX() < mMyBoard.GetSize()) && (p.GetY() < mMyBoard.GetSize()))
            {
                valid = true;
            }
        }

        if (!valid)
        {
            std::cout << "Invalide!" << std::endl;
        }
    } while(!valid);

    return p;
}

bool Player::AskForPosition(Boat& b)
{
    bool valid = false;

    std::cout << "Placement le bateau: " <<  b.GetCode() << std::endl;
    std::cout << "Entrez les coordonnées de la proue (ex: B4): ";

    std::string coord;
    std::cin >> coord;

    std::cout << "Entrez l'orientation du bateau (sens croissant)(0=vertical, 1=horizontal): ";

    std::string direction;
    std::cin >> direction;

    Point p;
    valid = p.FromString(coord);

    if (valid)
    {
        Boat::Direction dir = Boat::HORIZONTAL;
        if (direction[0] == '0')
        {
            dir = Boat::VERTICAL;
        }

        std::cout << p;

        if ((p.GetX() < mMyBoard.GetSize()) && (p.GetY() < mMyBoard.GetSize()))
        {
            b.SetPosition(p, dir);
            valid = mMyBoard.AddBoat(b);
        }
    }

    if (!valid)
    {
        std::cout << "Coordonnées invalides" << std::endl;
    }

    return valid;
}
