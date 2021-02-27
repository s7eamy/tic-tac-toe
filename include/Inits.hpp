#pragma once
#include "Square.hpp"
#include <string>

SDL_Texture* LoadTexture( std::string path );
bool InitMedia();
bool Init();
void Kill();
void Init_rects( square arr[] );