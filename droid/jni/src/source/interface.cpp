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
#include <vector>

#include "SDL_headers.h"

#include "types.h"
#include "config.h"
#include "color.h"
#include "window.h"
#include "timer.h"
#include "image.h"
#include "animation.h"
#include "sprite.h"
#include "font.h"
#include "interface.h"
#include "game.h"

Font *Interface::defaultFont = NULL;
Image *Interface::pad = NULL;
Image *Interface::buttonA = NULL;

void Interface::init() {
	defaultFont = new Font("fonts/vani.ttf");
	
	pad = new Image("graphics/interface/pad.png");
	pad->setAlpha(175);
	
	buttonA = new Image("graphics/interface/a.png");
	buttonA->setAlpha(175);
}

void Interface::quit() {
	delete defaultFont;
	delete pad;
	delete buttonA;
}

void Interface::renderPad() {
	pad->render(Window::main->viewportX() + 16, Window::main->viewportY() + Window::main->viewportH() - pad->height() - 16, pad->width(), pad->height());
	
	buttonA->render(Window::main->viewportX() + Window::main->viewportW() - buttonA->width() - 16, Window::main->viewportY() + Window::main->viewportH() - buttonA->height() - 16, buttonA->width(), buttonA->height());
}

void Interface::renderHUD() {
#ifdef PAD
	renderPad();
#endif
}

