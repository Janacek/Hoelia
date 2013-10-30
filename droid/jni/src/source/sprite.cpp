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
#include "timer.h"
#include "image.h"
#include "animation.h"
#include "sprite.h"

Sprite::Sprite(const char *filename, u16 frameWidth, u16 frameHeight) : Image(filename) {
	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
}

Sprite::~Sprite() {
}

void Sprite::drawFrame(s16 x, s16 y, u16 frame) {
	u16 frameY = (frame / (m_width / m_frameWidth)) * m_frameHeight;
	u16 frameX = (frame - (frameY / m_frameHeight) * (m_width / m_frameWidth)) * m_frameWidth;
	
	render(x, y, m_frameWidth, m_frameHeight, frameX, frameY, m_frameWidth, m_frameHeight);
}

void Sprite::addAnimation(u16 size, u16 *tabAnim, u16 delay) {
	Animation* tmp = new Animation(size, tabAnim, delay);
	m_animations.push_back(tmp);
}

void Sprite::resetAnimation(u16 anim) {
	m_animations[anim]->timer.reset();
}

void Sprite::startAnimation(u16 anim) {
	m_animations[anim]->timer.start();
}

void Sprite::stopAnimation(u16 anim) {
	m_animations[anim]->timer.stop();
}

bool Sprite::animationAtEnd(u16 anim) {
	return m_animations[anim]->timer.time() / m_animations[anim]->delay >= m_animations[anim]->size;
}

bool Sprite::animationAtFrame(u16 anim, u16 frame) {
	return (u16)(m_animations[anim]->timer.time() / m_animations[anim]->delay) == frame;
}

void Sprite::playAnimation(s16 x, s16 y, u16 anim) {
	if(!m_animations[anim]->isPlaying) {
		resetAnimation(anim);
		startAnimation(anim);
		m_animations[anim]->isPlaying = true;
	}
	
	if(animationAtEnd(anim)) {
		resetAnimation(anim);
		startAnimation(anim);
	}
	
	u16 animToDraw = m_animations[anim]->tabAnim[(u16)(m_animations[anim]->timer.time() / m_animations[anim]->delay)];
	drawFrame(x, y, animToDraw);
}

