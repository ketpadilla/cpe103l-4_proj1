// * CPE103L-4 PROJECT 1 - COLLABORATIVE PROGRAMMING
/* 
  Group 6 - Presenter #8
  MENDOZA, Gabrielle Joy
  MONTAÑA, Marielle
  PADILLA, Kristian Emmanuel
  PEREZ, Joaquin Manuel
*/

// header files and namespace
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include "includes/printUI.h"
#include "includes/helper.h"
using namespace std;


// prototype functions
char homeScreen(char choice);
char transactionScreen(char choice);
void balanceScreen(string accounts[5][4], string userID, int index);
void withdrawalScreen(string accounts[5][4], string userID, int index);
string identifyUser(string accounts[5][4], string userID, string admin[4]);

// global variables
string accounts[5][4] = {
  {"0123-4567-8901", "Dina Bale", "5000.00", "1111"},
  {"2345-6789-0123", "Mally Gaya", "0.00", "2222"},
  {"3456-7890-1234", "Toto Lee", "10000.00", "3333"},
  {"4567-8901-2345", "Mina Mahal", "2500", "4444"},
  {"5678-9012-3456", "Cory Pot", "10000.00", "5555"}
};
string admin[4] = {"0000-0000-0001", "Admin", "None", "0000"};
string userID;
int userAcct;


// * main
int main() {
  char choice;

  // main
  choice = homeScreen(choice);
  switch (choice) {
    case 'S':
      userID = identifyUser(accounts, userID, admin);
      break;
    case 'Q':
      cout << "Quiting program" << endl;
      return 0;
    default:
      cout << "Invalid choice" << endl;
      return 1;

  }


  // final user validation
  if (userID == "-1") {
    return 1;
  }

  // ! PLACE INTO A FUNCTION TO BE REPEATED
  // customer transaction
  choice = transactionScreen(choice);
  // find index of userID in accounts
  int index = findIndex(accounts, userID);  
  switch (choice) {
    case 'B':
      balanceScreen(accounts, userID, index);
      break;
    case 'W':
      withdrawalScreen(accounts, userID, index);
      break;
    case 'D':

      break;
    case 'C':
      cout << "Canceling transaction" << endl;
      return 0;
    default:
      cout << "Invalid choice" << endl;
      return 1;
  }

  return 0;
}


// output #1
char homeScreen(char choice) {
  char options[2] = {'S', 'Q'};
  int size = sizeof(options)/sizeof(options[0]);
  string text[3] = {
    "S -> Start Transaction",
    "Q -> Quit",
    "Enter your choice: _____" 
  };

  // print screen contents
  printUI(text, sizeof(text)/sizeof(text[0]));

  // get, validate, and return choice
  choice = validateChoice(choice, options, size);
  return choice;
}


// output #2
string identifyUser(string accounts[5][4], string userID, string admin[4]) {
  string userNum, acctPin;
  int size = 5; 
  int attempts = 0;

  // account number
  string textNum[2] = {
    "Please enter your account number to start:",
    "__________"
  };

  // print screen contents
  printUI(textNum, sizeof(textNum)/sizeof(textNum[0]));

  // get and validate user input
  userNum = validateUser("Account Number", userNum, accounts, attempts, size, 0);
  if (userNum == "-1") {
    cout << "Invalid account number. Try again." << endl;
    return "-1";
  }

  // account pin
  string textPin[2] = {
    "Enter your pin number:",
    "__________"
  };

  // print screen contents
  printUI(textPin, sizeof(textPin)/sizeof(textPin[0]));

  // get and validate user input
  acctPin = validateUser("Pin", acctPin, accounts, attempts, size, 3);
  if (acctPin == "-1") {
    cout << "CAPTURED CARD…. PLEASE CALL 143-44" << endl;
    return "-1";
  }

  // return validated account number
  return userNum;
}


// output #3
char transactionScreen(char choice) {
  // transaction options
  char options[4] = {'B', 'W', 'D', 'C'};
  int size = sizeof(options)/sizeof(options[0]);
  string text[8] = {
    "Select Type of Transaction",
    " ",
    "B -> Balance Inquiry",
    "W -> Withdrawal",
    "D -> Deposit",
    "C -> Cancel",
    " ",
    "Enter transaction type: _____"
  };

  // print screen contents
  printUI(text, sizeof(text)/sizeof(text[0]));
 
  // get, validate, and return choice
  choice = validateChoice(choice, options, size);
  return choice;
}


// output #4 (balance)
void balanceScreen(string accounts[5][4], string userID, int index) {
  // exit option
  char options[4] = {'X'};
  int size = sizeof(options)/sizeof(options[0]);

  // print balance
  string text[5] = {
    "Account #: " + accounts[index][0],  
    "Account Name: " + accounts[index][1],  
    "Balance: " + accounts[index][2],  
    " ",
    "Press X to Exit."
  };

  // print screen contents
  printUI(text, sizeof(text)/sizeof(text[0]));

  // get and validate and exit
  char choice = validateChoice(choice, options, size);
}


// output #4 (withdrawal)
void withdrawalScreen(string accounts[5][4], string userID, int index) {
  // exit option
  char choice;
  char options[4] = {'X'};
  int size = sizeof(options)/sizeof(options[0]);

  string withdrawAmt;
  double balance = stod(accounts[index][2]);
  
  string text[4] = {
    "Enter amount to be widrawn",  
    "__________",  
    " ",  
    "Press X to Exit."
  };

  // print screen contents
  printUI(text, sizeof(text)/sizeof(text[0]));

  while (true) {
    cout << "Amount: ";
    cin >> withdrawAmt;

    // Check if the input is 'X'
    if (toupper(withdrawAmt[0]) == 'X' && withdrawAmt.length() == 1) {
      return;
    }

    // Check if the input is a valid number
    bool valid = true;
    for (int i = 0; i < withdrawAmt.length(); ++i) {
      if (!isdigit(withdrawAmt[i])) {
        valid = false;
        break;
      }
    }

    if (valid) {
      try {
        double amount = stod(withdrawAmt);
        if (amount > balance) {
          cout << "Insufficient funds." << endl;
        } else {
          balance -= amount;
          accounts[index][2] = to_string(balance);
          cout << "Withdrawal successful.";
          return;
        }
      } catch (const invalid_argument &e) {
        cout << "Invalid input. Please enter a valid amount." << endl;
      } catch (const out_of_range &e) {
        cout << "Invalid input. Please enter a valid amount." << endl;
      }
    } else {
      cout << "Invalid input. Please enter a valid amount or 'X' to exit." << endl;
    }

    // Clear input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

// ! TO BE IMPLEMENTED

