#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Square.hpp"

const int SCREEN_WIDTH = 602; 
const int SCREEN_HEIGHT = 602;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTextureX = NULL;
SDL_Texture* gTextureO = NULL;
enum positions
{
    TOP_LEFT, TOP_CENTER, TOP_RIGHT,
    MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT,
    BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT,
    NUM_OF_POSITIONS
};

bool Init();
void Kill();
void Init_rects( square arr[] );
void Draw_board( square board[] );
std::string Enum_to_str( int val );
SDL_Texture* LoadTexture( std::string path );
bool InitMedia();
bool CheckVictory( square board[] );
void Color( square* first, square* second, square* third );
bool CheckDraw( square board[] );

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
    std::cout << "It is now O's turn!\n";
    while( running )
    {
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
                            // draws naught or cross depending on whose turn it is
                            if( turn )
                                SDL_RenderCopy( gRenderer, gTextureO, NULL, &board[i].checker );
                            else
                                SDL_RenderCopy( gRenderer, gTextureX, NULL, &board[i].checker );
                            SDL_RenderPresent( gRenderer );
                            //std::cout << "You occupied " << Enum_to_str( i ) << std::endl;
                            if( CheckVictory( board ) )
                            {
                                running = false;
                                char who = turn ? 'O' : 'X';
                                std::cout << who << " has won!" << std::endl;
                                SDL_Delay(2000);
                            }
                            else if( CheckDraw( board ) )
                            {
                                running = false;
                                std::cout << "It's a draw!" << std::endl;
                                SDL_Delay(2000);
                            }
                            else
                            {
                                turn = !turn; // other p
                                char who = turn ? 'O' : 'X';
                                std::cout << "It is now " << who << "'s turn!" << std::endl;
                            }
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
    }
    Kill();
    return 0;
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
    SDL_RenderPresent( gRenderer );
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
    SDL_RenderFillRect( gRenderer, &board[ TOP_LEFT ].checker );
    SDL_RenderFillRect( gRenderer, &board[ TOP_RIGHT ].checker );
    SDL_RenderFillRect( gRenderer, &board[ MIDDLE_CENTER ].checker );
    SDL_RenderFillRect( gRenderer, &board[ BOTTOM_LEFT ].checker );
    SDL_RenderFillRect( gRenderer, &board[ BOTTOM_RIGHT ].checker );
    SDL_RenderFillRect( gRenderer, &board[ TOP_CENTER ].checker );
    SDL_RenderFillRect( gRenderer, &board[ MIDDLE_LEFT ].checker );
    SDL_RenderFillRect( gRenderer, &board[ MIDDLE_RIGHT ].checker );
    SDL_RenderFillRect( gRenderer, &board[ BOTTOM_CENTER ].checker );
    // draws them on window
    SDL_RenderDrawRect( gRenderer, &board[ TOP_LEFT ].checker );
    SDL_RenderDrawRect( gRenderer, &board[ TOP_CENTER ].checker );
    SDL_RenderDrawRect( gRenderer, &board[ TOP_RIGHT ].checker );
    SDL_RenderDrawRect( gRenderer, &board[ MIDDLE_LEFT ].checker );
    SDL_RenderDrawRect( gRenderer, &board[ MIDDLE_CENTER ].checker );
    SDL_RenderDrawRect( gRenderer, &board[ MIDDLE_RIGHT ].checker );
    SDL_RenderDrawRect( gRenderer, &board[ BOTTOM_LEFT ].checker );
    SDL_RenderDrawRect( gRenderer, &board[ BOTTOM_CENTER ].checker );
    SDL_RenderDrawRect( gRenderer, &board[ BOTTOM_RIGHT ].checker );
    SDL_RenderPresent( gRenderer );
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