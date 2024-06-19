// header files and namespace
#include <iostream>
#include <string>
#include <cmath>
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

  // if input is invalid, prompt again
  cout << "Invalid input" << endl;
  return validateChoice(choice, options, size);
}


// validate user data
string validateUser(string text, string input, string accounts[5][4], int attempts, int size, int index) {
  if (attempts == 3) {
    return "-1";
  };

  cout << text << ": ";
  cin >> input;

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
    return input;
  } else {
    cout << "Invalid input" << endl;
    attempts++;
    return validateUser(text, input, accounts, attempts, size, index);
  }
}