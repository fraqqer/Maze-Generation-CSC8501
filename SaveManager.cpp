#include "SaveManager.h"

bool SaveManager::DetectSaveFile()
{
    std::ifstream fin("maze.txt");

    if (fin.fail() == false)
        fin.close();

    return !fin.fail();
}

bool SaveManager::DetectSaveFile(const char* fileName)
{
    std::ifstream fin(fileName);

    if (fin.fail() == false)
        fin.close();

    return !fin.fail();
}

bool SaveManager::LoadPrompt()
{
    char loadResponse = CHAR_MIN;
    char overwriteResponse = CHAR_MIN;
    std::vector<Cell*> arr;

    do {
        std::cout << "A save file has been detected! Load? (Y/N): ";
        std::cin >> loadResponse;

        // If they wish to load the save file, load here.
        if (toupper(loadResponse) == 'Y')
        {
            CLEAR_CONSOLE;
            arr = SaveManager::LoadSaveFile("Maze.txt");
            Maze::PromptConsole(arr);
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
            {
                break;
            }

        }
    } while (toupper(loadResponse) != 'Y' && toupper(loadResponse) != 'N' || toupper(overwriteResponse) == 'N');

    return false;
}

std::vector<Cell*> SaveManager::LoadSaveFile(const char* fileName)
{
    std::ifstream file(fileName);
    std::vector<Cell*> array;
    if (file.is_open())
    {
        int row = 0;
        for (std::string line; std::getline(file, line); )
        {
            std::cout << line << std::endl;
            for (int column = 0; column < line.length(); column++)
            {
                array.push_back(new Cell(column, row, line[column]));
            }
            MAZE_COLUMNS = line.length();
            row++;
        }
        MAZE_ROWS = row;
    }

    file.close();
    return array;
}

bool SaveFile(const char* fileName, std::vector<Cell*>& cells)
{
    char confirmationResponse = CHAR_MIN;
    std::string name;
    do
    {
        if (std::string(fileName).length() < 6)
        {
            name = "";
            do
            {
                std::cout << "Please enter a valid file name: ";
                std::getline(std::cin, name);            
            } while (name.length() < 0);
        }
        else
        {
            name = std::string(fileName).substr(5, sizeof(fileName));
        }

        std::cout << "This maze will be saved as \'" << name << ".txt\', are you sure? (Y/N): ";
        std::cin >> confirmationResponse;
    } while (toupper(confirmationResponse) != 'Y' && toupper(confirmationResponse) != 'N');

    if (toupper(confirmationResponse) == 'N')
    {
        return false;
    }
    else
    {
        std::string outputName = name + ".txt";
        std::ofstream file(outputName, std::ios::app);

        if (file.is_open())
        {
            for (int row = 0; row < MAZE_ROWS; row++)
            {
                for (int column = 0; column < MAZE_COLUMNS; column++)
                {
                    int index = (row * MAZE_COLUMNS) + column;
                    char value = cells.at(index)->GetValue();
                    const char* ptr = &value;
                    file.write(ptr, 1);
                }
                char value = '\n';
                const char* ptr = &value;
                file.write(ptr, 1);
            }
        }

        file.close();
        std::cout << "\'" << outputName << "\' saved successfully." << std::endl;
        return true;
    }
}