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
#ifndef CHARACTER_H
#define CHARACTER_H

typedef enum {
	CHARACTER_PLAYER,
	CHARACTER_NPC,
	CHARACTER_MONSTER
} CharacterType;

typedef enum {
	DIR_DOWN,
	DIR_RIGHT,
	DIR_LEFT,
	DIR_UP
} CharacterDirection;

class Character : public Sprite {
	public:
		Character(const char *filename, CharacterType type, u16 x, u16 y, CharacterDirection direction, u16 mapID, u16 frameWidth = 16, u16 frameHeight = 16);
		virtual ~Character();
		
		virtual void move() = 0;
		
		virtual void action() = 0;
		
		void render();
		
		// Collisions functions
		//bool inNonPassableTile();
		void mapCollisions();
		void testCollisions();
		void doorCollisions();
		
		u16 x() const { return m_x; }
		u16 y() const { return m_y; }
		
		u16 mapID() const { return m_mapID; }
		
		bool isPlayer()  { return m_type == CHARACTER_PLAYER;	}
		bool isNPC()	 { return m_type == CHARACTER_NPC;		}
		bool isMonster() { return m_type == CHARACTER_MONSTER;  }
		
		static u16 counter;
		
	protected:
		/* Informations */
			u16 m_id;
			
			CharacterType m_type;
			
		/* Position */
			u16 m_x;
			u16 m_y;
			
			s8 m_vx;
			s8 m_vy;
			
			CharacterDirection m_direction;
			
			u16 m_mapID;
			
		/* Collisions */
			bool m_inCollision;
			bool m_inDoor;
			
			s16 m_hitboxX;
			s16 m_hitboxY;
			u16 m_hitboxW;
			u16 m_hitboxH;
			
		/* Movement */
			bool m_canMove;
			bool m_canTurn;
			bool m_moving;
};

#endif // CHARACTER_H
