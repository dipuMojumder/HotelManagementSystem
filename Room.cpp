#include "Room.h"
#include <iostream>
#include <iomanip>

using namespace std;

Room::Room(int number, const string& style, double p)
    : User("", "", "", "", ""), roomNumber(number), roomStyle(style), price(p), isOccupied(false),
      billAmount(0.0), isCheckedIn(false), numDays(0) {}

int Room::getRoomNumber() const {
    return roomNumber;
}

string Room::getRoomStyle() const {
    return roomStyle;
}

double Room::getPrice() const {
    return price;
}

bool Room::isRoomOccupied() const {
    return isOccupied;
}

string Room::getArrivalDate() const {
    return arrivalDate;
}

string Room::getDepartureDate() const {
    return departureDate;
}

int Room::getNumDays() const {
    return numDays;
}

void Room::bookRoom(const string& arrival, const string& departure, int days) {
    isOccupied = true;
    arrivalDate = arrival;
    departureDate = departure;
    numDays = days;
}

void Room::cancelBooking() {
    isOccupied = false;
    arrivalDate.clear();
    departureDate.clear();
    numDays = 0;
}

void Room::displayRoomInfo() const {
    cout << "Room Number: " << roomNumber << "\n"
         << "Room Style: " << roomStyle << "\n"
         << "Price: Tk " << fixed << setprecision(2) << price << "\n"
         << "Status: " << (isOccupied ? "Occupied" : "Available") << "\n";
    if (isOccupied) {
        cout << "Booking Dates: " << arrivalDate << " to " << departureDate << "\n";
    }
}

bool Room::isChecked() const {
    return isCheckedIn;
}

void Room::checkIn() {
    isCheckedIn = true;
    cout << "Guest checked in.\n";
}

void Room::checkOut() {
    isCheckedIn = false;
    cout << "Guest checked out.\n";
}

void Room::calculateBill() {
    if (isOccupied && isCheckedIn) {
        billAmount = numDays * price;
        cout << "Bill calculated. Total amount due: Tk " << fixed << setprecision(2) << billAmount << endl;
    } else {
        cout << "No guest checked in or room not occupied.\n";
    }
}

double Room::getBillAmount() const {
    return billAmount;
}

void Room::payBill(double amount) {
    if (amount >= billAmount) {
        cout << "Payment successful. Due amount: Tk 0.00\n";
        billAmount = 0.0;
    } else {
        cout << "Insufficient amount. Payment failed.\n";
    }
}
