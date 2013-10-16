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
		~Image();
		
		void render();
		
		// Set position
		void setPosRect(s16 x, s16 y, u16 w, u16 h);
		
		// Set clip rect
		void setClipRect(s16 x, s16 y, u16 w, u16 h);
		
	private:
		// Image size
		u16 m_width;
		u16 m_height;
		
		// Surface object
		SDL_Surface *m_surface;
		
		// Texture object
		SDL_Texture *m_texture;
		
		// SDL rects
		SDL_Rect m_clipRect;
		SDL_Rect m_posRect;
};

#endif // IMAGE_H
