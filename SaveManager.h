#pragma once
#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

class SaveManager
{
public:
	static bool DetectSaveFile();
	static void LoadPrompt();
	static void LoadSaveFile(const char* fileName);
	static void SaveFile(const char* fileName);
};

#endif