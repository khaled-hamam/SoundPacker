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

bool compareFunction(File i, File j) { return (i.duration < j.duration); }

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

vector<Folder> worstFitDecreasingLS(vector<File> inputFiles, float maxDuration)
{
	sort(inputFiles.rbegin(), inputFiles.rend(), compareFunction);
	vector<Folder> myFolders;
	Folder fisrtFolder;
	fisrtFolder.totalDuration = 0;
	myFolders.push_back(fisrtFolder);
	for (int i = 0; i < inputFiles.size(); i++) {
		int wstidx = -1;
		int max = -1;
		for (int j = 0; j < myFolders.size(); j++) {
			if (maxDuration - myFolders[j].totalDuration >= inputFiles[i].duration) {
				if (maxDuration - myFolders[j].totalDuration > max) {
					max = maxDuration - myFolders[j].totalDuration;
					wstidx = j;
				}
			}
		}
		if (wstidx != -1) {
			myFolders[wstidx].files.push_back(inputFiles[i]);
			myFolders[wstidx].totalDuration += inputFiles[i].duration;
		}
		else {
			Folder newFolder;
			newFolder.totalDuration = inputFiles[i].duration;
			myFolders.push_back(newFolder);
		}
	}
	return myFolders;
}

vector<Folder> worstFitDecreasingPQ(vector<File> inputFiles, float maxDuration)
{
	priority_queue < Folder, vector<Folder>, greater<Folder> > myFolderspq;
	sort(inputFiles.rbegin(), inputFiles.rend(), compareFunction); // O(N Log N)
	Folder fisrtFolder;
	fisrtFolder.totalDuration = 0;
	myFolderspq.push(fisrtFolder); // O(Log M)
	Folder temp;
	for (int i = 0; i < inputFiles.size(); i++) {
		if (inputFiles[i].duration <= (maxDuration - myFolderspq.top().totalDuration)) {
			temp = myFolderspq.top(); //O(1)
			temp.files.push_back(inputFiles[i]); // O(1)
			temp.totalDuration += inputFiles[i].duration; // O(1)
			myFolderspq.pop(); // O(log M)
			myFolderspq.push(temp); // O(Log M)
		}
		else {
			temp.totalDuration = inputFiles[i].duration;;
			temp.files.push_back(inputFiles[i]); // O(1)
			myFolderspq.push(temp); //O(Log M)
		}
	}
	vector<Folder> myFolders;
	for (int i = 0; i < myFolderspq.size(); i++) {
		myFolders.push_back(myFolderspq.top()); // O(1)
		myFolderspq.pop(); // O(log M)
	}
	return myFolders;
}

vector<Folder> FirstFitDecreasingLS(vector<File> inputFiles, float maxDuration)
{
	vector<Folder> myFolders;
	for (int i = 0; i < inputFiles.size(); i++) {
		int k = 0;
		for (int j = 0; j < myFolders.size(); j++) {
			if ((maxDuration - myFolders[j].totalDuration) >= inputFiles[i].duration) {
				myFolders[j].files.push_back(inputFiles[i]);
				myFolders[j].totalDuration += inputFiles[i].duration;
				k = 1;
				break;
			}
		}
		if (!k) {
			Folder folder;
			folder.files.push_back(inputFiles[i]);
			folder.totalDuration = inputFiles[i].duration;
			myFolders.push_back(folder);
		}
	}
	return myFolders;
}
int dp[10001][351];
bool store[10001][351];
vector<Folder> folderFilling(vector<File> files, float maxDuration)
{
	vector<Folder> folders;
	while (!files.empty()) {
		memset(dp, -1, sizeof dp);
		memset(store, 0, sizeof store);
		Folder folder;
		for (int i = 0; i <= files.size(); i++) {
			for (int j = 0; j <= maxDuration; j++) {
				int duration = files[i - 1].duration;
				if (!i) {
					dp[i][j] = 0;
				}
				else if (duration <= j && dp[i - 1][j] < duration + dp[i - 1][j - duration]) {
					dp[i][j] = duration + dp[i - 1][j - duration];
					store[i][j] = true;
				}
				else {
					dp[i][j] = dp[i - 1][j];
					store[i][j] = false;
				}
			}
		}
		cout << dp[files.size()][(int)maxDuration] << endl;
		int j = maxDuration;
		for (int i = files.size(); i >= 1; i--) {
			if (store[i][j]) {
				folder.files.push_back(files[i - 1]);
				j -= files[i - 1].duration;
				files.erase(files.begin() + (i - 1));
			}
		}

		folders.push_back(folder);
	}
	return folders;
}

