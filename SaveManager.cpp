#include "SaveManager.h"
#include <fstream>
#include <iostream>
#include <limits>

#define CLEAR_CONSOLE system("CLS");

/*
Determines whether "Maze.txt" exists in the current directory. Checks if it does not exist by using <ifstream>'s fail() function and returns the opposite result signalling whether a file has been detected.

Further work needs to be done in order to make sure it detects any .txt file as a potential save file, most likely through regex or substring.
*/
bool SaveManager::DetectSaveFile()
{
    std::ifstream fin("Maze.txt");

    if (fin.fail() == false)
        fin.close();

    return !fin.fail();
}

void SaveManager::LoadPrompt()
{
    char loadResponse = CHAR_MIN;
    char overwriteResponse = CHAR_MIN;

    do {
        std::cout << "A save file has been detected! Load? (Y/N): ";
        std::cin >> loadResponse;

        // If they wish to load the save file, load here.
        if (toupper(loadResponse) == 'Y')
        {
            CLEAR_CONSOLE;
            SaveManager::LoadSaveFile("Maze.txt");
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
}

/*
Not implemented.
*/
void SaveManager::LoadSaveFile(const char* fileName)
{

    // Attempt to load the file. If the maximum amount of rows or columns are bigger than 30, abort loading and return error.
}

void SaveManager::SaveFile(const char* fileName)
{
    std::ofstream fout(fileName);
    
}