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

#include "types.h"
#include "window.h"
#include "image.h"
#include "map.h"
#include "game.h"

Game::Game() {
	m_continue = true;
	m_paused = false;
	
	// Initialize game main window
	Window::main = new Window("Hoelia", 640, 480);
}

Game::~Game() {
	delete Window::main;
}

void Game::mainLoop() {
	// Initialize time counters
	u32 lastTime = 0;
	u32 actualTime = 0;
	
	/* TEST FOR MAPS */
	Image *plainTiles = new Image("graphics/tilesets/plain.png");
	u16 plainInfo[256];
	for(u16 i = 0 ; i < 256 ; i++) plainInfo[i] = 0;
	Tileset *plain = new Tileset{plainTiles, plainInfo, 16, 16};
	
	Map *a1 = new Map("maps/a1.map", plain, 40, 30, 0, 0, 0);
	
	a1->render();
 	
	while(m_continue) {
		// Process events
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0) {
			switch(event.type) {
				case SDL_QUIT:
					m_continue = false;
					break;
				default:
					break;
			}
		}
		
		// Skip 15 ms between each frame
		actualTime = SDL_GetTicks();
		if(actualTime - lastTime < 15) {
			SDL_Delay(15 - (actualTime - lastTime));
			continue;
		}
		
		// Update render
		Window::main->update();
	}
	
	delete a1;
	delete plain;
	delete plainTiles;
}

