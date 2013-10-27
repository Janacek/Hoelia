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
#include "image.h"
#include "map.h"
#include "mapManager.h"

Tileset **MapManager::tilesets = NULL;
Map ***MapManager::zones = NULL;

u16 MapManager::zonesSizes[NB_ZONES] = {
	OVERWORLD_SIZE * OVERWORLD_SIZE,
	INDOOR_SIZE,
	CAVE_1_SIZE * CAVE_1_SIZE
};

/*	Tiles informations:
		0: Passable
		1: Non passable
		2: Slows and can be cutted
		3: Non passable but can be cutted and can be lifted
		4: Non passable but can be burned
		6: Fireplace
		7: Hole
		8: Empty chest
		9: Closed chest
		10: Placard
		11: Doors
		12: Rock, can be lifted
		13: Soft soil
		14: Stairs
		15: Stairs to underground
		16: Cane of Somaria's rock
		17: Hook's rock
		18: Block of sand 
		19: Low water
*/

u16 plainInfo[256] = {
	0,0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,0,0,0,0,4,0,1,1,
	1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,11,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	1,1,1,1,1,1,1,1,1,1,11,6,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,19,19,0,0,0,0,0,0,0,0,7,1,
	8,9,10,7,12,13,13,1,14,15,1,16,17,0,18,1
};

u16 indoorInfo[256] = {
	0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,
	1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,
	1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
	1,1,1,1,1,1,1,1,1,1,0,11,11,1,1,0,
	1,1,1,1,1,1,1,1,1,1,0,11,11,0,0,0,
	1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,
	1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,1,
	1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	19,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	8,9,10,7,0,0,1,12,15,15,11,11,0,0,0,0
};

u16 undergroundInfo[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,15,15,11,11,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,11,0,11,11,0,0,0,0,0,0,0,0,0,0,
	8,9,10,0,0,0,0,0,0,19,0,0,0,0,0,0
};

void MapManager::initTilesets() {
	tilesets = new Tileset*[NB_TILESETS];
	
	/* PLAIN */
	tilesets[0] = new Tileset;
	tilesets[0]->tiles = new Image("graphics/tilesets/plain.png");
	tilesets[0]->info = plainInfo;
	
	/* INDOOR */
	tilesets[1] = new Tileset;
	tilesets[1]->tiles = new Image("graphics/tilesets/indoor.png");
	tilesets[1]->info = indoorInfo;
	
	/* UNDERGROUND */
	tilesets[2] = new Tileset;
	tilesets[2]->tiles = new Image("graphics/tilesets/underground.png");
	tilesets[2]->info = undergroundInfo;
}

void MapManager::initMaps() {
	zones = new Map**[NB_ZONES];
	
	zones[0] = new Map*[zonesSizes[0]];
	zones[1] = new Map*[zonesSizes[1]];
	zones[2] = new Map*[zonesSizes[2]];
	
	/* OVERWORLD */
	zones[0][MAP_POS(0, 0, 0)] = new Map("maps/a1.map", tilesets[0], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 0, 0, 0);
	zones[0][MAP_POS(1, 0, 0)] = new Map("maps/b1.map", tilesets[0], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 1, 0, 0);
	zones[0][MAP_POS(0, 1, 0)] = new Map("maps/a2.map", tilesets[0], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 0, 1, 0);
	zones[0][MAP_POS(1, 1, 0)] = new Map("maps/b2.map", tilesets[0], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 1, 1, 0);
	
	/* INDOOR */
	zones[1][0] = new Map("maps/in1.map", tilesets[1], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 0, 0, 1);
	zones[1][1] = new Map("maps/in2.map", tilesets[1], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 0, 0, 1);
	zones[1][2] = new Map("maps/in3.map", tilesets[1], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 0, 0, 1);
	
	/* CAVE 1 */
	zones[2][MAP_POS(0, 0, 2)] = new Map("maps/ca1a1.map", tilesets[2], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 0, 0, 2);
	zones[2][MAP_POS(1, 0, 2)] = NULL;
	zones[2][MAP_POS(0, 1, 2)] = new Map("maps/ca1a2.map", tilesets[2], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 0, 1, 2);
	zones[2][MAP_POS(1, 1, 2)] = new Map("maps/ca1b2.map", tilesets[2], DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, 1, 1, 2);
}

void MapManager::initAll() {
	initTilesets();
	initMaps();
}

void MapManager::free() {
	for(u16 i = 0 ; i < NB_ZONES ; i++) {
		delete[] zones[i];
	}
	delete[] tilesets;
}
