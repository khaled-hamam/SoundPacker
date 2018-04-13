#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "SoundPackingLib.h"

bool directoryExists(std::string directory);
void createFolder(std::string name, std::string path);
void copyFile(std::string name, std::string origin, std::string destination);
void generateMetadata(std::vector<Folder> folders, std::string destination);
std::vector<File> parseInput(std::string inputFile);
float parseDurationString(std::string durationString);
