#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Cell.h"
#include "Maze.h"

#define CLEAR_CONSOLE system("CLS");

extern int MAZE_ROWS;
extern int MAZE_COLUMNS;
extern bool SaveFile(const char* fileName, std::vector<Cell*>& cells);
class SaveManager
{
public:
	static bool DetectSaveFile();
	static bool DetectSaveFile(const char* fileName);
	static std::vector<Cell*> LoadSaveFile(const char* fileName);
	static bool LoadPrompt();
};

#endif