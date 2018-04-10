#include "HelperFunctions.h"

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
