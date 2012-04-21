/*
*
* This .h file defines the fade in and fade out functions.
*
* It also defines the collision boundaries for all doors and objects.
* object_min/max_x/y[]
* 
* 
*/


extern int current_map;
extern BITMAP *background_layer;
extern BITMAP *sprite_layer;
extern BITMAP *cloudright[4];
extern BITMAP *clouddown[4];
extern BITMAP *cloudleft[4];
extern BITMAP *cloudup[4];
extern int cloud_direction;
extern BITMAP *scroll;
extern int camera_x;
extern int camera_y;
//#define NUMBER_OF_MAPS 2
extern int map_height[10];
extern int map_width[10];
#define ALTON_CITY          1
#define ALTON_ACADEMY       2
#define ALTON_HOUSE         3
#define ALTON_HOUSE_TWO     5
#define ALTON_HOUSE_THREE   6
#define ALTON_FOREST        4 //quick,dirty
BITMAP *sprite_buffer;
BITMAP *collision_buffer;


int object_min_x[1000];
int object_max_x[1000];
int object_min_y[1000];
int object_max_y[1000];
int door_min_x[10];
int door_min_y[10];
int door_max_x[10];
int door_max_y[10];
extern int n;

#define BLACK makecol(0,0,0)
extern int cloudx;
extern int cloudy;
extern int cnt;
//=====================================================================
//      fading functions. highcolor_fade_in() and highcolor_fade_out()=
//=====================================================================
void highcolor_fade_out(int speed)
{
    BITMAP *bmp_orig, *bmp_buff;

    if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
        {
            int a;
            blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (speed <= 0) speed = 16;
        
            for (a = 255-speed; a > 0; a-=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
                vsync();
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(bmp_buff);
        }
        destroy_bitmap(bmp_orig);
    }

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));
}


void highcolor_fade_in(BITMAP *bmp_orig, int speed)
{
   BITMAP *bmp_buff;

    if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        int a;
        if (speed <= 0) speed = 16;
        
        for (a = 0; a < 256; a+=speed)
        {
            clear(bmp_buff);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
            vsync();
            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(bmp_buff);
    } 

    blit(bmp_orig, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
}

//============================================================================
// 		     initialising the map with map_change()                          =
//============================================================================
int map_change()
{
//here, fade out and blank out the sprite buffer
//-----------------------------------------------------
highcolor_fade_out(10);
sprite_buffer    = create_bitmap(640,480);
rectfill(sprite_buffer,0,0,640,480,makecol(255,0,255));
//-----------------------------------------------------

// then prepare the necessary collision variables and such for
// whichever room you happen to be in
if (current_map==ALTON_CITY)
{
//blank out the collision detection arrays
for (n=0; n<1000; n++)
{
object_min_x[n]=0;
object_min_y[n]=0;
object_max_x[n]=0;
object_max_y[n]=0;
}
for (n=0; n<10; n++)
{
door_min_x[n]=0;
door_min_y[n]=0;
door_max_x[n]=0;
door_max_y[n]=0;	
}


//alton city>>alton academy door
door_min_x[1]=1824;
door_min_y[1]=734;
door_max_x[1]=1855;
door_max_y[1]=760;	

//alton city>> alton house door
door_min_x[2]=1334;
door_min_y[2]=1142;
door_max_x[2]=1420;
door_max_y[2]=1151;	

//alton city>> alton house 2
door_min_x[3]=1550;
door_min_y[3]=1142;
door_max_x[3]=1650;
door_max_y[3]=1151;	

//alton city>> alton house 3
door_min_x[4]=1780;
door_min_y[4]=1142;
door_max_x[4]=1870;
door_max_y[4]=1151;	

//alton city>> alton forest door
/*						 alton forest has been cut.
door_min_x[5]=1024;
door_min_y[5]=0;
door_max_x[5]=1184;
door_max_y[5]=20;
*/
//the map boundaries
object_min_x[0]=0;
object_max_x[0]=1907;
object_max_y[0]=1260;
object_min_y[0]=20;

//three houses
object_min_x[1]=1760;object_min_y[1]=1151;object_max_x[1]=1887;object_max_y[1]=1255;
object_min_x[4]=1312;object_min_y[4]=1136;object_max_x[4]=1344;object_max_y[4]=1151;
object_min_x[5]=1408;object_min_y[5]=1136;object_max_x[5]=1439;object_max_y[5]=1151;
//-------------
object_min_x[2]=1536;object_min_y[2]=1151;object_max_x[2]=1664;object_max_y[2]=1255;
object_min_x[6]=1536;object_min_y[6]=1136;object_max_x[6]=1568;object_max_y[6]=1151;
object_min_x[7]=1631;object_min_y[7]=1136;object_max_x[7]=1663;object_max_y[7]=1151;
//-------------
object_min_x[3]=1312;object_min_y[3]=1151;object_max_x[3]=1440;object_max_y[3]=1255;
object_min_x[8]=1760;object_min_y[8]=1136;object_max_x[8]=1792;object_max_y[8]=1151;
object_min_x[9]=1855;object_min_y[9]=1136;object_max_x[9]=1887;object_max_y[9]=1151;

//a rock
object_min_x[10]=1763;object_min_y[10]=964;object_max_x[10]=1789;object_max_y[10]=987;
//the old well
object_min_x[11]=1447;object_min_y[11]=928;object_max_x[11]=1489;object_max_y[11]=963;
//some boxes
object_min_x[12]=1699;object_min_y[12]=801;object_max_x[12]=1790;object_max_y[12]=830;
object_min_x[13]=1891;object_min_y[13]=801;object_max_x[13]=1920;object_max_y[13]=830;

//the academy
object_min_x[14]=1696;object_min_y[14]=672;object_max_x[14]=1822;object_max_y[14]=799;
object_min_x[15]=1856;object_min_y[15]=672;object_max_x[15]=1920;object_max_y[15]=799;
object_min_x[16]=1822;object_min_y[16]=672;object_max_x[16]=1856;object_max_y[16]=743;

//trees
object_min_x[22]=68; object_min_y[22]=960 ;object_max_x[22]=124 ;object_max_y[22]=986;
object_min_x[23]=194;object_min_y[23]=832 ;object_max_x[23]=222 ;object_max_y[23]=863;
object_min_x[24]=295;object_min_y[24]=864 ;object_max_x[24]=346 ;object_max_y[24]=891;
object_min_x[25]=390;object_min_y[25]=1216;object_max_x[25]=442 ;object_max_y[25]=1245;
object_min_x[26]=420;object_min_y[26]=800 ;object_max_x[26]=472 ;object_max_y[26]=827;
object_min_x[27]=516;object_min_y[27]=1152;object_max_x[27]=568 ;object_max_y[27]=1179;
object_min_x[28]=550;object_min_y[28]=896 ;object_max_x[28]=601 ;object_max_y[28]=925;
object_min_x[29]=675;object_min_y[29]=960 ;object_max_x[29]=701 ;object_max_y[29]=989;
object_min_x[30]=676;object_min_y[30]=832 ;object_max_x[30]=729 ;object_max_y[30]=857;
object_min_x[31]=1170;object_min_y[31]=1248 ;object_max_x[31]=1202 ;object_max_y[31]=1267;
object_min_x[32]= 937;object_min_y[32]=1216 ;object_max_x[32]= 973 ;object_max_y[32]=1236;
object_min_x[33]= 748;object_min_y[33]=1248 ;object_max_x[33]= 787 ;object_max_y[33]=1272;
object_min_x[34]=1095;object_min_y[34]= 832 ;object_max_x[34]=1140 ;object_max_y[34]= 850;
object_min_x[35]= 870;object_min_y[35]= 928 ;object_max_x[35]= 922 ;object_max_y[35]= 945;


//water
// - you can't walk on it.
object_min_x[50]=0;object_min_y[50]=994;object_max_x[50]=56;object_max_y[50]=1230;
object_min_x[51]=64;object_min_y[51]=994;object_max_x[51]=470;object_max_y[51]=1166;
object_min_x[52]=133;object_min_y[52]=935;object_max_x[52]=440;object_max_y[52]=995;
object_min_x[53]=137;object_min_y[53]=905;object_max_x[53]=250;object_max_y[53]=932;
object_min_x[54]=473;object_min_y[54]=1001;object_max_x[54]=505;object_max_y[54]=1138;

object_min_x[55]=1620;object_min_y[55]=460;object_max_x[55]=1713;object_max_y[55]=490;


//alton academy
object_min_x[39]=1536;object_min_y[39]=223;object_max_x[39]=1632;object_max_y[39]=410;
object_min_x[40]=1600;object_min_y[40]=410;object_max_x[40]=1632;object_max_y[40]=441;
object_min_x[41]=1696;object_min_y[41]=380;object_max_x[41]=1727;object_max_y[41]=441;
object_min_x[42]=1725;object_min_y[42]=385;object_max_x[42]=1920;object_max_y[42]=410;
object_min_x[43]=1725;object_min_y[43]=385;object_max_x[43]=1920;object_max_y[43]=410;

//the door that blocks alton academy
object_min_x[49]=1635;object_min_y[49]=380;object_max_x[49]=1700;object_max_y[49]=400;



//rocks, boundaries
object_min_x[43]=1410;object_min_y[43]=88;object_max_x[43]=1920;object_max_y[43]=215;

object_min_x[44]=670;object_min_y[44]=0;object_max_x[44]=1024;object_max_y[44]=215;
object_min_x[45]=1184;object_min_y[45]=0;object_max_x[45]=1920;object_max_y[45]=215;

object_min_x[46]=607;object_min_y[46]=150;object_max_x[46]=671;object_max_y[46]=275;
object_min_x[47]=0;object_min_y[47]=377;object_max_x[47]=610;object_max_y[47]=500;
object_min_x[48]=603;object_min_y[48]=158;object_max_x[48]=607;object_max_y[48]=459;




background_layer = load_bitmap("maps/alton/background_layer.bmp", NULL);
sprite_layer = load_bitmap("maps/alton/sprite_layer.bmp", NULL);

}

if (current_map==ALTON_ACADEMY)
{


for (n=0; n<50; n++)
{
object_max_x[n]=0;
object_min_x[n]=0;
object_min_y[n]=0;
object_max_y[n]=0;
}
for (n=0; n<10; n++)
{
door_min_x[n]=0;
door_min_y[n]=0;
door_max_x[n]=0;
door_max_y[n]=0;		
}


//the map's border
object_min_x[0]=35;
object_min_y[0]=100;
object_max_y[0]=640;
object_max_x[0]=593;
//blank
object_max_x[1]=0;
object_min_x[1]=0;
object_min_y[1]=0;
object_max_y[1]=0;
//a bookshelf
object_min_x[2]=32;
object_min_y[2]=175;
object_max_x[2]=95;
object_max_y[2]=198;
//some boxes
object_min_x[3]=96;
object_min_y[3]=132;
object_max_x[3]=223;
object_max_y[3]=159;
//materia ore
object_min_x[4]=128;
object_min_y[4]=160;
object_max_x[4]=223;
object_max_y[4]=223;
//anvil and water trough
object_min_x[5]=298;
object_min_y[5]=148;
object_max_x[5]=347;
object_max_y[5]=220;
//smelted materia ore
object_min_x[6]=390;
object_min_y[6]=135;
object_max_x[6]=413;
object_max_y[6]=213;
//armor forged with materia
object_min_x[7]=448;
object_min_y[7]=200;
object_max_x[7]=479;
object_max_y[7]=223;
//another bookshelf.
object_min_x[8]=544;
object_min_y[8]=175;
object_max_x[8]=607;
object_max_y[8]=198;

// desks
object_min_x[9]=72;object_min_y[9]=293;object_max_x[9]=object_min_x[9]+19;object_max_y[9]=object_min_y[9]+24;
object_min_x[11]=72;object_min_y[11]=389;object_max_x[11]=object_min_x[11]+19;object_max_y[11]=object_min_y[11]+24;
object_min_x[12]=72;object_min_y[12]=485;object_max_x[12]=object_min_x[12]+19;object_max_y[12]=object_min_y[12]+24;
object_min_x[10]=168;object_min_y[10]=293;object_max_x[10]=object_min_x[10]+19;object_max_y[10]=object_min_y[10]+24;
object_min_x[13]=168;object_min_y[13]=389;object_max_x[13]=object_min_x[13]+19;object_max_y[13]=object_min_y[13]+24;
object_min_x[14]=168;object_min_y[14]=485;object_max_x[14]=object_min_x[14]+19;object_max_y[14]=object_min_y[14]+24;
object_min_x[15]=456;object_min_y[15]=485;object_max_x[15]=object_min_x[15]+19;object_max_y[15]=object_min_y[15]+24;
object_min_x[16]=456;object_min_y[16]=389;object_max_x[16]=object_min_x[16]+19;object_max_y[16]=object_min_y[16]+24;
object_min_x[17]=456;object_min_y[17]=293;object_max_x[17]=object_min_x[17]+19;object_max_y[17]=object_min_y[17]+24;
object_min_x[18]=552;object_min_y[18]=485;object_max_x[18]=object_min_x[18]+19;object_max_y[18]=object_min_y[18]+24;
object_min_x[19]=552;object_min_y[19]=389;object_max_x[19]=object_min_x[19]+19;object_max_y[19]=object_min_y[19]+24;
object_min_x[20]=552;object_min_y[20]=293;object_max_x[20]=object_min_x[20]+19;object_max_y[20]=object_min_y[20]+24;

//south walls
object_min_x[21]=0;object_min_y[21]=576;object_max_y[21]=640;object_max_x[21]=285;
object_min_x[22]=352;object_min_y[22]=576;object_max_y[22]=640;object_max_x[22]=640;
//and a door back to the city
door_min_x[1]=287;door_min_y[1]=610;door_max_x[1]=352;door_max_y[1]=640;

	background_layer = load_bitmap("maps/academy/background_layer.bmp", NULL);
	sprite_layer = load_bitmap("maps/academy/sprite_layer.bmp", NULL);
}


// All the houses look the same, so I'd like to
// put them all in the same room, then position the character based on
// which one you walked out of when you do so.
if (current_map==ALTON_HOUSE || current_map==ALTON_HOUSE_TWO || current_map==ALTON_HOUSE_THREE)
{


for (n=0; n<1000; n++)
{
object_max_x[n]=0;
object_min_x[n]=0;
object_min_y[n]=0;
object_max_y[n]=0;
}
for (n=0; n<10; n++)
{
door_min_x[n]=0;
door_min_y[n]=0;
door_max_x[n]=0;
door_max_y[n]=0;		
}


//the map's border
object_min_x[0]=35;
object_min_y[0]=100;
object_max_y[0]=640;
object_max_x[0]=593;
//object template
object_min_x[1]=0; object_min_y[1]=0; object_max_x[1]=0; object_max_y[1]=0;

//walls
object_min_x[2]=48; object_min_y[2]=76; object_max_x[2]=62; object_max_y[2]=594;
object_min_x[3]=64; object_min_y[3]=96; object_max_x[3]=278; object_max_y[3]=149;
object_min_x[4]=361; object_min_y[4]=96; object_max_x[4]=565; object_max_y[4]=149;
object_min_x[5]=576; object_min_y[5]=76; object_max_x[5]=591; object_max_y[5]=595;


// desks
object_min_x[6]=454; object_min_y[6]=323; object_max_x[6]=538; object_max_y[6]=337;
object_min_x[7]=453; object_min_y[7]=419; object_max_x[7]=538; object_max_y[7]=433;
object_min_x[8]=102; object_min_y[8]=420; object_max_x[8]=186; object_max_y[8]=433;
object_min_x[9]=102; object_min_y[9]=323; object_max_x[9]=186; object_max_y[9]=337;

//beds
object_min_x[10]=109; object_min_y[10]=500; object_max_x[10]=144; object_max_y[10]=531;
object_min_x[11]=493; object_min_y[11]=500; object_max_x[11]=528; object_max_y[11]=531;
//object_min_x[12]=; object_min_y[12]=; object_max_x[12]=; object_max_y[12]=;
//object_min_x[13]=; object_min_y[13]=; object_max_x[13]=; object_max_y[13]=;
//object_min_x[14]=; object_min_y[14]=; object_max_x[14]=; object_max_y[14]=;
//object_min_x[15]=; object_min_y[15]=; object_max_x[15]=; object_max_y[15]=;
//object_min_x[16]=; object_min_y[16]=; object_max_x[16]=; object_max_y[16]=;
//object_min_x[17]=; object_min_y[17]=; object_max_x[17]=; object_max_y[17]=;
//object_min_x[18]=; object_min_y[18]=; object_max_x[18]=; object_max_y[18]=;


//south walls
object_min_x[21]=0;object_min_y[21]=576;object_max_y[21]=640;object_max_x[21]=640;



//and a door back to the city
door_min_x[1]=287;door_min_y[1]=110;door_max_x[1]=352;door_max_y[1]=150;

	background_layer = load_bitmap("maps/house/background_layer.bmp", NULL);
	sprite_layer = load_bitmap("maps/house/sprite_layer.bmp", NULL);
}

if (current_map==ALTON_FOREST)
{

for (n=0; n<50; n++)
{
object_max_x[n]=0;
object_min_x[n]=0;
object_min_y[n]=0;
object_max_y[n]=0;
}
for (n=0; n<10; n++)
{
door_min_x[n]=0;
door_min_y[n]=0;
door_max_x[n]=0;
door_max_y[n]=0;		
}


//the map's border
object_min_x[0]=35;
object_min_y[0]=50;
object_max_y[0]=3200;
object_max_x[0]=600;
//object template
object_min_x[1]=0;
object_min_y[1]=0;
object_max_x[1]=0;
object_max_y[1]=0;


//and a door back to the city
door_min_x[1]=0;door_min_y[1]=3185;door_max_x[1]=640;door_max_y[1]=3200;


	background_layer = load_bitmap("maps/forest/background_layer.bmp", NULL);
	sprite_layer = load_bitmap("maps/forest/sprite_layer.bmp", NULL);
}










//create the scroll window (shouldnt this be smaller?)
destroy_bitmap(scroll);
scroll = create_bitmap(map_width[current_map], map_height[current_map]);
blit(sprite_layer, sprite_buffer, camera_x, camera_y, 0, 0, 645, 485);
// draw cloud on the sprite layer
if (cloud_direction==1)
	draw_sprite(sprite_buffer, cloudright[0], cloudx-camera_x,cloudy-camera_y);
if (cloud_direction==2)
	draw_sprite(sprite_buffer, clouddown[0], cloudx-camera_x,cloudy-camera_y);
if (cloud_direction==3)
	draw_sprite(sprite_buffer, cloudleft[0], cloudx-camera_x,cloudy-camera_y);
if (cloud_direction==4)
	draw_sprite(sprite_buffer, cloudup[0], cloudx-camera_x,cloudy-camera_y);

blit(background_layer, scroll, camera_x, camera_y, 0, 0, 640, 480); 
draw_sprite(scroll, sprite_buffer,0,0);

//finally, draw the opening screen and fade into it.
//blit(sprite_layer, sprite_buffer, x, y, 0, 0, 645, 485); 
//blit(background_layer, scroll, x, y, 0, 0, 640, 480); 
//blit(sprite_buffer, scroll, 0, 0, 0, 0, 640, 480);
//	draw_sprite(scroll, sprite_buffer,0,0);



highcolor_fade_in(scroll,10);
sleepytime=15.0;

return 0;
}




