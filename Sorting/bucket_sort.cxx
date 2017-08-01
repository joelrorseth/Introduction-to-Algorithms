//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Bucket Sort (pg. 201)
//  Worst case time complexity: O(n^2)
//  Average case time complexity: O(n)
//
//  Implemented by Joel Rorseth
//  Created on August 1, 2017
//

#include <iostream>
#include <vector>
#include <algorithm>


// Note: Bucket sort assumes that the input set consists only of
// floating point numbers in the range [0.0, 1.0]. They numbers 
// should ideally be uniformly distributed across this range.


// Bucket Sort
template <typename T>
void bucket_sort(std::vector<T> & list) {

    int n = list.size();

    std::vector<T> buckets[n];


    // Distribute numbers into different buckets
    for (auto & number: list) 
        buckets[ (int)(n*number) ].push_back(number);

    // Sort each bucket (typically using Insertion Sort)
    for (auto & bucket: buckets)
        std::sort(bucket.begin(), bucket.end());


    // Concatenate buckets back into original list
    int index = 0;
    for (auto & bucket: buckets)
        for (auto & number: bucket)
            list[index++] = number;
}


// Demonstration
int main() {

    std::vector<float> list{0.465, 0.899, 0.919, 0.212, 0.355, 0.650};

    std::cout << "Input List: [";
    for (auto & number: list)
        std::cout << number << ',';
    std::cout << ']' << '\n';

    bucket_sort(list);

    std::cout << "Bucket Sorted: [";
    for (auto & number: list)
        std::cout << number << ',';
    std::cout << ']' << std::endl;
}
