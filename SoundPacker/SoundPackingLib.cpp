#include "stdafx.h"
#include "SoundPackingLib.h"
 
using namespace std;
using namespace System;
using namespace System::Diagnostics;

bool compareFunction(File i, File j) { return (i.duration < j.duration); }

double runAlgorithm(string inputFile, string algorithm, float duration, bool allowCopy) {
	
	return 0;
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
		} else {
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
		} else {
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
		if (!k){
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
				if (!i){
					dp[i][j] = 0;
				} else if (duration <= j && dp[i - 1][j] < duration + dp[i - 1][j - duration]){
					dp[i][j] = duration + dp[i - 1][j - duration];
					store[i][j] = true;
				} else {
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


