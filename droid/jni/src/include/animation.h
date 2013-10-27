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
#ifndef ANIMATION_H
#define ANIMATION_H

struct Animation {
	Animation(u16 _size, u16 *_tabAnim, u16 _delay, bool _isPlaying = false) :
		size(_size), tabAnim(_tabAnim), delay(_delay), isPlaying(_isPlaying) {}
	
	u16 size;
	u16 *tabAnim;	// Animation table
	u16 delay;		// Delay between animations
	Timer timer;
	bool isPlaying;
};

typedef Animation Animation;

#endif // ANIMATION_H
