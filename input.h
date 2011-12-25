
#define RIGHTBUTTON 1
#define DOWNBUTTON 2
#define LEFTBUTTON 3
#define UPBUTTON 4


extern int curframe, framedelay, framecount;

void character_control()
{
//==============================================
if (key[KEY_1])
{
current_map=1;
map_change();
}

if (key[KEY_2])
{
current_map=2;
map_change();
}
//========================================================
//get information on the player if they're walking around
if (key[KEY_D])
{
xcollision= cloudx+3;
ycollision= cloudy;
 if (colltest()==1)
  {
   if (cloud_direction==1)
    {
     cloudx-=1;
     broken_key = RIGHTBUTTON;
     cloud_state = RESTING;
    }
  }

if (broken_key != RIGHTBUTTON)
  {
  broken_key=0;
  cloud_state=WALKING;
  cloud_direction=1;
  //-------------------------------
  //draw cloud walking to the right
  cloudx+=3;
   if (framecount++ > framedelay)
   {
   framecount = 0;
   curframe++;
    if (curframe > 2)
    curframe=0;
   }
    while(cloudx+18>camera_x+540 && camera_x+640<map_width[current_map])
    {
    camera_x++;
    }
   }
 }

else if (key[KEY_A])
{
ycollision= cloudy;
xcollision= cloudx-3;
 if (colltest()==1)
	{
	if (cloud_direction==3)
	 {
	  cloudx+=1;
	  broken_key = LEFTBUTTON;
	  cloud_state = RESTING;
	 }
	}
	
if (broken_key != LEFTBUTTON)
  {
	broken_key=0;
	//-------------------------------
	//draw cloud walking to the left
	cloud_state=WALKING;
	cloud_direction=3;
	cloudx-=3;
	if (framecount++ > framedelay)
	{
	framecount = 0;
	curframe++;
	if (curframe > 2)
		curframe=0;
	}	
	while(cloudx<camera_x+100 && camera_x>0)
	{
  	 camera_x--;
	}
}
}

else if (key[KEY_S])
{
xcollision= cloudx;
ycollision= cloudy+3;
 if (colltest()==1)
	{
	if (cloud_direction==2)
	 {
	  cloudy-=1;
	  broken_key = DOWNBUTTON;
	  cloud_state = RESTING;
	 }
	}
// else
if (broken_key != DOWNBUTTON)
  {
	broken_key=0;
	cloud_state=WALKING;
	cloud_direction=2;
	cloudy+=3;
	if (framecount++ > framedelay)
	{
	framecount = 0;
	curframe++;
	if (curframe > 2)
		curframe=0;
	}
	while(cloudy+22>camera_y+380 && camera_y+480<map_height[current_map])
	{
 	 camera_y++;
	}
}
}

else if (key[KEY_W])
{
xcollision= cloudx;
ycollision= cloudy-3;
 if (colltest()==1)
	{
	if (cloud_direction==4)
	 {
	  cloudy+=1;
	  broken_key = UPBUTTON;
	  cloud_state = RESTING;
	 }
	}
// else
if (broken_key != UPBUTTON)
  {
	broken_key=0;
	cloud_state=WALKING;
	cloud_direction=4;
	cloudy-=3;
	if (framecount++ > framedelay)
		{
		framecount = 0;
		curframe++;
		if (curframe > 2)
			curframe=0;
		}
	while(cloudy<camera_y+100 && camera_y>0)
	{
	 camera_y--;
	}
}
}
else
	cloud_state=RESTING;	
//========================================================	
	
}



