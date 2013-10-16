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
#ifndef WINDOW_H
#define WINDOW_H

class Window {
	public:
		Window(const char *caption, u16 width, u16 height);
		~Window();
		
		// Clear render
		void clear();
		
		// Update render
		void update();
		
		SDL_Renderer *renderer() { return m_renderer; }
		
		// Game main window
		static Window *main;
		
	private:
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		
		// Window size
		u16 m_width;
		u16 m_height;
};

#endif // WINDOW_H
