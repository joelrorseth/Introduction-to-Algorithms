//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Merge Sort (pg. 31, 34)
//  Worst case time complexity: O(n log(n))
//
//  Implemented by Joel Rorseth
//  Created on May 4, 2017
//

#include <iostream>
#include <vector>


//  Given two sorted lists [p,q] and (q,r], merge together into
//  one sorted list. Load both ranges into two sublists, and compare
//  both lists at each index to determine which value to copy to 'list'

template <typename T>
void merge(std::vector<T> & list, int p, int q, int r) {

    auto n1 = q - p + 1;
    auto n2 = r - q;

    // Create temporary lists
    std::vector<T> l_list{};
    std::vector<T> r_list{};
    
    l_list.reserve(n1 + 1);
    r_list.reserve(n2 + 1);

    for (int i = 0; i < n1; i++) 
        l_list[i] = list[p + i];
    for (int j = 0; j < n2; j++)
        r_list[j] = list[q + j + 1];

    l_list[n1] = INT_MAX;
    r_list[n2] = INT_MAX;

    // Simple pointers for each sublist
    int i = 0, j = 0;

    // Loop through every element in [p,r]
    for (auto k = p; k <= r; k++) {

        // Determine if next sorted value should be from
        // left or right sublists, then copy to original list

        if (l_list[i] <= r_list[j]) {

            list[k] = l_list[i];
            ++i;

        } else if (l_list[i] > r_list[j]) {

            list[k] = r_list[j];
            ++j;
        }
    }
}


//  Until the range [p,r] of list contains only one element, recursively
//  split left and right halves of list. Eventually, both halves will be
//  merged back sorted, starting with the lists containing one element.

template <typename T>
void merge_sort(std::vector<T> & list, int p, int r) {

    // Keep recursively calling until there is one element in [p, r]
    if (p < r) {

        auto q = (p + r) / 2;
        merge_sort(list, p, q);
        merge_sort(list, q + 1, r);

        merge(list, p, q, r);
    }
}


// Demonstration
int main(int argc, char * argv[]) {

    std::vector<int> a{1,9,2,6,5,4,7,3,8};

    // Print vector contents
    std::cout << "Before sorting...\n\tstd::vector a = { ";
    for (auto num: a)
        std::cout << num << ", ";
    std::cout << "}" << std::endl;

    // Call the merge sort with start and end index positions
    merge_sort(a, 0, a.size() - 1);

    // Print vector again
    std::cout << "After sorting...\n\tstd::vector a = { ";
    for (auto num: a)
        std::cout << num << ", ";
    std::cout << "}" << std::endl;
}
