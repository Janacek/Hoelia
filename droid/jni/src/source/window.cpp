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
#include "config.h"
#include "window.h"
#include "image.h"
#include "map.h"
#include "mapManager.h"

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
	
	m_viewportX = 0;
	m_viewportY = 0;
	
#ifndef VIEWPORT
	// Initialize viewport size
	m_viewportW = m_width;
	m_viewportH = m_height;
#else
	// Initialize viewport size
	m_viewportW = m_width / 2;
	m_viewportH = m_height / 2;
	
	// Set viewport
	SDL_RenderSetLogicalSize(m_renderer, m_viewportW, m_viewportH);
#endif
}

Window::~Window() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void Window::clear() {
	SDL_RenderClear(m_renderer);
}

void Window::update() {
/*#ifdef VIEWPORT
	centerViewportWithObject(CharacterManager::player()->x(),
							 CharacterManager::player()->y(),
							 CharacterManager::player()->frameWidth(),
							 CharacterManager::player()->frameHeight());
#endif*/
	
	SDL_RenderPresent(m_renderer);
}

void Window::updateViewportPosition(s16 x, s16 y) {
	// Check if the viewport is in the map
	if(x < 0) x = 0;
	if(x + m_viewportW >= MapManager::currentMap->width() * 16) x = MapManager::currentMap->width() * 16 - m_viewportW - 1;
	if(y < 0) y = 0;
	if(y + m_viewportH >= MapManager::currentMap->height() * 16) y = MapManager::currentMap->height() * 16 - m_viewportH - 1;
	
	// Update viewport position
	m_viewportX = x;
	m_viewportY = y;
	
	// Set viewport
	SDL_Rect viewportRect = {-x, y - m_height / 2, m_width, m_height};
	SDL_RenderSetViewport(m_renderer, &viewportRect);
}

void Window::centerViewportWithObject(s16 x, s16 y, u16 w, u16 h) {
	updateViewportPosition(x - (m_viewportW - w) / 2, y - (m_viewportH - h) / 2);
}

