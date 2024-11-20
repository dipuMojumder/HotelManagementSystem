#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string name;
    string gender;
    string email;
    string nid;
    string contactNo;

public:
    User(const string& n, const string& g, const string& e, const string& id, const string& contact);

    string getName() const;
    string getGender() const;
    string getEmail() const;
    string getNID() const;
    string getContactNo() const;
};

#endif // USER_H
