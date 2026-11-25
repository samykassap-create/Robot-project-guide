#include "PrintShop.h"
#include <iostream>
#include <iomanip>

PrintShop::PrintShop() : nextJobId(101) {
    // Initialise the three printing services
    services[0] = {1, "Black-and-white", 2};
    services[1] = {2, "Colour", 5};
    services[2] = {3, "Photo printing", 10};
}

Service* PrintShop::getService(int serviceId) {
    for (int i = 0; i < NUM_SERVICES; ++i) {
        if (services[i].id == serviceId) {
            return &services[i];
        }
    }
    return nullptr;
}

const Service* PrintShop::getService(int serviceId) const {
    for (int i = 0; i < NUM_SERVICES; ++i) {
        if (services[i].id == serviceId) {
            return &services[i];
        }
    }
    return nullptr;
}

void PrintShop::showServices() const {
    std::cout << "ID   Service          Price per page\n";
    std::cout << "------------------------------------\n";
    for (int i = 0; i < NUM_SERVICES; ++i) {
        std::cout << std::left << std::setw(5) << services[i].id
                  << std::setw(17) << services[i].name
                  << "EGP " << services[i].pricePerPage << "\n";
    }
}

bool PrintShop::registerCustomer(int id, const std::string& name) {
    if (id <= 0) {
        std::cout << "Customer ID must be a positive number.\n";
        return false;
    }

    if (!customers.insert(id, name)) {
        std::cout << "Customer ID already exists. The original record is unchanged; no duplicate is added.\n";
        return false;
    }

    std::cout << "Customer registered successfully.\n";
    return true;
}

bool PrintShop::findCustomer(int id) const {
    Customer* cust = customers.find(id);
    if (cust != nullptr) {
        std::cout << "Customer found: " << cust->id << " | " << cust->name << "\n";
        return true;
    } else {
        std::cout << "Customer not found. Customer list is unchanged.\n";
        return false;
    }
}

void PrintShop::listCustomers() const {
    customers.displayAll();
}

bool PrintShop::submitJob(int customerId, int serviceId, int pageCount) {
    // 1. Validate customer existence
    Customer* cust = customers.find(customerId);
    if (cust == nullptr) {
        std::cout << "Customer not found; job not added. Queue remains empty.\n";
        return false;
    }

    // 2. Validate service ID
    Service* serv = getService(serviceId);
    if (serv == nullptr) {
        std::cout << "Invalid service ID; job not added. Queue remains empty.\n";
        return false;
    }

    // 3. Validate page count
    if (pageCount <= 0) {
        std::cout << "Page count must be positive. Neither attempt adds a job.\n";
        return false;
    }

    // 4. Validate queue capacity
    if (waitingQueue.isFull()) {
        std::cout << "Queue is full; job not added. The original 20 jobs remain in order.\n";
        return false;
    }

    // 5. Capture price at time of submission
    int unitPrice = serv->pricePerPage;
    int totalPrice = pageCount * unitPrice;

    PrintJob job = {
        nextJobId,
        customerId,
        serviceId,
        serv->name,
        pageCount,
        unitPrice,
        totalPrice
    };

    waitingQueue.enqueue(job);
    std::cout << "Job " << nextJobId << " added to waiting queue.\n";
    std::cout << "Unit price: EGP " << unitPrice << " | Total: EGP " << totalPrice << "\n";

    nextJobId++;
    return true;
}

void PrintShop::showWaitingJobs() const {
    waitingQueue.display();
}

bool PrintShop::processNextJob() {
    if (waitingQueue.isEmpty()) {
        std::cout << "No waiting jobs to process. History remains empty.\n";
        return false;
    }

    PrintJob job;
    waitingQueue.dequeue(job);
    completedHistory.append(job);

    std::cout << "Processed job " << job.jobId << " | Customer " << job.customerId
              << " | Total EGP " << job.totalPrice << "\n";
    return true;
}

void PrintShop::showHistoryOldestFirst() const {
    completedHistory.displayOldestFirst();
}

void PrintShop::showHistoryNewestFirst() const {
    completedHistory.displayNewestFirst();
}

bool PrintShop::changeServicePrice(int serviceId, int newPrice) {
    Service* serv = getService(serviceId);
    if (serv == nullptr) {
        std::cout << "Invalid service ID. No price changes; undo stack remains empty.\n";
        return false;
    }

    if (newPrice <= 0) {
        std::cout << "Price must be positive. Current price remains EGP " << serv->pricePerPage
                  << "; undo stack stays empty.\n";
        return false;
    }

    if (undoStack.isFull()) {
        std::cout << "Price change stack is full; cannot record undo. Price change rejected.\n";
        return false;
    }

    int oldPrice = serv->pricePerPage;
    PriceChangeRecord rec = {serviceId, oldPrice};
    undoStack.push(rec);

    serv->pricePerPage = newPrice;
    std::cout << "Service " << serviceId << " price changed: EGP " << oldPrice
              << " to EGP " << newPrice << "\n";
    return true;
}

bool PrintShop::undoPriceChange() {
    if (undoStack.isEmpty()) {
        std::cout << "No price changes to undo. All prices remain unchanged.\n";
        return false;
    }

    PriceChangeRecord rec;
    undoStack.pop(rec);

    Service* serv = getService(rec.serviceId);
    if (serv != nullptr) {
        serv->pricePerPage = rec.oldPrice;
        std::cout << "Undo complete: service " << rec.serviceId << " restored to EGP " << rec.oldPrice << "\n";
        return true;
    }

    return false;
}
