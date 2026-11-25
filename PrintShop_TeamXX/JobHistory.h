#ifndef JOB_HISTORY_H
#define JOB_HISTORY_H

#include "Models.h"
#include <iostream>

// Node for Doubly Linked List
struct HistoryNode {
    PrintJob data;
    HistoryNode* prev;
    HistoryNode* next;

    HistoryNode(const PrintJob& j, HistoryNode* p = nullptr, HistoryNode* n = nullptr)
        : data(j), prev(p), next(n) {}
};

// Doubly Linked List for Completed Print Jobs History
class JobHistory {
private:
    HistoryNode* head;
    HistoryNode* tail;
    int count;

public:
    JobHistory();
    ~JobHistory();

    // Prevent copying
    JobHistory(const JobHistory&) = delete;
    JobHistory& operator=(const JobHistory&) = delete;

    bool isEmpty() const;
    int getCount() const;

    void append(const PrintJob& job);
    void displayOldestFirst() const;
    void displayNewestFirst() const;
    void clear();
};

#endif // JOB_HISTORY_H
