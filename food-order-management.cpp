
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <limits>
using namespace std;

struct Food {
    int id;
    string name;
    double price;
};

struct Order {
    int id;
    string customer;
    string foodName;
    int quantity;
    double total;
    string status;
};

class FoodOrderManagement {
private:
    vector<Food> menu;
    queue<Order> pendingOrders;
    stack<Order> completedOrders;
    list<Order> orderHistory;
    int nextOrderId = 1001;

public:
    FoodOrderManagement() {
        menu = {
            {1, "Veg Burger", 99},
            {2, "Cheese Pizza", 199},
            {3, "Veg Sandwich", 79},
            {4, "Masala Dosa", 89},
            {5, "French Fries", 69},
            {6, "Paneer Roll", 129},
            {7, "Cold Coffee", 89},
            {8, "Chocolate Brownie", 99}
        };
    }

    void displayMenu() {
        cout << "\n========== FOOD MENU ==========\n";
        cout << left << setw(8) << "ID"
             << setw(25) << "Food Item"
             << "Price (Rs.)\n";
        cout << "------------------------------------------\n";

        for (const auto& food : menu) {
            cout << left << setw(8) << food.id
                 << setw(25) << food.name
                 << fixed << setprecision(2)
                 << food.price << '\n';
        }
    }

    Food* findFood(int id) {
        for (auto& food : menu) {
            if (food.id == id)
                return &food;
        }
        return nullptr;
    }

    void searchFood() {
        string name;
        cout << "Enter food name to search: ";
        getline(cin >> ws, name);

        bool found = false;

        for (const auto& food : menu) {
            if (food.name.find(name) != string::npos) {
                cout << food.id << ". " << food.name
                     << " - Rs. " << food.price << '\n';
                found = true;
            }
        }

        if (!found)
            cout << "Food item not found.\n";
    }

    void sortMenu() {
        sort(menu.begin(), menu.end(),
             [](const Food& a, const Food& b) {
                 return a.price < b.price;
             });

        cout << "\nMenu sorted by price (low to high):\n";
        displayMenu();
    }

    void placeOrder() {
        string customer;
        int foodId, quantity;

        cout << "Enter customer name: ";
        getline(cin >> ws, customer);

        displayMenu();

        cout << "Enter food ID: ";
        if (!(cin >> foodId)) {
            resetInput();
            cout << "Invalid food ID.\n";
            return;
        }

        Food* food = findFood(foodId);

        if (food == nullptr) {
            cout << "Invalid food ID.\n";
            return;
        }

        cout << "Enter quantity: ";
        if (!(cin >> quantity)) {
            resetInput();
            cout << "Invalid quantity.\n";
            return;
        }

        if (quantity <= 0) {
            cout << "Quantity must be greater than zero.\n";
            return;
        }

        Order order;
        order.id = nextOrderId++;
        order.customer = customer;
        order.foodName = food->name;
        order.quantity = quantity;
        order.total = food->price * quantity;
        order.status = "Pending";

        pendingOrders.push(order);
        orderHistory.push_back(order);

        cout << "\nOrder placed successfully!\n";
        printOrder(order);
    }

    void processOrder() {
        if (pendingOrders.empty()) {
            cout << "No pending orders.\n";
            return;
        }

        Order order = pendingOrders.front();
        pendingOrders.pop();

        order.status = "Completed";
        completedOrders.push(order);

        for (auto& oldOrder : orderHistory) {
            if (oldOrder.id == order.id) {
                oldOrder.status = "Completed";
                break;
            }
        }

        cout << "\nOrder processed successfully!\n";
        printOrder(order);
    }

    void viewPendingOrders() {
        if (pendingOrders.empty()) {
            cout << "No pending orders.\n";
            return;
        }

        queue<Order> temp = pendingOrders;

        cout << "\n========== PENDING ORDERS ==========\n";
        while (!temp.empty()) {
            printOrder(temp.front());
            temp.pop();
        }
    }

    void viewOrderHistory() {
        if (orderHistory.empty()) {
            cout << "No order history available.\n";
            return;
        }

        cout << "\n========== ORDER HISTORY ==========\n";

        for (const auto& order : orderHistory)
            printOrder(order);
    }

    void searchOrder() {
        int id;

        cout << "Enter order ID: ";
        if (!(cin >> id)) {
            resetInput();
            cout << "Invalid order ID.\n";
            return;
        }

        for (const auto& order : orderHistory) {
            if (order.id == id) {
                cout << "\nOrder found:\n";
                printOrder(order);
                return;
            }
        }

        cout << "Order not found.\n";
    }

    void viewLastCompletedOrder() {
        if (completedOrders.empty()) {
            cout << "No completed orders yet.\n";
            return;
        }

        cout << "\nMost recently completed order:\n";
        printOrder(completedOrders.top());
    }

    void printOrder(const Order& order) {
        cout << "Order ID: " << order.id
             << " | Customer: " << order.customer
             << " | Item: " << order.foodName
             << " | Quantity: " << order.quantity
             << " | Total: Rs. " << fixed << setprecision(2)
             << order.total
             << " | Status: " << order.status << '\n';
    }

    void resetInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void run() {
        int choice = -1;

        do {
            cout << "\n\n====================================\n";
            cout << "     FOOD ORDER MANAGEMENT SYSTEM\n";
            cout << "====================================\n";
            cout << "1. Display Food Menu\n";
            cout << "2. Search Food Item\n";
            cout << "3. Sort Menu by Price\n";
            cout << "4. Place Order\n";
            cout << "5. Process Next Order\n";
            cout << "6. View Pending Orders\n";
            cout << "7. View Order History\n";
            cout << "8. Search Order by ID\n";
            cout << "9. View Last Completed Order\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                resetInput();
                cout << "Please enter a valid number.\n";
                continue;
            }

            switch (choice) {
                case 1: displayMenu(); break;
                case 2: searchFood(); break;
                case 3: sortMenu(); break;
                case 4: placeOrder(); break;
                case 5: processOrder(); break;
                case 6: viewPendingOrders(); break;
                case 7: viewOrderHistory(); break;
                case 8: searchOrder(); break;
                case 9: viewLastCompletedOrder(); break;
                case 0:
                    cout << "Thank you for using our system!\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }

        } while (choice != 0);
    }
};

int main() {
    FoodOrderManagement app;
    app.run();
    return 0;
}
