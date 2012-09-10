// Part of the stonex map editor


#include <allegro.h>
#include "mapinfo.hpp"


int main()
{
	//external things the main loop will need
	extern int map_init();
	extern int get_user_input();
	extern int gfx_engine();
	extern int save_map();
	extern int load_map();

	//allegro setup
	allegro_init();
	install_keyboard();
	install_mouse();
	//install_timer(); commented 9/9/2012
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768,0,0);
	//extern BITMAP *screen_buffer; commented 9/9/2012
	map_init();
	load_map();
	

	//the main loop. 
	while(!key[KEY_ESC])
	{
		get_user_input();
		gfx_engine();
	}

return 0;
}
END_OF_MAIN();
