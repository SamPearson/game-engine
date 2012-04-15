/*
*
*	A game engine written in c with allegro
*
*
*/


#include <allegro.h>

//fps stuff
int sleepytime=15;
int framesps=0;
int target_fps=60;
volatile int mainloopticks=0;

#include "mapswitch.h"
int camera_x=1280, camera_y=800;
int map_height[10];
int map_width[10];
int current_map=1;

#include "collision.h"
extern int xcollision, ycollision;
int broken_key=0;
#define RIGHTBUTTON 1
#define DOWNBUTTON 2
#define LEFTBUTTON 3
#define UPBUTTON 4


#include "graphics.h"
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640				
#define HEIGHT 480		
#define BATTLE 2		
#define WALKING 1			
#define RESTING 0				
//character data
extern BITMAP *cloudright[4];
extern BITMAP *clouddown[4];
extern BITMAP *cloudleft[4];
extern BITMAP *cloudup[4];
int cloudx=1590, cloudy=1100, cloud_direction=4, cloud_state=0, count;
//animation data
char s[20];
int curframe=0, framedelay=5, framecount=0;
int n=0, cnt=0;
//screen buffering
BITMAP *background_layer;
BITMAP *sprite_layer;
BITMAP *scroll;
extern BITMAP *sprite_buffer;

#include "input.h"

#include <stdio.h>




void ticker()
{
mainloopticks++;	
}
END_OF_FUNCTION(ticker)






int main()
{

graphics_setup();
map_change();
   LOCK_VARIABLE(mainloopticks);
   LOCK_FUNCTION(get_fps);
   install_int_ex(get_fps, BPS_TO_TIMER(1));

//main loop
    while (!key[KEY_ESC])	//this means the only way to exit the game is the esc key. weak.
    {
	character_control();	//take player input
	graphics_engine();		//update graphics
	doortest();
	debug_textwindow();
//	debug_drawdoors();		//also draws collision
	if(sleepytime<0)
		sleepytime=0;	
	rest(sleepytime);
	ticker();
    }





destroy_bitmap(scroll);
destroy_bitmap(background_layer);
destroy_bitmap(sprite_layer);
return 0;
}

END_OF_MAIN();
