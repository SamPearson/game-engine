#ifndef	FADEINFADEOUT_HPP
#define	FADEINFADEOUT_HPP 
#endif

//Fade from the current screen to black
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

//use this to fade from black into the bitmap given in argument 1
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
