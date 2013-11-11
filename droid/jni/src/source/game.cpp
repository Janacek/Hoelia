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
#include <vector>

#include "SDL_headers.h"

#include "types.h"
#include "config.h"
#include "timer.h"
#include "color.h"
#include "keyboard.h"
#include "window.h"
#include "image.h"
#include "font.h"
#include "interface.h"
#include "animation.h"
#include "sprite.h"
#include "character.h"
#include "player.h"
#include "characterManager.h"
#include "map.h"
#include "mapManager.h"
#include "door.h"
#include "doorManager.h"
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
	
	CharacterManager::init();
	
	MapManager::init();
	
	DoorManager::init();
	
	Interface::init();
}

Game::~Game() {
	Interface::free();
	
	DoorManager::free();
	
	MapManager::free();
	
	CharacterManager::free();
	
	delete Window::main;
}

void Game::mainLoop() {
	MapManager::currentMap->render();
	
	while(m_continue) {
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0) {
			switch(event.type) {
				case SDL_QUIT:
					m_continue = false;
					break;
#ifndef __ANDROID__
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE: m_continue = false; break;
						case SDLK_p: m_paused = !m_paused; break;
						default: break;
					}
#else
				case SDL_FINGERDOWN:
				case SDL_FINGERMOTION:
					Keyboard::updatePad(&event);
					break;
				case SDL_FINGERUP:
					Keyboard::resetPad(&event, true);
					break;
				case SDL_APP_WILLENTERBACKGROUND:
					continue;
#endif
				default:
					break;
			}
		}
		
		Keyboard::update();
		
		scroll();
		
#ifdef VIEWPORT
		MapManager::currentMap->render();
#else
		MapManager::currentMap->update();
#endif
		
		CharacterManager::moveCharacters();
		CharacterManager::renderCharacters();
		
		Interface::renderHUD();
		
		Window::main->update();
	}
}

void Game::scroll() {
	s16 moveX = 0;
	s16 moveY = 0;
	u16 iMax = 0;
	s16 playerX = 0;
	s16 playerY = 0;
	
	if(CharacterManager::player()->x() > (MapManager::currentMap->width() - 1) * 16 + 1)		{ moveX =  16; iMax = 40; playerX = -16; }
	else if(CharacterManager::player()->x() < -2)												{ moveX = -16; iMax = 40; playerX =  16; }
	else if(CharacterManager::player()->y() > (MapManager::currentMap->height() - 1) * 16 + 1)	{ moveY =  16; iMax = 30; playerY = -16; }
	else if(CharacterManager::player()->y() < -2)												{ moveY = -16; iMax = 30; playerY =  16; }
	else																						{ return; }
	
	// Reset player movement vectors
	CharacterManager::player()->stop();
	
	for(u16 i = 0 ; i < iMax ; i++) {
		// Move characters
		for(std::vector<Character*>::iterator it = MapManager::currentMap->characters()->begin() ; it != MapManager::currentMap->characters()->end() ; it++) {
			if((i & 1) || !(i & 11)) (*it)->moveX(playerX); else (*it)->moveX(playerX - playerX / 16);
			if((i & 1) || !(i & 15)) (*it)->moveY(playerY); else (*it)->moveY(playerY - playerY / 16);
		}
		
		// Move view to scroll
		Map::viewRect.x += moveX;
		Map::viewRect.y += moveY;
		
#ifdef VIEWPORT
		// Update viewport
		Window::main->updateViewportPosition(Window::main->viewportX() - moveX, Window::main->viewportY() - moveY);
#endif
		
		// Refresh display on time in two
		if(i & 1) {
			Window::main->clear();
			MapManager::refreshMaps(MapManager::zones[MapManager::currentMap->zone()], moveX, moveY);
			CharacterManager::renderCharacters();
			Interface::renderHUD();
			Window::main->update(false);
		}
	}
	
	Map *tempOldMap = MapManager::currentMap;
	
	// Update currentMap variable
	if(MapManager::currentMap != NULL
	&& MapManager::currentMap->x() + moveX / 16 >= 0
	&& MapManager::currentMap->x() + moveX / 16 < MapManager::zonesSizes[MapManager::currentMap->zone()]
	&& MapManager::currentMap->y() + moveY / 16 >= 0
	&& MapManager::currentMap->y() + moveY / 16 < MapManager::zonesSizes[MapManager::currentMap->zone()]) MapManager::currentMap = MapManager::zones[MapManager::currentMap->zone()][MAP_POS(MapManager::currentMap->x() + moveX / 16, MapManager::currentMap->y() + moveY / 16, MapManager::currentMap->zone())];
	
	printf("Scrolling: zones[%d][MAP_POS(%d, %d, %d)]\n", tempOldMap->zone(), tempOldMap->x() + moveX / 16, tempOldMap->y() + moveY / 16, tempOldMap->zone());
	
	if(MapManager::currentMap == NULL) {
		fprintf(stderr, "Bad scrolling: zones[%d][MAP_POS(%d, %d, %d)]\n", tempOldMap->zone(), tempOldMap->x() + moveX / 16, tempOldMap->y() + moveY / 16, tempOldMap->zone());
		exit(EXIT_FAILURE);
	}
}

