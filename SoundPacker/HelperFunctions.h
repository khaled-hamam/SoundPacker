#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include "SoundPackingLib.h"
using namespace std;

bool directoryExists(string directory);
void createFolder(string name, string path);
void copyFile(string name, string origin, string destination);
void generateMetadata(vector<Folder> folders, string destination);
