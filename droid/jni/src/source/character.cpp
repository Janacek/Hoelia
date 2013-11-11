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
#include "timer.h"
#include "image.h"
#include "animation.h"
#include "sprite.h"
#include "character.h"

u16 Character::counter = 0;

Character::Character(const char *filename, CharacterType type, u16 x, u16 y, CharacterDirection direction, u16 mapID, u16 frameWidth, u16 frameHeight) : Sprite(filename, frameWidth, frameHeight) {
	m_id = counter;
	counter++;
	
	m_type = type;
	
	m_x = x;
	m_y = y;
	
	m_vx = 0;
	m_vy = 0;
	
	m_direction = direction;
	
	m_mapID = mapID;
	
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

