#ifndef CELL_H
#define CELL_H
#include "CSC8501_CW1.h"

class Cell
{
private:
	char row;
	char column;
	char value;
public:
	Cell();
	Cell(unsigned int x, unsigned int y, char character)
	{
		column = x;
		row = y;
		value = character;

		if (row == 0 || row == MAZE_ROWS - 1)
			this->boundary = true;
		else if (column == 0 || column == MAZE_COLUMNS - 1)
			this->boundary = true;
		else if (character == 'S')
		{
			currentPosition = this;
			this->visited = true;
		}
	}
	const inline char GetValue() { return value; }
	const inline unsigned char GetColumn() { return column; }
	const inline unsigned char GetRow() { return row; }
	inline void SetValue(char input) { value = input; }
	bool boundary = false;
	bool visited = false;
};

#endif