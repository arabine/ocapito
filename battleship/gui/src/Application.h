#pragma once

#include "UiBoard.h"

class Application
{

public:
    void Initialize();

    void Loop();

private:
    UiBoard m_boatsGrid;
    UiBoard m_shotsGrid;

    void CreateBottomBar();


};
