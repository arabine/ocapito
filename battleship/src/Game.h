#pragma once

#include "Player.h"
#include "Fleet.h"
#include "IGame.h"

class Game : public IGame
{

public:
    enum State {
        MY_TURN,
        HIS_TURN,
    };

    Game(Game::State state)
        : mState(state)
    {
        for (auto &b : mFleet.boats)
        {
            do {
                b.GenerateRandomPosition(10, 10);
            } while(!mPlayer.PlaceBoat(b));
        }

        mPlayer.PrintMyBoard();
    }

    virtual ~Game() {}

    void RunSoloGameVersusAI();

    // From IGame
    // virtual void LookMyBoard(ITileVisitor &v);

protected:
    State mState;
    Player mPlayer;
    Fleet mFleet;
};
