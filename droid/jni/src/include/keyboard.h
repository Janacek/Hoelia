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
#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef enum {
	PAD_UP,
	PAD_DOWN,
	PAD_LEFT,
	PAD_RIGHT,
	PAD_A
} PadState;

namespace Keyboard {
	const u8 *getState();
	
	bool isKeyPressed(u32 key);
	
	extern const u8 *state;
	
	extern u8 padState[5];
	extern s32 padFinger[5];
	
	void update();
	
	void forceUpdate();
	
	void resetPad(SDL_Event *e, bool released = false);
	
	void updatePad(SDL_Event *e);
	
	// Game keys
	extern const u32 GameUp;
	extern const u32 GameDown;
	extern const u32 GameLeft;
	extern const u32 GameRight;
	extern const u32 GameAttack;
};

#endif // KEYBOARD_H
