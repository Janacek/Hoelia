/*---------------------------------------------------------------------------------
	
	Radonia
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
#include "keyboard.h"

const u8 *Keyboard::state = NULL;
u8 Keyboard::padState[5] = {0, 0, 0, 0, 0};
s32 Keyboard::padFinger[5] = {-1, -1, -1, -1, -1};

#ifndef __ANDROID__
	const u32 Keyboard::GameUp = SDL_SCANCODE_UP;
	const u32 Keyboard::GameDown = SDL_SCANCODE_DOWN;
	const u32 Keyboard::GameLeft = SDL_SCANCODE_LEFT;
	const u32 Keyboard::GameRight = SDL_SCANCODE_RIGHT;
	const u32 Keyboard::GameAttack = SDL_SCANCODE_S;
#else
	const u32 Keyboard::GameUp = PAD_UP;
	const u32 Keyboard::GameDown = PAD_DOWN;
	const u32 Keyboard::GameLeft = PAD_LEFT;
	const u32 Keyboard::GameRight = PAD_RIGHT;
	const u32 Keyboard::GameAttack = PAD_A;
#endif

const u8 *Keyboard::getState() {
	return SDL_GetKeyboardState(NULL);
}

bool Keyboard::isKeyPressed(u32 key) {
#ifndef __ANDROID__
	if(state[key]) return true;
	else		   return false;
#else
	if(padState[key]) return true;
	else			  return false;
#endif
}

void Keyboard::update() {
	state = getState();
}

void Keyboard::forceUpdate() {
	SDL_PumpEvents();
	update();
}

void Keyboard::resetPad(SDL_Event *e, bool released) {
	// Reset pad state
	if(padFinger[PAD_UP] == e->tfinger.fingerId || padFinger[PAD_UP] < 0) {
		padState[PAD_UP] = 0;
		padState[PAD_DOWN] = 0;
		padState[PAD_LEFT] = 0;
		padState[PAD_RIGHT] = 0;
	}
	if(padFinger[PAD_A] == e->tfinger.fingerId || padFinger[PAD_A] < 0) padState[PAD_A] = 0;
	
	// Reset finger state
	if(padFinger[PAD_UP] == e->tfinger.fingerId && released) padFinger[PAD_UP] = -1;
	if(padFinger[PAD_A]	== e->tfinger.fingerId && released) padFinger[PAD_A] = -1;
}

void Keyboard::updatePad(SDL_Event *e) {
/*	// Get finger position
	u16 fx = e->tfinger.x * Game::MainWindow->viewportW();
	u16 fy = e->tfinger.y * Game::MainWindow->viewportH();
	
	// Get pad position
	u16 px = Interface::pad->posRect()->x - Game::MainWindow->viewportX();
	u16 py = Interface::pad->posRect()->y - Game::MainWindow->viewportY();
	
	// Get 'A' button position
	u16 ax = Interface::buttonA->posRect()->x - Game::MainWindow->viewportX();
	u16 ay = Interface::buttonA->posRect()->y - Game::MainWindow->viewportY();
	
	resetPad(e);
*/	
	/* TEST PAD */
/*	// Up: (0;0;71;28)
	if(fx > px - 16 && fx < px + 71 + 16 && fy > py - 16 && fy < py + 28 - 8) {
		padState[PAD_UP] = 1;
		padFinger[PAD_UP] = e->tfinger.fingerId;
	}
	
	// Down: (0;44;71;71)
	if(fx > px - 16 && fx < px + 71 + 16 && fy > py + 44 + 8 && fy < py + 71 + 16) {
		padState[PAD_DOWN] = 1;
		padFinger[PAD_UP] = e->tfinger.fingerId;
	}
	
	// Left: (0;0;28;71)
	if(fx > px - 16 && fx < px + 28 - 8 && fy > py - 16 && fy < py + 71 + 16) {
		padState[PAD_LEFT] = 1;
		padFinger[PAD_UP] = e->tfinger.fingerId;
	}
	
	// Right: (44;0;71;71)
	if(fx > px + 44 + 8 && fx < px + 71 + 16 && fy > py - 16 && fy < py + 71 + 16) {
		padState[PAD_RIGHT] = 1;
		padFinger[PAD_UP] = e->tfinger.fingerId;
	}
	
	// Button A
	if(fx > ax && fx < ax + 32 && fy > ay && fy < ay + 32) {
		padState[PAD_A] = 1;
		padFinger[PAD_A] = e->tfinger.fingerId;
	}
*/}

