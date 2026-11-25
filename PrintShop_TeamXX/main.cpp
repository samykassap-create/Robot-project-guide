#include "PrintShop.h"
#include <iostream>
#include <string>
#include <limits>

void printMainMenu() {
    std::cout << "\nUNIVERSITY PRINT SHOP\n";
    std::cout << " 1. Register customer       7. Process next job\n";
    std::cout << " 2. Find customer           8. History oldest first\n";
    std::cout << " 3. List customers          9. History newest first\n";
    std::cout << " 4. Show services          10. Change service price\n";
    std::cout << " 5. Submit print job       11. Undo price change\n";
    std::cout << " 6. Show waiting jobs       0. Exit\n";
    std::cout << "Choice: > ";
}

bool safeReadInt(int& value, const std::string& prompt) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

int main() {
    PrintShop shop;
    int choice = -1;

    while (true) {
        printMainMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string invalidStr;
            std::cin >> invalidStr;
            std::cout << "Invalid input; please enter a menu number.\n";
            continue;
        }

        if (choice < 0 || choice > 11) {
            std::cout << "Invalid menu option. Program accepts the next valid choice.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Exiting University Print Shop Management System. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: { // Register customer
                int custId = 0;
                if (!safeReadInt(custId, "Customer ID: > ")) {
                    std::cout << "Invalid customer ID format.\n";
                    break;
                }
                std::cout << "Customer name: > ";
                std::string custName;
                std::cin >> std::ws; // Consume leading whitespace/newline
                std::getline(std::cin, custName);
                if (custName.empty()) {
                    std::cout << "Customer name cannot be empty.\n";
                    break;
                }
                shop.registerCustomer(custId, custName);
                break;
            }
            case 2: { // Find customer
                int custId = 0;
                if (!safeReadInt(custId, "Customer ID: > ")) {
                    std::cout << "Invalid customer ID format.\n";
                    break;
                }
                shop.findCustomer(custId);
                break;
            }
            case 3: { // List customers
                shop.listCustomers();
                break;
            }
            case 4: { // Show services
                shop.showServices();
                break;
            }
            case 5: { // Submit print job
                int custId = 0;
                int servId = 0;
                int pages = 0;

                if (!safeReadInt(custId, "Customer ID: > ")) {
                    std::cout << "Invalid customer ID format.\n";
                    break;
                }
                if (!safeReadInt(servId, "Service ID: > ")) {
                    std::cout << "Invalid service ID format.\n";
                    break;
                }
                if (!safeReadInt(pages, "Number of pages: > ")) {
                    std::cout << "Invalid page count format.\n";
                    break;
                }

                shop.submitJob(custId, servId, pages);
                break;
            }
            case 6: { // Show waiting jobs
                shop.showWaitingJobs();
                break;
            }
            case 7: { // Process next job
                shop.processNextJob();
                break;
            }
            case 8: { // History oldest first
                shop.showHistoryOldestFirst();
                break;
            }
            case 9: { // History newest first
                shop.showHistoryNewestFirst();
                break;
            }
            case 10: { // Change service price
                int servId = 0;
                int newPrice = 0;

                if (!safeReadInt(servId, "Service ID: > ")) {
                    std::cout << "Invalid service ID format.\n";
                    break;
                }
                std::string pricePrompt = "Change service " + std::to_string(servId) + " to: > ";
                if (!safeReadInt(newPrice, pricePrompt)) {
                    std::cout << "Invalid price format.\n";
                    break;
                }

                shop.changeServicePrice(servId, newPrice);
                break;
            }
            case 11: { // Undo price change
                shop.undoPriceChange();
                break;
            }
            default:
                break;
        }
    }

    return 0;
}
