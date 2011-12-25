
extern int cloudx;
extern int cloudy;
extern int cloud_state;

extern int camera_x;
extern int camera_y;
int xcollision;
int ycollision;

extern int current_map;
extern int object_min_x[];
extern int object_max_x[];
extern int object_min_y[];
extern int object_max_y[];


extern int broken_key;

extern BITMAP *background_layer;





int colltest()
{
cloud_state=0;
if (xcollision<object_min_x[0] || ycollision<object_min_y[0] || xcollision>object_max_x[0] || ycollision>object_max_y[0])
return 1;

for (n=1; n<1000; n++)
{
if (ycollision<object_max_y[n] && xcollision+18>object_min_x[n] && ycollision+22>object_min_y[n] && xcollision<object_max_x[n])
return 1;
}

return 0;
}

void doortest()
{
if (current_map==ALTON_CITY)
{
		if (ycollision<door_max_y[1] && xcollision+18>door_min_x[1] && ycollision+22>door_min_y[1] && xcollision<door_max_x[1])
			{
				current_map=ALTON_ACADEMY;
				cloudx=300,cloudy=550,camera_x=0,camera_y=160,cloud_direction=4;
				map_change();
			}
	
		if (ycollision<door_max_y[2] && xcollision+18>door_min_x[2] && ycollision+22>door_min_y[2] && xcollision<door_max_x[2])
			{
				current_map=ALTON_HOUSE;
				cloudx=300,cloudy=160,camera_x=0,camera_y=0,cloud_direction=2;
				map_change();
			}	
			
	
		if (ycollision<door_max_y[3] && xcollision+18>door_min_x[3] && ycollision+22>door_min_y[3] && xcollision<door_max_x[3])
			{
				current_map=ALTON_HOUSE_TWO;
				cloudx=300,cloudy=160,camera_x=0,camera_y=0,cloud_direction=2;
				map_change();
			}	
			
	
		if (ycollision<door_max_y[4] && xcollision+18>door_min_x[4] && ycollision+22>door_min_y[4] && xcollision<door_max_x[4])
			{
				current_map=ALTON_HOUSE_THREE;
				cloudx=300,cloudy=160,camera_x=0,camera_y=0,cloud_direction=2;
				map_change();
			}	
			
		if (ycollision<door_max_y[5] && xcollision+18>door_min_x[5] && ycollision+22>door_min_y[5] && xcollision<door_max_x[5])
			{
				current_map=ALTON_FOREST;
				cloudx=300,cloudy=3100,camera_x=0,camera_y=2720,cloud_direction=4;
				map_change();
			}	
		
}		


if (current_map==ALTON_ACADEMY)
{
		if (ycollision<door_max_y[1] && xcollision+18>door_min_x[1] && ycollision+22>door_min_y[1] && xcollision<door_max_x[1])
			{
				current_map=ALTON_CITY;
				cloudx=1835, cloudy=804, camera_x=1280, camera_y=600, cloud_direction=2;

				map_change();
			}
}


if (current_map==ALTON_HOUSE || current_map==ALTON_HOUSE_TWO || current_map==ALTON_HOUSE_THREE)
{
		if (ycollision<door_max_y[1] && xcollision+18>door_min_x[1] && ycollision+22>door_min_y[1] && xcollision<door_max_x[1])
			{

				if (current_map==ALTON_HOUSE)
				cloudx=1364, cloudy=1100, camera_x=1280, camera_y=800, cloud_direction=4;

				if (current_map==ALTON_HOUSE_TWO)
				cloudx=1590, cloudy=1100, camera_x=1280, camera_y=800, cloud_direction=4;

				if (current_map==ALTON_HOUSE_THREE)
				cloudx=1810, cloudy=1100, camera_x=1280, camera_y=800, cloud_direction=4;


				current_map=ALTON_CITY;
				map_change();
			}



}


if (current_map==ALTON_FOREST)
{
		if (ycollision<door_max_y[1] && xcollision+18>door_min_x[1] && ycollision+22>door_min_y[1] && xcollision<door_max_x[1])
			{
				current_map=ALTON_CITY;
				cloudx=1095, cloudy=40, camera_x=900, camera_y=0, cloud_direction=2;
				map_change();
			}
	
}


}
