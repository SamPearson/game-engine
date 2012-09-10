
extern int door_min_x[10],door_min_y[10],door_max_x[10],door_max_y[10];
extern int n;
extern int cloudx,cloudy;
extern int sleep_time, framesps;
void debug_drawdoors()
{


 //draw all the doors
 for (n=0;n<10;n++)
  {
	rect (sprite_layer,door_min_x[n],door_min_y[n],door_max_x[n],door_max_y[n],makecol(4,248,2));	
  }	
//draw all the collision boxes	
  for (n=1;n<1000;n++)
  {
	rectfill (sprite_layer,object_min_x[n],object_min_y[n],object_max_x[n],object_max_y[n],makecol(255,255,255));
  }
	
}

 void debug_textwindow()
 {
	textprintf_ex(screen, font, 0, 10, makecol(255,255,255), makecol(0,0,0), "sleep time: %i", sleep_time);
	textprintf_ex(screen, font, 0, 20, makecol(255,255,255), makecol(0,0,0), "frames per second: %i", framesps);
	textprintf_ex(screen, font, 0, 30, makecol(255,255,255), makecol(0,0,0), "cloudx: %i", cloudx);
	textprintf_ex(screen, font, 0, 40, makecol(255,255,255), makecol(0,0,0), "cloudy: %i", cloudy);
 	
}
