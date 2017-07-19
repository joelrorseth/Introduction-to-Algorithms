//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Max Priority Queue (pg. 162)
//
//  Implemented by Joel Rorseth
//  Created on July 13, 2017
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>


// This priority queue implementation stores priority values (keys) only,
// directly in a max heap. As such, it follows the ordering property defined
// by a max heap. Therefore, highest priority elements are stored at top


// A custom C++ Heap class
template <typename T>
class Heap {

    private:
        // This implementation will represent the heap as an 'array'
        std::vector<T> heap;

    public:
        int heap_size;
        long unsigned int length;

        // Constructors
        Heap<T>(int n) : heap{n}, heap_size{0}, length{n} {}
        Heap<T>(std::vector<T> & list) : heap{list},
            heap_size{0}, length{list.size()} {}

        // Overridden [] mutator
        T & operator[](int index) {
            if (index < 0)
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



// Heap maximum w/ max heap (pg. 163) - O(1)
// Return the 'maximum' element in the heap
template <typename T>
T heap_maximum(Heap<T> & heap) {
    return heap[0];
}


// Priority queue extract maximum w/ max heap (pg. 163) - O(log n)
// Retrieves and remove maximum element from heap, then reorders heap
template <typename T>
T heap_extract_max(Heap<T> & heap) {

    // Error
    if (heap.heap_size < 1) {
        std::cout << "\tError: Heap underflow" << std::endl;
        return INT_MIN;
    }

    // Extract highest priority element (top of tree in a max priority queue)
    T max = heap[0];

    // Replace extracted element with lowest priority element, then
    // heapify it back into proper position based on priority (O(log n))
    heap[0] = heap[heap.heap_size - 1];
    --heap.heap_size;

    max_heapify(heap, 0);

    return max;
}


// Priority queue increase key w/ max heap (pg. 164) - O(log n)
// Increases the key (priority) of an element, then reorders heap
template <typename T>
void heap_increase_key(Heap<T> & heap, int index, T key) {

    if (key < heap[index]) {
        std::cout << "\tError: New key is smaller than current key." << std::endl;
        return;
    }

    // Assign element at specified index the requested priority
    heap[index] = key;

    // To fix the likely violation of heap ordering property, reorder the heap
    // by traversing up the heap, comparing current index element with parent (O(log n))
    while (index > 0 && heap[heap.parent(index)] < heap[index]) {

        // Current index will become parent's to allow comparison with the parent's parent
        std::swap(heap[index], heap[heap.parent(index)]);
        index = heap.parent(index);
    }
}


// Priority queue insert w/ max heap (pg. 164) - O(log n)
// Inserts a new element into priority queue / heap
template <typename T>
void max_heap_insert(Heap<T> & heap, T key) {

    // Clear out a spot at the end for new element (no priority yet)
    ++heap.heap_size;
    heap[heap.heap_size - 1] = INT_MIN;

    // Now that you are providing a priority, sort it into place (O (log n))
    heap_increase_key(heap, heap.heap_size - 1, key);
}


// Demonstration
int main() {

    std::vector<int> keys{1,4,5,7,2,4,9,0};
    Heap<int> priority_queue{keys};

    for (auto & key: keys) {
      std::cout << "Inserting element into queue with priority "
        << key << std::endl;
      max_heap_insert(priority_queue, key);
    }

    std::cout << "\nNow dequeuing elements in order of priority...\n"
      << std::endl;

    while (priority_queue.heap_size > 0) {

      auto next = heap_extract_max(priority_queue);
      std::cout << "Next up, extracting element with priority "
        << next << std::endl;
    }
}
