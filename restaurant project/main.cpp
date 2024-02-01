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
    string* sellingHistory;
    int sellingHistoryIndex;
    string* reservationHistory;
    int reservationHistoryIndex;

public:
    Restaurant(string password) : adminPassword(password), foodList(nullptr), foodListSize(0), deleteHistory(new string[100]), deleteHistoryIndex(0),
                                   sellingHistory(new string[100]), sellingHistoryIndex(0), reservationHistory(new string[100]), reservationHistoryIndex(0) {}

    ~Restaurant() {

        Food* current = foodList;
        while (current != nullptr) {
            Food* next = current->next;
            delete current;
            current = next;
        }


        delete[] deleteHistory;
        delete[] sellingHistory;
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

    void showDeleteHistory() {
        cout << "Delete History:\n";
        for (int i = 0; i < deleteHistoryIndex; i++) {
            cout << deleteHistory[i] << endl;
        }
    }

    void showSellingHistory() {
        cout << "Selling History:\n";
        for (int i = 0; i < sellingHistoryIndex; i++) {
            cout << sellingHistory[i] << endl;
        }
    }

    void showReservationHistory() {
        cout << "Reservation History:\n";
        for (int i = 0; i < reservationHistoryIndex; i++) {
            cout << reservationHistory[i] << endl;
        }
    }

    void sellFood(string name, int quantity) {
        Food* current = foodList;
        while (current != nullptr) {
            if (current->name == name) {
                if (current->quantity >= quantity) {
                    current->quantity -= quantity;
                    sellingHistory[sellingHistoryIndex++] = "Sold " + to_string(quantity) + " " + name;
                } else {
                    cout << "Not enough quantity of " << name << " available." << endl;
                }
                return;
            }
            current = current->next;
        }

        cout << "Food not found." << endl;
    }

    void reserveFood(string name, int quantity) {
        Food* current = foodList;
        while (current != nullptr) {
            if (current->name == name) {
                if (current->quantity >= quantity) {
                    current->quantity -= quantity;
                    reservationHistory[reservationHistoryIndex++] = "Reserved " + to_string(quantity) + " " + name;
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
    cout << "Enter admin password: ";
    cin >> adminPassword;

