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
#include "color.h"
#include "window.h"
#include "image.h"
#include "map.h"
#include "mapManager.h"
#include "font.h"
#include "interface.h"
#include "game.h"

Game::Game() {
#ifdef __ANDROID__
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	
	__android_log_print(ANDROID_LOG_INFO, "Hoelia", "Current display: %dx%d", current.w, current.h);
	
	Window::main = new Window("Hoelia", current.w, current.h);
#else
	Window::main = new Window("Hoelia", 640, 480);
#endif
	
	m_continue = true;
	m_paused = false;
	
	MapManager::initAll();
	
	Interface::init();
}

Game::~Game() {
	Interface::quit();
	
	MapManager::free();
	
	delete Window::main;
}

void Game::mainLoop() {
	// Initialize time counters
	u32 lastTime = 0;
	u32 actualTime = 0;
	
	MapManager::currentMap->render();
	
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
		
		Interface::renderHUD();
		
		// Update render
		Window::main->update();
	}
}

