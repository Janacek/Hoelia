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
#include "window.h"
#include "image.h"

Image::Image(const char *filename) {
	SDL_RWops *image = SDL_RWFromFile(filename, "rb");
	m_surface = IMG_Load_RW(image, 1);
	
	if(!m_surface) {
		fprintf(stderr, "Failed to load image \"%s\": %s\n", filename, IMG_GetError());
		exit(EXIT_FAILURE);
	}
	
	m_width = m_surface->w;
	m_height = m_surface->h;
	
	m_texture = SDL_CreateTextureFromSurface(Window::main->renderer(), m_surface);
	if(!m_texture) {
		fprintf(stderr, "Failed to create texture from image: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	m_clipRect.x = 0;
	m_clipRect.y = 0;
	m_clipRect.w = m_width;
	m_clipRect.h = m_height;
	
	m_posRect.x = 0;
	m_posRect.y = 0;
	m_posRect.w = m_width;
	m_posRect.h = m_height;
}

Image::Image(SDL_Surface *surface) {
	m_surface = surface;
	
	m_width = m_surface->w;
	m_height = m_surface->h;
	
	m_texture = SDL_CreateTextureFromSurface(Window::main->renderer(), m_surface);
	
	m_clipRect.x = 0;
	m_clipRect.y = 0;
	m_clipRect.w = m_width;
	m_clipRect.h = m_height;
	
	m_posRect.x = 0;
	m_posRect.y = 0;
	m_posRect.w = m_width;
	m_posRect.h = m_height;
}

Image::~Image() {
	SDL_FreeSurface(m_surface);
	SDL_DestroyTexture(m_texture);
}

void Image::render() {
	SDL_RenderCopy(Window::main->renderer(), m_texture, &m_clipRect, &m_posRect);
}

void Image::render(s16 x, s16 y, u16 w, u16 h, s16 clipX, s16 clipY, u16 clipW, u16 clipH) {
	m_posRect.x = x;
	m_posRect.y = y;
	if(w != 0) m_posRect.w = w;
	if(h != 0) m_posRect.h = h;
	
	if(clipX != -1) m_clipRect.x = clipX;
	if(clipY != -1) m_clipRect.y = clipY;
	if(clipW != 0) m_clipRect.w = clipW;
	if(clipH != 0) m_clipRect.h = clipH;
	
	render();
}

void Image::setPosRect(s16 x, s16 y, u16 w, u16 h) {
	m_posRect.x = x;
	m_posRect.y = y;
	m_posRect.w = w;
	m_posRect.h = h;
}

void Image::setClipRect(s16 x, s16 y, u16 w, u16 h) {
	m_clipRect.x = x;
	m_clipRect.y = y;
	m_clipRect.w = w;
	m_clipRect.h = h;
}

