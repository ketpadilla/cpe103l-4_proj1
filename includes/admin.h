#ifndef ADMIN_H
#define ADMIN_H

// header files and namespace
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "helper.h"
using namespace std;


char validateChoice(char choice, char options[], int size);

// admin details
string admin[4] = {"0000-0000-0001", "Admin", "None", "0000"};


// ...
bool checkAdmin(string userID) {
  if (userID == admin[0]) {
    return true;
  }

  return false;
}


// ...
string validateAdmin(string text, string input, string admin[4], int attempts, int index) {
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

  if (input == admin[index]) {
    valid = true;
  }

  if (valid) {
    return output;
  } else {
    cout << "Invalid input" << endl;
    attempts++;
    return validateAdmin(text, input, admin, attempts, index);
  }
}


// ...
char adminPages(char choice) {
  switch (choice) {
    case 'V':
      cout << "To implement." << endl;
      break;
    case 'A':
      cout << "To implement." << endl;
      break;
    case 'E':
      cout << "To implement." << endl;
      break;
    case 'C':
      cout << "To implement." << endl;
      choice = 'X';
      break;
    case 'X':
      cout << "Exiting program." << endl;
      choice = 'X';
      break;
    default:
      cout << "Invalid choice." << endl;
      choice = 'X';
      break;
  }
  return choice;
}

// ...
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
    "(X) - Exit"
    " ",
    "Enter your choice: _____"
  };

  // print screen contents
  printUI(textNum, sizeof(textNum)/sizeof(textNum[0]));

  // get, validate, and return choice
  choice = validateChoice(choice, options, size);
  choice = adminPages(choice);
  return choice;
}


#endif // ADMIN_H