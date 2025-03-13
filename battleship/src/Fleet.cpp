#include "Fleet.h"

Fleet::Fleet ()
{
    boats.push_back(Boat('B', 4));
    boats.push_back(Boat('S', 3));
    boats.push_back(Boat('A', 5));
    boats.push_back(Boat('D', 2));
    boats.push_back(Boat('C', 3));
}

bool Fleet::IsDestroyed() const {
    unsigned int counter = 0;
    for (const auto &b: boats)
    {
        if (b.IsDestroyed())
        {
            std::cout << b.GetCode() << " is destroyed! " << std::endl;
            counter++;
        }
    }
    return counter == boats.size();
}
