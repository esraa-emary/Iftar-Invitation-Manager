# 🌙 Iftar Invitation Manager

## 📌 Overview
**Iftar Invitation Manager** is a simple C++ program designed to manage guest invitations for Iftar gatherings. It allows users to add guests, update invitations, send reminders, and sort the guest list based on invitation dates.

## 🚀 Features
- Add guests with their name, contact information, and Iftar date.
- Display the list of all invited guests.
- Update invitation dates for specific guests.
- Send reminders based on the Iftar date.
- Sort guests based on invitation dates.

## 🛠️ Technologies Used
- **Language**: C++ (No STL used)

## 📖 Code Explanation
### 🔹 **Guest Class**

```cpp
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
```

### 🔹 **IftarManager Class**
Handles the list of guests and provides functions to:
- Add and display guests
- Update invitations
- Send reminders
- Sort the guest list

```cpp
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
```

## 👨‍💻 Contributing
Contributions are welcome! Feel free to fork the repo and submit a pull request.

## ✍️ Authors
- Esraa Emary Abd El-Salam: [GitHub](https://github.com/esraa-emary) - [LinkedIn](https://www.linkedin.com/in/esraa-emary-b372b8303/)
- Mariam Badr Yehia: [GitHub](https://github.com/Mariam-Badr-MB) - [LinkedIn](https://www.linkedin.com/in/mariambadr13/)
- George Malak Magdy:  [GitHub](https://github.com/GeorgeMalakM) - [LinkedIn](https://www.linkedin.com/in/george-malak204/)
- John Ayman Demian:  [GitHub](https://github.com/Johnayman1) - [LinkedIn]()
- Mohammed Atef Abd El-Kader: [GitHub](https://github.com/Mohammed-3tef) - [LinkedIn](https://www.linkedin.com/in/mohammed-atef-b0a408299/)

## 📜 License
This project is licensed under the MIT License.

---
✨ **Developed with ❤️ in C++** ✨

