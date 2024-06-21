#include <iostream>
using namespace std;

bool checkAmt(double amount, bool valid) {
  int notes[] = {1000, 500, 100};
  int noteCount[3] = {0, 0, 0};

  for (int i = 0; i < 3; i++) {
      while (amount >= notes[i]) {
          noteCount[i]++;
          amount -= notes[i];
      }
  }

  cout << "Number of 1000 bills: " << noteCount[0] << endl;
  cout << "Number of 500 bills: " << noteCount[1] << endl;
  cout << "Number of 100 bills: " << noteCount[2] << endl;

  if (amount != 0) {
      cout << "Amount cannot be dispensed." << endl;
      valid = false;
  }
  
  return valid;
}


int main() {
  double amount = 11800;
  bool valid = true;

  valid = checkAmt(amount, valid);

  cout << valid << endl;
}