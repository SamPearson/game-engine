// Part of the stonex map editor

#include <allegro.h>
#include "mapinfo.hpp"
#include "tools.hpp"

int lock_mouse(int mousewall_left, int mousewall_right, int mousewall_top, int mousewall_bottom);

int copy();
int paste();


int fill_button()
{
	int x,y;
	for (y=0; y<mapbuffer_height_in_tiles ; y++)
	{ 	for (x=0; x<mapbuffer_width_in_tiles ; x++)
		{
			map_tile_db[x+map_position_x][y+map_position_y]=current_tile;
		}

	}
	return 0;
}


int toggle_grids()
{
	extern int draw_grid_on_map;
	extern int draw_grid_on_tiles;
	extern int grid_preference;
	grid_preference++;

	if (grid_preference > 3)
		grid_preference = 0;

	if (grid_preference == 0)
		{
			draw_grid_on_map = 0;
			draw_grid_on_tiles = 0;
		}
	if (grid_preference == 1)
		draw_grid_on_map = 1, draw_grid_on_tiles = 0;

	if (grid_preference == 2)
		draw_grid_on_map = 1, draw_grid_on_tiles = 1;

	if (grid_preference == 3)
		draw_grid_on_map = 0, draw_grid_on_tiles = 1;

	rest(300);
}
















int copy_paste( int mode)
{
	//values of mode
	//1 - regular paste
	//2 - fill area
	//3 - paste a horizontally inverted copy
	//4 - paste a vertically inverted copy

	extern int gfx_engine();
	int draw_grid(int lowest_x, int lowest_y, int highest_x, int highest_y, int tile_size, BITMAP *bitmap, int color);
	extern BITMAP *map_buffer;
	int gridright, gridleft, gridtop, gridbottom;
	int copy_x= -1, copy_y= -1, copy2_x= -1, copy2_y= -1;
	int diff_x, diff_y;
	int paste_x=-1, paste_y=-1;

	extern int draw_grid_on_map;
	int grid_pref = draw_grid_on_map;
	draw_grid_on_map = 0;				// just some stuff to define for the duration of this function
	int cancel_copy = 0;				//^^	vv
	set_mouse_range(mapbuffer_location_x, mapbuffer_location_y, mapbuffer_location_x + mapbuffer_width_in_tiles * tile_width, mapbuffer_location_y + mapbuffer_height_in_tiles * tile_width );

	int paste_buffer[20][20];
	int pastebuffer_width;
	int pastebuffer_height;
	int x,y;
	for (x=0; x <20; x++)
	{
		for (y=0; y <20; y++)
		{
			paste_buffer[x][y] = -1;
		}
	}

	//click on a copy start position
	rest(300);//to avoid getting previous input bleeing into this
	while (( copy_x < 0 || copy_y < 0 ) && cancel_copy == 0)
	{	
		if (mouse_b & 2)
			cancel_copy = 1;

		if (mouse_b & 1)
		{
			copy_x = (mouse_x - mapbuffer_location_x) / tile_width;
			copy_y = (mouse_y - mapbuffer_location_y) / tile_width;
			rest(300);
		}
		gfx_engine();
	}

	//click on a copy end position
	while (( copy2_x < 0 || copy2_y < 0 ) && cancel_copy == 0)
	{		
		if (mouse_b & 2)
			cancel_copy = 1;

		if (mouse_b & 1)
		{
			copy2_x = (mouse_x - mapbuffer_location_x) / tile_width;
			copy2_y = (mouse_y - mapbuffer_location_y) / tile_width;
			rest(300);
		}

		if ((mouse_x - mapbuffer_location_x) / tile_width > copy_x) 
		{
			gridright = (mouse_x - mapbuffer_location_x) / tile_width + 1;
			gridleft = copy_x;
		}
		else
		{
			gridright= copy_x + 1;
			gridleft = (mouse_x - mapbuffer_location_x) / tile_width;
		}
		if ((mouse_y - mapbuffer_location_y) / tile_width > copy_y) 
		{
			gridbottom = (mouse_y - mapbuffer_location_y) / tile_width + 1;
			gridtop = copy_y;
		}
		else
		{
			gridbottom= copy_y + 1;
			gridtop = ((mouse_y - mapbuffer_location_y) / tile_width);
		}


		gridright *=tile_width, gridleft *=tile_width, gridtop *=tile_width, gridbottom *=tile_width;
		draw_grid(gridleft, gridtop, gridright, gridbottom, tile_width, map_buffer, makecol(255,255,255));
		gfx_engine();
	}
	

	// prepare to paste
	diff_x = abs(copy_x - copy2_x);
	diff_y = abs(copy_y - copy2_y);
	//click on a paste position
	while (( paste_x < 0 || paste_y < 0 ) && cancel_copy == 0)
	{		
		if (mouse_b & 2)
			cancel_copy = 1;

		//draw the grid showing where stuff will be pasted
		gridleft		= (mouse_x - mapbuffer_location_x) / tile_width * tile_width; //dividing and multiplying by the same number to round to the nearest tile
		gridtop		= (mouse_y - mapbuffer_location_y) / tile_width * tile_width; //dividing and multiplying by the same number to round to the nearest tile
		gridright		= (((mouse_x - mapbuffer_location_x + diff_x * tile_width) / tile_width) + 1) * tile_width; //dividing and multiplying by the same number to round to the nearest tile
		gridbottom	= (((mouse_y - mapbuffer_location_y + diff_y * tile_width) / tile_width) + 1) * tile_width; //dividing and multiplying by the same number to round to the nearest tile
		draw_grid( gridleft, gridtop, gridright, gridbottom, tile_width, map_buffer, makecol(255,255,255));

		if (mouse_b & 1)
		{
			paste_x = (mouse_x - mapbuffer_location_x) / tile_width;
			paste_y = (mouse_y - mapbuffer_location_y) / tile_width;
			rest(300);
		}
		gfx_engine();
	}

	//paste, then we're done.
	if (mode == 1) //regular paste
	{
		if (cancel_copy == 0)
		{
			for (x=0; x <= diff_x; x++)
			{
				for (y=0; y <= diff_y; y++)
				{
					paste_buffer[x][y] = map_tile_db[copy_x + map_position_x + x][copy_y + map_position_y + y];
				}
			}
			for (y=0; y <= diff_y; y++)
			{
				for (x=0; x <=diff_x; x++)
				{
					map_tile_db[paste_x+map_position_x + x][paste_y + map_position_y + y] = paste_buffer[x][y];
				}
			}	
		}
	}

	if (mode == 2) //fill area
	{
		if (cancel_copy == 0)
		{

			for (y=0; y <= diff_y; y++)
			{
				for (x=0; x <=diff_x; x++)
				{
					map_tile_db[paste_x+map_position_x + x][paste_y + map_position_y + y] = current_tile;
				}
			}	
		}
	}

	if (mode == 3) //paste a horizontal mirror of the buffer.
	{
		if (cancel_copy == 0)
		{
			for (y=0; y <= diff_y; y++)
			{
				for (x=diff_x; x >= 0; x--)
				{
					paste_buffer[diff_x - x][y] = map_tile_db[copy_x + map_position_x + x][copy_y + map_position_y + y];
				}
			}
			for (y=0; y <= diff_y; y++)
			{
				for (x=0; x <=diff_x; x++)
				{
					map_tile_db[paste_x+map_position_x + x][paste_y + map_position_y + y] = paste_buffer[x][y];
				}
			}	
		}
	}

	if (mode == 4) //paste a vertical mirror of the buffer.
	{
		if (cancel_copy == 0)
		{
			for (y=diff_y; y >= 0; y--)
			{
				for (x=0; x <= diff_x; x++)
				{
					paste_buffer[x][diff_y - y] = map_tile_db[copy_x + map_position_x + x][copy_y + map_position_y + y];
				}
			}
			for (y=0; y <= diff_y; y++)
			{
				for (x=0; x <=diff_x; x++)
				{
					map_tile_db[paste_x+map_position_x + x][paste_y + map_position_y + y] = paste_buffer[x][y];
				}
			}	
		}
	}

	//redefining some stuff I set only for the duration of this function
	set_mouse_range(0,0,1024,768);	//
	draw_grid_on_map = grid_pref;	//
}


int copy()
{


	return 0;
}



int paste()
{




	return 0;
}



int save_as_bitmap()
{
	int x,y;
//	extern int map_tile_db[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES];
	BITMAP *map = create_bitmap(MAP_WIDTH_IN_TILES*tile_width, MAP_HEIGHT_IN_TILES*tile_width);
	PALETTE pal;
	get_palette(pal);
	for (y=0 ; y< MAP_HEIGHT_IN_TILES; y+=1)
	{	for (x=0 ; x< MAP_WIDTH_IN_TILES; x+=1)
		{
//			blit(tile[map_tile_db[x/32+map_position_x][y/32+map_position_y]], map, 0,0, x,y, tile_width,tile_width);		
			blit(tile[map_tile_db[x][y]], map, 0,0, x*tile_width,y*tile_width, tile_width,tile_width);		
		}
	}
	save_bitmap("saved_map.bmp", map , pal);
	destroy_bitmap(map);
	return 0;
}












int test_function()//use only to debug. call this function wherever you want to test something.
{

	textprintf_ex(screen_buffer, font, 500 , 720, makecol(255,255,255), -1, "map x: %d", map_position_x );
	textprintf_ex(screen_buffer,  font, 500 , 730, makecol(255,255,255), -1, "map y: %d", map_position_y);
//	textprintf_ex(screen_buffer, font, 500 , 740, makecol(255,255,255), -1, "in copypaste mode?: %d", );
}
