#pragma once
#include "Models.h"

typedef std::vector<File>::iterator Iterator;
typedef array<Iterator *> Parameters;

public ref class AsyncSort {
public:
    static int workingThreads = 0;
    static int maxWorkingThreads = 4;

    static void asyncMergeSort(Object^ params);
};

void asyncMergeSort(Iterator begin, Iterator end) {
    AsyncSort::asyncMergeSort(gcnew Parameters { new Iterator(begin), new Iterator(end) });
}
