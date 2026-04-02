# Bank-System-Problems-Level3

---

# Bank Client Management System (C++)

## Overview

This project is a console-based system for managing bank client data using C++.
The system allows you to:

* Display all clients.
* Add a new client.
* Delete a client.
* Update client information.
* Search for a client.

Client data is stored in a text file (`Clients.txt`) for easy retrieval.

---

## File Data Format

Each client is stored on a separate line in the following format:

```
AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance
```

Example:

```
A222#//#164293#//#Ahmed Mohamed Faheem#//#01029551696#//#250000000000.000000
```

---

## Client Data Structure

```cpp
struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
```

---

## Main System Functions

### 1. Reading and Writing Data

* `LoadClientsDataFromFile(filename)`
  Loads all clients from the file into `vector<stClient>`.
* `SaveClientDataToFile(filename, vClient)`
  Saves client data back to the file after updates or deletions.

### 2. Check if a Client Exists

```cpp
bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
```

Checks if a client already exists before adding a new one.

### 3. Adding a New Client

1. `ReadClientData()` to input client information.
2. `AddClientToFile(ClientsFileName, ConvertRecordToLine(Client))` to save it to the file.

### 4. Deleting a Client

* Marks the client as `MarkForDelete = true`.
* Saves the file again without the deleted client.

### 5. Updating a Client

* Finds the client by account number.
* Uses `ChangeClientRecord(AccountNumber)` to modify details.
* Saves the updated data to the file.

### 6. Searching for a Client

* Search by account number.
* Display client details as a formatted card.

---

## User Interface (Console Menu)

Main menu options:

```
[1] Show All Clients List.
[2] Add New Client.
[3] Delete Client.
[4] Update Client Info.
[5] Find Client.
[6] Exit.
```

* After each operation, the user returns to the main menu.
* You can add, delete, or search multiple clients without restarting the program.

---

## Running the Program

1. Place all project files (`.cpp` and `.h`) in the same folder.
2. Ensure `Clients.txt` exists, either empty or with client data.
3. Compile and run the project.
   Example using g++:

```bash
g++ main.cpp -o BankSystem
./BankSystem
```

---

## Notes

* Account balances are stored as `double`.
* `#//#` is used as a delimiter between fields for reading and writing.
* The program uses `vector<stClient>` to hold all client data in memory during execution.

---
