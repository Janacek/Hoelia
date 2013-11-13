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
#include "color.h"
#include "timer.h"
#include "font.h"
#include "image.h"
#include "window.h"
#include "animation.h"
#include "sprite.h"
#include "character.h"
#include "player.h"
#include "characterManager.h"
#include "map.h"
#include "mapManager.h"
#include "door.h"
#include "doorManager.h"
#include "interface.h"

u16 Character::counter = 0;

Character::Character(const char *filename, CharacterType type, s16 x, s16 y, CharacterDirection direction, u16 mapID, u16 frameWidth, u16 frameHeight) : Sprite(filename, frameWidth, frameHeight) {
	m_id = counter;
	counter++;
	
	m_type = type;
	
	m_x = x;
	m_y = y;
	
	m_vx = 0;
	m_vy = 0;
	
	m_direction = direction;
	
	m_mapID = mapID;
	
	m_inCollision = false;
	m_inDoor = false;
	
	m_hitboxX = 3;
	m_hitboxY = 10;
	m_hitboxW = m_frameWidth - 6;
	m_hitboxH = m_frameHeight - 12;
	
	m_canMove = true;
	m_canTurn = true;
	m_moving = false;
}

Character::~Character() {
}

void Character::move() {
}

void Character::render() {
	if(m_moving) playAnimation(m_x, m_y, m_direction);
	else		 drawFrame(m_x, m_y, m_direction);
}

bool passable(s16 x, s16 y) {
	return !inTable(MapManager::nonPassableTiles, MapManager::currentMap->tileset()->info[MapManager::currentMap->getTile(x >> 4, y >> 4)]);
}

void Character::mapCollisions() {
	// Up and down
	if(m_vy != 0) {
		if (!passable(m_x + m_hitboxX			 , m_y + m_hitboxY + m_vy			 )
		||  !passable(m_x + m_hitboxX + m_hitboxW, m_y + m_hitboxY + m_vy			 )
		||  !passable(m_x + m_hitboxX			 , m_y + m_hitboxY + m_vy + m_hitboxH)
		||  !passable(m_x + m_hitboxX + m_hitboxW, m_y + m_hitboxY + m_vy + m_hitboxH)) {
			/* Let player slide on tiles corners */
			// Top left
			if (!passable(m_x + m_hitboxX + m_hitboxW + 8, m_y + m_hitboxY + m_vy)
			&&	 passable(m_x + m_hitboxX				 , m_y + m_hitboxY + m_vy)) {
				m_vx = -1;
			}
			// Top right
			if (!passable(m_x + m_hitboxX - 8		 , m_y + m_hitboxY + m_vy)
			&&   passable(m_x + m_hitboxX + m_hitboxW, m_y + m_hitboxY + m_vy)) {
				m_vx = 1;
			}
			// Bottom left
			if (!passable(m_x + m_hitboxX + m_hitboxW + 8, m_y + m_hitboxY + m_hitboxH + m_vy)
			&&	 passable(m_x + m_hitboxX				 , m_y + m_hitboxY + m_hitboxH + m_vy)) {
				m_vx = -1;
			}
			// Bottom right
			if (!passable(m_x + m_hitboxX - 8		 , m_y + m_hitboxY + m_hitboxH + m_vy)
			&&   passable(m_x + m_hitboxX + m_hitboxW, m_y + m_hitboxY + m_hitboxH + m_vy)) {
				m_vx = 1;
			}
			
			m_vy = 0;
		}
	}
	
	// Left and right
	if(m_vx != 0) {
		if (!passable(m_x + m_hitboxX + m_vx			, m_y + m_hitboxY			 )
		||  !passable(m_x + m_hitboxX + m_vx + m_hitboxW, m_y + m_hitboxY			 )
		||  !passable(m_x + m_hitboxX + m_vx			, m_y + m_hitboxY + m_hitboxH)
		||  !passable(m_x + m_hitboxX + m_vx + m_hitboxW, m_y + m_hitboxY + m_hitboxH)) {
			/* Let player slide on tiles corners */
			// Top left
			if (!passable(m_x + m_hitboxX + m_vx, m_y + m_hitboxY + m_hitboxH + 0)
			&&	 passable(m_x + m_hitboxX + m_vx, m_y + m_hitboxY				 )) {
				m_vy = -1;
			}
			// Bottom left
			if (!passable(m_x + m_hitboxX + m_vx, m_y + m_hitboxY - 0		 )
			&&   passable(m_x + m_hitboxX + m_vx, m_y + m_hitboxY + m_hitboxH)) {
				m_vy = 1;
			}
			// Top right
			if (!passable(m_x + m_hitboxX + m_hitboxW + m_vx, m_y + m_hitboxY + m_hitboxH + 0)
			&&	 passable(m_x + m_hitboxX + m_hitboxW + m_vx, m_y + m_hitboxY				 )) {
				m_vy = -1;
			}
			// Bottom right
			if (!passable(m_x + m_hitboxX + m_hitboxW + m_vx, m_y + m_hitboxY - 0		 )
			&&   passable(m_x + m_hitboxX + m_hitboxW + m_vx, m_y + m_hitboxY + m_hitboxH)) {
				m_vy = 1;
			}
			
			m_vx = 0;
		}
	}
}

void Character::testCollisions() {
	m_inCollision = false;
	
	mapCollisions();
}

void Character::doorCollisions() {
	if(inZones(m_x, m_y, MapManager::changeMapTiles) && !m_inDoor) {
		s16 doorID = DoorManager::findDoorID(m_x, m_y, MapManager::currentMap->id(), MapManager::currentMap->zone());
		if(doorID == -1) return;
		
		m_vx = 0;
		m_vy = 0;
		
		Window::main->clear();
		Window::main->drawFillRect(Window::main->viewportX(), Window::main->viewportY(), Window::main->viewportW() / 2, Window::main->viewportH(), Color::white);
		Window::main->drawFillRect(Window::main->viewportX() + Window::main->viewportW() / 2, Window::main->viewportY(), Window::main->viewportW() / 2, Window::main->viewportH(), Color::white);
		Window::main->update();
		
		MapManager::currentMap = MapManager::zones[DoorManager::doors[DoorManager::doors[doorID]->nextDoorID]->mapZone][DoorManager::doors[DoorManager::doors[doorID]->nextDoorID]->mapID];
		if(!MapManager::currentMap) exit(EXIT_FAILURE);
		
		m_x = DoorManager::doors[DoorManager::doors[doorID]->nextDoorID]->x;
		m_y = DoorManager::doors[DoorManager::doors[doorID]->nextDoorID]->y;
		m_direction = DoorManager::doors[DoorManager::doors[doorID]->nextDoorID]->direction;
		
		//Map::viewRect.x = MapManager::currentMap->x() * MAP_WIDTH * 16;
		//Map::viewRect.y = MapManager::currentMap->y() * MAP_HEIGHT * 16;
		
		for(u16 x = 0 ; x <= MapManager::currentMap->height() / 1.5 ; x++) {
			Window::main->clear();
			MapManager::currentMap->render();
			CharacterManager::renderCharacters();
			Interface::renderHUD();
			Window::main->drawFillRect(Window::main->viewportX() - 32 * x, Window::main->viewportY(), Window::main->viewportW() / 2, Window::main->viewportH(), Color::white);
			Window::main->drawFillRect(Window::main->viewportX() + Window::main->viewportW() / 2 + 32 * x, Window::main->viewportY(), Window::main->viewportW() / 2, Window::main->viewportH(), Color::white);
			Window::main->update();
		}
		
		m_inDoor = true;
	}
	
	if(!inZones(m_x, m_y, MapManager::changeMapTiles) && m_inDoor) {
		m_inDoor = false;
	}
}

