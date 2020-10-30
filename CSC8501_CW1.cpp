#include <cctype>
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

    system("CLS");
}

// Not implemented.
void Load(const char* fileName)
{
    // Attempt to load the file. If the maximum amount of rows or columns are bigger than 30, abort loading and return error.
}

void GenerateMaze()
{
    unsigned short rowCenter = MAZE_ROWS / 2;
    unsigned short columnCenter = MAZE_COLUMNS / 2;

    for (unsigned char row = 0; row < MAZE_ROWS; row++)
    {
        for (unsigned char column = 0; column < MAZE_COLUMNS; column++)
        {
            // Starting cell
            if (row == rowCenter && column == columnCenter)
            {
                std::cout << 'S';
            }
            else
            {
                if (row >= rowCenter - 1 && row <= rowCenter + 1 && column >= columnCenter - 1 && column <= columnCenter + 1)
                    std::cout << ' ';
                else
                    std::cout << 'X';
            }
        }
        std::cout << std::endl;
    }
}

int main()
{
    if (DetectSaveFile())
    {
        char loadResponse = CHAR_MIN;
        char overwriteResponse = CHAR_MIN;

        do {
            std::cout << "A save file has been detected! Load? (Y/N): ";
            std::cin >> loadResponse;

            // If they wish to load the save file, load here.
            if (toupper(loadResponse) == 'Y')
            {
                Load("Maze.txt");
                break;
            }
            // Otherwise, ask them if they are sure.
            else
            {
                do {
                    std::cout << "The current save file will be overwritten, are you sure? (Y/N): ";
                    std::cin >> overwriteResponse;
                } while (toupper(overwriteResponse) != 'Y' && toupper(overwriteResponse) != 'N');

                // If they are sure, overwrite the save file. Otherwise, continue.
                if (toupper(overwriteResponse) == 'Y')
                    break;
            }
        } while (toupper(loadResponse) != 'Y' && toupper(loadResponse) != 'N' || toupper(overwriteResponse) == 'N');

        system("CLS");
    }

    CreateUserMaze();
    GenerateMaze();
}

void PollInput()
{

}