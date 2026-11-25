#ifndef MODELS_H
#define MODELS_H

#include <string>

// Service record
struct Service {
    int id;
    std::string name;
    int pricePerPage; // Price in EGP (positive whole number)
};

// Customer record
struct Customer {
    int id;
    std::string name;
};

// Print job record
struct PrintJob {
    int jobId;
    int customerId;
    int serviceId;
    std::string serviceName;
    int pageCount;
    int unitPrice;   // Captured at submission time
    int totalPrice;  // pageCount * unitPrice
};

// Price-change record for undo stack
struct PriceChangeRecord {
    int serviceId;
    int oldPrice;
};

#endif // MODELS_H
