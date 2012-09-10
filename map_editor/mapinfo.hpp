// Part of the stonex map editor

#ifndef MAPINFO_HPP_
#define MAPINFO_HPP_

#define MAP_WIDTH_IN_TILES 45
#define MAP_HEIGHT_IN_TILES 23

extern int tile_width;
extern int map_tile_db[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES];
extern int mapbuffer_width_in_tiles;
extern int mapbuffer_height_in_tiles;
extern int mapbuffer_location_x;
extern int mapbuffer_location_y;
extern int tilebuffer_width_in_tiles;
extern int tilebuffer_height_in_tiles;
extern int tilebuffer_location_x;
extern int tilebuffer_location_y;
extern int map_position_x;
extern int map_position_y;
extern BITMAP *tile[144]; // tile[0] is a void tile, used only to denote unused space on the map.
extern int current_tile;
extern BITMAP *screen_buffer;

#endif /*MAPINFO_HPP_*/
