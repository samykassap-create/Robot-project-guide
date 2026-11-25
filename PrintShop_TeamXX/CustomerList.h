#ifndef CUSTOMER_LIST_H
#define CUSTOMER_LIST_H

#include "Models.h"
#include <iostream>

// Node for Singly Linked List
struct CustomerNode {
    Customer data;
    CustomerNode* next;

    CustomerNode(const Customer& c, CustomerNode* n = nullptr)
        : data(c), next(n) {}
};

// Singly Linked List for Customer Records
class CustomerList {
private:
    CustomerNode* head;
    int count;

public:
    CustomerList();
    ~CustomerList();

    // Prevent copying to avoid double deallocation of nodes
    CustomerList(const CustomerList&) = delete;
    CustomerList& operator=(const CustomerList&) = delete;

    bool insert(int id, const std::string& name);
    Customer* find(int id) const;
    void displayAll() const;
    bool isEmpty() const;
    int getCount() const;
    void clear();
};

#endif // CUSTOMER_LIST_H
