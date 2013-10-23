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
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>

#include "SDL_headers.h"

#include "types.h"
#include "image.h"
#include "map.h"

u16 Map::counter = 0;

Map::Map(const char *filename, Tileset *tileset, u16 width, u16 height, u16 mapX, u16 mapY, u16 area) {
	m_id = counter;
	counter++;
	
	m_tileset = tileset;
	
	m_width = width;
	m_height = height;
	
	m_mapX = mapX;
	m_mapY = mapY;
	
	m_area = area;
	
	// Make a temporary variable to get map file data
	u16* data = (u16*)malloc(m_width * m_height * sizeof(u16));
	
	// Get filesize for SDL_RWread
	int filesize;
	struct stat file_status;
	if(stat(filename, &file_status) != 0) {
		filesize = sizeof(data) * m_width * m_height;
	} else {
		filesize = file_status.st_size;
	}
	
	// Load map from file
	SDL_RWops *f = SDL_RWFromFile(filename, "r");
	if(!f) {
		fprintf(stderr, "Unable to open file %s: %s\n", filename, SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_RWread(f, data, 2, filesize);
	SDL_RWclose(f);
	
	// Save data in current map
	m_data = data;
}

Map::~Map() {
	free(m_data);
}

void Map::renderTile(u16 tileX, u16 tileY) {
	// Get absolute coordinates
	u16 posX = (tileX + m_mapX * m_width) * m_tileset->tileWidth;
	u16 posY = (tileY + m_mapY * m_height) * m_tileset->tileHeight;
	
	// Get tile id
	u16 tileID = getTile(tileX, tileY);
	
	// Get tile position in the tileset
	u16 tilesetY = (tileID / (m_tileset->tiles->width() / m_tileset->tileHeight)) * m_tileset->tileHeight;
	u16 tilesetX = (tileID - (tilesetY / m_tileset->tileHeight) * (m_tileset->tiles->width() / m_tileset->tileHeight)) * m_tileset->tileWidth;
	
	// Set position and clip tile to display
	m_tileset->tiles->setPosRect(posX, posY, m_tileset->tileWidth, m_tileset->tileHeight);
	m_tileset->tiles->setClipRect(tilesetX, tilesetY, m_tileset->tileWidth, m_tileset->tileHeight);
	
	// Render the tile
	m_tileset->tiles->render();
}

void Map::render() {
	for(u16 y = 0 ; y < m_height ; y++) {
		for(u16 x = 0 ; x < m_width ; x++) {
			renderTile(x, y);
		}
	}
}

u16 Map::getTile(u16 tileX, u16 tileY) {
	if(tileX + tileY * m_width < m_width * m_height) {
		return m_data[tileX + tileY * m_width];
	} else {
		return 0; // The tile is out of range
	}
}

