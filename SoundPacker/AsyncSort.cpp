#include "stdafx.h"
#include "AsyncSort.h"
using namespace System;
using namespace System::Threading;

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
        // Launching synchronous operations if Working Threads reached the maximum number
        if (AsyncSort::workingThreads > AsyncSort::maxWorkingThreads) {
            std::sort(begin, middle);  // Removing the options of async using std::sort to the left half
            AsyncSort::asyncMergeSort(gcnew Parameters { new Iterator(middle), new Iterator(end) });  // Keeping the async option in future iterations to the right half
        } else {
            // Launching 2 asyncMergeSort threads
            AsyncSort::workingThreads++;
            Thread^ leftThread = gcnew Thread(gcnew ParameterizedThreadStart(&AsyncSort::asyncMergeSort));
            leftThread->Start(gcnew Parameters { new Iterator(begin), new Iterator(middle)});

            AsyncSort::workingThreads++;
            Thread^ rightThread = gcnew Thread(gcnew ParameterizedThreadStart(&AsyncSort::asyncMergeSort));
            rightThread->Start(gcnew Parameters { new Iterator(middle), new Iterator(end) });

            // Waiting for the Threads to Finish
            leftThread->Join();
            AsyncSort::workingThreads--;

            rightThread->Join();
            AsyncSort::workingThreads--;
        }
    }

    // Merging the Two Halves
    std::inplace_merge(begin, middle, end);
}

