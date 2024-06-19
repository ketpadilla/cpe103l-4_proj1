#ifndef HELPER_H
#define HELPER_H

// header files and namespace
#include <iostream>
#include <string>
#include <cmath>
#include "admin.h"
using namespace std;


// validate user input for menu options
char validateChoice(char choice, char options[], int size) {
  // get user choice
  char input;
  cout << "Choice: ";
  cin >> input;
  input = toupper(input); 

  // validate input
  for (int i = 0; i < size; i++) {
    if (input == toupper(options[i])) {
      return input;
    }
  }

  // if input is invalid
  cout << "Invalid input" << endl;

  // clear input buffer and prompt again
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return validateChoice(choice, options, size);
}


// validate user data
string validateUser(string text, string input, string accounts[][4], int attempts, int size, int index) {
  if (attempts == 3) {
    return "-1";
  };

  cout << "Attempts left: " << 3 - attempts << endl;
  cout << text << ": ";
  cin >> input;

  if (checkAdmin(input)) {
    return "0";
  }

  string output = input;
  input.erase(remove(input.begin(), input.end(), '-'), input.end());

  bool valid = false;
  
  for (int i = 0; i < size; i++) {
    // Create a temporary copy of accounts[i][0] without '-'
    string arr = accounts[i][index];
    arr.erase(remove(arr.begin(), arr.end(), '-'), arr.end());

    if (input == arr) {
      valid = true;
      break;
    }
  }; 

  if (valid) {
    return output;
  } else {
    cout << "Invalid input" << endl;
    attempts++;
    return validateUser(text, input, accounts, attempts, size, index);
  }
}



// find index of userID in accounts
int findIndex(string accounts[][4], string userID) {
  for (int i = 0; i < 5; i++) {
    if (userID == accounts[i][0]) {
      return i;
    }
  }

  return -1;
}


// show customer details
void showDetails(string accounts[][4]) {
  for (int i = 0; i < 5; i++) {
    cout << "Account Number: " << accounts[i][0] << endl;
    cout << "Name: " << accounts[i][1] << endl;
    cout << "Balance: " << accounts[i][2] << endl;
    cout << "PIN: " << accounts[i][3] << endl;
    cout << endl;
  }
}


// edit customer details
void editDetails(string accounts[][4]) {
  // get userID
  string userID;
  cout << "Enter account number: ";
  cin >> userID;

  // print current details
  int index = findIndex(accounts, userID);
  cout << "Account details:" << endl;
  for (int i = 0; i < 4; i++) {
    cout << accounts[index][i] << endl;
  }

  // change details
  if (index != -1) {
    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, accounts[index][1]);

    cout << "Enter new balance: ";
    cin >> accounts[index][2];
    
    cout << "Details updated successfully!" << endl;
  } else {
    cout << "User not found!" << endl;
  }

  // print new details
  cout << endl << "Account details:" << endl;
  for (int i = 0; i < 4; i++) {
    cout << accounts[index][i] << endl;
  }
}


// change customer
void changePin(string accounts[][4]) {
  // get userID
  string userID;
  cout << "Enter account number: ";
  cin >> userID;

  // print current details
  int index = findIndex(accounts, userID);
  cout << "Account details:" << endl;
  for (int i = 0; i < 4; i++) {
    cout << accounts[index][i] << endl;
  }

  // change pin
  if (index != -1) {
    cout << "Enter new PIN: ";
    cin >> accounts[index][3];
    cout << endl << "Pin updated successfully!" << endl;
  } else {
    cout << "User not found!" << endl;
  }

  // print new details
  cout << "Account details:" << endl;
  for (int i = 0; i < 4; i++) {
    cout << accounts[index][i] << endl;
  }
}


// ! new customer does not save to array
// add new customer
string addCustomer(string accounts[][4]) {
  // get size
  int size = 0;
  for (int i = 0; i < 5; i++) {
    if (accounts[i][0].empty()) {
      break;
    }
    size++;
  }

  cout << size << endl;
  // get user input for new customer details
  string accountNumber, name, balance, pin;
  cout << "Enter account number: ";
  cin >> accountNumber;
  cout << "Enter name: ";
  cin.ignore();
  getline(cin, name);
  cout << "Enter balance: ";
  cin >> balance;
  cout << "Enter PIN: ";
  cin >> pin;

  // add new customer to the accounts array
  accounts[size + 1][0] = accountNumber;
  accounts[size + 1][1] = name;
  accounts[size + 1][2] = balance;
  accounts[size + 1][3] = pin;

  // increment the size counter
  size++;

  cout << "New customer added successfully!" << endl;
}


#endif // HELPER_H