#include <iostream>
#include <random>
#include <stack>
#include <string>
#include <vector>
#include "Cell.h"

#ifndef MAZE_H
#define MAZE_H

#define CLEAR_CONSOLE system("CLS");

extern bool SaveFile(const char* fileName, std::vector<Cell*>& cells);
extern Cell* currentPosition;
extern int MAZE_ROWS;
extern int MAZE_COLUMNS;

int main();

class Maze
{
private:
	static inline bool CheckIfVisitable(Cell** directions, int index)
	{
		return ((directions[index]->visited == false) &&
			!(directions[index]->GetRow() < 0 || directions[index]->GetRow() > MAZE_ROWS) &&
			!(directions[index]->GetColumn() < 0 || directions[index]->GetColumn() > MAZE_COLUMNS) &&
			(directions[index]->boundary == false));
	}
	static void Solve(std::vector<Cell*>& arr);
	static void DrawMaze(std::vector<Cell*>& arr);
	static std::vector<Cell*> FilterVisitable(Cell** directions, std::vector<Cell*>& cells, int cellRow, int cellColumn);
	static void FindExit(std::vector<Cell*>& arr);
	static void Visit(std::stack<Cell*>* currentPath, std::vector<Cell*>& cells);
public:
	static void Initialise();
	static void MazeSettings();
	static void PromptConsole(std::vector<Cell*>& arr);
	static bool Solve(std::vector<Cell*>& arr, std::stack<Cell*>& stack, Cell* startingPosition, Cell* endingPosition, bool exitFound);
	const static unsigned int MIN_MAZE_ROWS = 10;
	const static unsigned int MAX_MAZE_ROWS = 30;
	const static unsigned int MIN_MAZE_COLUMNS = 10;
	const static unsigned int MAX_MAZE_COLUMNS = 30;
};

#endif