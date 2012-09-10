// Part of the stonex map editor


#include <allegro.h>
#include "mapinfo.hpp"

volatile int ticks;
void ticker(void)// ticker function. for use byt the fps regulator
{
	++ticks;
}END_OF_FUNCTION(ticker);
const int updates_per_second=60;

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
	install_timer();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768,0,0);
	extern BITMAP *screen_buffer;
	map_init();
	load_map();
	
	//fps setup
	LOCK_FUNCTION(ticker);
	LOCK_VARIABLE(ticks);
	install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));

	while(!key[KEY_ESC])
	{

		while(ticks==0)
		{
			rest(100 / updates_per_second); //rest until a tick has passed	
		}

		while(ticks>0)
		{
			int old_ticks = ticks;

			//logic goes here
			get_user_input();

			ticks--;
			if  (old_ticks <= ticks) //logic is taking too long, abort and draw a frame.
				break;
		}
		//drawing goes here
		gfx_engine();

	}

save_map();
return 0;
}
END_OF_MAIN();
