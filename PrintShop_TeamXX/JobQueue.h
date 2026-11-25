#ifndef JOB_QUEUE_H
#define JOB_QUEUE_H

#include "Models.h"
#include <iostream>

// Circular Array Queue for Waiting Print Jobs
class JobQueue {
public:
    static const int CAPACITY = 20;

private:
    PrintJob elements[CAPACITY];
    int front;
    int rear;
    int count;

public:
    JobQueue();

    bool isFull() const;
    bool isEmpty() const;
    int getCount() const;

    bool enqueue(const PrintJob& job);
    bool dequeue(PrintJob& outJob);
    void display() const;
};

#endif // JOB_QUEUE_H
