#ifndef ADMIN_H
#define ADMIN_H

// header files and namespace
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "helper.h"
using namespace std;


// prototype
char validateChoice(char choice, char options[], int size);
int findIndex(string accounts[][4], string userID);
int getSize(string accounts[][4]);

// admin details
string admin[4] = {"0000-0000-0001", "Admin", "None", "0000"};


// check if user is admin
bool checkAdmin(string userID) {
  if (userID == admin[0]) {
    return true;
  }

  return false;
}


// validate input for admin
string validateAdmin(string text, string input, string admin[4], int attempts, int index) {
  if (attempts == 0) {
    return "-1";
  };

  cout << "Attempts left: " << attempts << endl;
  cout << text << ": ";
  cin >> input;

  if (checkAdmin(input)) {
    return "0";
  }

  string output = input;
  input.erase(remove(input.begin(), input.end(), '-'), input.end());

  bool valid = false;

  if (input == admin[index]) {
    valid = true;
  }

  if (valid) {
    return output;
  } else {
    cout << "Invalid input" << endl;
    attempts--;
    return validateAdmin(text, input, admin, attempts, index);
  }
}


// admin menu
char adminScreen(char choice) {
  char options[5] = {'V', 'A', 'E', 'C', 'X'};
  int size = sizeof(options)/sizeof(options[0]);
  string textNum[9] = {
    "What would you like to do?",
    " ",
    "(V) - View Customer Information",
    "(A) - Add New Customer",
    "(E) - Edit Customer Information",
    "(C) - Change Customer Pin Number",
    "(X) - Exit",
    " ",
    "Enter your choice: _____"
  };

  // print screen contents
  printUI(textNum, sizeof(textNum)/sizeof(textNum[0]));

  // get, validate, and return choice
  choice = validateChoice(choice, options, size);
  return choice;
}


// show customer details
void showDetails(string accounts[][4]) {
  // get size
  int size = getSize(accounts);

  for (int i = 0; i < size; i++) {
    cout << "Account Number: " << accounts[i][0] << endl;
    cout << "Name: " << accounts[i][1] << endl;
    cout << "Balance: " << accounts[i][2] << endl;
    cout << "PIN: " << accounts[i][3] << endl;
    cout << endl;
  }

  cout << "Press any key to continue." << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}


// get index of user in accounts 
int selectCustomer(string accounts[][4]) {
  // get userID and index
  string userID;
  cout << "Enter account number: ";
  cin >> userID;
  return findIndex(accounts, userID);
}


// change customer name
string changeName(string name) {
  // ask admin if they want to change the customer's name
  cout << "Do you want to change the account's name, " + name + "? (Y/N): ";

  // get and validate choice
  char choice;
  char options[4] = {'Y', 'N'};
  int size = sizeof(options)/sizeof(options[0]);
  choice = validateChoice(choice, options, size);

  // do not change name if choice is 'N'
  if (choice == 'N') {
    return name;
  }

  // change name
  cout << "Enter new name: ";
  cin.ignore();
  getline(cin, name);
  cout << endl << "Name updated successfully!" << endl;
  return name;
}


// change customer pin
string changeBalance(string balance) {
  // ask admin if they want to change the customer's name
  cout << "Do you want to change the account's balance, " + balance + "? (Y/N): ";

  // get and validate choice
  char choice;
  char options[4] = {'Y', 'N'};
  int size = sizeof(options)/sizeof(options[0]);
  choice = validateChoice(choice, options, size);

  // do not change name if choice is 'N'
  if (choice == 'N') {
    return balance;
  }

  cout << "Enter new balance: ";
  cin.ignore();
  getline(cin, balance);
  cout << endl << "Balance updated successfully!" << endl;
  return balance;
}


// change customer deetails
string changeDetail(string detail, string type) {
  // ask admin if they want to change the customer's name
  cout << "Do you want to change the account's " + type + ", " + detail + "? (Y/N): ";

  // get and validate choice
  char choice;
  char options[4] = {'Y', 'N'};
  int size = sizeof(options)/sizeof(options[0]);
  choice = validateChoice(choice, options, size);

  // do not change name if choice is 'N'
  if (choice == 'N') {
    return detail;
  }

  cout << "Enter new " + type + ": ";
  cin.ignore();
  getline(cin, detail);
  cout << endl << type << " updated successfully!" << endl;
  return detail;
}


// change customer pin
string changePin(string pin) {
  // ? Validation not implemented
  cout << "Enter new PIN: ";
  cin >> pin;
  cout << endl << "Pin updated successfully!" << endl;
  return pin;
}


// add new customer
string addCustomer(string text) {
  // ? Validation not implemented
  string input;
  cout << text << ": ";
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cin >> input;
  return input;
}


#endif // ADMIN_H