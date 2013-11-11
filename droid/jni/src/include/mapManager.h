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

#define MAP_POS(x, y, zone) (u16)((x) + (y) * sqrt((double)MapManager::zonesSizes[zone]))

namespace MapManager {
	void init();
	void free();
	
	void initTilesets();
	void initMaps();
	
	void refreshMaps(Map **maps, s16 moveX, s16 moveY);
	
	extern Tileset **tilesets;
	extern Map ***zones;
	
	extern u16 zonesSizes[NB_ZONES];
	
	extern u16 nonPassableTiles[13];
	extern u16 changeMapTiles[3];
	
	extern Map *currentMap;
}

// Get map id from zone
u16 _mid(u16 zone, u16 id);

bool inTable(u16 tiles[], u16 id);
bool inTiles(s16 tileX, s16 tileY, u16 tiles[]);
bool inZone(s16 x, s16 y, u16 tile);
bool inZones(s16 x, s16 y, u16 tiles[]);

#endif // MAPMANAGER_H
