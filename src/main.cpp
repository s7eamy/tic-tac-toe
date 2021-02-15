#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 600; 
const int SCREEN_HEIGHT = 600;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
enum positions
{
    TOP_LEFT, TOP_CENTER, TOP_RIGHT,
    MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT,
    BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
};

bool Init();
void Kill();
void Init_rects( SDL_Rect arr[] );
void Draw_board( const SDL_Rect board[] );

int main(int argc, char* args[])
{
    if( !Init() ) return 1;
    SDL_Rect checkers[9];
    Init_rects( checkers );
    Draw_board( checkers );
    SDL_Event e;
    bool running = true;
    while( running )
    {
        while( SDL_PollEvent( &e ) > 0 )
        {
            if( e.type == SDL_QUIT )
            {
                running = false;
            }
        }
    }
    Kill();
    return 0;
}

// draws the playing board
void Draw_board( const SDL_Rect board[] )
{
    // colors the rectangles
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
    /*
    SDL_RenderFillRect( gRenderer, &board[ TOP_LEFT ] );
    SDL_RenderFillRect( gRenderer, &board[ TOP_RIGHT ] );
    SDL_RenderFillRect( gRenderer, &board[ MIDDLE_CENTER ] );
    SDL_RenderFillRect( gRenderer, &board[ BOTTOM_LEFT ] );
    SDL_RenderFillRect( gRenderer, &board[ BOTTOM_RIGHT ] );
    SDL_SetRenderDrawColor( gRenderer, 233, 233, 233, 255 );
    SDL_RenderFillRect( gRenderer, &board[ TOP_CENTER ] );
    SDL_RenderFillRect( gRenderer, &board[ MIDDLE_LEFT ] );
    SDL_RenderFillRect( gRenderer, &board[ MIDDLE_RIGHT ] );
    SDL_RenderFillRect( gRenderer, &board[ BOTTOM_CENTER ] );
    */
    // draws them on window
    SDL_RenderDrawRects( gRenderer, board, 9 );
    SDL_RenderPresent( gRenderer );
}
// initialize array of SDL_Rectangles
void Init_rects( SDL_Rect arr[] )
{
    // top row
    arr[TOP_LEFT]      = { 0,                0,                 SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
    arr[TOP_CENTER]    = { SCREEN_WIDTH/3,   0,                 SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
    arr[TOP_RIGHT]     = { SCREEN_WIDTH/3*2, 0,                 SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
    // middle row
    arr[MIDDLE_LEFT]   = { 0,                SCREEN_HEIGHT/3,   SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
    arr[MIDDLE_CENTER] = { SCREEN_WIDTH/3,   SCREEN_HEIGHT/3,   SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
    arr[MIDDLE_RIGHT]  = { SCREEN_WIDTH/3*2, SCREEN_HEIGHT/3,   SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
    // bottom row
    arr[BOTTOM_LEFT]   = { 0,                SCREEN_HEIGHT/3*2, SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
    arr[BOTTOM_CENTER] = { SCREEN_WIDTH/3,   SCREEN_HEIGHT/3*2, SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
    arr[BOTTOM_RIGHT]  = { SCREEN_WIDTH/3*2, SCREEN_HEIGHT/3*2, SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
}
// create window, renderer, init sdl subsystems
bool Init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL failed to initialize! Error: " << SDL_GetError() << std::endl;
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
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
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
    SDL_Quit();
}