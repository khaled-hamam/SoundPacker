#pragma once
#include "Models.h"

typedef std::vector<File>::reverse_iterator Iterator;
typedef array<Iterator *> Parameters;

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
std::vector<Folder> worstFitDecreasingLS(std::vector<File> inputFiles, int maxDuration, bool multithreading);
std::vector<Folder> worstFitDecreasingPQ(std::vector<File> inputFiles, int maxDuration, bool multithreading);
std::vector<Folder> firstFitDecreasingLS(std::vector<File> inputFiles, int maxDuration, bool multithreading);
std::vector<Folder> bestFit(std::vector<File>files, int maxDuration);
std::vector<Folder> folderFilling(std::vector<File> files, int maxDuration);
