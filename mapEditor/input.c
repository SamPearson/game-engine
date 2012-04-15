// Part of the stonex map editor

#include <allegro.h>
#include "mapInfo.h"

int get_user_input();
int fill_button();
int toggle_grids();
int grid_preference = 2;




int get_user_input()
{
	extern int copy();
	extern int paste();
	extern int save_as_bitmap();
	extern int save_map();
	extern int load_map();
	extern int copy_paste(int mode);
	int x,y;
	if (mouse_b & 1) // if left mouse is clicked
	{
		//if clicking the tile buffer area
		if ((mouse_x > tilebuffer_location_x) && (mouse_y > tilebuffer_location_y) 
										&& mouse_x < tilebuffer_location_x + tilebuffer_width_in_tiles * tile_width && mouse_y < tilebuffer_location_y + tilebuffer_height_in_tiles * tile_width)
		{
			current_tile	=	((mouse_y - tilebuffer_location_y) / 32)*8 ;
			current_tile	+=	((mouse_x - tilebuffer_location_x) / 32);
		}

		//if clicking in the map area
		if ((mouse_x > mapbuffer_location_x) && (mouse_y > mapbuffer_location_y) 
										&& mouse_x < mapbuffer_width_in_tiles * tile_width + mapbuffer_location_x && mouse_y < mapbuffer_height_in_tiles * tile_width + mapbuffer_location_y)
		{
		x= ((mouse_x - mapbuffer_location_x) / 32);
		y= ((mouse_y - mapbuffer_location_y) /32);
		map_tile_db[x+map_position_x][y+map_position_y]=current_tile;
		}

		//if clicking the fill tool
		if (mouse_x > 5 && mouse_y >5 && mouse_x < 90 && mouse_y < 40)
			fill_button();
			copy();
		//if clicking the fill area button
		if (mouse_x > 5 && mouse_y >45 && mouse_x < 90 && mouse_y < 80)
			copy_paste(2);
		//if clicking the copy button
		if (mouse_x > 5 && mouse_y >85 && mouse_x < 90 && mouse_y < 120)
			copy_paste(1);

		//if clicking the repeat copy button
		if (mouse_x > 5 && mouse_y >125 && mouse_x < 90 && mouse_y < 160)
			copy_paste(2);

		//if clicking the mirror h copy button
		if (mouse_x > 5 && mouse_y >165 && mouse_x < 90 && mouse_y < 200)
			copy_paste(3);

		//if clicking the mirror v copy button
		if (mouse_x > 5 && mouse_y >205 && mouse_x < 90 && mouse_y < 240)
			copy_paste(4);

		//if clicking the  blank button
		if (mouse_x > 5 && mouse_y >245 && mouse_x < 90 && mouse_y < 280)
			save_as_bitmap();

		//if clicking the  blank button
		if (mouse_x > 5 && mouse_y >285 && mouse_x < 90 && mouse_y < 320)
			paste();


		//if clicking the toggle grids button
		if (mouse_x > 5 && mouse_y >325 && mouse_x < 90 && mouse_y < 360)
			toggle_grids();

		//if clicking the reload map button
		if (mouse_x > 5 && mouse_y >365 && mouse_x < 90 && mouse_y < 400)
			load_map();

		//if clicking the save map button
		if (mouse_x > 5 && mouse_y >405 && mouse_x < 90 && mouse_y < 440)
			save_map();

	}//endif left mouse is clicked.












	if (key[KEY_W])
	{
		map_position_y--;
		if (map_position_y<0)
		map_position_y=0;
		rest(10);
	}//endif w key
	if (key[KEY_A])
	{
		map_position_x--;
		if (map_position_x<0)
		map_position_x=0;
		rest(10);
	}//endif a key
	if (key[KEY_S])
	{
		map_position_y++;
		if (map_position_y>=MAP_HEIGHT_IN_TILES - 20)
		map_position_y=MAP_HEIGHT_IN_TILES - 20;
		rest(10);
	}//endif s key
	if (key[KEY_D])
	{
		map_position_x++;
		if (map_position_x>=MAP_WIDTH_IN_TILES - 20)
		map_position_x=MAP_WIDTH_IN_TILES - 20;
		rest(10);
	}//endif d key
	return 0;
}












