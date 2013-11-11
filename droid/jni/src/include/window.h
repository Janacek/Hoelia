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
			
		void updateViewportPosition(s16 x, s16 y);
		
		void centerViewportWithObject(s16 x, s16 y, u16 w, u16 h);
		
		void setRendererColor(Color color);
		
		void drawRect(s16 x, s16 y, u16 w, u16 h, Color c);
		
		void drawFillRect(s16 x, s16 y, u16 w, u16 h, Color c);
		
		SDL_Renderer *renderer() { return m_renderer; }
		
		s16 viewportX() const { return m_viewportX; }
		s16 viewportY() const { return m_viewportY; }
		
		u16 viewportW() const { return m_viewportW; }
		u16 viewportH() const { return m_viewportH; }
		
		// Game main window
		static Window *main;
		
	private:
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		
		// Window size
		u16 m_width;
		u16 m_height;
		
		s16 m_viewportX;
		s16 m_viewportY;
		
		u16 m_viewportW;
		u16 m_viewportH;
};

#endif // WINDOW_H
