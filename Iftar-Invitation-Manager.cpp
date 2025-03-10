/*
 * Authors:
    * Author1: Esraa Emary Abd El-Salam, ID: 20230054
    * Author2: Mariam Badr Yehia, ID: 20230391
    * Author3: John Ayman Demian, ID: 20230109
    * Author4: Mohammed Atef Abd El-Kader, ID: 20231143
    * Author5: George Malak Magdy, ID: 20231042
 * Date : 8/3/2025
 * Prof : Dr. Besheer
 * Description: This is a program that manages "Iftar Invitations" which makes you add a guest,
                display it and edit the date of invitation.
 * Version: V1.0
*/

// < ========================================================================================== >
#include <bits/stdc++.h>
using namespace std;

bool isValidName(const string& name);
bool isValidContact(const string& contact) ;
bool isValidDate(const string& date) ;

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
    void display_guest();
    void update_invitation(string new_date);
    bool operator < ( Guest& other)  ;
};
// < ============================== Iftar Manager Class ============================== >
class IftarManager {
    Guest* guestList = new Guest[0];
    int size = 0;
public:
    ~IftarManager();
    void add_guest(Guest guest);
    void remove_guest(Guest guest);
    void display_all_guests();
    void update_guest_invitation(string name, string new_date);
    void send_reminder(string date);
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

        cout << "Invalid Date, it should be in the format YYYY-MM-DD." << endl;
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
void Guest::display_guest() {
     cout << this->name << ", " << "Contact: " << this->contact << ", " << "Iftar Date: " << this->iftar_date << endl;
}
// <============================== update_invitation Function ============================== >
void Guest::update_invitation(string new_date) {
       this->iftar_date = new_date;
}
// <============================== Overloading Function ============================== >
bool Guest::operator < ( Guest &other){
    int TempYear1 = stoi( getDate().substr(0,4))
            ,TempMonth1 = stoi(getDate().substr(5,2))
                ,Tempday1 = stoi(getDate().substr(7,2)) ;

    int TempYear2 = stoi(other.getDate().substr(0,4))
            ,TempMonth2 = stoi(other.getDate().substr(5,2))
                ,Tempday2 = stoi(other.getDate().substr(7,2)) ;

    if (TempYear1 != TempYear2) return TempYear1 < TempYear2;
    if (TempMonth1 != TempMonth2) return TempMonth1 < TempMonth2;
    if (Tempday1 != Tempday2) return Tempday1 < Tempday2;

    return this-> name < other.name ;
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
    newGuest[this->size] = guest;
    if (this->guestList) {
        delete[] this->guestList;
    }
    // Add the new guest to the list and increment the size.
    this->guestList = newGuest;
    this->size++;
    sort_guest_list();      // Sort the guest list after adding a new guest.
}
// < ============================== display_all_guests Function ============================== >
void IftarManager::display_all_guests() {

    if (this->size == 0) {
        cout << "No Guests to Print. " << endl;
    }else {
        for (int i = 0; i < this->size; i++) {
            cout << "Guest: " ; this->guestList[i].display_guest();
        }
        cout << endl;
    }
}
// < ============================== update_guest_invitation Function ============================== >
void IftarManager::update_guest_invitation(string name, string new_date) {

    bool found = false;

    while (isValidName(new_date)) {
        cout << "Invalid Date, it should be in the format YYYY-MM-DD." << endl;
        cout << "Please, Enter a valid guest iftar date: ";
        getline(cin, new_date);
    }

    while (!found) {
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
}
// < ============================== send_reminder Function ============================== >
void IftarManager::send_reminder(string date) {
    while (true) {
        if (isValidDate(date)) {
            bool found = false;
            cout << "Sending Reminder..." << endl;
            for (int i = 0; i < this->size; i++) {
                if (this->guestList[i].getDate() == date) {
                    found = true;
                    cout <<"Reminder sent to " <<guestList[i].getName() <<": Your Iftar invitation is on " <<date <<"!" << endl; ;
                }
            }
            if (found == false) {
                cout <<"No Guest has this Iftar date " << endl << endl;
            }
            break;
        }if (!isValidDate(date)) {
            cout <<"Please enter a valid date : ";
            getline(cin, date);
        }
    }

}
// < ============================== sort_guest_list With Merge Function ============================== >
void IftarManager::Merge(Guest* GS, int Left, int Middle, int Right ) {
    int SizeArr1 = Middle - Left + 1;
    int SizeArr2 = Right - Middle;
    Guest Arr1[SizeArr1] , Arr2[SizeArr2] ;
    for (int i = 0; i < SizeArr1 ; ++i) {
        Arr1[i] = GS[Left + i];
    }
    for (int i = 0; i < SizeArr2 ; ++i) {
        Arr2[i] = GS[Middle + 1 + i];
    }
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
    if(Left < Right){
        int Middle = (Left + Right) / 2 ;
        Help_Merge_sorting(Temp, Left, Middle);
        Help_Merge_sorting(Temp, Middle + 1, Right);
        Merge(Temp, Left, Middle, Right);
    }
}
void IftarManager::sort_guest_list(){
    Help_Merge_sorting(this->guestList , 0, this-> size - 1);
}
// < ============================== remove Function ============================== >
void IftarManager::remove_guest(Guest guest) {

    // Implement
}

IftarManager::~IftarManager() {
    delete[] guestList;
}

// < ============================== Main Function ============================== >
int main() {

    cout << endl << " ******************  Welcome to Iftar Invitation Manager ******************"  << endl << endl;
    // Create Iftar Manager
    IftarManager manager = IftarManager();

    while (true) {

        string name , date , contact , guestName , new_date , reminder;;
        long long numOfGuests ;
        int choice ;

        cout << "1) Add new guest" <<endl;
        cout << "2) Remove guest" <<endl;
        cout << "3) Update Guest Invitation" <<endl;
        cout << "4) Send Reminder " <<endl;
        cout << "5) Display All Guest List " <<endl;
        cout << "6) Exit" <<endl;

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

                 cout << "Please, enter  number of guests you want to Add: ";
                 cin >> numOfGuests;
                 while (cin.fail() || numOfGuests < 1) {
                     cout << "Invalid Input, \n Please, enter valid number : ";
                     cin.clear();
                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                     cin >> numOfGuests;
                  }

                 for (int i = 0; i < numOfGuests; i++) {

                   cout << "Please, enter name of guest "<< i + 1 << " : " ; cin >> name ;
                   cout << "Please, enter contact(email or phone number) of guest "<< i + 1<< " : "; cin >> contact;
                     cout << "Please, enter invitation date (YYYY-MM-DD) of guest "<< i + 1<< " : "; cin >> date ;

                  Guest Add_Guest = Guest(name, contact , date);
                   manager.add_guest(Add_Guest);
                     cout << endl ;
                }
                break ;

            case 2:

                cout << "Please, enter  number of guests you want to remove: ";
                cin >> numOfGuests;
                while (cin.fail() || numOfGuests < 1) {
                    cout << "Invalid Input, \n Please, enter valid number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> numOfGuests;
                 }

                for (int i = 0; i < numOfGuests; i++) {

                    cout << "Please, enter name of guest "<< i + 1<< " : "; cin >> name ;
                    cout << "Please, enter contact(email or phone number) of guest "<< i + 1<< " : "; cin >> contact;
                    cout << "Please, enter invitation date (YYYY-MM-DD) of guest "<< i + 1<< " : "; cin >> date ;

                   Guest Remove_Guest = Guest(name, contact , date);
                   manager.remove_guest(Remove_Guest);
                    cout << endl ;
                 }

                 break ;

            case 3:

                cout << "Please, enter guest’s name: " ; cin >> guestName ;
                cout << "Please, enter new guest’s invitation date (YYYY-MM-DD): " ; cin >> date ;

                manager.update_guest_invitation( guestName, new_date);
                break ;

            case 4:
                cout << "Please , enter date you want to send reminder message to all guests on this date: " ; cin >> reminder;
               manager.send_reminder( reminder);
               break ;

            case 5:
                manager.display_all_guests();
                break ;

            case 6:
                cout << endl << " ***** Thanks for using this Iftar Invitation Manager ***** ";
                manager.~IftarManager();
                exit(0);

            default:
                cout << "Invalid choice, \n Please, enter valid choice: ";
        }
    }
}

bool isValidName(const string& name) {
    // Regular expression for the name format (only letters and spaces).
    regex namePattern("[A-Za-z ]+$");
    return regex_match(name, namePattern);
}
bool isValidContact(const string& contact) {
    // Regular expressions for the phone number and email formats respectively.
    regex phoneNumberPattern("(010|011|012|015)\\d{8}$");
    regex emailPattern("^[A-Za-z0-9][A-Za-z0-9._-]*@(gmail|yahoo|outlook|hotmail)\\.com$");
    return regex_match(contact, emailPattern) || regex_match(contact, phoneNumberPattern);
}
bool isValidDate(const string& date) {
    // Regular expression for the date format (YYYY-MM-DD).
    regex datePattern("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$");

    if (regex_match(date, datePattern)) {
        // Last day of every month in a non-leap year (Note: The array is 1-based).
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Extract year, month, and day from the date string.
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));

        // Adjust February for leap years.
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) daysInMonth[2] = 29;

        if (day <= daysInMonth[month]) return true;
    }
    return false;
}
