#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <future>
using namespace std;

// Needed Variables
namespace asyncSort {
    static int workingThreads = 0;
    static int maxWorkingThreads = 4;
}


// Function Definition
template <class T>
void asyncMergeSort(T begin, T end);


// Function Body
template <class T>
void asyncMergeSort(T begin, T end) {
    if (begin == end)  // Base Case
        return;

    // Dividing the vector
    auto const middle = begin + (end - begin) / 2;  // Calculating the middle position iterator

    if (end - middle > 1) {  // Remaining elements > 2
        // Launching synchronous operations if Working Threads reached the maximum number
        if (asyncSort::workingThreads > asyncSort::maxWorkingThreads) {
            sort(begin, middle);  // Removing the options of async using std::sort to the left half
            asyncMergeSort(middle, end);  // Keeping the async option in future iterations to the right half
        } else {
            // Launching 2 asyncMergeSort threads
            asyncSort::workingThreads++;
            thread leftThread(asyncMergeSort<T>, begin, middle);

            asyncSort::workingThreads++;
            thread rightThread(asyncMergeSort<T>, middle, end);

            // Waiting for the Threads to Finish
            leftThread.join(); 
            asyncSort::workingThreads--;

            rightThread.join(); 
            asyncSort::workingThreads--;
        }
    }

    // Merging the Two Halves
    inplace_merge(begin, middle, end);
}