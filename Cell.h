#ifndef CELL_H
#define CELL_H

extern int MAZE_ROWS;
extern int MAZE_COLUMNS;

class Cell
{
private:
	int row;
	int column;
	int distance;
	char value;
public:
	Cell();
	Cell(unsigned int x, unsigned int y, char character)
	{
		column = x;
		row = y;
		value = character;
		distance = INT_MAX;
		if (row == 0 || row == MAZE_ROWS - 1)
			this->boundary = true;
		else if (column == 0 || column == MAZE_COLUMNS - 1)
			this->boundary = true;
		else if (character == 'S')
		{
			extern Cell* currentPosition;
			currentPosition = this;
			this->visited = true;
		}
	}
	inline char GetValue() { return value; }
	const inline int GetColumn() { return column; }
	const inline int GetRow() { return row; }
	const inline int GetDistance() { return distance; }
	inline void SetValue(char input) { value = input; }
	inline void SetDistance(int dist) { distance = dist; }
	bool boundary = false;
	bool visited = false;
};


#endif