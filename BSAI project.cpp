/*
 * ======================================================================================
 * PROJECT:      INVENTORY MANAGEMENT SYSTEM
 * LANGUAGE:     C++
 * AUTHOR:       [MAHAD AHMED]
 * DESCRIPTION:  A console-based application to manage a simple inventory.
 * Features include Adding, Viewing, Searching, and Removing items.
 * The system uses parallel arrays and robust input validation.
 * ======================================================================================
 */

#include <iostream>
#include <string>
#include <limits> // Required for numeric_limits to clear invalid inputs

using namespace std;

/*
  --------------------------------------------------------------------------------------
                             ANSI COLOR CODES
  --------------------------------------------------------------------------------------
 */
const string RESET  = "\033[0m";
const string RED    = "\033[31m";
const string GREEN  = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE   = "\033[34m";
const string CYAN   = "\033[36m";
const string BOLD   = "\033[1m";


/*
 --------------------------------------------------------------------------------------
 * MAX_ITEMS: Defines the maximum capacity of the inventory.
 * items[]:   Array to store the names of the items.
 * quantity[]: Array to store the count of each item.
 * countItems: Tracks the current number of items stored in the system.
--------------------------------------------------------------------------------------
 */
const int MAX_ITEMS = 10;

string items[MAX_ITEMS];
int quantity[MAX_ITEMS];
int countItems = 0;


/*
 * ======================================================================================
 * FUNCTION: addItem
 * Performs bounds checking to ensure array is not full.
 * Performs input validation to ensure quantity is a positive number.
 * ======================================================================================
 */
void addItem() {

    // STEP 1: Check if the inventory has reached its maximum capacity
    if (countItems >= MAX_ITEMS) {
        cout << "\n" 
             << RED 
             << "Error: Inventory is full. Cannot add more items." 
             << RESET 
             << "\n";
        return; 
    }

    // STEP 2: Display Header
    cout << "\n" 
         << CYAN 
         << BOLD 
         << "---------- Add New Item ----------" 
         << RESET 
         << "\n";

    // STEP 3: Get Item Name 
    cout << YELLOW 
         << "Enter item name: " 
         << RESET;

    cin.ignore();
    
    while (true) {
        getline(cin, items[countItems]);
        if (items[countItems].empty()) {
            cout << RED << "Item name cannot be empty! Enter again: " << RESET;
        } else {
            break;
        }
    }

    // STEP 4: Get Item Quantity with Robust Error Handling
    cout << YELLOW 
         << "Enter quantity: " 
         << RESET;

    //  check: user pressing ENTER without typing
    string qtyInput;

    while (true) {
        cin>> qtyInput;

        // Check if empty
        if (qtyInput.empty()) {
            cout << RED << "Quantity cannot be empty! Enter again: " << RESET;
            continue;
        }

        // Convert string to integer safely
        bool valid = true;
        for (char c : qtyInput) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << RED << "Invalid input! Please enter a NUMBER: " << RESET;
            continue;
        }

        // Convert to integer
        quantity[countItems] = stoi(qtyInput);

        // Check negative
        if (quantity[countItems] < 0) {
            cout << RED << "Quantity cannot be negative. Enter again: " << RESET;
        } else {
            break;
        }
    }

    // STEP 5: Increment Counter and Success Message
    countItems++;
    
    cout << GREEN 
         << "Item added successfully!" 
         << RESET 
         << "\n";
}


/*
 * ======================================================================================
 * FUNCTION: viewItems
 * PURPOSE:  Displays all items currently stored in the inventory in a tabular format.
 * Checks if the inventory is empty before printing.
 * ======================================================================================
 */
void viewItems() {

    // Display Header
    cout << "\n" 
         << CYAN 
         << BOLD 
         << "---------- Current Inventory ----------" 
         << RESET 
         << "\n";

    // Check if there are no items to display
    if (countItems == 0) {
        cout << YELLOW 
             << "Inventory is empty.\n" 
             << RESET;
        return;
    }

    // Print Table Column Headers
    cout << BLUE 
         << BOLD 
         << "ID\tItem Name\tQuantity\n" 
         << RESET;
         
    cout << CYAN 
         << "--------------------------------------\n" 
         << RESET;

    // Loop through the arrays and print each item
    for (int i = 0; i < countItems; i++) {
        cout << (i + 1) << "\t" 
             << items[i] << "\t\t" 
             << quantity[i] << endl;
    }

    // Print Table Footer
    cout << CYAN 
         << "--------------------------------------\n" 
         << RESET;
}


/*
 * ======================================================================================
 * FUNCTION: searchItem
 * PURPOSE:  Allows the user to search for a specific item by name.
 * Displays the item details if found, or an error message if not.
 * ======================================================================================
 */
void searchItem() {

    // Check if inventory is empty first
    if (countItems == 0) {
        cout << "\n" 
             << YELLOW 
             << "Inventory is empty.\n" 
             << RESET;
        return;
    }

    string searchName;

    cout << "\n" 
         << YELLOW 
         << "Enter item name to search: " 
         << RESET;
         
    cin.ignore(); // Clear buffer
    getline(cin, searchName);

    bool found = false; // Flag to track if item is found

    for (int i = 0; i < countItems; i++) {
        if (items[i] == searchName) {
            
            cout << "\n" 
                 << GREEN 
                 << "Item found!\n" 
                 << RESET;
                 
            cout << BOLD 
                 << "Item: " 
                 << items[i] 
                 << RESET 
                 << " | Quantity: " 
                 << BOLD 
                 << quantity[i] 
                 << RESET 
                 << endl;
            
            found = true;
            break; // Stop searching once found
        }
    }

    // If the loop finishes and item was not found
    if (!found) {
        cout << RED 
             << "[!] Item not found in inventory.\n" 
             << RESET;
    }
}
/*
 * ======================================================================================
 * FUNCTION: removeItem
 * PURPOSE:  Removes an item from the inventory by name.
 * Uses a linear search to find the index, then shifts all subsequent
 * elements one position to the left to fill the gap.
 * ======================================================================================
 */
void removeItem() {

    // Check if empty
    if (countItems == 0) {
        cout << "\n" 
             << YELLOW 
             << "Inventory is empty. Nothing to remove.\n" 
             << RESET;
        return;
    }

    string name;

    // Display Header
    cout << "\n" 
         << CYAN 
         << BOLD 
         << "---------- Remove Item ----------\n" 
         << RESET;
         
    cout << YELLOW 
         << "Enter item name to remove: " 
         << RESET;
    
    // Modified input to accept spaces
    cin.ignore(); // Clear buffer
    getline(cin, name);

    int pos = -1; // Variable to store the index of the item to remove

    // Step 1: Find the item index
    for (int i = 0; i < countItems; i++) {
        if (items[i] == name) {
            pos = i;
            break;
        }
    }

    // Step 2: Handle case where item does not exist
    if (pos == -1) {
        cout << RED 
             << "[!] Item not found.\n" 
             << RESET;
        return;
    }

    // Step 3: Shift items left to overwrite the deleted item
    // This maintains the contiguous nature of the array
    for (int i = pos; i < countItems - 1; i++) {
        items[i] = items[i + 1];
        quantity[i] = quantity[i + 1];
    }

    // Step 4: Decrement the total count
    countItems--;

    cout << GREEN 
         << "[✔] Item removed successfully.\n" 
         << RESET;
}


/*
 * ======================================================================================
 * FUNCTION: main
 * PURPOSE:  The entry point of the program.
 * Displays the main menu and handles user navigation via a switch statement.
 * Contains the main application loop.
 * ======================================================================================
 */
int main() {

    int choice;
    while (true) {
        cout << "\n" 
             << CYAN 
             << "=====================================\n" 
             << RESET;
             
        cout << BOLD 
             << "      PRIME INVENTORY MANAGEMENT SYSTEM\n" 
             << RESET;
             
        cout << CYAN 
             << "=====================================\n" 
             << RESET;
             
        cout << "1. Add Item\n";
        cout << "2. View Items\n";
        cout << "3. Search Item\n";
        cout << "4. Remove Item\n";
        cout << "5. Exit\n";
        
        cout << YELLOW 
             << "Enter choice: " 
             << RESET;

        cin >> choice;

        // ---------------------------------------------
        // Input Validation for Menu Choice
        // ---------------------------------------------
        if (cin.fail()) {
            cin.clear();             // Reset error state
            cin.ignore(10000, '\n'); // Clear buffer
            
            cout << RED 
                 << "Invalid input! Please enter a number (1-5).\n" 
                 << RESET;
            continue; // Restart the loop
        }
        switch (choice) {
            case 1: 
                addItem(); 
                break;
            
            case 2: 
                viewItems(); 
                break;
            
            case 3: 
                searchItem(); 
                break;
            
            case 4: 
                removeItem(); 
                break;
            
            case 5:
                cout << "\n" 
                     << GREEN 
                     << "Exiting program... Goodbye!\n" 
                     << RESET;
                return 0; // Terminate program

            default:
                cout << RED 
                     << " Invalid choice! Please select 1-5.\n" 
                     << RESET;
        }
    }

    return 0;
}