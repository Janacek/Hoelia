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
#ifndef FONT_H
#define FONT_H

typedef enum {
	FONT_SMALL	= 12,
	FONT_MEDIUM = 20,
	FONT_LARGE	= 30
} FontSize;

class Font {
	public:
		Font(const char *filename);
		~Font();
		
		void print(const char *str, u16 x, u16 y, FontSize size, Color color = Color::black);
		
		void printTextBox(const char *str, u16 x, u16 y, u16 width, u16 height, FontSize size, Color color = Color::black);
		
	private:
		TTF_Font *m_fontSmall;
		TTF_Font *m_fontMedium;
		TTF_Font *m_fontLarge;
};

#endif // FONT_H
