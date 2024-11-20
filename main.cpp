#include "HotelManager.h"
#include <iostream>

using namespace std;

void makeRoomAvailable(Room& room) {
    room.cancelBooking();
    cout << "Room " << room.getRoomNumber() << " is now available.\n";
}

int main() {
    HotelManager hotelManager;
    hotelManager.loadGuests();

    while (true) {
        cout << "------------------------\n";
        cout << "1. Manager\n";
        cout << "2. Guest\n";
        cout << "3. Exit\n";
        cout << "------------------------\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string managerUsername = "admin";
            string managerPassword = "adminpass";

            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (username == managerUsername && password == managerPassword) {
                while (true) {
                    cout << "------------------------\n";
                    cout << "1. Display all rooms\n";
                    cout << "2. Display available rooms\n";
                    cout << "3. Display all guests\n";
                    cout << "4. Cancel booking\n";
                    cout << "5. Make room available\n";
                    cout << "6. Delete stored data\n"; // New option for deleting data
                    cout << "7. Logout\n";
                    cout << "------------------------\n";
                    cout << "Choose an option: ";

                    int managerChoice;
                    cin >> managerChoice;

                    switch (managerChoice) {
                    case 1:
                        hotelManager.displayAllRooms();
                        break;
                    case 2:
                        hotelManager.displayAvailableRooms();
                        break;
                    case 3:
                        hotelManager.displayAllGuests();
                        break;
                    case 4:
                        hotelManager.cancelBookingByManager();
                        hotelManager.saveGuests(); // Save data after modifications
                        break;
                    case 5: {
                        int roomNumber;
                        cout << "Enter room number to make available: ";
                        cin >> roomNumber;
                        Room* room = hotelManager.findRoomByNumber(roomNumber);
                        if (room != nullptr) {
                            makeRoomAvailable(*room);
                            hotelManager.saveGuests(); // Save data after modifications
                        } else {
                            cout << "Room not found.\n";
                        }
                        break;
                    }
                    case 6:
                        hotelManager.deleteStoredData(); // Call to delete stored data
                        hotelManager.saveGuests(); // Save data after deletion
                        break;
                    case 7:
                        cout << "Logged out from manager account.\n";
                        break;
                    default:
                        cout << "Invalid choice.\n";
                        break;
                    }

                    if (managerChoice == 7) {
                        break;
                    }
                }
            } else {
                cout << "Invalid credentials.\n";
            }
            break;
        }
        case 2: {
            cout << "------------------------\n";
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Go back\n";
            cout << "------------------------\n";
            cout << "Choose an option: ";

            int guestChoice;
            cin >> guestChoice;

            switch (guestChoice) {
            case 1:
                hotelManager.registerGuest();
                hotelManager.saveGuests(); // Save data after registration
                break;
            case 2: {
                string guestName, guestPassword;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, guestName);
                cout << "Enter password: ";
                getline(cin, guestPassword);

                Guest* guest = hotelManager.guestLogin(guestName, guestPassword);
                if (guest != nullptr) {
                    while (true) {
                        cout << "------------------------\n";
                        cout << "1. Book a room\n";
                        cout << "2. Cancel booking\n";
                        cout << "3. Check in\n";
                        cout << "4. Check out\n";
                        cout << "5. Pay bill\n";
                        cout << "6. Logout\n";
                        cout << "------------------------\n";
                        cout << "Choose an option: ";

                        int guestOption;
                        cin >> guestOption;

                        switch (guestOption) {
                        case 1:
                            hotelManager.bookRoom(*guest);
                            hotelManager.saveGuests(); // Save data after booking
                            break;
                        case 2:
                            hotelManager.cancelBooking(*guest);
                            hotelManager.saveGuests(); // Save data after cancellation
                            break;
                        case 3:
                            hotelManager.checkInRoom(*guest);
                            hotelManager.saveGuests(); // Save data after check-in
                            break;
                        case 4: {
                            int roomNumber;
                            cout << "Enter room number to check out: ";
                            cin >> roomNumber;
                            hotelManager.checkOutRoom(roomNumber);
                            hotelManager.saveGuests(); // Save data after check-out
                            break;
                        }
                        case 5:
                            hotelManager.payGuestBill(*guest);
                            hotelManager.saveGuests(); // Save data after payment
                            break;
                        case 6:
                            cout << "Logged out from guest account.\n";
                            break;
                        default:
                            cout << "Invalid choice.\n";
                            break;
                        }

                        if (guestOption == 6) {
                            break;
                        }
                    }
                } else {
                    cout << "Invalid credentials.\n";
                }
                break;
            }
            case 3:
                cout << "Going back...\n";
                break;
            default:
                cout << "Invalid choice.\n";
                break;
            }
            break;
        }
        case 3:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }

    return 0;
}
