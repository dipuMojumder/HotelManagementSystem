// HotelManager.h

#ifndef HOTELMANAGER_H
#define HOTELMANAGER_H

#include "Room.h"
#include "Guest.h"
#include <vector>
#include <unordered_map>

using namespace std;

class HotelManager {
private:
    vector<Room> rooms;
    vector<Guest> guests;
    unordered_map<string, pair<Room*, Guest*>> bookedRooms;

public:
    HotelManager();

    void initializeRooms();
    void displayAllRooms() const;
    void displayAvailableRooms() const;
    void displayAllGuests() const;
    Room* findRoomByNumber(int roomNumber);
    void registerGuest();
    Guest* guestLogin(const string& name, const string& password);
    void bookRoom(Guest& guest);
    void cancelBooking(Guest& guest);
    void checkInRoom(Guest& guest);
    void checkOutRoom(int roomNumber);
    void payGuestBill(Guest& guest);
    void cancelBookingByManager();
    void deleteStoredData();
    void saveGuests();
    void loadGuests();

    // Virtual function declaration
    virtual void displayGuestInfo(const Guest& guest) const;

    // Destructor
    virtual ~HotelManager() = default;
};

#endif // HOTELMANAGER_H
