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

bool isValidName(const string& name) {
    // Regular expression for the name format (only letters and spaces).
    const regex namePattern("[A-Za-z ]+$");
    return regex_match(name, namePattern);
}

bool isValidContact(const string& contact) {
    // Regular expressions for the phone number and email formats respectively.
    const regex phoneNumberPattern("(010|011|012|015)\\d{8}$");
    const regex emailPattern("^[A-Za-z0-9][A-Za-z0-9._-]*@(gmail|yahoo|outlook|hotmail)\\.com$");
    return regex_match(contact, emailPattern) || regex_match(contact, phoneNumberPattern);
}

bool isValidDate(const string& date) {
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

// < ============================== Guest Class ============================== >
class Guest {
    string name;
    string contact;
    string iftar_date;
public:
    Guest() = default;
    Guest(string guestName, string guestContact, string guestIftar_date);
    string getName();
    string getDate();
    void display_guest() const;
    void update_invitation(const string &new_date);
    bool operator < ( Guest& other);
    bool operator == (const Guest& other) const;
};

// < ============================== Iftar Manager Class ============================== >
class IftarManager {
    Guest* guestList = new Guest[0];
    int size = 0;
public:
    ~IftarManager();
    void add_guest(const Guest &guest);
    void remove_guest(const Guest &guest );
    void display_all_guests() const;
    void update_guest_invitation(string name, string new_date);
    void send_reminder(string date) const;
    void sort_guest_list();
    void Merge(Guest* Guest_List_sort,  int Right, int Middle, int Left);
    void Help_Merge_sorting(Guest *Temp, int Left, int Right);
};

// < ============================== Implementation For Guest Class ============================== >

// < ============================== Constructor ============================== >
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

// <============================== get Name Function ============================== >
string Guest::getName() {
    return this->name;
}

// <============================== get Date Function ============================== >
string Guest::getDate() {
    return this->iftar_date ;
}

// <============================== display_guest Function ============================== >
void Guest::display_guest() const{
     cout << this->name << ", " << "Contact: " << this->contact << ", " << "Iftar Date: " << this->iftar_date << endl;
}

// <============================== update_invitation Function ============================== >
void Guest::update_invitation(const string &new_date) {
       this->iftar_date = new_date;
}

// <============================== Overloading Function ============================== >
bool Guest::operator < ( Guest &other){
    // Extract year, month, and day from the date string of both guests to compare them.
    const int tempYear1 = stoi( getDate().substr(0,4));
    const int tempMonth1 = stoi(getDate().substr(5,2));
    int tempDay1 = stoi(getDate().substr(8,2)) ;

    const int tempYear2 = stoi(other.getDate().substr(0,4));
    const int tempMonth2 = stoi(other.getDate().substr(5,2));
    int tempDay2 = stoi(other.getDate().substr(8,2)) ;

    // Compare the dates of the two guests.
    if (tempYear1 != tempYear2) return tempYear1 < tempYear2;
    if (tempMonth1 != tempMonth2) return tempMonth1 < tempMonth2;
    if (tempDay1 != tempDay2) return tempDay1 < tempDay2;

    return this-> name < other.name ;
}

bool Guest::operator == (const Guest& other) const{
    return (this->name == other.name && this->contact == other.contact && this->iftar_date == other.iftar_date);
}

// < ============================== Implementation For Iftar Manager Class ============================== >

// < ============================== add_guest Function ============================== >
void IftarManager::add_guest(const Guest &guest) {
    // Create a new guest list with a size of one more than the current size.
    auto* newGuest = new Guest[this->size + 1];
    for (int i = 0; i < this->size; i++) {
        newGuest[i] = this->guestList[i];
    }

    // Delete the old guest list and assign the new guest list.
    newGuest[this->size] = guest;
    delete[] this->guestList;

    // Add the new guest to the list and increment the size.
    this->guestList = newGuest;
    this->size++;
    sort_guest_list();      // Sort the guest list after adding a new guest.
}

// < ============================== display_all_guests Function ============================== >
void IftarManager::display_all_guests() const{
    if (this->size == 0) {
        cout << "No Guests to Print. " << endl;
    }
    else {
        for (int i = 0; i < this->size; i++) {
            cout << "Guest: " ; this->guestList[i].display_guest();
        }
        cout << endl;
    }
}

// < ============================== update_guest_invitation Function ============================== >
void IftarManager::update_guest_invitation(string name, string new_date) {
    if (this->size == 0) {
        cout << "There is no guest to remove." << endl;
        return;
    }

    bool found = false;
    while (isValidName(new_date)) {
        cout << "Invalid Date, it should be in the format YYYY-MM-DD." << endl;
        cout << "Please, Enter a valid guest iftar date: ";
        getline(cin, new_date);
    }

    while (true) {
        for (int i = 0; i < this->size; i++) {
            if (guestList[i].getName() == name) {
                guestList[i].update_invitation(new_date);
                found = true;
            }
        }
        if (found) break ;
        cout << "Please, Enter a valid name in Guests invitation List: ";
        getline(cin, name);
    }

    cout << "Updating invitation for " + name + "..." << endl << endl;
    sort_guest_list();      // Sort the guest list after updating the guest's date.
}

// < ============================== send_reminder Function ============================== >
void IftarManager::send_reminder(string date) const{
    while (true) {
        if (isValidDate(date)) {
            bool found = false;
            cout << "Sending Reminder..." << endl;

            for (int i = 0; i < this->size; i++) {
                if (this->guestList[i].getDate() == date) {
                    found = true;
                    cout << "Reminder sent to " << guestList[i].getName() << ": Your Iftar invitation is on " << date << "!" << endl;
                }
            }
            if (!found) {
                cout << "No Guest has this Iftar date " << endl << endl;
            }
            break;
        }
        else {
            cout << "Please enter a valid date : ";
            getline(cin, date);
        }
    }
    cout << endl ;
}

// < ============================== sort_guest_list With Merge Function ============================== >
void IftarManager::Merge(Guest* GS, int Left, int Middle, int Right ) {
    const int SizeArr1 = Middle - Left + 1;
    const int SizeArr2 = Right - Middle;
    Guest Arr1[SizeArr1] , Arr2[SizeArr2] ;
    for (int i = 0; i < SizeArr1 ; ++i) {
        Arr1[i] = GS[Left + i];
    }
    for (int i = 0; i < SizeArr2 ; ++i) {
        Arr2[i] = GS[Middle + 1 + i];
    }

    // Merge the two arrays into GS [Left, Right].
    int StartArr1 = 0 , StartArr2 = 0 , TempLeft = Left;
    while((StartArr1 < SizeArr1) && (StartArr2 < SizeArr2)){
        if( Arr1[StartArr1] < Arr2[StartArr2]){
            GS[TempLeft] = Arr1[StartArr1];
            ++StartArr1;
        }else{
            GS[TempLeft] = Arr2[StartArr2];
            ++StartArr2;
        }
        ++TempLeft;
    }

    // Copy the remaining elements of Arr1 and Arr2 if there are any.
    while(StartArr1 < SizeArr1){
        GS[TempLeft] = Arr1[StartArr1];
        ++StartArr1;
        ++TempLeft;
    }
    while (StartArr2 < SizeArr2){
        GS[TempLeft] = Arr2[StartArr2];
        ++StartArr2;
        ++TempLeft;
    }
}

void IftarManager::Help_Merge_sorting(Guest *Temp, int Left, int Right) {
    if (Left < Right){
        const int Middle = Left + (Right - Left) / 2 ;
        Help_Merge_sorting(Temp, Left, Middle);
        Help_Merge_sorting(Temp, Middle + 1, Right);
        Merge(Temp, Left, Middle, Right);
    }
}

void IftarManager::sort_guest_list(){
    Help_Merge_sorting(this->guestList , 0, this-> size - 1);
}

// < ============================== remove Function ============================== >
void IftarManager::remove_guest(const Guest &guest) {
    if (this->size == 0) {
        cout << "There is no guest to remove." << endl;
        return;
    }

    bool found = false; string name , contact , date ;
    auto * Temp_list = new Guest [size - 1] ;
    int temp_ind = 0 ;

    while (true) {
        for (int i = 0; i < this->size; i++) {
            if (guestList[i] == guest) {
                found = true;
            }
            else {
                Temp_list[temp_ind++] = this->guestList[i];
            }
        }

        if (found) break ;

        cout << "Please, Enter a valid Guest in Guests invitation List "<< endl;
        cin.ignore();
        cout << "Please, enter name of guest: " ; getline(cin, name) ;
        cout << "Please, enter contact(email or phone number) of guest: "; getline(cin, contact) ;
        cout << "Please, enter invitation date (YYYY-MM-DD) of guest: " ; getline(cin, date);
    }

    delete [] this->guestList;
    this->guestList = Temp_list ;
    --this->size;
    cout << "Guest is removed from the Iftar invitation list...." << endl ;
}

IftarManager::~IftarManager() {
    delete[] guestList;
}

// < ============================== Main Function ============================== >
int main() {

    cout << endl << " ------------------  Welcome to Iftar Invitation Manager ------------------"  << endl << endl;

    IftarManager manager = IftarManager();

    while (true) {
        string name , date , contact , guestName , new_date , reminder;
        long long numOfGuests ;
        int choice ;

        cout << "1) Add new guest." << endl;
        cout << "2) Remove guest." << endl;
        cout << "3) Update Guest Invitation." << endl;
        cout << "4) Send Reminder." << endl;
        cout << "5) Display All Guest List." << endl;
        cout << "6) Exit." << endl;

        cout << endl << "Please, Select an option:";
        cin >> choice ;

        while (cin.fail() || choice < 1 || choice > 6) {
            cout << "Invalid choice, \nPlease, enter valid choice: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice ;
        }
        cout << endl ;

        switch (choice) {
            case 1:
                 cout << "Please, enter number of guests you want to Add: ";
                 cin >> numOfGuests;

                 while (cin.fail() || numOfGuests < 1) {
                     cout << "Invalid Input, \n Please, enter valid number : ";
                     cin.clear();
                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                     cin >> numOfGuests;
                 }
                 cin.ignore();

                 for (int i = 0; i < numOfGuests; i++) {
                    cout << "Please, enter name of guest " << i + 1 << " : " ; getline(cin, name) ;
                    cout << "Please, enter contact (email or phone number) of guest " << i + 1<< " : "; getline(cin, contact) ;
                    cout << "Please, enter invitation date (YYYY-MM-DD) of guest " << i + 1<< " : " ; getline(cin, date);

                    auto Add_Guest = Guest(name, contact , date);
                    manager.add_guest(Add_Guest);
                    cout << endl ;
                }
                break ;

            case 2:
                cout << "Please, enter number of guests you want to remove: ";
                cin >> numOfGuests;

                while (cin.fail() || numOfGuests < 1) {
                    cout << "Invalid Input, \n Please, enter valid number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> numOfGuests;
                }
                cin.ignore();

                for (int i = 0; i < numOfGuests; i++) {
                    cout << "Please, enter name of guest " << i + 1 << " : " ; getline(cin, name) ;
                    cout << "Please, enter contact (email or phone number) of guest " << i + 1 << " : "; getline(cin, contact) ;
                    cout << "Please, enter invitation date (YYYY-MM-DD) of guest " << i + 1 << " : " ; getline(cin, date);

                    auto const  Remove_Guest = Guest(name, contact , date);
                    manager.remove_guest(Remove_Guest);
                    cout << endl ;
                }
                break ;

            case 3:
                cin.ignore();
                cout << "Please, enter name of guest: " ; getline(cin, guestName) ;
                cout << "Please, enter new invitation date (YYYY-MM-DD): " ; getline(cin, new_date) ;

                manager.update_guest_invitation( guestName, new_date);
                break ;

            case 4:
                cin.ignore();
                cout << "Please, enter date you want to send reminder message to all guests on this date: " ; getline(cin, reminder);
                manager.send_reminder( reminder);
                break ;

            case 5:
                manager.display_all_guests();
                break ;

            case 6:
                cout << " ----- Thanks for using this Iftar Invitation Manager ----- "<< endl;
                exit(0);

            default:
                cout << "Invalid choice, \n Please, enter valid choice: ";
        }
    }
}