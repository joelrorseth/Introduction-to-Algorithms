//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Heapsort, Heapify, BuildHeap (using Max Heap)
//  Worst case time complexity: O(n log(n))
//
//  Implemented by Joel Rorseth
//  Created on June 18, 2017
//

#include <iostream>
#include <vector>
#include <algorithm>

// A custom C++ Heap class
template <typename T>
class Heap {

    private:
        // This implementation will represent the heap as an 'array'
        std::vector<T> heap;

    public:
        int heap_size;
        unsigned long length;

        // Constructors
        Heap<T>() : heap_size{0}, length{0} {}
        Heap<T>(std::vector<T> & list) : heap{list},
            heap_size{0}, length{list.size()} {}

        // Overridden [] mutator
        T & operator[](int index) {
            if (index >= heap.size() || index < 0)
                throw std::out_of_range("Index out of range");
            return heap[index];
        }

        // Overridden [] accessor
        const T & operator[](int index) const {
            if (index >= heap.size() || index < 0)
                throw std::out_of_range("Index out of range");
            return heap[index];
        }

         // Node child/parent index calculations for array representation
         // Compiler will most likely perform in O(1) using bit shifting

        int left(int index) { return (2*index)+1; }
        int right(int index) { return (2*index)+2; }
        int parent(int index) { return (index-1)/2; }
};



// Heapify w/ max heap (pg. 154) - O(log n)
// If needed, make heap[index] 'float down' to satisfy ordering property
template <typename T>
void max_heapify(Heap<T> & heap, int index) {

    int largest;

    int left = heap.left(index);
    int right = heap.right(index);

    if (left < heap.heap_size && heap[left] > heap[index])
        largest = left;
    else
        largest = index;

    if (right < heap.heap_size && heap[right] > heap[largest])
        largest = right;

    if (largest != index) {
        std::swap(heap[index], heap[largest]);

        max_heapify(heap, largest);
    }
}


// Build Heap w/ max heap (pg. 157) - O(n)
// Heapify all non-leaf nodes to make them sink to appropriate spot
template <typename T>
void build_max_heap(Heap<T> & heap) {

    heap.heap_size = heap.length;
    for (int index = ((heap.length - 1) / 2); index >= 0; --index)
        max_heapify(heap, index);
}


// Heapsort for max heaps (pg. 160) - O(n log n)
// Make a max heap, then swap from bottom up to arrange in sorted order
template <typename T>
void max_heapsort(Heap<T> & heap) {

    build_max_heap(heap);

    for (int index = heap.length - 1; index >= 1; --index) {

        std::swap(heap[0], heap[index]);
        //T temp = heap[0];
        //heap[0] = heap[index];
        //heap[index] = temp;

        --heap.heap_size;
        max_heapify(heap, 0);
    }
}



// Print out array representation of the heap
template <typename T>
void print_heap(Heap<T> & heap) {

    for (int i = 0; i < heap.length; ++i) {
        std::cout << heap[i] << ',' << ' ';
    }
    std::cout << std::endl;
}

// Demonstration
int main() {

    std::vector<int> contents{1,4,5,7,2,4,9,0};
    Heap<int> heap{contents};

    std::cout << "Unsorted Heap: ";
    print_heap(heap);

    max_heapsort(heap);
    std::cout << "Heapsorted Heap: ";
    print_heap(heap);
    std::cout << std::endl;
}
