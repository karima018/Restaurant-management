
#include <iostream>
using namespace std;

int main() {
  int choice;
  cout << "1. Menu Card\n2. Restaurant Reservation\n3. Bill Payment\nChoice: ";
  cin >> choice;

  if (choice == 1) {
    // Display menu card
    cout << "**Menu Card**\n";
    cout << "1. Pizza - 400tk\n";
    cout << "2. Pasta - 350tk\n";
    cout << "3. Salad - 200tk\n";
    cout << "1. cake - 500tk\n";
    cout << "2. juice - 150tk\n";
    cout << "3. ice-cream -220tk\n";
  } else if (choice == 2) {
    // Make reservation
    int numTables;
cout << "Enter number of tables (maximum 10): ";
cin >> numTables;

if (numTables > 10) {
  cout << "Sorry, we can only reserve a maximum of 10 tables.\n";
} else {
  cout << "Reservation confirmed for " << numTables << " tables.\n";
}


    cout << "Reservation confirmed for " << numTables << " tables.\n";
  } else if (choice == 3) {
    // Pay bill
    float billAmount;
cout << "Enter bill amount: ";
cin >> billAmount;

if (billAmount > 0) {
  cout << "Bill paid successfully.\n";
} else {
  cout << "Invalid bill amount.\n";
}
  }

  return 0;

}
