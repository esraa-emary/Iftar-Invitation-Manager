/*
 * Authors:
    * Author1: Esraa Emary Abd El-Salam      ID: 20230054
    * Author2: Mariam Badr Yehia             ID: 20230391
    * Author3: John Ayman Demian             ID: 20230109
    * Author4: Mohammed Atef Abd El-Kader    ID: 20231143
    * Author5: George Malak Magdy            ID: 20231042
 * Date : 8/3/2025
 * Prof : Dr. Besheer
 * Description: This is a program that manages "Iftar Invitations" which makes you add a guest,
                display it and edit the date of invitation.
 * Version: V3.0
*/
// < ========================================================================================== >

#include <bits/stdc++.h>

using namespace std;

// ----------------------------------------------- Prototype of the helper function

bool is_PositiveInt(const string &str);
bool isValidDate(const string &date) ;
bool isValidContact(const string &contact);
bool isValidName(const string &name);

// ----------------------------------------------- CURRENT DATE

const string current_date = "2025-03-24";


// ----------------------------------------------- GUEST CLASS

class Guest {
    string name;
    string contact;
    string iftar_date;

public:
    Guest() = default;

    Guest(string guestName, string guestContact, string guestIftar_date);

    void display_guest() const;

    void update_invitation(const string &new_date);

    // getters.
    string getName();

    string getDate();

    string getMail();

    // operator overloading.
    bool operator<(Guest &other);
};

// ----------------------------------------------- IFTAR MANAGER CLASS

class IftarManager {
    Guest *guestList = new Guest[0];
    int no_guests = 0;

    void Merge(Guest *Guest_List_sort, int Right, int Middle, int Left);

    void Help_Merge_sorting(Guest *Temp, int Left, int Right);

public:
    ~IftarManager();

    void add_guest(const Guest &guest);

    void remove_guest(const string &name);

    void display_all_guests() const;

    void update_guest_invitation(string name, string new_date);

    void send_reminder(string date) const;

    void sort_guest_list();
};

// ----------------------------------------------- IMPLEMENTATION FOR GUEST CLASS

// ----------------------------------------------- CONSTRUCTOR

Guest::Guest(string guestName, string guestContact, string guestIftar_date) {
    // Check if the guest name is valid and assign it.
    while (true) {
        if (isValidName(guestName)) {
            this->name = guestName;
            break;
        }

        cout << "Invalid Name, it should contain only letters." << endl;
        cout << "Please enter a valid guest name: ";
        getline(cin, guestName);
    }

    // Check if the guest contact (phone number or email) is valid and assign it.
    while (true) {
        if (isValidContact(guestContact)) {
            this->contact = guestContact;
            break;
        }

        cout << "Invalid Contact." << endl;
        cout << "Please enter a valid guest contact: ";
        getline(cin, guestContact);
    }

    // Check if the guest iftar date is valid and assign it.
    while (true) {
        if (isValidDate(guestIftar_date)) {
            this->iftar_date = guestIftar_date;
            break;
        }

        cout << "Invalid Date, it should be in the format (YYYY-MM-DD)." << endl;
        cout << "Please, Enter a valid guest iftar date: ";
        getline(cin, guestIftar_date);
    }
}

// ----------------------------------------------- GETTERS FUNCTIONS

string Guest::getName() {
    return this->name;
}

string Guest::getDate() {
    return this->iftar_date;
}

string Guest::getMail() {
    return this->contact;
}

// ---------------------------------------------- DISPLAY GUEST FUNCTION

void Guest::display_guest() const {
    cout << this->name << ", " << "Contact: " << this->contact << ", " << "Iftar Date: " << this->iftar_date << endl;
}

// ----------------------------------------------- UPDATE INVITATION FUNCTION

void Guest::update_invitation(const string &new_date) {
    this->iftar_date = new_date;
}

// ----------------------------------------------- OVERLOADING FUNCTIONS

bool Guest::operator<(Guest &other) {
    // Extract year, month, and day from the date string of both guests to compare them.
    const int tempYear1 = stoi(getDate().substr(0, 4));
    const int tempMonth1 = stoi(getDate().substr(5, 2));
    int tempDay1 = stoi(getDate().substr(8, 2));

    const int tempYear2 = stoi(other.getDate().substr(0, 4));
    const int tempMonth2 = stoi(other.getDate().substr(5, 2));
    int tempDay2 = stoi(other.getDate().substr(8, 2));

    // Compare the dates of the two guests.
    if (tempYear1 != tempYear2) return tempYear1 < tempYear2;
    if (tempMonth1 != tempMonth2) return tempMonth1 < tempMonth2;
    if (tempDay1 != tempDay2) return tempDay1 < tempDay2;

    return this->name < other.name;
}

// ----------------------------------------------- IMPLEMENTATION FOR IFTAR MANAGER CLASS

// ----------------------------------------------- ADD GUEST FUNCTION

void IftarManager::add_guest(const Guest &guest) {
    // Create a new guest list with a size of one more than the current size.
    auto *newGuest = new Guest[this->no_guests + 1];
    for (int i = 0; i < this->no_guests; i++) {
        newGuest[i] = this->guestList[i];
    }

    // Delete the old guest list and assign the new guest list.
    newGuest[this->no_guests] = guest;
    delete[] this->guestList;

    // Add the new guest to the list and increment the size.
    this->guestList = newGuest;
    this->no_guests++;
    sort_guest_list();      // Sort the guest list after adding a new guest.
}

// ----------------------------------------------- DISPLAY ALL GUESTS FUNCTION

void IftarManager::display_all_guests() const {
    if (this->no_guests == 0) {
        cout << "No Guests Now to Print. " << endl;
    } else {
        for (int i = 0; i < this->no_guests; i++) {
            cout << "Guest: ";
            this->guestList[i].display_guest();
        }
        cout << endl;
    }
}

// ----------------------------------------------- UPDATE GUEST INVITATION FUNCTION

void IftarManager::update_guest_invitation(string name, string new_date) {
    if (this->no_guests == 0) {
        cout << "There is no guest to remove." << endl;
        return;
    }

    bool found = false;
    while (isValidName(new_date)) {
        cout << "Invalid Date, it should be in the format YYYY-MM-DD." << endl;
        cout << "Please, Enter a valid guest iftar date: ";
        getline(cin, new_date);
    }

    // Check Valid name
    while (true) {
        for (int i = 0; i < this->no_guests; i++) {
            if (guestList[i].getName() == name) {
                guestList[i].update_invitation(new_date);
                found = true;
            }
        }
        if (found) break;
        cout << "Please, Enter a valid name in Guests invitation List: ";
        getline(cin, name);
    }

    cout << "Updating invitation for " + name + "..." << endl << endl;
    sort_guest_list();      // Sort the guest list after updating the guest's date.
}

// ----------------------------------------------- SEND REMINDER FUNCTION

void IftarManager::send_reminder(string date) const {
    int retry_count = 3; // Prevent infinite loop
    while (retry_count--) {
        if (isValidDate(date)) {
            bool found = false;
            cout << "Sending Reminder..." << endl;

            for (int i = 0; i < this->no_guests; i++) {
                if (this->guestList[i].getDate() == date) {
                    found = true;
                    const regex emailPattern(
                            "^[A-Za-z0-9][A-Za-z0-9._-]*@(gmail|yahoo|outlook|hotmail)\\.com$", regex_constants::icase);

                    if (regex_match(guestList[i].getMail(), emailPattern)) {
                        string guest_name = guestList[i].getName();
                        string api_key_public = "db50e3d92c0c72ac9296163768e4b994";
                        string api_key_private = "be920e0b4089be96d539f7b250324d97";
                        string to_email = guestList[i].getMail();
                        string from_email = "fcaicu.assignments@gmail.com";
                        string subject = "Reminder for Iftar Invitation on " + date;

                        string message_body = "Dear " + guest_name + ", Your Iftar invitation is on " + date +
                                              ". Looking forward to seeing you! Best regards, Iftar Manager";


                        string json_payload = "{"
                                              "\"Messages\":[{"
                                              "\"From\":{"
                                              "\"Email\":\"" + from_email + "\","
                                                                            "\"Name\":\"" + "Fake Mail" + "\""
                                                                                                          "},"
                                                                                                          "\"To\":[{"
                                                                                                          "\"Email\":\"" +
                                              to_email + "\","
                                                         "\"Name\":\"" + guest_name + "\""
                                                                                      "}],"
                                                                                      "\"Subject\":\"" + subject + "\","
                                                                                                                   "\"TextPart\":\"" +
                                              message_body + "\""
                                                             "}]"
                                                             "}";

                        string escaped_payload;
                        for (char c: json_payload) {
                            if (c == '"') escaped_payload += "\\\"";
                            else if (c == '\\') escaped_payload += "\\\\";
                            else escaped_payload += c;
                        }

                        string curl_command = "curl -X POST https://api.mailjet.com/v3.1/send "
                                              "-H \"Content-Type: application/json\" "
                                              "-u \"" + api_key_public + ":" + api_key_private + "\" "
                                                                                                 "-d \"" +
                                              escaped_payload + "\"";

                        cout << "\nSending reminder to " << to_email << "..." << endl;
                        system(curl_command.c_str());
                    }

                    cout << "Reminder sent to " << guestList[i].getName()
                         << ": Your Iftar invitation is on " << date << "!" << endl;
                }
            }

            if (!found) {
                cout << "No Guest has this Iftar date." << endl;
            }

            return; // Exit the function after processing
        }

        if (retry_count > 0) {
            cout << "Please enter a valid date: ";
            getline(cin, date);
        } else {
            cout << "Too many invalid attempts. Exiting reminder function." << endl;
        }
    }

    cout << "\nMay your Iftar gatherings be full of warmth and blessings!" << endl;
}

// ----------------------------------------------- SORT GUEST LIST WITH MERGE FUNCTION

void IftarManager::Merge(Guest *GS, int Left, int Middle, int Right) {
    const int SizeArr1 = Middle - Left + 1;
    const int SizeArr2 = Right - Middle;
    Guest Arr1[SizeArr1], Arr2[SizeArr2];
    for (int i = 0; i < SizeArr1; ++i) {
        Arr1[i] = GS[Left + i];
    }
    for (int i = 0; i < SizeArr2; ++i) {
        Arr2[i] = GS[Middle + 1 + i];
    }

    // Merge the two arrays into GS [Left, Right].
    int StartArr1 = 0, StartArr2 = 0, TempLeft = Left;
    while ((StartArr1 < SizeArr1) && (StartArr2 < SizeArr2)) {
        if (Arr1[StartArr1] < Arr2[StartArr2]) {
            GS[TempLeft] = Arr1[StartArr1];
            ++StartArr1;
        } else {
            GS[TempLeft] = Arr2[StartArr2];
            ++StartArr2;
        }
        ++TempLeft;
    }

    // Copy the remaining elements of Arr1 and Arr2 if there are any.
    while (StartArr1 < SizeArr1) {
        GS[TempLeft] = Arr1[StartArr1];
        ++StartArr1;
        ++TempLeft;
    }
    while (StartArr2 < SizeArr2) {
        GS[TempLeft] = Arr2[StartArr2];
        ++StartArr2;
        ++TempLeft;
    }
}

void IftarManager::Help_Merge_sorting(Guest *Temp, int Left, int Right) {
    if (Left < Right) {
        const int Middle = Left + (Right - Left) / 2;
        Help_Merge_sorting(Temp, Left, Middle);
        Help_Merge_sorting(Temp, Middle + 1, Right);
        Merge(Temp, Left, Middle, Right);
    }
}

void IftarManager::sort_guest_list() {
    Help_Merge_sorting(this->guestList, 0, this->no_guests - 1);
}

// ----------------------------------------------- REMOVE FUNCTION

void IftarManager::remove_guest(const string &name) {
    if (this->no_guests == 0) {
        cout << "There is no guest to remove." << endl;
        return;
    }

    // Create temp guest list and boolean to check if guest exists
    bool found = false;
    auto *Temp_list = new Guest[no_guests - 1];
    int temp_ind = 0;

    while (true) {
        temp_ind = 0;
        for (int i = 0; i < this->no_guests; i++) {
            if (guestList[i].getName() == name && !found) {
                found = true;
            } else if (temp_ind < this->no_guests - 1) {
                Temp_list[temp_ind++] = this->guestList[i];
            }
        }

        if (found) break;
        cout << "Guest Not Found in Iftar invitation list !" << endl;
        delete[] Temp_list;
        return;
    }

    // Free main guestlist and update it with temp list
    delete[] this->guestList;
    this->guestList = Temp_list;
    --this->no_guests;
    cout << "Guest is removed from the Iftar invitation list...." << endl;
}

// ----------------------------------------------- DESTRUCTOR

IftarManager::~IftarManager() {
    delete[] guestList;
}

// ----------------------------------------------- ANOTHER SOME HELPER FUNCTIONS

void runFromTerminal() {
    IftarManager manager = IftarManager();
    while (true) {
        string name, numOfGuests ,choice;
        long long numofGuests  ;

        cout << "\n1) Add new guest." << endl;
        cout << "2) Remove guest." << endl;
        cout << "3) Update Guest Invitation." << endl;
        cout << "4) Send Reminder." << endl;
        cout << "5) Display All Guest List." << endl;
        cout << "6) Exit." << endl;

        cout << endl << "Please, Select an option : ";
        getline(cin , choice);

        while ( choice != "1" &&  choice != "2" && choice != "3" && choice !="4" && choice !="5" && choice !="6" ){
            cout << "Invalid choice, \nPlease, enter valid choice: ";
            getline(cin , choice);
        }
        cout << endl;

        if (choice == "1") {
            string contact , date;
            cout << "Please, enter number of guests you want to Add : ";
            getline(cin , numOfGuests);

            while (!is_PositiveInt(numOfGuests)) {
                cout << "Invalid Input, \n Please, enter valid number : ";
                getline(cin , numOfGuests);
            }

             numofGuests = stoll(numOfGuests);

            for (int i = 0; i < numofGuests; i++) {
                cout << "Please, enter name of guest " << i + 1 << " : ";
                getline(cin, name);

                cout << "Please, enter contact (email or phone number) of guest " << i + 1 << " : ";
                getline(cin, contact);
                
                cout << "Please, enter invitation date (YYYY-MM-DD) of guest " << i + 1 << " : ";
                getline(cin, date);

                auto Add_Guest = Guest(name, contact, date);
                manager.add_guest(Add_Guest);
                cout << endl;
            }
        }else if (choice == "2") {

            cout << "Please, enter number of guests you want to remove: ";
            getline(cin , numOfGuests);

            while (!is_PositiveInt(numOfGuests)) {
                cout << "Invalid Input, \n Please, enter valid number : ";
                getline(cin , numOfGuests);
            }

            for (int i = 0; i < numofGuests; i++) {
                cout << "Please, enter name of guest " << i + 1 << " : ";
                getline(cin, name);
                manager.remove_guest(name);
                cout << endl;
            }

        }else if (choice == "3") {
            string new_date , guestName;

            cout << "Please, enter name of guest: ";
            getline(cin, guestName);
            cout << "Please, enter new invitation date (YYYY-MM-DD): ";
            getline(cin, new_date);

            manager.update_guest_invitation(guestName, new_date);

        }else if (choice == "4") {
            string reminder;
            cout << "Please, enter date you want to send reminder message to all guests on this date: ";
            getline(cin, reminder);
            manager.send_reminder(reminder);

        }else if (choice == "5") {
            manager.display_all_guests();

        }else if (choice == "6") {
            return;
        }
    }
}

void initializeInMAin() {
    cout << endl;

    // ----------------------------------------------- TEST 1
    cout << "// ----------------------------------------------- TEST 1\n\n";
    // Create Iftar Manager
    IftarManager manager = IftarManager();

    // Add guests
    Guest guest1 = Guest("Aisha", "aisha@gmail.com", "2025-03-15");
    Guest guest2 = Guest("Omar", "omar@gmail.com", "2025-03-18");
    Guest guest3 = Guest("Zainab", "zainab@gmail.com", "2025-03-20");

    manager.add_guest(guest1);
    manager.add_guest(guest2);
    manager.add_guest(guest3);

    // Display guest list
    manager.display_all_guests();

    // Update invitation date for Omar
    manager.update_guest_invitation("Omar", "2025-03-15");

    // Display updated guest lis
    manager.display_all_guests();

    // Send reminders
    manager.send_reminder("2025-03-15");


    // ----------------------------------------------- TEST 2
    cout << "\n// ----------------------------------------------- TEST 2\n\n";
    // Create Iftar Manager
    IftarManager manager2 = IftarManager();

    // Add guests
    Guest guest4 = Guest("mona", "mona@gmail.com", "2025-03-22");
    Guest guest5 = Guest("ahmed", "ahmed@yahoo.com", "2025-03-25");
    Guest guest6 = Guest("esraa", "01123456789", "2025-03-20");

    manager2.add_guest(guest4);
    manager2.add_guest(guest5);
    manager2.add_guest(guest6);

    // Display guest list
    manager2.display_all_guests();

    // Update invitation date for Omar
    manager2.update_guest_invitation("mona", "2025-03-20");

    // Display updated guest lis
    manager2.display_all_guests();

    // Send reminders
    manager2.send_reminder("2025-03-20");

    // Delete guest
    manager2.remove_guest("ahmed");


    // ----------------------------------------------- TEST 3
    cout << "\n// ----------------------------------------------- TEST 3\n\n";
    // Create Iftar Manager
    IftarManager manager3 = IftarManager();

    // Add guests
    Guest guest7 = Guest("john", "john@outlook.com", "2025-03-22");
    Guest guest8 = Guest("mohammed", "mohammed@hotmail.com", "2025-03-25");
    Guest guest9 = Guest("george", "01123456789", "2025-03-20");

    manager3.add_guest(guest7);
    manager3.add_guest(guest8);
    manager3.add_guest(guest9);

    // Display guest list
    manager3.display_all_guests();

    // Update invitation date for Omar
    manager3.update_guest_invitation("george", "2025-03-22");

    // Display updated guest lis
    manager3.display_all_guests();

    // Send reminders
    manager3.send_reminder("2025-03-22");

    // Delete guest
    manager3.remove_guest("george");
}

// ----------------------------------------------- MAIN FUNCTION

int main() {
    cout << endl << " ------------------  Welcome to Iftar Invitation Manager ------------------" << endl;

    string choice;
    while (true) {
        while (true) {
            cout << "\nWhat do you want to do?" << endl;
            cout << "1) Run From Terminal." << endl;
            cout << "2) Initialize in main." << endl;
            cout << "3) Exit." << endl;
            cout << "\nPlease, enter your choice : ";
            getline(cin, choice);

            // Check the validity of input.
            if (choice == "1" || choice == "2" || choice == "3") break;
            cout << "Invalid choice. Please, Try again." << endl;
        }

        // Run from the terminal.
        if (choice == "1") runFromTerminal();

            // Initialize in main.
        else if (choice == "2") initializeInMAin();
        else break;
    }

    cout << "\n----- Thank you for using our system! Goodbye! -----" << endl;
}
// ----------------------------------------------- HELPER FUNCTIONS

bool isValidName(const string &name) {
    // Regular expression for the name format (only letters and spaces).
    const regex namePattern("[A-Za-z ]+$");
    return regex_match(name, namePattern);
}

bool isValidContact(const string &contact) {
    // Regular expressions for the phone number and email formats respectively.
    const regex phoneNumberPattern("(010|011|012|015)\\d{8}$");
    const regex emailPattern("^[A-Za-z0-9][A-Za-z0-9._-]*@(gmail|yahoo|outlook|hotmail)\\.com$");
    return regex_match(contact, emailPattern) || regex_match(contact, phoneNumberPattern);
}

bool isValidDate(const string &date) {
    // Regular expression for the date format (YYYY-MM-DD).
    const regex datePattern("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$");

    if (regex_match(date, datePattern)) {
        // Last day of every month in a non-leap year (Note: The array is 1-based).
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Extract year, month, and day from the date string.
        const int year = stoi(date.substr(0, 4));
        const int month = stoi(date.substr(5, 2));
        const int day = stoi(date.substr(8, 2));

        // Adjust February for leap years.
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) daysInMonth[2] = 29;

        if (day <= daysInMonth[month]) return true;
    }
    return false;
}

bool is_PositiveInt(const string &str) {
    static const regex positiveIntegerPattern(R"(^[1-9]\d*$)");
    return regex_match(str, positiveIntegerPattern);
}
