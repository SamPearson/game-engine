// Part of the stonex map editor

#include <allegro.h>
#include "mapinfo.hpp"

BITMAP *map_buffer;
BITMAP *screen_buffer;
BITMAP *tile_buffer;
BITMAP *menu_buffer;
int test_function();//use only for debug. call this when you want to test something.
int gfx_engine();
int map_init();
int draw_ui();
int draw_map();
int get_tiles();
int draw_grid(int lowest_x, int lowest_y, int highest_x, int highest_y, int tile_size, BITMAP *bitmap, int color);


int map_collision_db[100][100];
int map_tile_db[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES] = {};
int tile_width = 32;



int mapbuffer_width_in_tiles = 20, mapbuffer_height_in_tiles = 20;
int mapbuffer_location_x = 100, mapbuffer_location_y = 64;
int tilebuffer_width_in_tiles = 8, tilebuffer_height_in_tiles = 24;
int tilebuffer_location_x = 768, tilebuffer_location_y = 0;

int map_position_x = 0;//
int map_position_y = 0;// coordinates for where the top left corner of the editable buffer lines up with the on the full map.
BITMAP *tile[144]; // tile[0] is a void tile, used only to denote unused space on the map.
int current_tile = 1;
int draw_grid_on_map=1;
int draw_grid_on_tiles=1;

int map_init()
{//map initialisation function. creates or defines multiple bitmap buffers

	map_buffer=create_bitmap(mapbuffer_width_in_tiles * tile_width, mapbuffer_height_in_tiles * tile_width);
	screen_buffer=create_bitmap(1024,768);
	tile_buffer=load_bitmap("tiles.bmp",0);
	menu_buffer=create_bitmap(100,768);
	get_tiles();
	return 0;
}

int gfx_engine()
{
	test_function();// used for debug commands and stuff.
	draw_ui(); // draws the ui and compress all buffers down to the screen_buffer, so only one draw to the screen is made.
	draw_map();// draws the individual tiles that correspond to the tile numbers in the map array.

	blit (screen_buffer, screen, 0,0,0,0,1024,768);
	rectfill (screen_buffer, 0,0,1024,768,makecol(0,0,0));
	return 0;
}


int draw_ui()
{

	int menubuffer_location_x = 0, menubuffer_location_y = 0;
	//draw the tile grid around the map
	if (draw_grid_on_map==1)
	draw_grid(0,0,639,639, tile_width, map_buffer, makecol(255,255,255));

	if (draw_grid_on_tiles==1)
	draw_grid(0,0,tilebuffer_width_in_tiles * tile_width , tilebuffer_height_in_tiles * tile_width, tile_width, tile_buffer, makecol(255,255,255));


	// when changing the names of buttons, remember to make sure they call the corresponding function in get_user_input()
	rect(menu_buffer,5,5,90,40,makecol(255,255,255));	//fill button
	textprintf_ex(menu_buffer, font, 30 , 20, makecol(255,255,255), -1, "Fill" );
	rect(menu_buffer,5,45,90,80,makecol(255,255,255));	//fill area button
	textprintf_ex(menu_buffer, font, 30 , 50, makecol(255,255,255), -1, "Fill" );
	textprintf_ex(menu_buffer, font, 30 , 60, makecol(255,255,255), -1, "area" );
	rect(menu_buffer,5,85,90,120,makecol(255,255,255));// copy button
	textprintf_ex(menu_buffer, font, 30 , 100, makecol(255,255,255), -1, "Copy" );
	rect(menu_buffer,5,125,90,160,makecol(255,255,255)); // repeat copy button
	textprintf_ex(menu_buffer, font, 25 , 130, makecol(255,255,255), -1, "Repeat" );
	textprintf_ex(menu_buffer, font, 30 , 140, makecol(255,255,255), -1, "copy" );
	rect(menu_buffer,5,165,90,200,makecol(255,255,255)); // mirror x copy button
	textprintf_ex(menu_buffer, font, 20 , 170, makecol(255,255,255), -1, "Mirror H" );
	textprintf_ex(menu_buffer, font, 30 , 180, makecol(255,255,255), -1, "copy" );
	rect(menu_buffer,5,205,90,240,makecol(255,255,255)); // mirror y copy button
	textprintf_ex(menu_buffer, font, 20 , 210, makecol(255,255,255), -1, "Mirror V" );
	textprintf_ex(menu_buffer, font, 30 , 220, makecol(255,255,255), -1, "copy" );

	rect(menu_buffer,5,245,90,280,makecol(255,255,255));
	rect(menu_buffer,5,285,90,320,makecol(255,255,255));

	rect(menu_buffer,5,325,90,360,makecol(255,255,255)); // toggle grids button
	textprintf_ex(menu_buffer, font, 25 , 330, makecol(255,255,255), -1, "Toggle" );
	textprintf_ex(menu_buffer, font, 30 , 340, makecol(255,255,255), -1, "grids" );
	rect(menu_buffer,5,365,90,400,makecol(255,255,255)); // reload map
	textprintf_ex(menu_buffer, font, 25 , 380, makecol(255,255,255), -1, "Reload" );	
	rect(menu_buffer,5,405,90,440,makecol(255,255,255)); // save map
	textprintf_ex(menu_buffer, font, 30 , 420, makecol(255,255,255), -1, "Save" );


	//here's where the layers all get flattened onto screen_buffer
	blit (menu_buffer, screen_buffer, 0,0,0,0,100,768);
	blit (map_buffer, screen_buffer, 0,0,mapbuffer_location_x,mapbuffer_location_y,641,641);
	blit (tile_buffer, screen_buffer, 0,0,tilebuffer_location_x,tilebuffer_location_y,255,768);
	destroy_bitmap (tile_buffer);
	tile_buffer=load_bitmap("tiles.bmp",0);

	//then I draw the mouse and I'm done.
	line (screen_buffer,	mouse_x-11,	mouse_y-9,	mouse_x+9,	mouse_y+11,	makecol(0,0,0));	//draw the cursor
	line (screen_buffer,	mouse_x-11,	mouse_y-11,	mouse_x+11,	mouse_y+11,	makecol(0,0,0));	//draw the cursor
	line (screen_buffer,	mouse_x-8,	mouse_y-8,	mouse_x+8,	mouse_y+8,	makecol(255,255,255));	//draw the cursor
	line (screen_buffer,	mouse_x-9,	mouse_y-11,	mouse_x+11,	mouse_y+9,	makecol(0,0,0));	//draw the cursor
	line (screen_buffer,	mouse_x-11,	mouse_y+9,	mouse_x+9,	mouse_y-11,	makecol(0,0,0));	//draw the cursor
	line (screen_buffer,	mouse_x-11,	mouse_y+11,	mouse_x+11,	mouse_y-11,	makecol(0,0,0));	//draw the cursor
	line (screen_buffer,	mouse_x-8,	mouse_y+8,	mouse_x+8,	mouse_y-8,	makecol(255,255,255));	//draw the cursor
	line (screen_buffer,	mouse_x-9,	mouse_y+11,	mouse_x+11,	mouse_y-9,	makecol(0,0,0));	//draw the cursor
	return 0;
}


int draw_map()
{
	int x,y;
	for (y=0 ; y< mapbuffer_height_in_tiles * tile_width; y+=32)
	{
		for (x=0 ; x< mapbuffer_width_in_tiles * tile_width; x+=32)
		{
			blit(tile[map_tile_db[x/32+map_position_x][y/32+map_position_y]], map_buffer, 0,0, x,y, tile_width,tile_width);	
		}
	}
	return 0;
}


int get_tiles()
{
	int x,y,z;
	for(x=0 ; x<=(tilebuffer_height_in_tiles * tilebuffer_width_in_tiles) ; x++)
	{
		tile[x] = create_bitmap(tile_width , tile_width);
	}

	z=0;
	for (y=0 ; y < tilebuffer_height_in_tiles * tile_width ; y+=32)
	{
		for (x=0 ; x < tilebuffer_width_in_tiles * tile_width ; x+=32)
		{	
			blit ( tile_buffer, tile[z], x,y, 0,0, tile_width,tile_width);
			z++;
		}
	}

	return 0;
}






int draw_grid(int lowest_x, int lowest_y, int highest_x, int highest_y, int tile_size, BITMAP *bitmap, int color)
{
	int cntx, cnty;
	for (cntx = lowest_x ; cntx <= highest_x ; cntx += tile_size)
	{
		line( bitmap, cntx, lowest_y, cntx, highest_y, color);
		for (cnty = lowest_y ; cnty <= highest_y; cnty += tile_size)
		{
			line(bitmap, lowest_x, cnty, highest_x, cnty, color);
		}
	}
	line(bitmap, highest_x, lowest_y, highest_x, highest_y, color);
	line(bitmap, lowest_x, highest_y, highest_x, highest_y, color);
	return 0;
}
