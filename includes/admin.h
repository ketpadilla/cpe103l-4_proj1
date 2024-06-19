#ifndef ADMIN_H
#define ADMIN_H

// header files and namespace
#include <iostream>
#include <string>
#include <cmath>
using namespace std;


// admin details
string admin[4] = {"0000-0000-0001", "Admin", "None", "0000"};


// 
bool checkAdmin(string userID) {
  if (userID == admin[0]) {
    return true;
  }

  return false;
}


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


#endif // ADMIN_H