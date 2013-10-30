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
#ifndef COLOR_H
#define COLOR_H

class Color {
	public:
		Color(u8 _r, u8 _g, u8 _b, u8 _a = 255);
		~Color();
		
		void invert() { r=255-r; g=255-g; b=255-b; }
		
		u8 r;
		u8 g;
		u8 b;
		u8 a;
		
		static Color white;
		static Color black;
		static Color life;
};

#endif // COLOR_H
