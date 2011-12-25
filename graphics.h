//hey guys, graphics here.

#include "debug.h"

#include <stdio.h>
extern char s[20];
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480

//define cloud's various states
#define BATTLE 2	//unused
#define WALKING 1
#define RESTING 0


BITMAP *cloudright[4];
BITMAP *clouddown[4];
BITMAP *cloudleft[4];
BITMAP *cloudup[4];
extern int curframe;

int graphics_setup()
{
map_width[ALTON_CITY]=1920;
map_height[ALTON_CITY]=1280;

map_width[ALTON_ACADEMY]=640;
map_height[ALTON_ACADEMY]=640;

map_width[ALTON_HOUSE]=640;
map_height[ALTON_HOUSE]=640;

map_width[ALTON_HOUSE_TWO]=640;
map_height[ALTON_HOUSE_TWO]=640;

map_width[ALTON_HOUSE_THREE]=640;
map_height[ALTON_HOUSE_THREE]=640;

map_width[ALTON_FOREST]=640;
map_height[ALTON_FOREST]=3200;


    //initialize allegro
    allegro_init();
    install_keyboard();
    install_timer();
    srand(time(NULL));
    set_color_depth(16);

    //set video mode
    if (set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0) != 0)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
//        allegro_message(allegro_error);
        return 0;
    }


//load sprites into cloud's arrarys. this graphics stuff should go in a seperate source file
//==========================================================================================
for (cnt=0; cnt<3; cnt++)
{
	sprintf(s,"sprites/cloud/cloudright%d.bmp", cnt+1);
	cloudright[cnt] = load_bitmap(s, NULL);
}
for (cnt=0; cnt<3; cnt++)
{
	sprintf(s,"sprites/cloud/clouddown%d.bmp", cnt+1);
	clouddown[cnt] = load_bitmap(s, NULL);
}
for (cnt=0; cnt<3; cnt++)
{
	sprintf(s,"sprites/cloud/cloudleft%d.bmp", cnt+1);
	cloudleft[cnt] = load_bitmap(s, NULL);
}
for (cnt=0; cnt<3; cnt++)
{
	sprintf(s,"sprites/cloud/cloudup%d.bmp", cnt+1);
	cloudup[cnt] = load_bitmap(s, NULL);
}
//==========================================================================================
//==========================================================================================



//create the virtual background
    scroll = create_bitmap(map_width[current_map], map_height[current_map]);
    if (scroll == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error creating virtual background");
        return 0;
    }	
	
	
return 0;		
}





void graphics_engine()
{
 blit(background_layer, scroll, camera_x, camera_y, camera_x, camera_y, 640, 480);



	if (cloud_state==WALKING)
{
	if (cloud_direction==1)
   draw_sprite(scroll, cloudright[curframe], cloudx,cloudy);
	if (cloud_direction==2)
   draw_sprite(scroll, clouddown[curframe], cloudx,cloudy);
	if (cloud_direction==3)
   draw_sprite(scroll, cloudleft[curframe], cloudx,cloudy);
	if (cloud_direction==4)
   draw_sprite(scroll, cloudup[curframe], cloudx,cloudy);
		
}


	if (cloud_state==RESTING)
{
if (cloud_direction==1)
	draw_sprite(scroll, cloudright[0], cloudx,cloudy);
if (cloud_direction==2)
	draw_sprite(scroll, clouddown[0], cloudx,cloudy);
if (cloud_direction==3)
	draw_sprite(scroll, cloudleft[0], cloudx,cloudy);
if (cloud_direction==4)
	draw_sprite(scroll, cloudup[0], cloudx,cloudy);
}


///////////////////////////////////////////////////////////////////////
//debug_draw();
///////////////////////////////////////////////////////////////////////
 blit(sprite_layer, sprite_buffer, camera_x, camera_y, 0, 0, 640, 480); 



	draw_sprite(scroll, sprite_buffer,camera_x,camera_y);
        //draw the scroll window portion of the virtual buffer
        blit(scroll, screen, camera_x, camera_y, 0, 0, 640, 480);
//blank out the sprite layer
	
	
	
	
}


void get_fps()
{
extern int sleepytime;
extern int target_fps;
framesps=mainloopticks;	
if (framesps<target_fps-5)
	sleepytime-=2;
if (framesps>target_fps+5)
	sleepytime+=2;
if (framesps<10)
	framesps=10;

mainloopticks=0;
}
