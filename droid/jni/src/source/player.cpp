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
#include "keyboard.h"
#include "image.h"
#include "animation.h"
#include "animationManager.h"
#include "sprite.h"
#include "character.h"
#include "player.h"

Player::Player(u16 x, u16 y, CharacterDirection direction, u16 mapID) : Character("graphics/characters/link.png", CHARACTER_PLAYER, x, y, direction, mapID) {
	addAnimation(2, playerAnimations[0], 125); // Down
	addAnimation(2, playerAnimations[1], 125); // Right
	addAnimation(2, playerAnimations[2], 125); // Left
	addAnimation(2, playerAnimations[3], 125); // Up
	addAnimation(4, playerAnimations[4], 100); // Attack down
	addAnimation(4, playerAnimations[5], 100); // Attack right
	addAnimation(4, playerAnimations[6], 100); // Attack left
	addAnimation(4, playerAnimations[7], 100); // Attack up
}

Player::~Player() {
}

void Player::move() {
	if(m_canMove) {
		m_moving = false;
		
		if(Keyboard::isKeyPressed(Keyboard::GameUp)) {
			if(!Keyboard::isKeyPressed(Keyboard::GameDown)) m_vy = -1;
			m_moving = true;
			
			if(!Keyboard::isKeyPressed(Keyboard::GameLeft) && !Keyboard::isKeyPressed(Keyboard::GameRight) && !Keyboard::isKeyPressed(Keyboard::GameDown)) {
				if(m_canTurn) m_direction = DIR_UP;
			}
		}
		
		if(Keyboard::isKeyPressed(Keyboard::GameDown)) {
			if(!Keyboard::isKeyPressed(Keyboard::GameUp)) m_vy = 1;
			m_moving = true;
			
			if(!Keyboard::isKeyPressed(Keyboard::GameLeft) && !Keyboard::isKeyPressed(Keyboard::GameRight) && !Keyboard::isKeyPressed(Keyboard::GameUp)) {
				if(m_canTurn) m_direction = DIR_DOWN;
			}
		}
		
		if(Keyboard::isKeyPressed(Keyboard::GameLeft)) {
			if(!Keyboard::isKeyPressed(Keyboard::GameRight)) m_vx = -1;
			m_moving = true;
			
			if(!Keyboard::isKeyPressed(Keyboard::GameUp) && !Keyboard::isKeyPressed(Keyboard::GameRight) && !Keyboard::isKeyPressed(Keyboard::GameDown)) {
				if(m_canTurn) m_direction = DIR_LEFT;
			}
		}
		
		if(Keyboard::isKeyPressed(Keyboard::GameRight)) {
			if(!Keyboard::isKeyPressed(Keyboard::GameLeft)) m_vx = 1;
			m_moving = true;
			
			if(!Keyboard::isKeyPressed(Keyboard::GameLeft) && !Keyboard::isKeyPressed(Keyboard::GameUp) && !Keyboard::isKeyPressed(Keyboard::GameDown)) {
				if(m_canTurn) m_direction = DIR_RIGHT;
			}
		}
	}
	
	m_x += m_vx;
	m_y += m_vy;
	
	m_vx = 0;
	m_vy = 0;
}

