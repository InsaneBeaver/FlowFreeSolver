#ifndef __SRC_GRID
#define __SRC_GRID
#include "square.h"
#include <iostream>
#include <fstream>
#include "assert.h"
#include <string>
#include <cctype>
#include <algorithm>

#define LOGGING
#define LOGFILEPATH "grids.txt"



struct GridInfo
{
	coordinate size;
	square_color number_of_colors;
	coordinate *** sources;
};

using namespace std;

class Grid
{
public:
	Grid(coordinate _size);
	Grid(square_color** grid, coordinate size);
	Grid(square_color** _grid, coordinate _size, Square * (*factory) (coordinate, coordinate, square_color, Square* [2]));
	~Grid();
	
	void print();
	coordinate getSize();
	square_color getNumberOfColors();
	Square* getSquare(coordinate x, coordinate y);
	Square** getSources(square_color color);
	
	
protected:
	Square*** grid; 
	square_color** originalgrid;
	square_color number_of_colors;
	coordinate size;
	Square*** sources;
	
	void setSources(square_color color, Square* first_source, Square* second_source); // Can only be called from a child for obvious reasons
	

};

square_color** generateEmptyGrid(coordinate _size);
void deleteGrid(square_color** grid, coordinate size);
void printGrid(square_color** grid, coordinate size);
uint64_t reducegrid(square_color ** grid, coordinate size);
GridInfo * readfen(string fen);

#ifdef LOGGING
void logGrid(square_color** grid, coordinate size);
void openlogfile();
void closelogfile();
#endif

#endif