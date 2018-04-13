#include "stdafx.h"
#include "HelperFunctions.h"
using namespace std;

bool directoryExists(string directory) {
	DWORD attributes = GetFileAttributesA(directory.c_str());

	if (attributes == INVALID_FILE_ATTRIBUTES)
		return false;

	return (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

void createFolder(string name, string path) {
	string folderDirectory = path + '\\' + name;
	if (!directoryExists(folderDirectory)) {
		string command = "mkdir " + folderDirectory;
		bool errorValue = system(command.c_str());
		if (errorValue)
			throw "Error in Creating the Folder";
	}
}

void copyFile(string name, string origin, string destination) {
	string destinationDirectory = destination + '\\' + name,
		originDirectory = origin + '\\' + name,
		command = "copy " + originDirectory + ' ' + destinationDirectory;

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

float parseDurationString(std::string durationString) {
	float hours, minutes, seconds;
	stringstream ss;

	// Parsing the Hours
	ss << durationString.substr(0, 2);
	ss >> hours; ss.clear();

	// Parsing the Minutes
	ss << durationString.substr(3, 2);
	ss >> minutes; ss.clear();

	// Parsing the Seconds
	ss << durationString.substr(6, 2);
	ss >> seconds; ss.clear();

	return (hours * 60) + minutes + (seconds / 60);
}
