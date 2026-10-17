#pragma once

/**
 * @file CircularQueue.h
 * @brief Declaration of a generic circular queue implementation using a static array.
 *
 * Author: Hafiz Abdullah Shakeel, Abdurrehman, Fakhir Ashar
 */

#include <vector>
#include <string>

class CircularQueue {
public:
    /**
     * @brief Construct a circular queue with a fixed maximum size.
     * @param maxSize Maximum number of elements the queue can hold.
     */
    explicit CircularQueue(int maxSize);

    /**
     * @brief Destructor.
     */
    ~CircularQueue();

    /**
     * @brief Add a customer (represented by a string) to the queue.
     * @param customer Name or identifier of the customer.
     * @return true if enqueued successfully, false if the queue is full.
     */
    bool enqueue(const std::string& customer);

    /**
     * @brief Remove the front customer from the queue.
     * @return The dequeued customer name; empty string if the queue is empty.
     */
    std::string dequeue();

    /**
     * @brief Check whether the queue is empty.
     * @return true if empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Check whether the queue is full.
     * @return true if full, false otherwise.
     */
    bool isFull() const;

    /**
     * @brief Get a snapshot of the underlying array for visualization.
     * @return Vector containing the queue slots; empty strings represent unused slots.
     */
    std::vector<std::string> display() const;

    /**
     * @brief Get the current front index.
     */
    int frontIndex() const { return front; }

    /**
     * @brief Get the current rear index.
     */
    int rearIndex() const { return rear; }

    /**
     * @brief Get the maximum capacity of the queue.
     */
    int capacity() const { return MAX_SIZE; }

private:
    int MAX_SIZE;                // Fixed capacity of the queue.
    int front;                    // Index of the front element. -1 indicates empty.
    int rear;                     // Index of the last element.
    std::vector<std::string> arr; // Underlying storage.
};
