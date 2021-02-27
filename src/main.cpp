#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Square.hpp"
#include "gvars.hpp"
#include "Inits.hpp"
#include "positions.cpp"



void Draw_board( square board[] );
std::string Enum_to_str( int val );
bool CheckVictory( square board[] );
void Color( square* first, square* second, square* third );
bool CheckDraw( square board[] );
void Redraw_board( square board[] );

int main(int argc, char* args[])
{
	if( !Init() ) return 1;
	if( !InitMedia() ) return 1;
	square board[9];
	Init_rects( board );
	Draw_board( board );
	SDL_Event e;
	bool running = true;
	bool turn = 1; // 1 is O, 0 is X
	while( running )
	{
		int win = 0;
		// get input
		while( SDL_PollEvent( &e ) > 0 && running )
		{
			switch( e.type )
			{
				case SDL_QUIT:
				running = false;
				break;

				case SDL_MOUSEBUTTONDOWN:
				SDL_Point click = {e.button.x, e.button.y};
				for( size_t i = 0; i < NUM_OF_POSITIONS; i++ )
				{
					if( SDL_PointInRect(&click, &board[i].checker) == SDL_TRUE )
					{
						if( board[i].isOccupied() == OCCUPIED_NOT )
						{
							board[i].Occupy( turn );
							if( CheckVictory( board ) )
								win = 1;
							else if( CheckDraw( board ) )
								win = 2;
							else
								turn = !turn;
							break;
						}
						else
						{
							std::cout << "This checker is occupied!" << std::endl;
						}
					}
				}
				break;
			}
		}
		// redraw board
		Draw_board( board );
		Redraw_board( board );
		CheckVictory( board );
		SDL_RenderPresent( gRenderer );
		// check for win
		if( win == 1 )
		{
			char who = turn ? 'O' : 'X';
			std::cout << who << " has won!" << std::endl;
			running = false;
			SDL_Delay( 2000 );
		}
		else if( win == 2 )
		{
			std::cout << "It's a draw!" << std::endl;
			running = false;
			SDL_Delay( 2000 );
		}
		
	}
	Kill();
	return 0;
}

// redraws board's textures
void Redraw_board( square board[] )
{
	for( size_t i = 0; i < NUM_OF_POSITIONS; i++ )
	{
		switch( board[i].isOccupied() )
		{
			case OCCUPIED_X:
			SDL_RenderCopy( gRenderer, gTextureX, NULL, &board[i].checker );
			break;

			case OCCUPIED_O:
			SDL_RenderCopy( gRenderer, gTextureO, NULL, &board[i].checker );
			break;

			case OCCUPIED_NOT:
			break;
		}
	}
}
// checks if draw
bool CheckDraw( square board[] )
{
	for( size_t i = 0; i < NUM_OF_POSITIONS; i++ )
	{
		if( board[i].isOccupied() == OCCUPIED_NOT )
			return false;
	}
	return true;
}
// colors rectangle green
void Color( square* first, square* second, square* third )
{
	SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND );
	SDL_SetRenderDrawColor( gRenderer, 163, 211, 170, 140 );
	SDL_RenderFillRect( gRenderer, &first->checker );
	SDL_RenderFillRect( gRenderer, &second->checker );
	SDL_RenderFillRect( gRenderer, &third->checker );
}
// checks for victory in board
bool CheckVictory( square board[] )
{
	bool win = false;
	// check for horizontal win
	if( board[ TOP_LEFT ].isOccupied()    == board[ TOP_CENTER ].isOccupied()    && board[ TOP_LEFT ].isOccupied()    == board[ TOP_RIGHT ].isOccupied()     && board[ TOP_LEFT ].isOccupied()    != OCCUPIED_NOT )
	{
		Color( &board[ TOP_LEFT ], &board[ TOP_CENTER ], &board[ TOP_RIGHT ] );
		win = true;
	}
	if( board[ MIDDLE_LEFT ].isOccupied() == board[ MIDDLE_CENTER ].isOccupied() && board[ MIDDLE_LEFT ].isOccupied() == board[ MIDDLE_RIGHT ].isOccupied()  && board[ MIDDLE_LEFT ].isOccupied() != OCCUPIED_NOT )
	{
		Color( &board[ MIDDLE_LEFT ], &board[ MIDDLE_CENTER ], &board[ MIDDLE_RIGHT ] );
		win = true;
	}
	if( board[ BOTTOM_LEFT ].isOccupied() == board[ BOTTOM_CENTER ].isOccupied() && board[ BOTTOM_LEFT ].isOccupied() == board[ BOTTOM_RIGHT ].isOccupied()  && board[ BOTTOM_LEFT ].isOccupied() != OCCUPIED_NOT )
	{
		Color( &board[ BOTTOM_LEFT ], &board[ BOTTOM_CENTER ], &board[ BOTTOM_RIGHT ] );
		win = true;
	}
	// check for vertical win
	if( board[ TOP_LEFT ].isOccupied()    == board[ MIDDLE_LEFT ].isOccupied()   && board[ TOP_LEFT ].isOccupied()    == board[ BOTTOM_LEFT ].isOccupied()   && board[ TOP_LEFT ].isOccupied()    != OCCUPIED_NOT )
	{
		Color( &board[ TOP_LEFT ], &board[ MIDDLE_LEFT ], &board[ BOTTOM_LEFT ] );
		win = true;
	}
	if( board[ TOP_CENTER ].isOccupied()  == board[ MIDDLE_CENTER ].isOccupied() && board[ TOP_CENTER ].isOccupied()  == board[ BOTTOM_CENTER ].isOccupied() && board[ TOP_CENTER ].isOccupied()  != OCCUPIED_NOT )
	{
		Color( &board[ TOP_CENTER ], &board[ MIDDLE_CENTER ], &board[ BOTTOM_CENTER ] );
		win = true;
	}
	if( board[ TOP_RIGHT ].isOccupied()   == board[ MIDDLE_RIGHT ].isOccupied()  && board[ TOP_RIGHT ].isOccupied()   == board[ BOTTOM_RIGHT ].isOccupied()  && board[ TOP_RIGHT ].isOccupied()   != OCCUPIED_NOT )
	{
		Color( &board[ TOP_RIGHT ], &board[ MIDDLE_RIGHT ], &board[ BOTTOM_RIGHT ] );
		win = true;
	}
	// check for diagonal win
	if( board[ TOP_LEFT ].isOccupied()    == board[ MIDDLE_CENTER ].isOccupied() && board[ TOP_LEFT ].isOccupied()    == board[ BOTTOM_RIGHT ].isOccupied()  && board[ TOP_LEFT ].isOccupied()    != OCCUPIED_NOT )
	{
		Color( &board[ TOP_LEFT ], &board[ MIDDLE_CENTER ], &board[ BOTTOM_RIGHT ] );
		win = true;
	}
	if( board[ TOP_RIGHT ].isOccupied()   == board[ MIDDLE_CENTER ].isOccupied() && board[ TOP_RIGHT ].isOccupied()   == board[ BOTTOM_LEFT ].isOccupied()   && board[ TOP_RIGHT ].isOccupied()   != OCCUPIED_NOT )
	{
		Color( &board[ TOP_RIGHT ], &board[ MIDDLE_CENTER ], &board[ BOTTOM_LEFT ] );
		win = true;
	}
	return win;
}
// prints enum string
std::string Enum_to_str( int val )
{
	switch( val )
	{
		case TOP_LEFT:
		return "TOP_LEFT ";

		case TOP_CENTER:
		return "TOP_CENTER";

		case TOP_RIGHT:
		return "TOP_RIGHT";

		case MIDDLE_LEFT:
		return "MIDDLE_LEFT";

		case MIDDLE_CENTER:
		return "MIDDLE_CENTER";

		case MIDDLE_RIGHT:
		return "MIDDLE_RIGHT";

		case BOTTOM_LEFT:
		return "BOTTOM_LEFT";

		case BOTTOM_CENTER:
		return "BOTTOM_CENTER";

		case BOTTOM_RIGHT:
		return "BOTTOM_RIGHT";
	}
	return "";
}
// draws the playing board (this has to be cleaned up)
void Draw_board( square board[] )
{
	// colors the rectangles
	SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
	for( size_t i = 0; i < NUM_OF_POSITIONS; i++ )
	{
		SDL_RenderFillRect( gRenderer, &board[ i ].checker );
	}
}
