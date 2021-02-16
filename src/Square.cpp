#include <iostream>
#include <SDL.h>
#include "Square.hpp"

enum occupations
{
    OCCUPIED_NOT,
    OCCUPIED_X,
    OCCUPIED_O
};

square::square() : occupiedByO( false ), occupiedByX( false ), checker( {0, 0, 0, 0} ) {}

int square::isOccupied()
{
    if( occupiedByO )
        return OCCUPIED_O;
    else if( occupiedByX )
        return OCCUPIED_X;
    else
        return OCCUPIED_NOT;
}

void square::Occupy( bool sign )
{
    if( !sign )
    {
        occupiedByX = true;
        occupiedByO = false;
    }
    else
    {
        occupiedByX = false;
        occupiedByO = true;
    }
}