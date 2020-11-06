#include "CSC8501_CW1.h"

int main()
{
    bool fileLoaded = false;
    if (SaveManager::DetectSaveFile())
    {
        fileLoaded = SaveManager::LoadPrompt();
        CLEAR_CONSOLE;
    }

    if (!fileLoaded)
    {
        Maze::MazeSettings();
        Maze::Initialise();
    }
}