// HotelManager.cpp

#include "HotelManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor
HotelManager::HotelManager() {
    initializeRooms();
}

// Initialize rooms with default values
void HotelManager::initializeRooms() {
    for (int floor = 1; floor <= 3; ++floor) {
        for (int roomNumber = 1; roomNumber <= 5; ++roomNumber) {
            string roomStyle;
            double price;

            int uniqueRoomNumber = floor * 100 + roomNumber;

            if (roomNumber == 3 || roomNumber == 4) {
                roomStyle = "Suite";
                price = 200.0;
            } else if (roomNumber == 5) {
                roomStyle = "Deluxe";
                price = 300.0;
            } else {
                roomStyle = "Standard";
                price = 100.0;
            }

            Room newRoom(uniqueRoomNumber, roomStyle, price);
            rooms.push_back(newRoom);
        }
    }
}

// Display information for all rooms
void HotelManager::displayAllRooms() const {
    if (rooms.empty()) {
        cout << "No rooms available.\n";
    } else {
        cout << "-------- Room Information --------\n";
        for (const auto& room : rooms) {
            room.displayRoomInfo();
            cout << "--------------------------------\n";
        }
    }
}

// Display information for available rooms
void HotelManager::displayAvailableRooms() const {
    if (rooms.empty()) {
        cout << "No rooms available.\n";
    } else {
        cout << "-------- Available Rooms --------\n";
        for (const auto& room : rooms) {
            if (!room.isRoomOccupied()) {
                room.displayRoomInfo();
                cout << "--------------------------------\n";
            }
        }
    }
}

// Display information for all guests
void HotelManager::displayAllGuests() const {
    if (guests.empty()) {
        cout << "No guests registered.\n";
    } else {
        cout << "-------- Guest Information --------\n";
        for (const auto& guest : guests) {
            displayGuestInfo(guest);
        }
    }
}

// Find a room by its number
Room* HotelManager::findRoomByNumber(int roomNumber) {
    for (auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber) {
            return &room;
        }
    }
    return nullptr;
}

// Register a new guest
void HotelManager::registerGuest() {
    string guestName, guestGender, guestEmail, guestNID, guestContact, guestPassword;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, guestName);

    cout << "Enter gender: ";
    getline(cin, guestGender);

    cout << "Enter email: ";
    getline(cin, guestEmail);

    cout << "Enter NID no.: ";
    getline(cin, guestNID);

    cout << "Enter contact no.: ";
    getline(cin, guestContact);

    cout << "Enter password: ";
    getline(cin, guestPassword);

    Guest newGuest(guestName, guestGender, guestEmail, guestNID, guestContact, guestPassword);
    guests.push_back(newGuest);
    cout << "Guest registered successfully!\n";
}

// Guest login function
Guest* HotelManager::guestLogin(const string& name, const string& password) {
    for (auto& guest : guests) {
        if (guest.getName() == name && guest.getPassword() == password) {
            return &guest;
        }
    }
    return nullptr;
}

// Book a room for a guest
void HotelManager::bookRoom(Guest& guest) {
    displayAvailableRooms();

    int roomNumber;
    cout << "Enter the room number you want to book: ";
    cin >> roomNumber;

    Room* selectedRoom = findRoomByNumber(roomNumber);

    if (selectedRoom != nullptr) {
        string arrival, departure;
        int days;
        cout << "Enter arrival date (YYYY-MM-DD): ";
        cin >> arrival;

        cout << "Enter departure date (YYYY-MM-DD): ";
        cin >> departure;

        cout << "Enter number of days staying: ";
        cin >> days;

        selectedRoom->bookRoom(arrival, departure, days);
        bookedRooms[guest.getName()] = make_pair(selectedRoom, &guest);
        guest.setBookingStatus("Booked");
        cout << "Room booked successfully!\n";
    } else {
        cout << "Invalid room number or room is already occupied.\n";
    }
}

// Cancel a booking for a guest
void HotelManager::cancelBooking(Guest& guest) {
    auto it = bookedRooms.find(guest.getName());
    if (it != bookedRooms.end()) {
        Room* bookedRoom = it->second.first;
        bookedRoom->cancelBooking();
        bookedRooms.erase(it);
        guest.setBookingStatus("Canceled");
        cout << "Booking canceled successfully!\n";
    } else {
        cout << "No booking found for the guest.\n";
    }
}

// Check in a guest to a booked room
void HotelManager::checkInRoom(Guest& guest) {
    auto it = bookedRooms.find(guest.getName());
    if (it != bookedRooms.end()) {
        Room* bookedRoom = it->second.first;
        if (!bookedRoom->isChecked()) {
            bookedRoom->checkIn();
            cout << "Guest checked in to room " << bookedRoom->getRoomNumber() << ".\n";
        } else {
            cout << "Room is already checked in.\n";
        }
    } else {
        cout << "No booking found for the guest.\n";
    }
}

// Check out a guest from a room
void HotelManager::checkOutRoom(int roomNumber) {
    Room* selectedRoom = findRoomByNumber(roomNumber);

    if (selectedRoom != nullptr && selectedRoom->isRoomOccupied() && !selectedRoom->isChecked()) {
        selectedRoom->checkOut();
        selectedRoom->calculateBill();

        // Mark the room as available again
        selectedRoom->cancelBooking();

        // Update guest's booking status
        for (auto& pair : bookedRooms) {
            if (pair.second.first->getRoomNumber() == roomNumber) {
                pair.second.second->setBookingStatus("Checked Out");
                break;
            }
        }

        cout << "Guest checked out from room " << roomNumber << ".\n";
    } else {
        cout << "Invalid room number, room is not occupied, or already checked out.\n";
    }
}

// Pay the bill for a guest
void HotelManager::payGuestBill(Guest& guest) {
    auto it = bookedRooms.find(guest.getName());
    if (it != bookedRooms.end()) {
        Room* bookedRoom = it->second.first;
        bookedRoom->calculateBill();
        double amount;
        cout << "Enter amount to pay: ";
        cin >> amount;
        bookedRoom->payBill(amount);
        guest.setBillPaid(amount >= bookedRoom->getPrice() * bookedRoom->getNumDays());
    } else {
        cout << "No booking found for the guest.\n";
    }
}

// Cancel a booking by the manager
void HotelManager::cancelBookingByManager() {
    string guestName;
    cout << "Enter guest name: ";
    cin.ignore();
    getline(cin, guestName);

    auto it = bookedRooms.find(guestName);
    if (it != bookedRooms.end()) {
        Room* bookedRoom = it->second.first;
        bookedRoom->cancelBooking();
        bookedRooms.erase(it);
        cout << "Booking canceled successfully for guest: " << guestName << endl;
    } else {
        cout << "No booking found for the guest.\n";
    }
}

// Delete all stored data
void HotelManager::deleteStoredData() {
    guests.clear();
    bookedRooms.clear();
    cout << "All stored data deleted successfully.\n";
}

// Save guest data to a file
void HotelManager::saveGuests() {
    ofstream outFile("hotel_data.txt");
    if (outFile.is_open()) {
        for (const auto& guest : guests) {
            outFile << guest.getName() << "," << guest.getGender() << "," << guest.getEmail() << ","
                    << guest.getNID() << "," << guest.getContactNo() << "," << guest.getPassword() << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

// Load guest data from a file
void HotelManager::loadGuests() {
    ifstream inFile("hotel_data.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            string name, gender, email, nid, contact, password;
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, gender, ',');
            getline(ss, email, ',');
            getline(ss, nid, ',');
            getline(ss, contact, ',');
            getline(ss, password, ',');
            Guest newGuest(name, gender, email, nid, contact, password);
            guests.push_back(newGuest);
        }
        inFile.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

// Implement virtual function to display guest information
void HotelManager::displayGuestInfo(const Guest& guest) const {
    cout << "Name: " << guest.getName() << "\n"
         << "Gender: " << guest.getGender() << "\n"
         << "Email: " << guest.getEmail() << "\n"
         << "NID: " << guest.getNID() << "\n"
         << "Contact No.: " << guest.getContactNo() << "\n"
         << "Booking Status: " << guest.getBookingStatus() << "\n";

    auto it = bookedRooms.find(guest.getName());
    if (it != bookedRooms.end()) {
        Room* bookedRoom = it->second.first;
        Guest* bookedGuest = it->second.second;
        cout << "Booked Room: " << bookedRoom->getRoomNumber() << "\n";
        cout << "Arrival Date: " << bookedRoom->getArrivalDate() << "\n";
        cout << "Departure Date: " << bookedRoom->getDepartureDate() << "\n";
        cout << "Total Bill: Tk " << fixed << setprecision(2) << bookedRoom->getPrice() * bookedRoom->getNumDays() << endl;
        cout << "Paid: " << (bookedGuest->isBillPaid() ? "Yes" : "No") << endl;
        cout << "Checked " << (bookedRoom->isChecked() ? "In" : "Out") << endl;
    }

    cout << "--------------------------------\n";
}
