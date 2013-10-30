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
#include "timer.h"
#include "animation.h"
#include "animationManager.h"

u16 playerAnimations[8][4] = {
	{4,0},
	{5,1},
	{6,2},
	{7,3},
	{8,12,12,12},
	{9,13,13,13},
	{10,14,14,14},
	{11,15,15,15}
};

u16 base16x16CharacterAnimations[4][4] = {
	{4,0},
	{5,1},
	{6,2},
	{7,3}
};

