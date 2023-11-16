#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const string ADMIN_PASSWORD = "admin123";

class VendingItem {
public:
    string name;
    double price;
    int quantity;

    VendingItem(const string& itemName, double itemPrice, int itemQuantity)
            : name(itemName), price(itemPrice), quantity(itemQuantity) {}
};

class VendingMachine {
private:
    VendingItem* items;
    size_t itemCount;

public:
    VendingMachine(VendingItem* vendingItems, size_t itemCount)
            : items(vendingItems), itemCount(itemCount) {}

    ~VendingMachine() {
        delete[] items;
    }

    void displayMenu() const {
        cout << "---------------------------" << endl;
        cout << "Vending Machine Menu:" << endl;
        cout << "---------------------------" << endl;

        for (size_t i = 0; i < itemCount; ++i) {
            cout << i + 1 << ". " << setw(15) << left << items[i].name << " $" << items[i].price;

            if (items[i].quantity > 0) {
                cout << "  [In Stock: " << items[i].quantity << "]";
            } else {
                cout << "  [Out of Stock]";
            }

            cout << endl;
        }

        cout << "---------------------------" << endl;
    }

    void processSelection(int choice) {
        if (choice < 1 || choice > static_cast<int>(itemCount)) {
            cout << "Invalid selection. Please try again." << endl;
            return;
        }

        VendingItem& selected = items[choice - 1];

        if (selected.quantity > 0) {
            cout << "You have selected: " << selected.name << endl;
            cout << "Price: $" << selected.price << endl;

            double itemPrice = selected.price;

            double insertedAmount;
            cout << "Please insert money: $";
            cin >> insertedAmount;

            if (insertedAmount >= itemPrice) {
                double change = insertedAmount - itemPrice;

                if (change > 0) {
                    cout << "Change: $" << change << endl;
                }

                selected.quantity--;
                cout << "Thank you for your purchase!" << endl;
            } else {
                cout << "Insufficient funds or invalid input. Transaction canceled." << endl;
            }
        } else {
            cout << "Sorry, " << selected.name << " is out of stock." << endl;
        }
    }

    bool isAdmin(string password) const {
        return password == ADMIN_PASSWORD;
    }

    void updateInventory() {
        cout << "Admin access granted. You can now update the inventory." << endl;

        int itemNumber;
        cout << "Enter the item number to update: ";
        cin >> itemNumber;

        if (itemNumber < 1 || itemNumber > static_cast<int>(itemCount)) {
            cout << "Invalid item number." << endl;
            return;
        }

        VendingItem& selected = items[itemNumber - 1];

        int choice;
        cout << "Select attribute to update (1. Price, 2. Quantity): ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter new price: $";
            cin >> selected.price;
            cout << "Price updated successfully." << endl;
        } else if (choice == 2) {
            cout << "Enter new quantity: ";
            cin >> selected.quantity;
            cout << "Quantity updated successfully." << endl;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
};

int main() {
    VendingItem itemsArray[] = {
            {"Coke", 1.10, 10},
            {"Celcius", 2.00, 10},
            {"Cheetos", 1.50, 10},
            {"Doritos", 1.50, 10},
            {"PopCorners", 1.50, 10},
            {"Snickers", 1.25, 10},
            {"Water", 1.00, 10},
            {"Monster", 2.00, 10}
    };

    VendingMachine vendingMachine(itemsArray, sizeof(itemsArray) / sizeof(VendingItem));

    int choice;
    string password;

    do {
        vendingMachine.displayMenu();

        cout << "Enter the number corresponding to your choice (0 to exit, -1 for admin): ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting vending machine. Thank you!" << endl;
            break;
        } else if (choice == -1) {
            cout << "Enter admin password: ";
            cin >> password;

            if (vendingMachine.isAdmin(password)) {
                vendingMachine.updateInventory();
            } else {
                cout << "Incorrect password. Access denied." << endl;
            }
        } else {
            vendingMachine.processSelection(choice);
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "-----------------------------------------" << endl;

    } while (true);

    return 0;
}