#include <algorithm>
#include <iostream>
#include <random>
#include <stack>
#include <time.h>
#include <vector>
#include "CSC8501_CW1.h"
#include "Cell.h"
#include "SaveManager.h"

#define CLEAR_CONSOLE system("CLS");

/*
Polls the user regarding the size of the maze.
*/
void MazeSettings()
{
    do {
        MAZE_ROWS = INT_MAX;
        std::cout << "Please specify the number of rows in the maze (" << MIN_MAZE_ROWS << " ~ " << MAX_MAZE_ROWS << "): ";
        std::cin >> MAZE_ROWS;
    } while (MAZE_ROWS < MIN_MAZE_ROWS || MAZE_ROWS > MAX_MAZE_ROWS);

    do {
        std::cout << "Please specify the number of columns in the maze (" << MIN_MAZE_COLUMNS << " ~ " << MAX_MAZE_COLUMNS << "): ";
        std::cin >> MAZE_COLUMNS;
    } while (MAZE_COLUMNS < MIN_MAZE_COLUMNS || MAZE_COLUMNS > MAX_MAZE_COLUMNS);

    CLEAR_CONSOLE;
}

void DrawMaze(std::vector<Cell*>& cells)
{
    CLEAR_CONSOLE;
    int centerRowIndex = (MAZE_ROWS / 2) - 1;
    int centerColumnIndex = (MAZE_COLUMNS / 2) - 1;
    for (int row = 0; row < MAZE_ROWS; row++)
    {
        for (int column = 0; column < MAZE_COLUMNS; column++)
        {
            int index = (row * MAZE_COLUMNS) + column;
            if (row >= centerRowIndex - 1 && row <= centerRowIndex + 1 && column >= centerColumnIndex - 1 && column <= centerColumnIndex + 1)
            {
                if (row == centerRowIndex && column == centerColumnIndex)
                    cells[index]->SetValue('S');
                else
                    cells[index]->SetValue(' ');
                cells[index]->visited = true;
            }
            std::cout << cells[index]->GetValue();
        }
        std::cout << std::endl;
    }
}

std::vector<Cell*> FilterVisitable(Cell** directions, std::vector<Cell*>& cells, char cellRow, char cellColumn)
{
    std::vector<Cell*> visitable;
    for (int index = 0; index < 4; index++)
    {
        if  ((directions[index]->visited == false) &&
            !(directions[index]->GetRow() < 0 || directions[index]->GetRow() > MAZE_ROWS) &&
            !(directions[index]->GetColumn() < 0 || directions[index]->GetColumn() > MAZE_COLUMNS) &&
            (directions[index]->boundary == false))
        {
            directions[index]->boundary = true;
            switch (index)
            {
            case 0:
                Cell* doubleNorth;
                doubleNorth = cells.at(((cellRow - 2) * MAZE_COLUMNS) + cellColumn);
                if ((doubleNorth->visited == false) && !(doubleNorth->GetRow() < 0 || doubleNorth->GetRow() > MAX_MAZE_ROWS)
                    && !(doubleNorth->GetColumn() < 0 || doubleNorth->GetColumn() > MAX_MAZE_COLUMNS) &&
                    (doubleNorth->boundary == false))
                {
                    visitable.push_back(directions[index]);
                }
                break;
            case 1:
                Cell* doubleEast;
                doubleEast = cells.at((cellRow * MAZE_COLUMNS) + (cellColumn + 2));
                if ((doubleEast->visited == false) && !(doubleEast->GetRow() < 0 || doubleEast->GetRow() > MAX_MAZE_ROWS)
                    && !(doubleEast->GetColumn() < 0 || doubleEast->GetColumn() > MAX_MAZE_COLUMNS) &&
                    (doubleEast->boundary == false))
                {
                    visitable.push_back(directions[index]);
                }
                break;
            case 2:
                Cell* doubleSouth;
                doubleSouth = cells.at(((cellRow + 2) * MAZE_COLUMNS) + cellColumn);
                if ((doubleSouth->visited == false) && !(doubleSouth->GetRow() < 0 || doubleSouth->GetRow() > MAX_MAZE_ROWS)
                    && !(doubleSouth->GetColumn() < 0 || doubleSouth->GetColumn() > MAX_MAZE_COLUMNS) &&
                    (doubleSouth->boundary == false))
                {
                    visitable.push_back(directions[index]);
                }
                break;
            case 3:
                Cell* doubleWest;
                doubleWest = cells.at((cellRow * MAZE_COLUMNS) + (cellColumn - 2));
                if ((doubleWest->visited == false) && !(doubleWest->GetRow() < 0 || doubleWest->GetRow() > MAX_MAZE_ROWS)
                    && !(doubleWest->GetColumn() < 0 || doubleWest->GetColumn() > MAX_MAZE_COLUMNS) &&
                    (doubleWest->boundary == false))
                {
                    visitable.push_back(directions[index]);
                }
                break;
            }
        }
    }

    return visitable;
}

void Visit(std::stack<Cell*>* currentPath, std::vector<Cell*>& cells)
{
    int cellRow = currentPath->size() == 0 ? (MAZE_ROWS / 2) - 1 : currentPosition->GetRow();
    int cellColumn = currentPath->size() == 0 ? (MAZE_COLUMNS / 2) - 1 : currentPosition->GetColumn();
    const unsigned short north = ((cellRow - 1) * MAZE_COLUMNS) + cellColumn;
    const unsigned short east = (cellRow * MAZE_COLUMNS) + (cellColumn + 1);
    const unsigned short south = ((cellRow + 1) * MAZE_COLUMNS) + cellColumn;
    const unsigned short west = (cellRow * MAZE_COLUMNS) + (cellColumn - 1);

    Cell* directions[4];
    directions[0] = cells.at(north);
    directions[1] = cells.at(east);
    directions[2] = cells.at(south);
    directions[3] = cells.at(west);
    std::vector<Cell*> possibleCells = FilterVisitable(directions, cells, cellRow, cellColumn);

    if (!possibleCells.empty() || possibleCells.size() == 1)
    {
        currentPath->push(currentPosition);
        std::default_random_engine dre;
        std::uniform_int_distribution<int> dis(0, possibleCells.size() - 1);
        int randomNumber = dis(dre);

        switch (currentPath->top()->GetRow() - possibleCells[randomNumber]->GetRow())
        {
        case 1: // north
            possibleCells[randomNumber]->SetValue(' ');
            possibleCells[randomNumber]->visited = true;
            currentPath->push(possibleCells[randomNumber]);
            int nSize;
            nSize = ((cellRow - 2) * MAZE_COLUMNS) + cellColumn;
            currentPosition = cells.at(nSize);
            currentPosition->SetValue(' ');
            currentPosition->visited = true;
            break;
        case -1: // south
            possibleCells[randomNumber]->SetValue(' ');
            possibleCells[randomNumber]->visited = true;
            currentPath->push(possibleCells[randomNumber]);
            int size;
            size = ((cellRow + 2) * MAZE_COLUMNS) + cellColumn;
            currentPosition = cells.at(size);
            currentPosition->SetValue(' ');
            currentPosition->visited = true;
            break;
        }

        switch (currentPath->top()->GetColumn() - possibleCells[randomNumber]->GetColumn())
        {
        case 1: // west
            possibleCells[randomNumber]->SetValue(' ');
            possibleCells[randomNumber]->visited = true;
            currentPath->push(possibleCells[randomNumber]);
            int wSize;
            wSize = (cellRow * MAZE_COLUMNS) + (cellColumn - 2);
            currentPosition = cells.at(wSize);
            currentPosition->SetValue(' ');
            currentPosition->visited = true;
            break;
        case -1: // east
            possibleCells[randomNumber]->SetValue(' ');
            possibleCells[randomNumber]->visited = true;
            currentPath->push(possibleCells[randomNumber]);
            currentPosition = cells.at((cellRow * MAZE_COLUMNS) + (cellColumn + 2));
            currentPosition->SetValue(' ');
            currentPosition->visited = true;
            break;
        }
    }
    else
    {
        if (!currentPath->empty())
        {
            currentPosition = currentPath->top();
            currentPath->pop();
        }
    }

    DrawMaze(cells);
    
    if (!currentPath->empty())
        Visit(currentPath, cells);
}

void InitialiseMaze()
{
    unsigned short centerRowIndex = (MAZE_ROWS / 2) - 1;
    unsigned short centerColumnIndex = (MAZE_COLUMNS / 2) - 1;

    std::vector<Cell*> array;
    array.reserve(MAZE_ROWS * MAZE_COLUMNS);

    // recursive backtracking algorithm
    std::stack<Cell*>* coordinates = new std::stack<Cell*>();

    for (unsigned char row = 0; row < MAZE_ROWS; row++)
    {
        for (unsigned char column = 0; column < MAZE_COLUMNS; column++)
        {
            Cell* cell = nullptr;
            if (row == centerRowIndex && column == centerColumnIndex)
                cell = new Cell(column, row, 'S');
            else
                cell = new Cell(column, row, 'X');
            array.push_back(cell);
            std::cout << cell->GetValue();
        }
        std::cout << std::endl;
    }

    Visit(coordinates, array);
}

int main()
{
    if (SaveManager::DetectSaveFile())
    {
        SaveManager::LoadPrompt();
        CLEAR_CONSOLE;
    }

    MazeSettings();
    InitialiseMaze();
}