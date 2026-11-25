#include "JobQueue.h"

JobQueue::JobQueue() : front(0), rear(-1), count(0) {}

bool JobQueue::isFull() const {
    return count == CAPACITY;
}

bool JobQueue::isEmpty() const {
    return count == 0;
}

int JobQueue::getCount() const {
    return count;
}

bool JobQueue::enqueue(const PrintJob& job) {
    if (isFull()) {
        return false;
    }
    rear = (rear + 1) % CAPACITY;
    elements[rear] = job;
    count++;
    return true;
}

bool JobQueue::dequeue(PrintJob& outJob) {
    if (isEmpty()) {
        return false;
    }
    outJob = elements[front];
    front = (front + 1) % CAPACITY;
    count--;
    return true;
}

void JobQueue::display() const {
    if (isEmpty()) {
        std::cout << "No waiting jobs in the queue.\n";
        return;
    }

    std::cout << "Waiting jobs: " << count << "\n";
    for (int i = 0; i < count; ++i) {
        int idx = (front + i) % CAPACITY;
        const PrintJob& j = elements[idx];
        std::cout << j.jobId << " | Customer " << j.customerId << " | " << j.serviceName
                  << " | " << j.pageCount << (j.pageCount == 1 ? " page" : " pages")
                  << " | EGP " << j.totalPrice << "\n";
    }
}
