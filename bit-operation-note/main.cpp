#include <iostream>
#include <vector>
#include "leetcode.h"

// Basic bit manipulation
// set: n = n | (1 << bit)
// clear: n = n & ~(1 << bit)
// check: n & (1 << bit) != 0
// toggle: n = n ^ (1 << bit)

// advanced bit manipulation
// clear the rightmost bit: n = n & (n-1)
// swap: a ^= b; b ^= a; a ^= b;
// use union to access the bit fields: union { uint32_t n; char c[4]; }
// 2's complement: -n = ~n + 1
// get the leftmost bit, ex 101 to 100 : n |= n >> 1; n |= n >> 2; n |= n >> 4; n |= n >> 8; n |= n >> 16; n = n - (n >> 1)
// get the rightmost bit, 1010 to 0010: n & -n = n & (~n + 1)

// special bit manipulation
// check if number is power of 2: n & (n-1) == 0
// check if number is power of 3: 奇数位置的1和偶数位置的1的数量差为 3 的倍数



bool isPowerOf2(int num) {
    return (num & (num-1)) == 0;
}

bool isPowerOf3(int num) {
    if (num < 0){
        num = -num;
    }
    if (num == 0){
        return true;
    }
    if (num == 1){
        return false;
    }
    int odd = 0;
    int even = 0;
    while (num != 0){
        if ((num & 1) == 1){
            ++even;
        }
        num = num >> 1;
        if ((num & 1) == 1){
            ++odd;
        }
        num = num >> 1;
    }
    return isPowerOf3(odd-even);
}

bool isBitSet(int num, int bit) {
    return (num & (1 << bit)) != 0;
}

int getBit1Count(int num) {
    int count = 0;
    while (num != 0){
        num = num & (num-1);
        ++count;
    }
    return  count;
}

void swap(int &a, int &b){
    a ^= b;
    b ^= a;
    a ^= b;
}

int main() {
    int num = 17;
    int num2 = 22;

    // check is bit set
    std::cout << isBitSet(num, 4) << std::endl;

    std::cout << std::hex << num << std::endl;
    std::cout << getBit1Count(num) << std::endl;

    swap(num, num2);

    std::cout << std::dec <<  num << std::endl;
    std::cout << std::dec <<  num2 << std::endl;

    // check is power of 2
    std::cout << isPowerOf2(15) << std::endl;
    std::cout << isPowerOf2(16) << std::endl;

    // check is power of 3
    std::cout << isPowerOf3(27) << std::endl;
    std::cout << isPowerOf3(80) << std::endl;

    // question
    // printWithArray(a, 5);
    int a[] = {1, 2, 3, 4, 5};
    printWithArray(a, 5);
    std::cout << std::endl;
    printWithArray(a, 5, 0);


    // try qsort
    std::cout << std::endl;
    std::vector<int> arr = {3, 2, 1, 4, 5};
    arr = qsort(arr);
    for (int i = 0; i < arr.size(); ++i){
        std::cout << arr[i] << " ";
    }

    // try merge sort
    std::cout << std::endl;
    std::vector<int> arr2 = {3, 2, 1, 4, 5};
    arr2 = merge_sort(arr2);
    for (int i = 0; i < arr2.size(); ++i){
        std::cout << arr2[i] << " ";
    }

    // try link list
    printf("\n");
    auto linkList = new DoubleLinkList();
    linkList->addNode(1);
    linkList->addNode(2);
    linkList->addNode(3);
    linkList->addNode(4);
    linkList->addNode(5);

    linkList->printList();
    linkList->reverseList();
    linkList->printList();

    return 0;
}
