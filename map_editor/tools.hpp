
# ifndef TOOLS_HPP_
# define TOOLS_HPP_



//mouse states
#define	DRAWING	1
#define	COPYTOOL	2
#define	FILLRANGE	3		


//int draw_grid(int lowest_x, int lowest_y, int highest_x, int highest_y, int tile_size, BITMAP *bitmap, int color);
//int draw_grid(int lowest_x, int lowest_y, int highest_x, int highest_y, int tile_size, BITMAP *bitmap, int color)
//{
//	int cntx, cnty;
//	for (cntx = lowest_x ; cntx <= highest_x ; cntx += tile_size)
//	{
//	 	line( bitmap, cntx, lowest_y, cntx, highest_y, color);
//		for (cnty = lowest_y ; cnty <= highest_y; cnty += tile_size)
//		{
//		 	line(bitmap, lowest_x, cnty, highest_x, cnty, color);
//		}
//	}
//	line(bitmap, highest_x, lowest_y, highest_x, highest_y, color);
//	line(bitmap, lowest_x, highest_y, highest_x, highest_y, color);
//	return 0;
//}

















#endif /*TOOLS_HPP_*/

