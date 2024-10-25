#include <iostream>
#include <vector>
#include <string>

class StringQueue {
private:
    std::vector<std::string> queue;
    int maxSize;
    int front;
    int rear;
    int currentSize;

public:
    // Constructor to initialize the queue with a given size
    StringQueue(int size) : maxSize(size), front(0), rear(0), currentSize(0) {
        queue.resize(maxSize);
    }

    // Method to add a string to the queue
    void enqueue(const std::string& element) {
        if (currentSize == maxSize) {
            // If the queue is full, move the front pointer
            front = (front + 1) % maxSize;
        } else {
            currentSize++;
        }
        queue[rear] = element;
        rear = (rear + 1) % maxSize;
    }

    bool full() {
        if (currentSize == maxSize) {
            return true;
        }
        return false;
    }

    // Method to return all strings in the queue concatenated together
    std::string concatenate() const {
        std::string result;
        for (int i = 0; i < currentSize; i++) {
            int index = (front + i) % maxSize;
            result += queue[index];
            if (i < currentSize - 1){
                result += " ";
            }
        }
        return result;
    }

    // Method to print the current queue (for debugging purposes)
    void printQueue() const {
        std::cout << "Queue: ";
        for (int i = 0; i < currentSize; i++) {
            int index = (front + i) % maxSize;
            std::cout << queue[index] << " ";
        }
        std::cout << std::endl;
    }
};


// main for debbugging
// int main() {
//     StringQueue sq(3);  // Create a queue with a maximum size of 3

//     sq.enqueue("\"hello");
//     sq.enqueue("World\"");

//     sq.printQueue();
//     std::cout << "Concatenated: " << sq.concatenate() << std::endl;

//     sq.enqueue("New");

//     sq.printQueue();
//     std::cout << "Concatenated: " << sq.concatenate() << std::endl;

//     return 0;
// }
