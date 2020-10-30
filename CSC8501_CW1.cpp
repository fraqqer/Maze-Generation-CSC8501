#include <iostream>
#include <fstream>
#include <string>

unsigned short MAZE_ROWS = SHRT_MIN;
unsigned short MAZE_COLUMNS = SHRT_MIN;

/*
Determines whether "Maze.txt" exists in the current directory. Checks if it does not exist by using <ifstream>'s fail() function and returns the opposite result signalling whether a file has been detected.

Further work needs to be done in order to make sure it detects any .txt file as a potential save file, most likely through regex or substring.
*/
bool DetectSaveFile()
{
    std::ifstream fin("Maze.txt");

    if (fin.fail() == false)
        fin.close();

    return !fin.fail();
}

/*
Polls the user regarding the size of the maze.
*/
void CreateUserMaze()
{
    const unsigned short MIN_MAZE_ROWS = 5;
    const unsigned short MAX_MAZE_ROWS = 30;
    do {
        std::cout << "Please specify the number of rows in the maze (" << MIN_MAZE_ROWS << " ~ " << MAX_MAZE_ROWS << "): ";
        std::cin >> MAZE_ROWS;
    } while (MAZE_ROWS < MIN_MAZE_ROWS || MAZE_ROWS > MAX_MAZE_ROWS);

    const unsigned short MIN_MAZE_COLUMNS = 5;
    const unsigned short MAX_MAZE_COLUMNS = 30;
    do {
        std::cout << "Please specify the number of columns in the maze (" << MIN_MAZE_COLUMNS << " ~ " << MAX_MAZE_COLUMNS << "): ";
        std::cin >> MAZE_COLUMNS;
    } while (MAZE_COLUMNS < MIN_MAZE_COLUMNS || MAZE_COLUMNS > MAX_MAZE_COLUMNS);
}

// Not implemented.
void Load(const char* fileName)
{
    // Attempt to load the file. If the maximum amount of rows or columns are bigger than 30, abort loading and return error.
    // QUESTION: What is the maximum amount of rows/columns a maze should be able to load?
}

int main()
{
    if (DetectSaveFile())
    {
        char response = CHAR_MIN;
        do {
            std::cout << "A save file has been detected! Load? (Y/N): ";
            std::cin >> response;
        } while (response != 'Y' && response != 'N');

        if (response == 'Y')
            Load("Maze.txt");
    }

    CreateUserMaze();
}

void GenerateMaze()
{
    for (unsigned char row = 0; row <= MAZE_ROWS; row++)
    {
        for (unsigned char column = 0; column <= MAZE_COLUMNS; column++)
        {
            std::cout << 'X';
        }
        std::cout << std::endl;
    }
}

void PollInput()
{

}