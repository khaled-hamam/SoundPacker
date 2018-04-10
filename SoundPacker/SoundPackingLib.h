#pragma once
#include <string>
using namespace std;

class File {
public:
	string name;
	int duration;
};

class Folder {
public:
	string name;
	vector<File> files;
	int totalDuration;

	int getTotalDuration() {
		int totalFolderDuration = 0;
		for (auto file : files) {
			totalDuration += file.duration;
		}

		return totalFolderDuration;
	}
};

const string WORST_FIT_LS		= "WORST_FIT_LS";
const string WORST_FIT_PQ		= "WORST_FIT_PQ";
const string WORST_FIT_DEC_LS	= "WORST_FIT_DEC_LS";
const string WORST_FIT_DEC_PQ	= "WORST_FIT_DEC_PQ";
const string FIRST_FIT			= "FIRST_FIT";
const string BEST_FIT			= "BEST_FIT";
const string MULTITHREADING		= "MULTITHREADING";
