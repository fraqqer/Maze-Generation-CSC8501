#ifndef CSC8501_CW1_H
#define CSC8501_CW1_H
class Cell;
struct DirectionX
{
	char NORTH = -1;
	char EAST = 1;
	char SOUTH = 1;
	char WEST = -1;
};

const unsigned int MIN_MAZE_ROWS = 5;
const unsigned int MAX_MAZE_ROWS = 16;
const unsigned int MIN_MAZE_COLUMNS = 5;
const unsigned int MAX_MAZE_COLUMNS = 16;
int MAZE_ROWS = 65535;
int MAZE_COLUMNS = 65535;
Cell* currentPosition = nullptr;
DirectionX dirX;

#endif