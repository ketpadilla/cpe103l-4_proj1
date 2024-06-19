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
#include "includes/printUI.h"
using namespace std;


// prototype functions
char homeScreen(char choice);
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
  choice = homeScreen(choice);

  // ! TO BE IMPLEMENTED
  switch (choice) {
    case 'S':
      userID = identifyUser(accounts, userID, admin);
      break;
    case 'Q':
      cout << "Quit" << endl;
      break;
    default:
      cout << "Invalid choice" << endl;
      break;
  }

  return 0;
}


// * function definitions
// output #1
char homeScreen(char choice) {
  char options[2] = {'S', 'Q'};
  string text[3] = {
    "S -> Start Transaction",
    "Q -> Quit",
    "Enter your choice: _____" 
  };

  // print screen contents
  printUI(text, sizeof(text)/sizeof(text[0]));

  // get user choice
  cout << "Choice: ";
  cin >> choice;

  // validate user input
  // ! TO IMPLEMENT: user input validation

  // return user choice
  return choice;
}


// output #2
string identifyUser(string accounts[5][4], string userID, string admin[4]) {
  string userNum, acctPin;
  int index;
  char choice;
  string text[2] = {
    "Enter your pin number:",
    "__________"
  };

  // print screen contents
  printUI(text, sizeof(text)/sizeof(text[0]));

  // get acct pin
  cout << "Pin: ";
  cin >> acctPin;

  // ! TO BE IMPLEMENTED
  return "To be implemented...";
}

// ! TO BE IMPLEMENTED


