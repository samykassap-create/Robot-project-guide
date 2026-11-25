#ifndef PRINT_SHOP_H
#define PRINT_SHOP_H

#include "Models.h"
#include "CustomerList.h"
#include "JobQueue.h"
#include "JobHistory.h"
#include "PriceStack.h"
#include <string>

class PrintShop {
public:
    static const int NUM_SERVICES = 3;

private:
    Service services[NUM_SERVICES];
    CustomerList customers;
    JobQueue waitingQueue;
    JobHistory completedHistory;
    PriceStack undoStack;
    int nextJobId;

    Service* getService(int serviceId);
    const Service* getService(int serviceId) const;

public:
    PrintShop();
    ~PrintShop() = default;

    // Prevent copying
    PrintShop(const PrintShop&) = delete;
    PrintShop& operator=(const PrintShop&) = delete;

    void showServices() const;
    bool registerCustomer(int id, const std::string& name);
    bool findCustomer(int id) const;
    void listCustomers() const;
    bool submitJob(int customerId, int serviceId, int pageCount);
    void showWaitingJobs() const;
    bool processNextJob();
    void showHistoryOldestFirst() const;
    void showHistoryNewestFirst() const;
    bool changeServicePrice(int serviceId, int newPrice);
    bool undoPriceChange();
};

#endif // PRINT_SHOP_H
