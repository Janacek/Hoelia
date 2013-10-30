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
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#define NB_TILESETS 3
#define NB_ZONES 3

#define DEFAULT_MAP_WIDTH 40
#define DEFAULT_MAP_HEIGHT 30

#define OVERWORLD_SIZE 2
#define INDOOR_SIZE 3
#define CAVE_1_SIZE 2

#define MAP_POS(x, y, zone) (u16)((x) + (y) * sqrt((double)MapManager::zonesSizes[zone]))

namespace MapManager {
	void initAll();
	void free();
	
	void initTilesets();
	void initMaps();
	
	extern Tileset **tilesets;
	extern Map ***zones;
	
	extern u16 zonesSizes[NB_ZONES];
	
	extern Map *currentMap;
}

#endif // MAPMANAGER_H
