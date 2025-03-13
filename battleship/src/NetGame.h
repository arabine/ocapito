#pragma once

#include "Game.h"
#include "httplib.h"

class NetGame : public Game
{

public:

    NetGame(int myPort, int opponentPort, Game::State state)
        : Game(state)
        , mPort(myPort)
        , mOpponentPort(opponentPort)
    {

    }

    void Start(const std::string &my_ip, const std::string &opponent_ip)
    {
        mMyIp = my_ip;
        mOpponentIp = opponent_ip;

        mServer.Post("/play", [this](const httplib::Request &req, httplib::Response &res) {

            // On reçoit le tir ennemy
            if (mState == HIS_TURN)
            {
               Point p;
               p.FromString(std::string(req.body));
               std::cout << "CLIENT played: " << p;
               mPlayer.EnemyFire(p);
               mPlayer.PrintMyBoard();

               // C'est à nous de jouer
                Play();

//               res->status;
//               res->body;
            }
            else
            {

            }

            res.set_content("Hello World!", "text/plain");
        });


        // On commence à tirer si c'est à notre tour de commencer ...
        if (mState == MY_TURN)
        {
            std::cout << "[NET] Make sure opponent is started before" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));

            mState = HIS_TURN;
            Play();
        }

        mServer.listen(mMyIp.data(), mPort);
    }

    void Play()
    {
        std::cout << "PLAY" << std::endl;
        Point p = mPlayer.Play();
        httplib::Client cli(mOpponentIp, mOpponentPort);

        auto res = cli.Post("/play", p.ToString(), "text/plain");
    }
private:
    int mPort = 12345;
    std::string mMyIp{"127.0.0.1"};
    std::string mOpponentIp{"127.0.0.1"};
    int mOpponentPort;
    httplib::Server mServer;
};
