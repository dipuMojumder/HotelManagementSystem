#include "Guest.h"
#include <iostream>

using namespace std;

Guest::Guest(const string& n, const string& g, const string& e,
             const string& id, const string& contact, const string& pass)
    : User(n, g, e, id, contact), password(pass), bookingStatus("No Booking"), dueAmount(0.0), billPaid(false) {}

string Guest::getPassword() const {
    return password;
}

string Guest::getBookingStatus() const {
    return bookingStatus;
}

void Guest::setBookingStatus(const string& status) {
    bookingStatus = status;
}

double Guest::getDueAmount() const {
    return dueAmount;
}

void Guest::addDueAmount(double amount) {
    dueAmount += amount;
}

bool Guest::isBillPaid() const {
    return billPaid;
}

void Guest::setBillPaid(bool paid) {
    billPaid = paid;
}
