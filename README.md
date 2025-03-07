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
Manages guest details including:
- **Attributes**: Name, Contact, Iftar Date
- **Methods**:
    - `display_guest()`: Displays guest details.
    - `update_invitation(new_date)`: Updates the Iftar date.

```cpp
class Guest {
    string name;
    string contact;
    string iftar_date;
public:
    Guest() = default;
    Guest(string guestName, string guestContact, string guestIftar_date);
    void display_guest();
    void update_invitation(string new_date);
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
    Guest* guestList;
    int size;
public:
    void add_guest(Guest guest);
    void display_all_guests();
    void update_guest_invitation(string name, string new_date);
    void send_reminder(string date);
    void sort_guest_list();
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

