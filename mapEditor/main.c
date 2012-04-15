/*
*
*	The map/level editor for the game engine
*
*	
*/

#include <allegro.h>
#include "mapInfo.h"


int main()
{
	//initialise allegro 
	allegro_init();
	install_keyboard();
	install_mouse();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768,0,0);
	
	//load and execute the map preparation functions
	extern int map_init();//
	map_init();
	extern int load_map();// 
	load_map();
	

	//these are defined in external files
	extern int get_user_input();
	extern int gfx_engine();

	while(!key[KEY_ESC])
	{//this is the main game loop.
		get_user_input();
		gfx_engine();
	}

return 0;
}
END_OF_MAIN();
