#include "User.h"

User::User(const string& n, const string& g, const string& e, const string& id, const string& contact)
    : name(n), gender(g), email(e), nid(id), contactNo(contact) {}

string User::getName() const {
    return name;
}

string User::getGender() const {
    return gender;
}

string User::getEmail() const {
    return email;
}

string User::getNID() const {
    return nid;
}

string User::getContactNo() const {
    return contactNo;
}
