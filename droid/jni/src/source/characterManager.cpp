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
#include <algorithm>
#include <vector>

#include "SDL_headers.h"

#include "types.h"
#include "config.h"
#include "timer.h"
#include "image.h"
#include "animation.h"
#include "sprite.h"
#include "character.h"
#include "player.h"
#include "characterManager.h"
#include "map.h"
#include "mapManager.h"

Character **CharacterManager::characters = NULL;

void CharacterManager::init() {
	characters = new Character*[NB_CHARACTERS];
	
	characters[0] = new Player(17 << 4, 21 << 4, DIR_RIGHT, 0);
}

void CharacterManager::free() {
	delete[] characters;
}


std::vector<Character*> CharacterManager::getCharactersInMap(u16 id) {
	std::vector<Character*> c;
	
	for(u16 i = 0 ; i < NB_CHARACTERS ; i++) {
		if(characters[i]->mapID() == id
		|| characters[i]->isPlayer()) {
			c.push_back(characters[i]);
		}
	}
	
	return c;
}


bool CharacterManager::sortCharacters(Character *c1, Character *c2) {
	return (c1->y() < c2->y());
}

void CharacterManager::moveCharacters() {
	std::vector<Character*> *v = MapManager::currentMap->characters();
	for(std::vector<Character*>::iterator it = v->begin() ; it != v->end() ; it++) {
		(*it)->move();
	}
}

void CharacterManager::renderCharacters() {
	std::vector<Character*> *v = MapManager::currentMap->characters();
	std::sort(v->begin(), v->end(), sortCharacters);
	for(std::vector<Character*>::iterator it = v->begin() ; it != v->end() ; it++) {
		if((*it)->isPlayer()) ((Player*)(*it))->action();
		(*it)->render();
	}
}

Player *CharacterManager::player() {
	return (Player*)characters[0];
}

