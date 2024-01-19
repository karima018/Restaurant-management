#include <iostream>
#include <vector>
#include <map>
using namespace std;
class Restaurant {
public:
    void addReservation(const string& name, const string& time) {
        reservations[time].push_back(name);
    }

    string getNameByTime(const string& time) {
        if (reservations.find(time) != reservations.end()) {
            return reservations[time][0];
        }
        return "No reservation at that time";
    }

private:
    map<string, vector<string>> reservations;
};

int main() {
    Restaurant restaurant;

    restaurant.addReservation("karima", "12:00");
    restaurant.addReservation("Abid", "1:00");
    restaurant.addReservation("Khadiza", "10:00");
    restaurant.addReservation("Mim", "11:00");
    restaurant.addReservation("zerin", "3:00");
    restaurant.addReservation("Munni", "3:00 PM");
    restaurant.addReservation("Munni", "10:00 AM");




    cout << "Name at 12:00: " << restaurant.getNameByTime("12:00") << "\n";
    cout << "Name at 13:00: " << restaurant.getNameByTime("1:00") << "\n";
    cout << "Name at 10:00: " << restaurant.getNameByTime("10:00") << "\n";
    cout << "Name at 11:00: " << restaurant.getNameByTime("11:00") << "\n";
    cout << "Name at 3:00: " << restaurant.getNameByTime("3:00") << "\n";
    cout << "Name at 3:00PM: " << restaurant.getNameByTime("3:00PM") << "\n";
    cout << "Name at 10:00 AM: " << restaurant.getNameByTime("3:00 AM") << "\n";


    return 0;
}
