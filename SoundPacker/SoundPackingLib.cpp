#include "stdafx.h"
#include "AsyncSort.h"
using namespace System;
using namespace System::Diagnostics;

std::vector<Folder> WorstFitLS(std::vector<File> files, int maxDuration) {
	std::vector<Folder>folders;

	
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

std::vector<Folder> WorstFitPQ(std::vector<File> files, int maxDuration) {
	std::priority_queue<Folder, std::vector<Folder>, std::greater<Folder> >folders;

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

	std::vector<Folder>folder;
	while (!folders.empty()) {
		folder.push_back(folders.top());
		folders.pop();
	}

	return folder;
}

std::vector<Folder> worstFitDecreasingLS(std::vector<File> inputFiles, int maxDuration, bool multithreading) {
	if (multithreading) {
	    asyncMergeSort(inputFiles.rbegin(), inputFiles.rend());
	} else {
		sort(inputFiles.rbegin(), inputFiles.rend()); // O(N Log N)
	}
	std::vector<Folder>folders;
	for (int i = 0; i < inputFiles.size(); i++) {  // O(N X M)
		int index = -1;  // O(1)
		int Max = -1;    // O(1)
		for (int j = 0; j < folders.size(); j++) {   // O(M)
			if (maxDuration - folders[j].totalDuration >= inputFiles[i].duration) { // O(1)
				if (maxDuration - folders[j].totalDuration>Max) {  // O(1)
					Max = maxDuration - folders[j].totalDuration;  // O(1)
					index = j;  // O(1)
				}
			}
		}
		if (index == -1) {
			folders.push_back(Folder());  // O(1)
			folders[folders.size() - 1].files.push_back(inputFiles[i]);  // O(1)
			folders[folders.size() - 1].totalDuration += inputFiles[i].duration;  // O(1)
		}
		else {
			folders[index].files.push_back(inputFiles[i]);  // O(1)
			folders[index].totalDuration += inputFiles[i].duration;  // O(1)
		}
	}

	return folders;
}


std::vector<Folder> worstFitDecreasingPQ(std::vector<File> inputFiles, int maxDuration, bool multithreading) {
	std::priority_queue < Folder, std::vector<Folder>, std::greater<Folder> > myFolderspq;
	if (multithreading) {
        asyncMergeSort(inputFiles.rbegin(), inputFiles.rend());
	} else {
		sort(inputFiles.rbegin(), inputFiles.rend()); // O(N Log N)
	}

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
	std::vector<Folder> myFolders;
	while (!myFolderspq.empty()) {
		myFolders.push_back(myFolderspq.top()); // O(1)
		myFolderspq.pop(); // O(log M)
	}
	return myFolders;
}

std::vector<Folder> firstFitDecreasingLS(std::vector<File> inputFiles, int maxDuration, bool multithreading) {
	if (multithreading) {
		asyncMergeSort(inputFiles.rbegin(), inputFiles.rend());  
	} else {
		sort(inputFiles.rbegin(), inputFiles.rend()); // O(N Log N)
	}

	std::vector<Folder> myFolders;
	for (int i = 0; i < inputFiles.size(); i++) {  // O(N X M)
		int k = 0;
		for (int j = 0; j < myFolders.size(); j++) {  // O(M)
			if ((maxDuration - myFolders[j].totalDuration) >= inputFiles[i].duration) {   // O(1)
				myFolders[j].files.push_back(inputFiles[i]);  // O(1)
				myFolders[j].totalDuration += inputFiles[i].duration;  // O(1)
				k = 1;
				break;
			}
		}
		if (!k) {
			Folder folder;
			folder.files.push_back(inputFiles[i]);  // O(1)
			folder.totalDuration = inputFiles[i].duration;  // O(1)
			myFolders.push_back(folder);  // O(1)
		}
	}
	return myFolders;

}

std::vector<Folder> bestFit(std::vector<File> files, int maxDuration) {

	std::vector<Folder>folders;

	sort(files.rbegin(), files.rend()); // O(N Log N)

	for (int i = 0; i<files.size(); i++) {		//O(N*N)
		int bestDurationInd = -1;			//O(1)
		for (int j = 0; j<folders.size(); j++) {	//O(N)

			int curDuration = maxDuration - folders[j].totalDuration;	//O(1)

			if (files[i].duration <= curDuration) {	//O(1)

				if (bestDurationInd == -1) {	//O(1)
					bestDurationInd = j;		//O(1)
				}
				else {
					if (folders[j].totalDuration < maxDuration - folders[bestDurationInd].totalDuration) //O(1)
					{	
						bestDurationInd = j;		//O(1)
					}
				}
			}
		}
		if (bestDurationInd == -1) {		//O(1)
			Folder folder;					//O(1)
			folder.totalDuration = 0;		//O(1)
			folder.totalDuration += files[i].duration;		//O(1)
			folder.files.push_back(files[i]);			//O(1)
			folders.push_back(folder);		//O(1)
		}	
		else {
			folders[bestDurationInd].totalDuration += files[i].duration;	//O(1)
			folders[bestDurationInd].files.push_back(files[i]);		//O(1)

		}

	}
	return folders;		//O(1)
}

int dp[10001][351];
bool store[10001][351];
std::vector<Folder> folderFilling(std::vector<File> files, int maxDuration) {

	std::vector<Folder> folders;		//O(1)
	int filesTaken = 0;			//O(1)
	while (filesTaken<files.size()) {		//O(n*n*d)

		memset(dp, -1, sizeof dp);			//O(n)
		memset(store, 0, sizeof store);		//O(n)

		Folder folder;					//O(1)

		for (int i = 0; i <= files.size(); i++) {		//O(n*d)
			for (int j = 0; j <= maxDuration; j++) {	//O(d)
				int duration = 0;		//O(1)
				if (!i)					//O(1)
				{
					dp[i][j] = 0;		//O(1)
				}
				else {
					duration = files[i - 1].duration;	//O(1)

					if (duration <= j && dp[i - 1][j] < duration + dp[i - 1][j - duration] && duration != -1)	//O(1)
					{
						dp[i][j] = duration + dp[i - 1][j - duration];		//O(1)
						store[i][j] = true;									//O(1)
					}
					else {
						dp[i][j] = dp[i - 1][j];				//O(1)
						store[i][j] = false;					//O(1)
					}
				}
			}
		}	
		int j = maxDuration;		//O(1)
		for (int i = files.size(); i >= 1; i--) {		//O(n)
			if (store[i][j]) {							//O(1)
				folder.totalDuration += files[i - 1].duration;		//O(1)
				folder.files.push_back(files[i - 1]);	//O(1)	
				j -= files[i - 1].duration;			//O(1)
				files[i - 1].duration = -1;			//O(1)
				filesTaken++;			//O(1)
			}
		}
		folders.push_back(folder);			//O(1)
	}
	return folders;			//O(1)
}