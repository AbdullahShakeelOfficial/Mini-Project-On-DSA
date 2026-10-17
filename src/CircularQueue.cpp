#include "CircularQueue.h"
#include <iostream>

CircularQueue::CircularQueue(int maxSize) : MAX_SIZE(maxSize), front(-1), rear(-1), arr(maxSize) {
    // Initialize all slots with empty strings.
    std::fill(arr.begin(), arr.end(), "");
}

CircularQueue::~CircularQueue() = default;

bool CircularQueue::enqueue(const std::string& customer) {
    if (isFull()) {
        // Queue is full; cannot add.
        return false;
    }
    // First element insertion.
    if (isEmpty()) {
        front = rear = 0;
    } else {
        // Move rear forward with wrap‑around.
        rear = (rear + 1) % MAX_SIZE;
    }
    arr[rear] = customer;
    return true;
}

std::string CircularQueue::dequeue() {
    if (isEmpty()) {
        return ""; // Nothing to dequeue.
    }
    std::string customer = arr[front];
    arr[front] = ""; // Clear slot for visualization.
    if (front == rear) {
        // Queue becomes empty after this removal.
        front = rear = -1;
    } else {
        // Move front forward with wrap‑around.
        front = (front + 1) % MAX_SIZE;
    }
    return customer;
}

bool CircularQueue::isEmpty() const {
    // Empty queue is indicated by front == -1.
    return front == -1;
}

bool CircularQueue::isFull() const {
    // Full queue when next position of rear would collide with front.
    // This strict condition avoids the classic off‑by‑one bug.
    return ((rear + 1) % MAX_SIZE) == front;
}

std::vector<std::string> CircularQueue::display() const {
    // Return a copy of the underlying array for frontend visualization.
    return arr;
}
