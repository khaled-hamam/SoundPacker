#pragma once
#include "SoundPackingLib.h"

double runAlgorithm(std::string inputFile, std::string algorithm, int duration, bool allowCopy, bool multithreading);
bool directoryExists(std::string directory);
void createFolder(std::string name, std::string path);
void copyFile(std::string name, std::string origin, std::string destination);
void generateMetadata(std::vector<Folder> folders, std::string destination);
std::vector<File> parseInput(std::string inputFile);
int parseDurationString(std::string durationString);