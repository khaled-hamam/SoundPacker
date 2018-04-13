#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>

class File {
public:
	std::string name;
	float duration;

	File() : name(""), duration(0) {}
	File(std::string name, float duration) : name(name), duration(duration) {}
};

class Folder {
public:
	std::string name;
	std::vector<File> files;
	float totalDuration;

	float getTotalDuration() {
		float totalFolderDuration = 0;
		for (auto file : files) {
			totalDuration += file.duration;
		}

		return totalFolderDuration;
	}

	const friend bool operator>(const Folder &a, const Folder &b);
};




const std::string WORST_FIT_LS = "Worst Fit Linear Seach";
const std::string WORST_FIT_PQ = "Worst Fit Priority Queue";
const std::string WORST_FIT_DEC_LS = "Worst Fit Dec. Linear Search";
const std::string WORST_FIT_DEC_PQ = "Worst Fit Dec. Priority Queue";
const std::string FIRST_FIT = "First Fit";
const std::string BEST_FIT = "Best Fit";
const std::string FOLDER_FILLING = "Folder Filling";
const std::string MULTITHREADING = "Multithreading Algorithm";

// TODO: Put runAlgorithm in HelperFunctions
double runAlgorithm(std::string inputFile, std::string algorithm, float duration, bool allowCopy);

std::vector<Folder> WorstFitLS(std::vector<File> files, int MaxDuration);
std::vector<Folder> WorstFitPQ(std::vector<File> files, int MaxDuration);
std::vector<Folder> worstFitDecreasingLS(std::vector<File> inputFiles, float maxDuration);
std::vector<Folder> worstFitDecreasingPQ(std::vector<File> inputFiles, float maxDuration);
std::vector<Folder> FirstFitDecreasingLS(std::vector<File> inputFiles, float maxDuration);
std::vector<Folder> folderFilling(std::vector<File> files, float maxDuration);