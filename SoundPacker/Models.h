#pragma once

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