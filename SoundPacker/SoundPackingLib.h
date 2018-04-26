#pragma once
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <string>
#include <functional>

class File {
public:
	std::string name;
	int duration;

	File() : name(""), duration(0) {}
	File(std::string name, int duration) : name(name), duration(duration) {}
    
    friend bool operator < (const File& a, const File& b) {
        return a.duration < b.duration;
    }
};

class Folder {
public:
	std::string name;
	std::vector<File> files;
	int totalDuration;

	Folder() : name(""), totalDuration(0) {}

	static std::string getName(int i) {
		std::stringstream ss; ss << i;
		std::string folderNumber;  ss >> folderNumber;
		return 'F' + folderNumber;
	}

	friend bool operator > (const Folder &a, const Folder &b) {
        return a.totalDuration > b.totalDuration;
    }
};


const std::string WORST_FIT_LS		= "Worst Fit Linear Search";
const std::string WORST_FIT_PQ		= "Worst Fit Priority Queue";
const std::string WORST_FIT_DEC_LS	= "Worst Fit Dec. Linear Search";
const std::string WORST_FIT_DEC_PQ	= "Worst Fit Dec. Priority Queue";
const std::string FIRST_FIT			= "First Fit";
const std::string BEST_FIT			= "Best Fit";
const std::string FOLDER_FILLING	= "Folder Filling";
const std::string MULTITHREADING	= "Multithreading Algorithm";


std::vector<Folder> WorstFitLS(std::vector<File> files, int MaxDuration);
std::vector<Folder> WorstFitPQ(std::vector<File> files, int MaxDuration);
std::vector<Folder> worstFitDecreasingLS(std::vector<File> inputFiles, int maxDuration);
std::vector<Folder> worstFitDecreasingPQ(std::vector<File> inputFiles, int maxDuration);
std::vector<Folder> firstFitDecreasingLS(std::vector<File> inputFiles, int maxDuration);
std::vector<Folder> bestFit(std::vector<File>files, int maxDuration);
std::vector<Folder> folderFilling(std::vector<File> files, int maxDuration);
