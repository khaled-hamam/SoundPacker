#include "stdafx.h"
#include "SoundPackingLib.h"
#include "HelperFunctions.h"

using namespace std;
using namespace System;
using namespace System::Diagnostics;

const bool operator>(const Folder &a, const Folder &b) {
	return a.totalDuration > b.totalDuration;
}

bool compareFunction(File a, File b) { 
	return a.duration < b.duration; 
}

vector<Folder> WorstFitLS(vector<File> files, int maxDuration) {
	vector<Folder>folders;

	
	for (int i = 0; i < files.size(); i++) {
		int index = -1;
		int Max = -1;
		for (int j = 0; j < folders.size(); j++) {
			if (maxDuration - folders[j].totalDuration >= files[i].duration) {
				if (maxDuration - folders[j].totalDuration>Max) {
					Max = maxDuration - folders[j].totalDuration;
					index = j;
				}
			}
		}
		if (index == -1) {
			folders.push_back(Folder());
			folders[folders.size() - 1].files.push_back(files[i]);
			folders[folders.size() - 1].totalDuration += files[i].duration;
		} else {
			folders[index].files.push_back(files[i]);
			folders[index].totalDuration += files[i].duration;
		}
	}

	return folders;
}

vector<Folder> WorstFitPQ(vector<File> files, int maxDuration) {
	std::priority_queue<Folder, vector<Folder>, greater<Folder> >folders;

	for (int i = 0; i < files.size(); i++) {
		if (folders.empty()) {
			folders.push(Folder());
			Folder temp = folders.top();
			folders.pop();
			temp.files.push_back(files[i]);
			temp.totalDuration += files[i].duration;
			folders.push(temp);
		}

		else if (maxDuration - folders.top().totalDuration >= files[i].duration) {
			Folder temp = folders.top();
			folders.pop();
			temp.files.push_back(files[i]);
			temp.totalDuration += files[i].duration;
			folders.push(temp);
		} else {
			folders.push(Folder());
			Folder temp = folders.top();
			folders.pop();
			temp.files.push_back(files[i]);
			temp.totalDuration += files[i].duration;
			folders.push(temp);
		}
	}

	vector<Folder>folder;
	while (!folders.empty()) {
		folder.push_back(folders.top());
		folders.pop();
	}

	return folder;
}

vector<Folder> worstFitDecreasingLS(vector<File> inputFiles, int maxDuration) {
	sort(inputFiles.rbegin(), inputFiles.rend(), compareFunction);
	vector<Folder>folders;
	for (int i = 0; i < inputFiles.size(); i++) {
		int index = -1;
		int Max = -1;
		for (int j = 0; j < folders.size(); j++) {
			if (maxDuration - folders[j].totalDuration >= inputFiles[i].duration) {
				if (maxDuration - folders[j].totalDuration>Max) {
					Max = maxDuration - folders[j].totalDuration;
					index = j;
				}
			}
		}
		if (index == -1) {
			folders.push_back(Folder());
			folders[folders.size() - 1].files.push_back(inputFiles[i]);
			folders[folders.size() - 1].totalDuration += inputFiles[i].duration;
		}
		else {
			folders[index].files.push_back(inputFiles[i]);
			folders[index].totalDuration += inputFiles[i].duration;
		}
	}

	return folders;
}

vector<Folder> worstFitDecreasingPQ(vector<File> inputFiles, int maxDuration) {
	priority_queue < Folder, vector<Folder>, greater<Folder> > myFolderspq;
	sort(inputFiles.rbegin(), inputFiles.rend(), compareFunction); // O(N Log N)
	Folder fisrtFolder;
	fisrtFolder.totalDuration = 0;
	myFolderspq.push(fisrtFolder); // O(Log M)
	for (int i = 0; i < inputFiles.size(); i++) {
		Folder temp;
		if (inputFiles[i].duration <= (maxDuration - myFolderspq.top().totalDuration)) {
			temp = myFolderspq.top(); //O(1)
			myFolderspq.pop(); // O(log M)
			temp.files.push_back(inputFiles[i]); // O(1)
			temp.totalDuration += inputFiles[i].duration; // O(1)
			myFolderspq.push(temp); // O(Log M)
		}
		else {
			temp.totalDuration = inputFiles[i].duration;
			temp.files.push_back(inputFiles[i]); // O(1)
			myFolderspq.push(temp); //O(Log M)
		}
	}
	vector<Folder> myFolders;
	while (!myFolderspq.empty()) {
		myFolders.push_back(myFolderspq.top()); // O(1)
		myFolderspq.pop(); // O(log M)
	}
	return myFolders;
}


vector<Folder> firstFitDecreasingLS(vector<File> inputFiles, int maxDuration) {
	vector<Folder> myFolders;
	sort(inputFiles.rbegin(), inputFiles.rend(), compareFunction); // O(N Log N)
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
vector<Folder> bestFit(vector<File>files, int maxDuration){
	
	vector<Folder>folders;
	
	for (int i = 0; i < files.size(); i++){
		int bestDurationInd = -1;
		for (int j = 0; j < folders.size(); j++){
			
			int curDuration = maxDuration-folders[j].totalDuration;
			
			if (files[i].duration <= curDuration ){
				
				if (bestDurationInd==-1){
					bestDurationInd = j;
				}
				else {
					if (folders[j].totalDuration < curDuration ){
						bestDurationInd = j;
					}
				}
			}
		}

		if (bestDurationInd==-1){
			Folder folder;
			folder.totalDuration = 0;
			folder.totalDuration += files[i].duration;
			folder.files.push_back(files[i]);
			folders.push_back(folder);
		}
		else {
			folders[bestDurationInd].totalDuration += files[i].duration;
			folders[bestDurationInd].files.push_back(files[i]);

		}
		
	}
	return folders;
}
int dp[10001][351];
bool store[10001][351];
vector<Folder> folderFilling(vector<File> files, int maxDuration){
	
		vector<Folder> folders;
		while(!files.empty()){
			
			memset(dp, -1, sizeof dp);
			memset(store, 0, sizeof store);

			Folder folder;
	
			 for (int i=0; i <= files.size(); i++){ 
				for (int j=0; j <= maxDuration; j++){
						int duration = 0;
						if (!i)
						{
							dp[i][j] = 0;
						}	
						else {
							duration = files[i - 1].duration;

							if (duration <= j && dp[i - 1][j] < duration + dp[i - 1][j - duration])
							{
								dp[i][j] = duration + dp[i - 1][j - duration];
								store[i][j] = true;
							}
							else {
								dp[i][j] = dp[i - 1][j];
								store[i][j] = false;
							}
						}
					}	
			}
			int j = maxDuration;
			for (int i = files.size(); i >= 1; i--){
				if (store[i][j]){
					folder.files.push_back(files[i-1]);
					j-=files[i-1].duration;
					swap(files[i-1],files.back());
					files.pop_back();
				}
			}
			
			
			folders.push_back(folder);		
		}
		return folders;
	}