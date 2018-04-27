#pragma once
#include "SoundPackingLib.h"

using namespace System;
using namespace System::Threading;

public ref class AsyncSort {
public:
    static int workingThreads = 0;
    static int maxWorkingThreads = 4;

    static void asyncMergeSort(Object^ params);
};

void asyncMergeSort(Iterator begin, Iterator end) {
    Iterator *bIt = new Iterator(begin);
    Iterator *eIt = new Iterator(end);
    AsyncSort::asyncMergeSort(gcnew Parameters { bIt, eIt });

    delete bIt;
    delete eIt;
}

void AsyncSort::asyncMergeSort(Object^ params) {
    // Parsing the Parameters
    Parameters^ arr = (Parameters ^)params;
    auto const begin = *arr[0];
    auto const end = *arr[1];

    if (begin == end)  // Base Case
        return;

    // Dividing the vector
    auto const middle = begin + (end - begin) / 2;  // Calculating the middle position iterator

    if (end - middle > 1) {  // Remaining elements > 2
        // Initializing new Iterators Pointers
        Iterator *bIt = new Iterator(begin);
        Iterator *mIt = new Iterator(middle);
        Iterator *eIt = new Iterator(end);

        // Launching synchronous operations if Working Threads reached the maximum number
        if (AsyncSort::workingThreads > AsyncSort::maxWorkingThreads) {
            std::sort(begin, middle);  // Removing the options of async using std::sort to the left half
            AsyncSort::asyncMergeSort(gcnew Parameters { mIt, eIt });  // Keeping the async option in future iterations to the right half
        } else {
            // Launching 2 asyncMergeSort threads
            AsyncSort::workingThreads++;
            Thread^ leftThread = gcnew Thread(gcnew ParameterizedThreadStart(&AsyncSort::asyncMergeSort));
            leftThread->Start(gcnew Parameters { bIt, mIt });

            AsyncSort::workingThreads++;
            Thread^ rightThread = gcnew Thread(gcnew ParameterizedThreadStart(&AsyncSort::asyncMergeSort));
            rightThread->Start(gcnew Parameters { mIt, eIt });

            // Waiting for the Threads to Finish
            leftThread->Join();
            AsyncSort::workingThreads--;

            rightThread->Join();
            AsyncSort::workingThreads--;
        }

        // Deleting the Iterators Pointers
        delete bIt;
        delete mIt;
        delete eIt;
    }

    // Merging the Two Halves
    std::inplace_merge(begin, middle, end);
}

