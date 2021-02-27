#include "Inits.hpp"
#include "gvars.hpp"
#include "positions.cpp"
#include <SDL2/SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 602; 
const int SCREEN_HEIGHT = 602;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTextureX = NULL;
SDL_Texture* gTextureO = NULL;

// initializes media (images)
bool InitMedia()
{
	gTextureO = LoadTexture( "naught.png" );
	if( !gTextureO )
	{
		std::cout << "Failed to load naught.png!\n";
		return false;
	}
	gTextureX = LoadTexture( "cross.png" );
	if( !gTextureX )
	{
		std::cout << "Failed to load cross.png!\n";
		return false;
	}
	return true;
}
// loads .png from path
SDL_Texture* LoadTexture( std::string path )
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( !loadedSurface )
	{
		std::cout << "Failed to load surface from " << path << "! Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( !newTexture )
		{
			std::cout << "Failed to create texture! Error: " << SDL_GetError() << std::endl;
		}
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}
// initialize array of SDL_Rectangles
void Init_rects( square board[] )
{
	int rect_h = SCREEN_HEIGHT/3;
	int rect_w = SCREEN_WIDTH/3;
	// top row
	board[TOP_LEFT].checker      = { 0,          0,          rect_w, rect_h };
	board[TOP_CENTER].checker    = { rect_w+1,   0,          rect_w, rect_h };
	board[TOP_RIGHT].checker     = { rect_w*2+2, 0,          rect_w, rect_h };
	// middle row
	board[MIDDLE_LEFT].checker   = { 0,          rect_h+1,   rect_w, rect_h };
	board[MIDDLE_CENTER].checker = { rect_w+1,   rect_h+1,   rect_w, rect_h };
	board[MIDDLE_RIGHT].checker  = { rect_w*2+2, rect_h+1,   rect_w, rect_h };
	// bottom row
	board[BOTTOM_LEFT].checker   = { 0,          rect_h*2+2, rect_w, rect_h };
	board[BOTTOM_CENTER].checker = { rect_w+1,   rect_h*2+2, rect_w, rect_h };
	board[BOTTOM_RIGHT].checker  = { rect_w*2+2, rect_h*2+2, rect_w, rect_h };
}
// create window, renderer, init sdl subsystems
bool Init()
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL failed to initialize! Error: " << SDL_GetError() << std::endl;
		return false;
	}
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		std::cout << "IMG failed to initialize! Error: " << IMG_GetError() << std::endl;
		return false;
	}
	gWindow = SDL_CreateWindow( "Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
		std::cout << "Failed to create window! Error: " << SDL_GetError() << std::endl;
		return false;
	}
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL )
	{
		std::cout << "Failed to create renderer! Error: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
	SDL_RenderClear( gRenderer );
	return true;
}
// destroy window, renderer, exit sdl subsystems
void Kill()
{
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;
	SDL_DestroyTexture( gTextureO );
	SDL_DestroyTexture( gTextureX );
	gTextureO = NULL;
	gTextureX = NULL;
	IMG_Quit();
	SDL_Quit();
}