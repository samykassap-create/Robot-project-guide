#include "CustomerList.h"

CustomerList::CustomerList() : head(nullptr), count(0) {}

CustomerList::~CustomerList() {
    clear();
}

bool CustomerList::isEmpty() const {
    return head == nullptr;
}

int CustomerList::getCount() const {
    return count;
}

void CustomerList::clear() {
    CustomerNode* current = head;
    while (current != nullptr) {
        CustomerNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    count = 0;
}

bool CustomerList::insert(int id, const std::string& name) {
    // Check for duplicate ID
    if (find(id) != nullptr) {
        return false;
    }

    Customer newCust = {id, name};
    CustomerNode* newNode = new CustomerNode(newCust, nullptr);

    // Append to end of list to preserve order of registration
    if (head == nullptr) {
        head = newNode;
    } else {
        CustomerNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    count++;
    return true;
}

Customer* CustomerList::find(int id) const {
    CustomerNode* curr = head;
    while (curr != nullptr) {
        if (curr->data.id == id) {
            return const_cast<Customer*>(&(curr->data));
        }
        curr = curr->next;
    }
    return nullptr;
}

void CustomerList::displayAll() const {
    if (head == nullptr) {
        std::cout << "No customers registered.\n";
        return;
    }

    std::cout << "ID   Name\n";
    std::cout << "------------------------------------\n";
    CustomerNode* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data.id << "\t" << curr->data.name << "\n";
        curr = curr->next;
    }
}
