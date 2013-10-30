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

Color Color::white(255, 255, 255);
Color Color::black(0, 0, 0);
Color Color::life(0, 125, 0);

Color::Color(u8 _r, u8 _g, u8 _b, u8 _a) {
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

Color::~Color() {
}

