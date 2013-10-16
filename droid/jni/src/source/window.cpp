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

Window *Window::main = NULL;

Window::Window(const char *caption, u16 width, u16 height) {
	m_width = width;
	m_height = height;
	
	// Initialize window
	m_window = SDL_CreateWindow(caption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);
	if(!m_window) {
		fprintf(stderr, "Error while initializing window: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	// Initialize renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if(!m_renderer) {
		fprintf(stderr, "Renderer couldn't be created: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

Window::~Window() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void Window::clear() {
	SDL_RenderClear(m_renderer);
}

void Window::update() {
	SDL_RenderPresent(m_renderer);
}

