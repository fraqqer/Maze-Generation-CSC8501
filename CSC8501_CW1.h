#include "SaveManager.h"
#include "Maze.h"

#ifndef CSC8501_CW1_H
#define CSC8501_CW1_H

#define CLEAR_CONSOLE system("CLS");

class Cell;

// Multiple classes need to access this information. These were always intended to be global variables.
extern Cell* currentPosition = nullptr;
extern int MAZE_ROWS = 65535;
extern int MAZE_COLUMNS = 65535;

#endif