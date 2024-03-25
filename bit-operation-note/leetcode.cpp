//
// Created by Leon Lin on 2024/3/25.
//
#include <cstdio>
#include <vector>
#include "leetcode.h"

using namespace std;

void printWithArray(int *a, int size){
    for (int i =0; i < 500; ++i){
        if (*a == i){
            ++a;
            if (--size < 0){
                break;
            }
        } else {
            printf("%d ", i);
        }
    }
}

void printWithArray(int *a, int size, int b){
    for (int i = b* 100; i < (b + 1)*100; ++i){
        if (*a == i){
            ++a;
            if (--size < 0){
                break;
            }
        } else {
            printf("%d ", i);
        }
    }
}

struct ListStruct{
    unsigned int DataH;
    unsigned int DataL;
    unsigned int NextPtr;
};
struct ListStruct ListArray[1000];
unsigned int ListHead = 0;

void findInLinkList(unsigned int DATA_A, unsigned int DATA_B){
    unsigned int CurrentPtr = ListHead;
    while (CurrentPtr != 0){
        if (ListArray[CurrentPtr].DataH == DATA_A && ListArray[CurrentPtr].DataL == DATA_B){
            printf("Found\n");
            return;
        }
        CurrentPtr = ListArray[CurrentPtr].NextPtr;
    }
    printf("Not Found\n");
}

std::vector<int> qsort(std::vector<int> arr){
    if (arr.size() <= 1){
        return arr;
    }
    int pivot = arr[0];
    auto leftArr = std::vector<int>();
    auto rightArr = std::vector<int>();
    for (int i=1;i<arr.size();i++){
        if (arr[i] <= pivot) {
            leftArr.push_back(arr[i]);
        } else {
            rightArr.push_back(arr[i]);
        }
    }
    auto sortedLeft = qsort(leftArr);
    auto sortedRight = qsort(rightArr);
    sortedLeft.push_back(pivot);
    sortedLeft.insert(sortedLeft.end(), sortedRight.begin(), sortedRight.end());
    return  sortedLeft;
}

std::vector<int> merge_sort(std::vector<int> arr){
    if (arr.size() <= 1){
        return arr;
    }
    // split
    auto leftArr = std::vector<int>();
    auto rightArr = std::vector<int>();
    auto middle = arr.begin();
    std::advance(middle, arr.size() / 2);
    leftArr.insert(leftArr.end(), arr.begin(), middle);
    rightArr.insert(rightArr.end(), middle, arr.end());
    // recursive call
    auto sortedLeft = merge_sort(leftArr);
    auto sortedRight = merge_sort(rightArr);
    // merge
    auto sortedArr = std::vector<int>();
    auto leftIter = sortedLeft.begin();
    auto rightIter = sortedRight.begin();
    while (leftIter != sortedLeft.end() && rightIter != sortedRight.end()){
        if (*leftIter < *rightIter){
            sortedArr.push_back(*leftIter);
            ++leftIter;
        } else {
            sortedArr.push_back(*rightIter);
            ++rightIter;
        }
    }
    if (leftIter != sortedLeft.end()){
        sortedArr.insert(sortedArr.end(), leftIter, sortedLeft.end());
    }
    if (rightIter != sortedRight.end()){
        sortedArr.insert(sortedArr.end(), rightIter, sortedRight.end());
    }
    return sortedArr;
}


