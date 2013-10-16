/*---------------------------------------------------------------------------------
	
	Hoelia
	Copyright (C) 2013-2014 Deloptia <deloptia.devteam@gmail.com>
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
---------------------------------------------------------------------------------*/
#include "SDL_headers.h"

#include "init.h"

void initSDL() {
	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	// Initialize SDL_image
	if(!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
		fprintf(stderr, "SDL_image init error: %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	}
	
	// Initialize SDL_ttf
	if(TTF_Init() < 0) {
		fprintf(stderr, "SDL_ttf init error: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	
	// Enable VSync if possible
	if(!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1")) {
		fprintf(stderr, "Warning: VSync not enabled!");
	}
}

void unloadSDL() {
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

