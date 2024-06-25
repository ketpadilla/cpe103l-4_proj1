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
#include "includes/admin.h"
using namespace std;


// prototype functions
char homeScreen(char choice);
string identifyUser(string accounts[][4], string userID);
char transactionScreen(char choice);
void balanceScreen(string acctNum, string acctName, string balance);
string transactions(string balance, string type);

// global variables
string accounts[][4] = {
  {"0123-4567-8901", "Dina Bale", "5000.00", "1111"},
  {"2345-6789-0123", "Mally Gaya", "0.00", "2222"},
  {"3456-7890-1234", "Toto Lee", "10000.00", "3333"},
  {"4567-8901-2345", "Mina Mahal", "2500", "4444"},
  {"5678-9012-3456", "Cory Pot", "10000.00", "5555"}
};


// * main
int main() {
  char choice;
  int userAcct;
  string userID;

  // * prompt start screen
  choice = homeScreen(choice);
  switch (choice) {
    case 'S': // validate use
      userID = identifyUser(accounts, userID); 
      if (userID == "-1") {
        return 1; // exit program if invalid user
      }
      break;
    case 'Q': // quit program
      cout << "Quiting program" << endl;
      return 0;
    default: // exit program if invalid choice
      cout << "Invalid choice" << endl;
      return 1;
  }

  // verify admin access
  bool adminAccess = false; // no admin access
  if (userID == admin[0]) { //
    adminAccess = true;
  }

  // * start admin access
  int index, size, newSize;
  while (adminAccess) {
    if (choice == 'X') { 
      break; // end admin access
    }

    // choose and make admin function
    choice = adminScreen(choice);
    switch (choice) {
      case 'V':
        showDetails(accounts);
        choice = 'S';
        break;
      case 'A':
        // get size and new size of accounts
        size = getSize(accounts);
        newSize = size++;

        // add new customer
        accounts[newSize][0] = addCustomer("Account Number");
        accounts[newSize][1] = addCustomer("Name");
        accounts[newSize][2] = addCustomer("Balance");
        accounts[newSize][3] = addCustomer("Pin");

        choice = 'S';
        break;
      case 'E':
        index = selectCustomer(accounts);
        accounts[index][1] = changeDetail(accounts[index][1], "Name");
        accounts[index][2] = changeDetail(accounts[index][1], "Balance");
        choice = 'S';
        break;
      case 'C':
        index = selectCustomer(accounts);
        accounts[index][3] = changePin(accounts[index][3]);
        choice = 'S';
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
  }

  // if userID is admin's then admin is finished 
  // if choice is X then the user is finished
  if (userID == admin[0] or choice == 'X') {
    return 0; 
  }

  // * start customer transaction
  index = findIndex(accounts, userID); // get index of user in accounts
  for (;;) {
    // get/update customer data  
    string acctNum = accounts[index][0]; // account number
    string acctName = accounts[index][1]; // account name
    string balance = accounts[index][2]; // account balance

    if (choice == 'X') {
      break; // break from loop if user is finished
    }

    // choose and make type of transaction
    choice = transactionScreen(choice);
    switch (choice) {
      case 'B': // check balance
        balanceScreen(acctNum, acctName, balance);
        choice = 'X'; 
        break;
      case 'W': // withdraw
        accounts[index][2] = transactions(balance, "withdraw");
        choice = 'S';
        break;
      case 'D': // deposit
        // data = depositScreen(balance);
        accounts[index][2] = transactions(balance, "deposit");
        choice = 'S';
        break;
      case 'C': // cancel transaction
        cout << "Canceling transaction" << endl;
        choice = 'X';
        break;
      default: // invalid, exit program
        cout << "Invalid choice" << endl;
        choice = 'X';
        break;
    }
  }

  return 0;
}


// output #1
char homeScreen(char choice) {
  // initialize available options and number of options
  char options[2] = {'S', 'Q'};
  int size = sizeof(options)/sizeof(options[0]);

  // screen contents
  string text[3] = {
    "S -> Start Transaction",
    "Q -> Quit",
    "Enter your choice: _____" 
  };
  
  printUI(text, sizeof(text)/sizeof(text[0]));

  // get, validate, and return choice
  choice = validateChoice(choice, options, size);
  return choice;
}


// output #2
string identifyUser(string accounts[][4], string userID) {
  // initialize user input and available attempts
  string userNum, acctPin;
  int attempts = 3;

  // get array size
  int size = 0;
  for (int i = 0; ; i++) {
    if (accounts[i][0].empty()) {
      break;
    }
    size++;
  }

  // screen contents
  string textNum[2] = {
    "Please enter your account number to start:",
    "__________"
  };

  printUI(textNum, sizeof(textNum)/sizeof(textNum[0]));

  // get and validate user input
  userNum = validateUser("Account Number", userNum, accounts, attempts, size, 0);
  if (userNum == "-1") {
    cout << "Invalid account number. Try again." << endl;
    return "-1";
  }

  // screen contents
  string textPin[2] = {
    "Enter your pin number:",
    "__________"
  };

  printUI(textPin, sizeof(textPin)/sizeof(textPin[0]));

  // get and validate user input
  if (userNum == "0") {
    acctPin = validateAdmin("Pin", acctPin, admin, attempts, 3);
    userNum = admin[0];
  } else {
    acctPin = validateUser("Pin", acctPin, accounts, attempts, size, 3);
  }

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
void balanceScreen(string acctNum, string acctName, string balance) {
  // exit option
  char options[4] = {'X'};
  int size = sizeof(options)/sizeof(options[0]);

  // print balance
  string text[] = {
    "Account #: " + acctNum,  
    "Account Name: " + acctName,  
    "Balance: " + balance,  
    " ",
    "Press X to Exit."
  };

  // print screen contents
  printUI(text, sizeof(text)/sizeof(text[0]));

  // get and validate and exit
  char choice = validateChoice(choice, options, size);
}


// output #4 (withdrawal and deposit)
string transactions(string balance, string type) {
  // initialize transaction amount and copy of balance
  string transactionAmt;
  double balanceCopy = stod(balance);

  // screen contents
  string text[4] = {
    "Enter amount to be " + type,  
    "__________",  
    " ",  
    "Press X to Exit."
  };

  printUI(text, sizeof(text)/sizeof(text[0]));

  // get and validate input and make transaction
    while (true) {
    cout << "Amount: ";
    cin >> transactionAmt;

    // check if the input is 'X'
    if (toupper(transactionAmt[0]) == 'X' && transactionAmt.length() == 1) {
        return "S";
    }

    // check if the input is a valid number
    bool valid = true;
    for (int i = 0; i < transactionAmt.length(); ++i) {
      if (!isdigit(transactionAmt[i])) {
        valid = false; // input is not a number
        break;
      }
    }

    // check if input is only composed of 100, 500, and 1000 bills
    if (valid) {
      valid = checkAmt(transactionAmt, valid);
    }

    // process transaction
    if (valid) {
      try {

        double amount = stod(transactionAmt); // convert string into numeric
        if (type == "withdraw") { // make withdrawal
          if (amount > balanceCopy) { // check if withdrawal amount is greater than balance
            cout << "Invalid transaction type." << endl;
          } else {
            balanceCopy -= amount;
          }
        } else if (type == "deposit") { // make deposit
          balanceCopy += amount;
        } else { // invalid transaction type, return balance as is
          return balance;
        }

          // update balance and return
          balance = to_string(balanceCopy);
          cout << "Transaction successful." << endl; 
          return balance;
      } catch (const invalid_argument &e) { // invalid input
        cout << "Invalid input. Please enter a valid amount." << endl;
      } catch (const out_of_range &e) { // invalid input
        cout << "Invalid input. Please enter a valid amount." << endl;
      }
    } else { // invalid input
      cout << "Invalid input. Please enter a valid amount or 'X' to exit." << endl;
    }

    // clear input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}