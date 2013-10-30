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
#ifndef MAP_H
#define MAP_H

typedef struct {
	Image *tiles;
	u16 *info; // Informations for collisions
	u16 tileWidth = 16;
	u16 tileHeight = 16;
} Tileset;

class Map {
	public:
		Map(const char *filename, Tileset *tileset, u16 width, u16 height, u16 mapX, u16 mapY, u16 zone = 0);
		~Map();
		
		void renderTile(u16 tileX, u16 tileY);
		void render();
		
		u16 getTile(u16 tileX, u16 tileY);
		
		u16 width() const { return m_width; }
		u16 height() const { return m_height; }
		
		// Number of maps initialized
		static u16 counter;
		
	private:
		u16 m_id;
		
		Tileset *m_tileset;
		
		u16 m_width;
		u16 m_height;
		
		u16 m_mapX;
		u16 m_mapY;
		
		u16 m_zone;
		
		u16 *m_data;
};

#endif // MAP_H
