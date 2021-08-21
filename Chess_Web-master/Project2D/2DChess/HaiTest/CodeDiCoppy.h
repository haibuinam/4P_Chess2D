

#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>

//#include "Header.h"
using namespace std;

// ONLY works if 'lo' starts from '0' 
// 'hi' is the end index of the array
//
int partition(int* array, const int& lo, const int& hi) {
    int i = lo, j = hi + 1; 
    int pivot = array[lo];
    while (i < j) {        
        while (array[i++] > pivot) if (i == hi) break;
        while (pivot < array[--j]) if (j == lo) break;
        if (i >= j) break;
        swap(array[i], array[j]);
    }
    swap(array[lo], array[j]);
    return j;
}


void quickSort(int* array, const int& lo, const int& hi) {
    if (hi <= lo) return;
    int j = partition(array, lo, hi);
    quickSort(array, lo, j);
    quickSort(array, j + 1, hi);
}
//thu gon array
void insertionSort(int* array, const int& lo, const int& hi) {
    for (int i = lo; i <= hi; i++)
        for (int j = i; j > lo && array[j] < array[j - 1]; j--)
            swap(array[j], array[j - 1]);
}
//loai bo cac ban sao
int removeDuplicates(int* array, const int& lo, const int& hi) {
    int i = lo, j = lo + 1;
    int newHigh = hi;
    while (j <= newHigh) {
        if (array[i] == array[j]) {
            int dupIndex = j;
            while (array[dupIndex] == array[i]) dupIndex++;
            int distance = dupIndex - j;
            newHigh -= distance;
            for (int k = j; k <= hi; k++)
                array[k] = array[k + distance];
        }
        i++; j++;
    }
    return newHigh;
}

// calculate movables1[] - movables2[]
void arrayMinusArray(int* mang1chieuA, int* mang1chieuB, int& endIndex1, int& endIndex2) {
    if (endIndex1 < 196) insertionSort(mang1chieuA, 0, endIndex1);
    else                  quickSort(mang1chieuA, 0, endIndex1);
    if (endIndex2 < 196) insertionSort(mang1chieuB, 0, endIndex2);
    else                  quickSort(mang1chieuB, 0, endIndex2);
    // print debugging for sort
    cout << endl;
    cout << "///////////////////////" << endl;
    cout << "BEGIN DEBUG SORT PRINT: " << endl;
    for (int k = 0; k <= endIndex1; k++) {
        cout << mang1chieuA[k] << " ";
    }
    cout << endl;
    for (int k = 0; k <= endIndex2; k++) {
        cout << mang1chieuB[k] << " ";
    }
    cout << endl;
    cout << "END OF DEBUG SORT" << endl;
    cout << "///////////////////////" << endl;

    endIndex1 = removeDuplicates(mang1chieuA, 0, endIndex1);
    endIndex2 = removeDuplicates(mang1chieuB, 0, endIndex2);

    // print debugging for remove duplicates
    cout << endl;
    cout << "///////////////////////" << endl;
    cout << "BEGIN DEBUG REMOVE DUPS PRINT: " << endl;
    for (int k = 0; k <= endIndex1; k++) {
        cout << mang1chieuA[k] << " ";
    }
    cout << endl;
    for (int k = 0; k <= endIndex2; k++) {
        cout << mang1chieuB[k] << " ";
    }
    cout << endl;
    cout << "END OF DEBUG REMOVE DUPS" << endl;
    cout << "///////////////////////" << endl;
    cout << endl;

    int i = 0, j = 0;
    while (i < endIndex1 && j < endIndex2) {
        if (mang1chieuA[i] > mang1chieuB[j]) j++;
        else if (mang1chieuA[i] < mang1chieuB[j]) i++;
        else {
            for (int k = i; k < endIndex1; k++)
                mang1chieuA[k] = mang1chieuA[k + 1];
            endIndex1--; j++;
        }
    }
}
/*
int main(int argc, char** argv) {
    int endIndex1 = 0, endIndex2 = 0;
    for (const auto& s : mang1chieuA) endIndex1++;
    for (const auto& s : mang1chieuB) endIndex2++;
    endIndex1 -= 1; endIndex2 -= 1;
    arrayMinusArray(mang1chieuA, mang1chieuB, endIndex1, endIndex2);

    cout << "array1[] after minus array2[]:" << endl;
    for (int i = 0; i <= endIndex1; i++)
        cout << mang1chieuA[i] << " ";

    cout << endl;
}
*/