/*
 * Authors:
    * Author1: Esraa Emary Abd El-Salam, ID: 20230054
    * Author2: Mohammed Atef Abd El-Kader, ID: 20231143
    * Author3: Mariam Badr Yehia, ID: 20230391
    * Author4: John Ayman Demian, ID: 20230109
    * Author5: George Malak Magdy, ID: 20231042

 * Description: This is a program that manages "Iftar Invitations" which makes you add a guest,
             display it and edit the date of invitation.

 * Version: V1.0
*/

// < ========================================================================================== >

#include <bits/stdc++.h>
using namespace std;

// < ============================== Guest Class ============================== >

class Guest {
    string name;
    string contact;
    string iftar_date;
public:
    Guest() = default;
    Guest(string guestName, string guestContact, string guestIftar_date);
    string getName();
    void display_guest();
    void update_invitation(string new_date);
};

// < ============================== Iftar Manager Class ============================== >

class IftarManager {
    Guest* guestList = new Guest[0];
    int size = 0;
public:
    void add_guest(Guest guest);
    void display_all_guests();
    void update_guest_invitation(string name, string new_date);
    void send_reminder(string date);
    void sort_guest_list();
};

// < ============================== Implementation For Guest Class ============================== >
// < ============================== Constructor ============================== >

Guest::Guest(string guestName, string guestContact, string guestIftar_date) {
    // Regular Expressions for phone number, email, and date.
    regex namePattern("[A-Za-z ]+$");
    regex phoneNumberPattern("(010|011|012|015)\\d{8}$");
    regex emailPattern("^[A-Za-z0-9][A-Za-z0-9._-]*@(gmail|yahoo|outlook|hotmail)\\.com$");
    regex datePattern("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$");

    // Check if the guest name is valid and assign it.
    while (true) {
        if (regex_match(guestName, namePattern)) {
            this->name = guestName;
            break;
        }

        cout << "Invalid Name, it should contain only letters." << endl;
        cout << "Please enter a valid guest name: ";
        getline(cin, guestName);
    }

    // Check if the guest contact (phone number or email) is valid and assign it.
    while (true) {
        if (regex_match(guestContact, phoneNumberPattern) || regex_match(guestContact, emailPattern)) {
            this->contact = guestContact;
            break;
        }

        cout << "Invalid Contact." << endl;
        cout << "Please enter a valid guest contact: ";
        getline(cin, guestContact);
    }

    // Check if the guest iftar date is valid and assign it.
    while (true) {
        if (regex_match(guestIftar_date, datePattern)) {
            // Last day of every month in a non-leap year (Note: The array is 1-based).
            int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            // Extract year, month, and day from the date string.
            int year = stoi(guestIftar_date.substr(0, 4));
            int month = stoi(guestIftar_date.substr(5, 2));
            int day = stoi(guestIftar_date.substr(8, 2));

            // Adjust February for leap years.
            if ((year %4 == 0 && year %100 != 0) || (year %400 == 0)) daysInMonth[2] = 29;

            if (day <= daysInMonth[month]) {
                this->iftar_date = guestIftar_date;
                break;
            }

            else cout << "Invalid Date, it should be in the format YYYY-MM-DD." << endl;
        }
        else cout << "Invalid Date, it should be in the format YYYY-MM-DD." << endl;

        cout << "Please, Enter a valid guest iftar date: ";
        getline(cin, guestIftar_date);
    }
}
// <============================== get Name Function ============================== >

string Guest::getName() {
    return this->name;
}

// <============================== display_guest Function ============================== >

void Guest::display_guest() {
     cout << this->name << ", " << "Contact: " << this->contact << ", " << "Iftar Date: " << this->iftar_date << endl;
}

// <============================== update_invitation Function ============================== >

void Guest::update_invitation(string new_date) {
       this->iftar_date = new_date;
}

// < ============================== Implementation For Iftar Manager Class ============================== >
// < ============================== add_guest Function ============================== >

void IftarManager::add_guest(Guest guest) {
    // Create a new guest list with a size of one more than the current size.
    auto* newGuest = new Guest[this->size + 1];
    for (int i = 0; i < this->size; i++) {
        newGuest[i] = this->guestList[i];
    }

    // Delete the old guest list and assign the new guest list.
    delete[] this->guestList;
    this->guestList = newGuest;

    // Add the new guest to the list and increment the size.
    newGuest[this->size] = guest;
    this->size++;

    sort_guest_list();      // Sort the guest list after adding a new guest.
}

// < ============================== display_all_guests Function ============================== >

void IftarManager::display_all_guests() {
    for (int i = 0; i < this->size; i++) {
        cout << "Guest: " ; this->guestList[i].display_guest();
    }
    cout << endl;
}

// < ============================== update_guest_invitation Function ============================== >

void IftarManager::update_guest_invitation(string name, string new_date) {
    for (int i = 0; i < this->size; i++) {
        if (guestList[i].getName() == name) {
            guestList[i].update_invitation(new_date);
        }
    }
    cout << "Updating invitation for " + name + "..." << endl;
}

// < ============================== send_reminder Function ============================== >

void IftarManager::send_reminder(string date) {

    cout << "Sending reminders... " << endl;
}

// < ============================== sort_guest_list Function ============================== >

void IftarManager::sort_guest_list() {

}

// < ============================== Main Function ============================== >

int main() {
    auto manager = IftarManager();
    string name, newIftarDate, contact, iftarDate, date ;

    cout << "Please, Enter guest name: ";
    getline(cin, name);
    cout << "Please, Enter guest contact: ";
    getline(cin, contact);
    cout << "Please, Enter guest iftar date should be in the format (YYYY-MM-DD): ";
    getline(cin, iftarDate);
    Guest guest(name, contact, iftarDate);
    manager.add_guest(guest);                           // Add guests

    manager.display_all_guests();                       // Display the guest list

    cout << "Please, Enter guest name: ";
    getline(cin, name);
    cout << "Please, Enter guest's new Date: ";
    getline(cin, newIftarDate);
    manager.update_guest_invitation(name, newIftarDate);   // Update invitation date for Omar

    manager.display_all_guests();               // Display the updated guest list

    cout << "Please, Enter date to send reminders: ";
    getline(cin, date);
    manager.send_reminder(date);                   // Send reminders

    return 0;
}