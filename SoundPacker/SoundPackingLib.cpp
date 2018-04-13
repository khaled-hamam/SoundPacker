#include "stdafx.h"
#include "SoundPackingLib.h"
#include "HelperFunctions.h"

using namespace std;
using namespace System;
using namespace System::Diagnostics;

double runAlgorithm(string inputFile, string algorithm, float duration, bool allowCopy) {
	// Reading the Input File and Parsing the input to vector<File>
	vector<File> inputFiles = parseInput(inputFile);

	// TODO: Calculating the Running Time of the Algorithm
	vector<Folder> resultFolders;
	if (algorithm == WORST_FIT_LS) {
		resultFolders = WorstFitLS(inputFiles, duration);
	} else if (algorithm == WORST_FIT_PQ) {
		resultFolders = WorstFitPQ(inputFiles, duration);
	} else {
		return -1;
	}

	// TODO: Generating the Metadata file
	// TODO: Copy the files to the destination folder if allowCopy == true
	
	return 0;
}

const bool operator>(const Folder &a, const Folder &b) {
	return a.totalDuration > b.totalDuration;
}

std::vector<Folder> WorstFitLS(std::vector<File> files, int MaxDuration) {
	vector<Folder>folders;

	for (int i = 0; i < files.size(); i++) {
		int index = -1;
		int Max = -1;
		for (int j = 0; j < folders.size(); j++) {
			if (folders.empty()) {
				folders.push_back(Folder());
			}

			if (MaxDuration - folders[j].getTotalDuration() >= files[i].duration) {
				if (MaxDuration - folders[j].getTotalDuration()>Max) {
					Max = MaxDuration - folders[j].getTotalDuration();
					index = j;
				}
			}
		}
		if (index == -1) {
			folders.push_back(Folder());
		} else {
			folders[index].files.push_back(files[i]);
			folders[index].totalDuration += files[i].duration;
		}
	}

	return folders;
}

std::vector<Folder> WorstFitPQ(std::vector<File> files, int MaxDuration) {
	std::priority_queue<Folder, vector<Folder>, greater<Folder> >folders;

	for (int i = 0; i < files.size(); i++) {
		if (folders.empty()) {
			Folder F;
			folders.push(F);
		}

		if (MaxDuration - folders.top().totalDuration >= files[i].duration) {
			Folder temp = folders.top();
			folders.pop();
			temp.files.push_back(files[i]);
			temp.totalDuration += files[i].duration;
			folders.push(temp);
		} else {
			folders.push(Folder());
		}
	}

	vector<Folder>folder;
	while (!folders.empty()) {
		folder.push_back(folders.top());
		folders.pop();
	}

	return folder;
}
