#ifndef ROOM_H
#define ROOM_H

#include "User.h"
#include <iostream>
#include <string>

using namespace std;

class Room : public User {
private:
    int roomNumber;
    string roomStyle;
    double price;
    bool isOccupied;
    string arrivalDate;
    string departureDate;
    double billAmount;
    bool isCheckedIn;
    int numDays;

public:
    Room(int number, const string& style, double p);

    int getRoomNumber() const;

    string getRoomStyle() const;

    double getPrice() const;

    bool isRoomOccupied() const;

    string getArrivalDate() const;

    string getDepartureDate() const;

    int getNumDays() const;

    void bookRoom(const string& arrival, const string& departure, int days);

    void cancelBooking();

    void displayRoomInfo() const;

    bool isChecked() const;

    void checkIn();

    void checkOut();

    void calculateBill();

    double getBillAmount() const;

    void payBill(double amount);
};

#endif // ROOM_H
