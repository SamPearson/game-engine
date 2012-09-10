


#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <allegro.h>
#include "mapinfo.hpp"

using std::string;
using std::ios;
using std::endl;
using std::ifstream;
using std::ofstream;



int load_map();
int save_map();



int load_map()
{
	int x,y;
	extern int map_tile_db[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES];
	string input_buffer;


	//open the file and read the contents.
	ifstream inFile;
	inFile.open("map_data.txt", ios::in);
	//if we can open the file for reading
	if (inFile.is_open())
	{
		for (y = 0; y < MAP_HEIGHT_IN_TILES; y++)
		{
			for (x = 0; x < MAP_WIDTH_IN_TILES; x++)
			{
			std::getline(inFile, input_buffer, '#');
			map_tile_db[x][y] = atoi(input_buffer.c_str());
			}
		}
		//close the file when you're done with it.
		inFile.close();
	}
	//endif the file could be opened for reading.
	else{}
		//need to put some sort of error message here.
	return 0;
}






int save_map()
{
	int x,y;
	extern int map_tile_db[MAP_WIDTH_IN_TILES][MAP_HEIGHT_IN_TILES];
	//create file object and open the file
	ofstream outFile;
	outFile.open("map_data.txt", ios::out);


	//if we can open the file
	if (outFile.is_open())
	{
		//write whatever to the file
		//make this into a nested for loop. map_tile_db[x][y]
		for (y = 0; y < MAP_HEIGHT_IN_TILES; y++)
		{
			for (x = 0; x < MAP_WIDTH_IN_TILES; x++)
			{
				outFile << map_tile_db[x][y] << '#';
			}
		}

		//close the file when done
		outFile.close();
	}
	else // if the file was not open
		//need to put some sort of error message here.
	//endif the file was open
	return 0;
}
