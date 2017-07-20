//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Counting Sort (pg. 195)
//  Worst case time complexity: O(n + k) with range [0, k]
//
//  Implemented by Joel Rorseth
//  Created on July 20, 2017
//

#include <iostream>
#include <vector>


void counting_sort(std::vector<int> & array) {

    // Determine 'k', the largest value in the array
    int k = array[0];
    for (int num: array)  if (num > k)  k = num;

    std::vector<int> sequential_count(k + 1, 0);
    std::vector<int> sorted(array.size(), 0);

    // Accumulate the sequential count element by element into array
    for (int & element: array)
        ++sequential_count[element];

    for (int i = 1; i < (int)sequential_count.size(); ++i)
        sequential_count[i] += sequential_count[i - 1];


    // Place each element in original array into correct position
    // Decrement sequential count for number to get position for next occurence
    for (int j = array.size() - 1; j >= 0; j--) {
        sorted[sequential_count[array[j]] - 1] = array[j];
        --sequential_count[array[j]];
    }

    // Assign the contents back into the original array
    // Counting sort must use second array, it doesn't work 'in place'
    for (int i = 0; i <= (int)array.size(); ++i)
        array[i] = sorted[i];
}


// Demonstration
int main(int argc, char * argv[]) {

    std::vector<int> a{2,5,3,0,2,3,0,3};

    // Print vector contents
    std::cout << "Before sorting...\n\tstd::vector a = { ";
    for (auto & num: a)  std::cout << num << ", ";
    std::cout << "}" << std::endl;

    counting_sort(a);

    // Print vector again
    std::cout << "After sorting...\n\tstd::vector a = { ";
    for (auto & num: a)  std::cout << num << ", ";
    std::cout << "}" << std::endl;
}
