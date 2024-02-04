 #include <iostream>
#include <string>

using namespace std;

struct Food {
    string name;
    int quantity;
    double price;
    Food* next;
};

class Restaurant {
private:
    string adminPassword;
    Food* foodList;
    int foodListSize;
    string* deleteHistory;
    int deleteHistoryIndex;
    string* reservationHistory;
    int reservationHistoryIndex;

public:
    Restaurant(string password) : adminPassword(password), foodList(nullptr), foodListSize(0), deleteHistory(new string[100]), deleteHistoryIndex(0),
                                   reservationHistory(new string[100]), reservationHistoryIndex(0) {}

    ~Restaurant() {
        Food* current = foodList;
        while (current != nullptr) {
            Food* next = current->next;
            delete current;
            current = next;
        }

        delete[] deleteHistory;
        delete[] reservationHistory;
    }

    bool adminLogin(string password) {
        return adminPassword == password;
    }

    void addFood(string name, int quantity, double price) {
        Food* newFood = new Food{name, quantity, price, nullptr};
        if (foodList == nullptr) {
            foodList = newFood;
        } else {
            Food* current = foodList;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newFood;
        }
        foodListSize++;
    }

    void updateFood(string name, int quantity, double price) {
        Food* current = foodList;
        while (current != nullptr) {
            if (current->name == name) {
                current->quantity = quantity;
                current->price = price;
                cout << "Food updated successfully!" << endl;
                return;
            }
            current = current->next;
        }

        cout << "Food not found. Adding as a new item." << endl;
        addFood(name, quantity, price);
    }

    void deleteFood(string name) {
        Food* current = foodList;
        Food* prev = nullptr;

        while (current != nullptr) {
            if (current->name == name) {
                if (prev == nullptr) {
                    foodList = current->next;
                } else {
                    prev->next = current->next;
                }

                deleteHistory[deleteHistoryIndex++] = "Deleted " + to_string(current->quantity) + " " + current->name;
                delete current;
                foodListSize--;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Food not found." << endl;
    }

    void showAllItems() {
        cout << "Food Items:\n";
        Food* current = foodList;
        while (current != nullptr) {
            cout << "Name: " << current->name << ", Quantity: " << current->quantity << ", Price: " << current->price << endl;
            current = current->next;
        }
    }

    void searchFoodQuantity(string name) {
        Food* current = foodList;
        while (current != nullptr) {
            if (current->name == name) {
                cout << "Total quantity of " << name << " is: " << current->quantity << endl;
                return;
            }
            current = current->next;
        }
        cout << "Food not found." << endl;
    }

    void searchFoodName(string name) {
        Food* current = foodList;
        cout << "Matching Food Items for Name: " << name << endl;
        bool found = false;
        while (current != nullptr) {
            if (current->name.find(name) != string::npos) {
                cout << "Name: " << current->name << ", Quantity: " << current->quantity << ", Price: " << current->price << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No matching food items found for name: " << name << endl;
        }
    }

    void showDeleteHistory() {
        cout << "Delete History:\n";
        for (int i = 0; i < deleteHistoryIndex; i++) {
            cout << deleteHistory[i] << endl;
        }
    }

    void showReservationHistory() {
        cout << "Reservation History:\n";
        for (int i = 0; i < reservationHistoryIndex; i++) {
            cout << reservationHistory[i] << endl;
        }
    }

    void reserveFood(string name, int quantity) {
        Food* current = foodList;
        while (current != nullptr) {
            if (current->name == name) {
                if (current->quantity >= quantity) {
                    current->quantity -= quantity;
                    reservationHistory[reservationHistoryIndex++] = "Reserved " + to_string(quantity) + " " + name;
                    cout << "Reservation successful! " << quantity << " " << name << " reserved." << endl;
                } else {
                    cout << "Not enough quantity of " << name << " available for reservation." << endl;
                }
                return;
            }
            current = current->next;
        }

        cout << "Food not found." << endl;
    }
};

int main() {
    Restaurant restaurant("12345");

    string adminPassword;
    cout << "Welcome to  Restaurant Management System!" << endl;
    cout << "Enter admin password: ";
    cin >> adminPassword;

    if (restaurant.adminLogin(adminPassword)) {
        cout << "Admin login successful! Welcome to the Admin Menu." << endl;

        int choice;
        do {
            cout << "\nAdmin Menu:" << endl;
            cout << "1. Add Food Item\n2. Update Food\n3. Delete Food Item\n";
            cout << "4. Show All Items\n5. Search Food Name\n6. Show Delete History\n";
            cout << "7. Reserve Food Item\n8. Show Reservation History\n9. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string name;
                    int quantity;
                    double price;
                    cout << "Enter food name: ";
                    cin >> name;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    cout << "Enter price: ";
                    cin >> price;
                    restaurant.addFood(name, quantity, price);
                    break;
                }
                case 2: {
                    string name;
                    int quantity;
                    double price;
                    cout << "Enter food name: ";
                    cin >> name;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    cout << "Enter price: ";
                    cin >> price;
                    restaurant.updateFood(name, quantity, price);
                    break;
                }
                case 3: {
                    string name;
                    cout << "Enter food name to delete: ";
                    cin >> name;
                    restaurant.deleteFood(name);
                    break;
                }
                case 4:
                    restaurant.showAllItems();
                    break;
                case 5: {
                    string name;
                    cout << "Enter food name to search: ";
                    cin >> name;
                    restaurant.searchFoodName(name);
                    break;
                }
                case 6:
                    restaurant.showDeleteHistory();
                    break;
                case 7: {
                    string name;
                    int quantity;
                    cout << "Enter food name to reserve: ";
                    cin >> name;
                    cout << "Enter quantity to reserve: ";
                    cin >> quantity;
                    restaurant.reserveFood(name, quantity);
                    break;
                }
                case 8:
                    restaurant.showReservationHistory();
                    break;
                case 9:
                    cout << "Logout done successful. Exiting from admin menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
            }
        } while (choice != 9);
    } else {
        cout << "Admin login failed. Exiting program." << endl;
    }

    return 0;
}
