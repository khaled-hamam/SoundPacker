#include "stdafx.h"
#include "HelperFunctions.h"
using namespace std;

double runAlgorithm(string inputFile, string algorithm, int duration, bool allowCopy) {
	// Reading the Input File and Parsing the input to vector<File>
	vector<File> inputFiles = parseInput(inputFile);

	// TODO: Calculating the Running Time of the Algorithm

	// Running the Selected Algorithm
	vector<Folder> resultFolders;
	if (algorithm == WORST_FIT_LS) {
		resultFolders = WorstFitLS(inputFiles, duration);
	}
	else if (algorithm == WORST_FIT_PQ) {
		resultFolders = WorstFitPQ(inputFiles, duration);
	}
	else {
		return -1;
	}

	// Getting The Parent Folder Path of the Input Metadata File
	string parentPath = inputFile;
	while (parentPath.back() != '\\') {  // Removing the File Name from the Path
		parentPath.pop_back();
	}

	// Creating the Algorithm Output Folder
	createFolder(algorithm, parentPath + "Packed Files");

	// Generating the Metadata file
	generateMetadata(resultFolders, parentPath + "Packed Files\\" + algorithm);

	// Copy the files to the destination folder if allowCopy == true
	if (allowCopy) {
		// Getting Input Files Path from The Parent Folder path
		string audioFilesPath = parentPath + "Audios";  // The Path now = {ParentFolder}\Audios

		for (int i = 0; i < resultFolders.size(); ++i) {
			resultFolders[i].name = Folder::getName(i + 1);  // Assigning the Name to 'F{i}'
			createFolder(resultFolders[i].name, parentPath + "Packed Files\\" + algorithm);
			for (auto file : resultFolders[i].files) {
				// Copying each file from the source to it's folder
				// New Path: Packed Files\algorithm_name\F{i}
				copyFile(file.name, audioFilesPath, parentPath + "Packed Files\\" + algorithm + '\\' + resultFolders[i].name);
			}
		}
	}

	// Returning the Elapsed Algorithm Time
	return 0;
}

bool directoryExists(string directory) {
	DWORD attributes = GetFileAttributesA(directory.c_str());

	if (attributes == INVALID_FILE_ATTRIBUTES)
		return false;

	return (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

void createFolder(string name, string path) {
	string folderDirectory = path + '\\' + name;
	if (!directoryExists(folderDirectory)) {
		string command = "mkdir \"" + folderDirectory + '"';
		bool errorValue = system(command.c_str());
		if (errorValue)
			throw "Error in Creating the Folder";
	}
}

void copyFile(string name, string origin, string destination) {
	string destinationDirectory = destination + '\\' + name,
		originDirectory = origin + '\\' + name,
		command = "copy \"" + originDirectory + "\" \"" + destinationDirectory + '"';

	bool errorValue = system(command.c_str());
	if (errorValue)
		throw "Error in Copying the File";
}

void generateMetadata(vector<Folder> folders, string destination) {
	fstream metaDataFile(destination + '\\' + "metadata.txt", fstream::out);

	for (auto folder : folders) {
		metaDataFile << "|Folder: " << folder.name << '\n'
			<< '|' << string(2, '-') << "Content: (" << folder.files.size() << " Audio Files, Total Duration: "
			<< folder.getTotalDuration() << " Seconds)\n";
		for (auto file : folder.files) {
			metaDataFile << '|' << string(4, '-') << "File: " << file.name << '\t' << "Duration: " << file.duration << " Seconds \n";
		}
		metaDataFile << "\n\n";
	}
}

std::vector<File> parseInput(std::string inputFile) {
	vector<File> inputFiles; int nFiles;
	fstream file(inputFile, fstream::in);
	
	file >> nFiles;
	for (int i = 0; i < nFiles; ++i) {
		string fileName; file >> fileName;
		string durationString; file >> durationString;
		inputFiles.push_back(File(fileName, parseDurationString(durationString)));
	}

	return inputFiles;
}

int parseDurationString(std::string durationString) {
	int hours, minutes, seconds;
	stringstream ss;

	// Parsing the Hours
	int hoursPartition = durationString.find(":");
	ss << durationString.substr(0, hoursPartition);
	ss >> hours; ss.clear();

	// Parsing the Minutes
	int minutesPartition = durationString.find(":", hoursPartition + 1);
	ss << durationString.substr(hoursPartition + 1, minutesPartition - hoursPartition - 1);
	ss >> minutes; ss.clear();

	// Parsing the Seconds
	ss << durationString.substr(minutesPartition + 1);
	ss >> seconds; ss.clear();

	return (hours * 60 * 60) + (minutes * 60) + seconds;
}
