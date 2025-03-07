/*
Author1: Esraa Emary Abd El-Salam
ID1: 20230054

Author2: Mohammed Atef Abd El-Kader
ID2: 20231143

Author3: Mariam Badr Yehia
ID3: 20230391

Author4: John Ayman Demian
ID4: 20230109

Author5: George Malak Magdy
ID5: 20231042

Description: This is a program that manage "Iftar Invitations" which make you add a guest,
             display it and edit date of invitation.

Version: v1.0
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
    Guest() {}

    Guest(string guestName, string guestContact, string guestIftar_date);

    void display_guest();

    void update_invitation(string new_date);
};


// < ============================== Iftar Manager Class ============================== >
class IftarManager {
    Guest guestList[100];
public:
    void add_guest(Guest guest);

    void display_all_guests();

    void update_guest_invitation(string name, string new_date);

    void send_reminder(string date);

    void sort_guest_list();
};


// < ============================== Implementation For Guest Class ============================== >
// < ============================== Constructor ============================== >
Guest::Guest(std::string guestName, std::string guestContact, std::string guestIftar_date) {
    name = guestName;
    contact = guestContact;
    iftar_date = guestIftar_date;
}

// <============================== display_guest Function ============================== >
void Guest::display_guest() {

}

// <============================== update_invitation Function ============================== >
void Guest::update_invitation(string new_date) {

    cout << "Updating invitation for Omar..." << endl;
}


// < ============================== Implementation For Iftar Manager Class ============================== >
// < ============================== add_guest Function ============================== >
void IftarManager::add_guest(Guest guest) {


    sort_guest_list();
}

// < ============================== display_all_guests Function ============================== >
void IftarManager::display_all_guests() {

}

// < ============================== update_guest_invitation Function ============================== >
void IftarManager::update_guest_invitation(std::string name, std::string new_date) {

}

// < ============================== send_reminder Function ============================== >
void IftarManager::send_reminder(std::string date) {

    cout << "Sending reminders... " << endl;
}

// < ============================== sort_guest_list Function ============================== >
void IftarManager::sort_guest_list() {

}


// < ============================== Main Function ============================== >
int main() {
    IftarManager manager;
    string name, newName, contact, iftarDate, date;

    cout << "Please enter guest name: ";
    getline(cin, name);
    cout << "Please enter guest contact: ";
    getline(cin, contact);
    cout << "Please enter guest iftar date: ";
    getline(cin, iftarDate);
    Guest guest(name, contact, iftarDate);
    manager.add_guest(guest);                           // Add guests

    manager.display_all_guests();                       // Display guest list

    cout << "Please enter guest name: ";
    getline(cin, name);
    cout << "Please enter guest's new name: ";
    getline(cin, newName);
    manager.update_guest_invitation(name, newName);   // Update invitation date for Omar

    manager.display_all_guests();               // Display updated guest list

    cout << "Please enter date to send reminders: ";
    getline(cin, date);
    manager.send_reminder(date);                   // Send reminders
    return 0;
}