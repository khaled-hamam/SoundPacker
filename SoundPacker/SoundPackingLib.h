#pragma once
#include <iostream>
#include <string>
#include <vector>

class File {
public:
	std::string name;
	int duration;
};

class Folder {
public:
	std::string name;
	std::vector<File> files;
	int totalDuration;

	int getTotalDuration() {
		int totalFolderDuration = 0;
		for (auto file : files) {
			totalDuration += file.duration;
		}

		return totalFolderDuration;
	}
};

const std::string WORST_FIT_LS		= "Worst Fit Linear Seach";
const std::string WORST_FIT_PQ		= "Worst Fit Priority Queue";
const std::string WORST_FIT_DEC_LS	= "Worst Fit Dec. Linear Search";
const std::string WORST_FIT_DEC_PQ	= "Worst Fit Dec. Priority Queue";
const std::string FIRST_FIT			= "First Fit";
const std::string BEST_FIT			= "Best Fit";
const std::string FOLDER_FILLING	= "Folder Filling";
const std::string MULTITHREADING	= "Multithreading Algorithm";

double runAlgorithm(std::string inputFile, std::string algorithm, float duration, bool allowCopy);