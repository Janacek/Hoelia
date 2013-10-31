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
#ifndef IMAGE_H
#define IMAGE_H

class Image {
	public:
		Image(const char *filename);
		Image(SDL_Surface *surface);
		~Image();
		
		void render();
		void render(s16 x, s16 y, u16 w = 0, u16 h = 0, s16 clipX = -1, s16 clipY = -1, u16 clipW = 0, u16 clipH = 0);
		
		void setPosRect(s16 x, s16 y, u16 w, u16 h);
		
		void setClipRect(s16 x, s16 y, u16 w, u16 h);
		
		void setAlpha(u8 alpha) { SDL_SetTextureAlphaMod(m_texture, alpha); }
		
		SDL_Rect posRect() const { return m_posRect; }
		
		u16 width() const { return m_width; }
		u16 height() const { return m_height; }
		
	protected:
		u16 m_width;
		u16 m_height;
		
		SDL_Surface *m_surface;
		
		SDL_Texture *m_texture;
		
		SDL_Rect m_clipRect;
		SDL_Rect m_posRect;
};

#endif // IMAGE_H
