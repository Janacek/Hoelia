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
#include "image.h"
#include "font.h"

Font::Font(const char *filename) {
	m_fontSmall  = TTF_OpenFont(filename, FONT_SMALL);
	m_fontMedium = TTF_OpenFont(filename, FONT_MEDIUM);
	m_fontLarge  = TTF_OpenFont(filename, FONT_LARGE);
}

Font::~Font() {
	TTF_CloseFont(m_fontSmall);
	TTF_CloseFont(m_fontMedium);
	TTF_CloseFont(m_fontLarge);
}

void Font::print(const char *str, u16 x, u16 y, FontSize size, Color color) {
	TTF_Font *font = NULL;
	
	switch(size) {
		case FONT_SMALL:  font = m_fontSmall;  break;
		case FONT_MEDIUM: font = m_fontMedium; break;
		case FONT_LARGE:  font = m_fontLarge;  break;
	}
	
	SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, str, SDL_Color{color.r, color.g, color.b});
	Image textToDisplay(textSurface);
	
	textToDisplay.render(x, y, textToDisplay.width(), textToDisplay.height());
}

void Font::printTextBox(const char *str, u16 x, u16 y, u16 width, u16 height, FontSize size, Color color) {
}

