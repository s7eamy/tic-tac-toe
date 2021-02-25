#pragma once
#include <SDL2/SDL.h>

enum occupations
{
    OCCUPIED_NOT = -1,
    OCCUPIED_X = 2,
    OCCUPIED_O = 1
};

class square
{
    public:
    bool occupiedByX;
    bool occupiedByO;
    SDL_Rect checker;

    int isOccupied();         // checks whether it's occupied, returns enum to what it's occupied by
    void Occupy( bool sign ); // occupy, set bools to true/false
    square();                 // default ctor
};