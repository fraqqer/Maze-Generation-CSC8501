#include "Maze.h"

/*
An initialisation method used prior to the recursive DFS method.
*/
void Maze::Solve(std::vector<Cell*>& arr)
{
    Cell* startingPosition = nullptr;
    Cell* endingPosition = nullptr;
    std::stack<Cell*> dfsStack;

    for (int row = 0; row < MAZE_ROWS; row++)
    {
        for (int column = 0; column < MAZE_COLUMNS; column++)
        {
            int index = (row * MAZE_COLUMNS) + column;
            arr.at(index)->visited = false;

            if (arr.at(index)->GetValue() == 'X')            // If the value is a wall, it is not traversable.
                arr.at(index)->visited = true;
            else if (arr.at(index)->GetValue() == 'S')       // If the value is at the start, reference it and say we have traversed since that'll be where we're starting.
            {
                startingPosition = arr.at(index);
                startingPosition->visited = true;
                dfsStack.push(startingPosition);
            }
            else if (arr.at(index)->GetValue() == 'E')       // If the value is at the end, reference it.
                endingPosition = arr.at(index);
        }
    }
    bool exitFound = false;
    Maze::Solve(arr, dfsStack, startingPosition, endingPosition, exitFound);
}

/*
A depth-first search algorithm used to solve mazes. (Source: https://www.programiz.com/dsa/graph-dfs)
*/
bool Maze::Solve(std::vector<Cell*>& arr, std::stack<Cell*>& stack, Cell* startingPosition, Cell* endingPosition, bool exitFound)
{
    // Check for visitable
    int cellRow = currentPosition->GetRow();
    int cellColumn = currentPosition->GetColumn();
    const unsigned short north = ((cellRow - 1) * MAZE_COLUMNS) + cellColumn;
    const unsigned short east = (cellRow * MAZE_COLUMNS) + (cellColumn + 1);
    const unsigned short south = ((cellRow + 1) * MAZE_COLUMNS) + cellColumn;
    const unsigned short west = (cellRow * MAZE_COLUMNS) + (cellColumn - 1);

    std::vector<Cell*> visitable;
    if (arr.at(north)->GetValue() == 'E' || arr.at(east)->GetValue() == 'E' || arr.at(south)->GetValue() == 'E' || arr.at(west)->GetValue() == 'E')
        exitFound = true;
    else
    {
        visitable.push_back(arr.at(north));
        visitable.push_back(arr.at(east));
        visitable.push_back(arr.at(south));
        visitable.push_back(arr.at(west));
    }

    for (int i = 0; i < visitable.size(); i++)
    {
        if ((!visitable[i]->visited) && (!exitFound))
        {
            currentPosition = visitable[i];
            currentPosition->visited = true;
            stack.push(currentPosition);
            Maze::Solve(arr, stack, startingPosition, endingPosition, exitFound);
            
            if (stack.size() != 0)
                stack.pop();
        }

    }

    if (exitFound)
    {
        while (stack.size() != 0)
        {
            stack.top()->SetValue('o');
            DrawMaze(arr);
            stack.pop();
        }
    }
    return false;
}

void Maze::FindExit(std::vector<Cell*>& arr)
{
    bool exitSet = false;
    int mode = rand() % 4;
    while (exitSet == false)
    {
        for (int row = 0; row < MAZE_ROWS; row++)
        {
            for (int column = 0; column < MAZE_COLUMNS; column++)
            {
                int index = (row * MAZE_COLUMNS) + column;

                switch (mode)
                {
                case 0:
                    int bottomIndex;
                    bottomIndex = index + (MAZE_ROWS + 1);

                    if (bottomIndex >= 0 && bottomIndex < MAX_MAZE_ROWS)
                        if (arr.at(index)->GetRow() == 0 && arr.at(index)->GetValue() == ' ')
                        {
                            arr.at(index)->SetValue('E');
                            Maze::DrawMaze(arr);
                            exitSet = true;
                        }
                    break;
                case 1:
                    int topIndex;
                    topIndex = index - MAZE_ROWS;

                    if (topIndex >= 0)
                        if ((arr.at(index)->GetRow() == MAZE_ROWS - 1) && arr.at(topIndex)->GetValue() == ' ')
                        {
                            arr.at(index)->SetValue('E');
                            Maze::DrawMaze(arr);
                            exitSet = true;
                        }
                    break;
                case 2:
                    int rightIndex;
                    rightIndex = index + 1;

                    if (rightIndex >= 0)
                        if ((arr.at(index)->GetColumn() == 0) && (arr.at(rightIndex)->GetValue() == ' '))
                        {
                            arr.at(index)->SetValue('E');
                            Maze::DrawMaze(arr);
                            exitSet = true;
                        }
                    break;
                case 3:
                    int leftIndex;
                    leftIndex = index - 1;

                    if (leftIndex >= 0)
                        if ((arr.at(index)->GetColumn() == MAZE_COLUMNS - 1) && (arr.at(leftIndex)->GetValue() == ' '))
                        {
                            arr.at(index)->SetValue('E');
                            Maze::DrawMaze(arr);
                            exitSet = true;
                        }
                    break;
                }

                if (exitSet)
                    break;
            }
            if (exitSet)
                break;
        }
        mode = rand() % 4;
    }
}

void Maze::PromptConsole(std::vector<Cell*>& arr)
{
    std::string response;
    bool fileSaved = false;
    do
    {
        std::cout << "> ";
        getline(std::cin, response);

        // Parse arguments
        if (std::string(response).substr(0, 4) == "save")
            fileSaved = SaveFile(response.c_str(), arr);
        else if (std::string(response).substr(0, 7) == "restart")
            main();
    } while (std::string(response).substr(0, 4) != "exit");
}

void Maze::Initialise()
{
    unsigned short centerRowIndex = (MAZE_ROWS / 2) - 1;
    unsigned short centerColumnIndex = (MAZE_COLUMNS / 2) - 1;

    std::vector<Cell*> maze;
    int arrIndex = MAZE_ROWS * MAZE_COLUMNS;
    maze.reserve(arrIndex);

    // Recursive backtracking algorithm
    std::stack<Cell*>* coordinates = new std::stack<Cell*>();

    // Create and output a grid with the starting position at the center and walls everywhere else.
    for (unsigned char row = 0; row < MAZE_ROWS; row++)
    {
        for (unsigned char column = 0; column < MAZE_COLUMNS; column++)
        {
            Cell* cell = nullptr;
            if (row == centerRowIndex && column == centerColumnIndex)
                cell = new Cell(column, row, 'S');
            else
                cell = new Cell(column, row, 'X');
            maze.push_back(cell);
            std::cout << cell->GetValue();
        }
        std::cout << std::endl;
    }

    Visit(coordinates, maze);
    Maze::FindExit(maze);
    Solve(maze);
    Maze::PromptConsole(maze);
}

void Maze::MazeSettings()
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

void Maze::DrawMaze(std::vector<Cell*>& cells)
{
    CLEAR_CONSOLE;
    int centerRowIndex = (MAZE_ROWS / 2) - 1;
    int centerColumnIndex = (MAZE_COLUMNS / 2) - 1;
    for (int row = 0; row < MAZE_ROWS; row++)
    {
        for (int column = 0; column < MAZE_COLUMNS; column++)
        {
            int index = (row * MAZE_COLUMNS) + column; // Index in the vector.

            // Starting room logic.
            if (row >= centerRowIndex - 1 && row <= centerRowIndex + 1 && column >= centerColumnIndex - 1 && column <= centerColumnIndex + 1)
            {
                if (row == centerRowIndex && column == centerColumnIndex)
                    cells[index]->SetValue('S');
                else if (cells[index]->GetValue() != 'o') // If a path from the exit has appeared, overwrite the empty space.
                    cells[index]->SetValue(' ');
                cells[index]->visited = true;
            }
            std::cout << cells[index]->GetValue();
        }
        std::cout << std::endl;
    }
}

/*
This is the recursive method of the 'recursive backtracking algorithm' used to generate mazes.
*/
void Maze::Visit(std::stack<Cell*>* currentPath, std::vector<Cell*>& cells)
{
    // If the stack has not been initialised, start from the center of the maze.
    int cellRow = currentPath->size() == 0 ? (MAZE_ROWS / 2) - 1 : currentPosition->GetRow();
    int cellColumn = currentPath->size() == 0 ? (MAZE_COLUMNS / 2) - 1 : currentPosition->GetColumn();
    const unsigned short north = ((cellRow - 1) * MAZE_COLUMNS) + cellColumn;
    const unsigned short east = (cellRow * MAZE_COLUMNS) + (cellColumn + 1);
    const unsigned short south = ((cellRow + 1) * MAZE_COLUMNS) + cellColumn;
    const unsigned short west = (cellRow * MAZE_COLUMNS) + (cellColumn - 1);

    // Find neighbouring cells
    Cell* neighbours[4];
    neighbours[0] = cells.at(north);
    neighbours[1] = cells.at(east);
    neighbours[2] = cells.at(south);
    neighbours[3] = cells.at(west);
    std::vector<Cell*> possibleCells = FilterVisitable(neighbours, cells, cellRow, cellColumn);

    // If there are neighbours that are possible to visit
    if (!possibleCells.empty())
    {
        // Save the current position, then randomly choose a direction to go in.
        currentPath->push(currentPosition);
        int randomNumber = rand() % possibleCells.size();

        // Checks whether there is a difference between the current row and the possible row. If it is above the current position, it will be 1.
        // Otherwise, it will be -1.
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
            int sSize;
            sSize = ((cellRow + 2) * MAZE_COLUMNS) + cellColumn;
            currentPosition = cells.at(sSize);
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
            int eSize;
            eSize = (cellRow * MAZE_COLUMNS) + (cellColumn + 2);
            currentPosition = cells.at(eSize);
            currentPosition->SetValue(' ');
            currentPosition->visited = true;
            break;
        }
    }
    else // If there are no possible cells to visit
    {
        if (!currentPath->empty()) // If the stack is not empty, change the current position to the top and pop it.
        {
            currentPosition = currentPath->top();
            currentPath->pop();
        }
    }

    // Refresh the console by drawing a new maze whenever a change has happened.
    Maze::DrawMaze(cells);

    // Backtrack.
    if (!currentPath->empty())
        Visit(currentPath, cells);
}

/*
Loop over every neighbouring cell, check if the cell in front of the neighbouring cell is visitable. If it is, add it to the visitable list.
*/
std::vector<Cell*> Maze::FilterVisitable(Cell** directions, std::vector<Cell*>& cells, int cellRow, int cellColumn)
{
    std::vector<Cell*> visitable;
    for (int index = 0; index < 4; index++)
    {
        if (CheckIfVisitable(directions, index))
        {
            directions[index]->visited = true;
            switch (index)
            {
            case 0:
                Cell * doubleNorth;
                int nnIndex;
                nnIndex = ((cellRow - 2) * MAZE_COLUMNS) + cellColumn;
                doubleNorth = cells.at(nnIndex);
                if ((doubleNorth->visited == false) && !(doubleNorth->GetRow() < 0 || doubleNorth->GetRow() > MAX_MAZE_ROWS)
                    && !(doubleNorth->GetColumn() < 0 || doubleNorth->GetColumn() > MAX_MAZE_COLUMNS) &&
                    (doubleNorth->boundary == false))
                {
                    visitable.push_back(directions[index]);
                }
                break;
            case 1:
                Cell * doubleEast;
                int eeIndex;
                eeIndex = (cellRow * MAZE_COLUMNS) + (cellColumn + 2);
                doubleEast = cells.at(eeIndex);
                if ((doubleEast->visited == false) && !(doubleEast->GetRow() < 0 || doubleEast->GetRow() > MAX_MAZE_ROWS)
                    && !(doubleEast->GetColumn() < 0 || doubleEast->GetColumn() > MAX_MAZE_COLUMNS) &&
                    (doubleEast->boundary == false))
                {
                    visitable.push_back(directions[index]);
                }
                break;
            case 2:
                Cell * doubleSouth;
                int ssIndex;
                ssIndex = ((cellRow + 2) * MAZE_COLUMNS) + cellColumn;
                doubleSouth = cells.at(ssIndex);
                if ((doubleSouth->visited == false) && !(doubleSouth->GetRow() < 0 || doubleSouth->GetRow() > MAX_MAZE_ROWS)
                    && !(doubleSouth->GetColumn() < 0 || doubleSouth->GetColumn() > MAX_MAZE_COLUMNS) &&
                    (doubleSouth->boundary == false))
                {
                    visitable.push_back(directions[index]);
                }
                break;
            case 3:
                Cell * doubleWest;
                int wwIndex;
                wwIndex = (cellRow * MAZE_COLUMNS) + (cellColumn - 2);
                doubleWest = cells.at(wwIndex);
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
