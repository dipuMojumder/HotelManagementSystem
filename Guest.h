#ifndef GUEST_H
#define GUEST_H

#include "User.h"
#include <iostream>
#include <string>

using namespace std;

class Guest : public User {
private:
    string password;
    string bookingStatus;
    double dueAmount;
    bool billPaid;

public:
    Guest(const string& n, const string& g, const string& e,
          const string& id, const string& contact, const string& pass);

    string getPassword() const;

    string getBookingStatus() const;

    void setBookingStatus(const string& status);

    double getDueAmount() const;

    void addDueAmount(double amount);

    bool isBillPaid() const;

    void setBillPaid(bool paid);
};

#endif // GUEST_H
