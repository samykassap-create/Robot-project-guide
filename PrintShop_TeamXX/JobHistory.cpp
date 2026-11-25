#include "JobHistory.h"

JobHistory::JobHistory() : head(nullptr), tail(nullptr), count(0) {}

JobHistory::~JobHistory() {
    clear();
}

bool JobHistory::isEmpty() const {
    return head == nullptr;
}

int JobHistory::getCount() const {
    return count;
}

void JobHistory::clear() {
    HistoryNode* curr = head;
    while (curr != nullptr) {
        HistoryNode* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

void JobHistory::append(const PrintJob& job) {
    HistoryNode* newNode = new HistoryNode(job, tail, nullptr);
    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
    count++;
}

void JobHistory::displayOldestFirst() const {
    if (isEmpty()) {
        std::cout << "No completed jobs.\n";
        return;
    }

    std::cout << "Completed history: oldest first\n";
    HistoryNode* curr = head;
    while (curr != nullptr) {
        const PrintJob& j = curr->data;
        std::cout << j.jobId << " | Customer " << j.customerId << " | " << j.serviceName
                  << " | " << j.pageCount << (j.pageCount == 1 ? " page" : " pages")
                  << " | EGP " << j.totalPrice << "\n";
        curr = curr->next;
    }
}

void JobHistory::displayNewestFirst() const {
    if (isEmpty()) {
        std::cout << "No completed jobs.\n";
        return;
    }

    std::cout << "Completed history: newest first\n";
    HistoryNode* curr = tail;
    while (curr != nullptr) {
        const PrintJob& j = curr->data;
        std::cout << j.jobId << " | Customer " << j.customerId << " | " << j.serviceName
                  << " | " << j.pageCount << (j.pageCount == 1 ? " page" : " pages")
                  << " | EGP " << j.totalPrice << "\n";
        curr = curr->prev;
    }
}
